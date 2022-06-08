#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "target_code_generator.h"
#include "utils.h"
#include "alphavm.h"

#define INSTRUCTION_SIZE 16
#define BIN_ARG_OFF_MASK  0x0FFFFFFF

/*  TODO List:
 *  generate_GERTETVAL
 *  gemetate_RET
 *  generate_JUMP
 *  emit_tcode
 *  push in a stack ijhead when on funcenter, and restore it when on funcexit
 * 
 *  P3 TESTFILES:
 *  backpatch0              > WORKING
 *  backpatch1              > SEG
 *  backpatch2              > SEG
 *  backpatch3              > SEG
 * 
*/

int target_code_file;
uint current_pquad;

struct incomplete_jump * ijhead = NULL;
uint totalij;  //used?

struct vminstr * instructions;
uint totalinstr;
uint currInstr=1;

uint numTableSize   =0;
uint strTableSize   =0;
uint userfTableSize =0;
uint libfTableSize  =0;

__const_array_t     carr;
__string_array_t    sarr;
__libfunc_array_t   lfarr;
__userfunc_array_t  ufarr;

// uint totalNumConsts;
// uint totalStringConsts;
// uint totalNamedLibfuncs;
// uint totalUserFuncs;

generator_func_t generators[] = {
    generate_ASSIGN,
    generate_ADD,
    generate_SUB,
    generate_MUL,
    generate_DIV_O,
    generate_MOD,
    generate_UMINUS,
    generate_AND_O,
    generate_OR_O,
    generate_NOT_O,
    generate_IF_EQ,
    generate_IF_NOTEQ,
    generate_IF_LESSEQ,
    generate_IF_GREATEREQ,
    generate_IF_LESS,
    generate_IF_GREATER,
    generate_CALL,
    generate_PARAM,
    generate_RET,
    generate_GETRETVAL,
    generate_FUNCSTART,
    generate_FUNCEND,
    generate_TABLECREATE,
    generate_TABLEGETELEM,
    generate_TABLESETELEM,
    generate_JUMP
};

int consts_newstring(char* input){
    if(!strTableSize){
        strTableSize = CONSTANT_T_INIT_SIZE;
        sarr.array = malloc(CONSTANT_T_INIT_SIZE*sizeof(char*));
        sarr.size = 0;
    }else if(sarr.size >= strTableSize){
        strTableSize += CONSTANT_T_INIT_SIZE;
        sarr.array = realloc(sarr.array,strTableSize*sizeof(char*));
    }
    
    int i=0;
    for(i=0;i<sarr.size;++i){
        if(!(strcmp(sarr.array[i],input))){
            return i;
        }
    }

    sarr.array[sarr.size] = strdup(input);
    ++sarr.size;
    return sarr.size - 1;
}

int consts_newnum(double input){
    if(!numTableSize){
        numTableSize = CONSTANT_T_INIT_SIZE;
        carr.array = malloc(numTableSize*sizeof(double));
        carr.size = 0;
    }else if(carr.size >= numTableSize){
        numTableSize += CONSTANT_T_INIT_SIZE;
        carr.array = realloc(carr.array,numTableSize*sizeof(double));
    }

    int i=0;
    for(i=0;i<carr.size;++i){
        if(carr.array[i]==input){
            return i-1;
        }
    }

    carr.array[carr.size] = input;
    ++carr.size;
    return carr.size - 1;
}

int libfuncs_newused(const char* input){
    if(!libfTableSize){
        libfTableSize = CONSTANT_T_INIT_SIZE;
        lfarr.array = malloc(libfTableSize*sizeof(char*));
    }else if(lfarr.size >= libfTableSize){
        libfTableSize += CONSTANT_T_INIT_SIZE;
        lfarr.array = realloc(lfarr.array,libfTableSize*sizeof(char*));
    }

    int i=0;
    for(i=0;i<lfarr.size;++i){
        if(!(strcmp(lfarr.array[i],input))){
            return i;
        }
    }

    lfarr.array[lfarr.size] = strdup(input);
    ++lfarr.size;
    return lfarr.size - 1;
}

int userfuncs_newused(struct userfunc* input){
    if(!userfTableSize){
        userfTableSize = CONSTANT_T_INIT_SIZE;
        ufarr.array = malloc(userfTableSize*sizeof(struct userfunc));
    }else if(ufarr.size >= userfTableSize){
        userfTableSize += CONSTANT_T_INIT_SIZE;
        ufarr.array = realloc(ufarr.array,userfTableSize*sizeof(struct userfunc));
    }

    int i=0;
    for(i=0;i<ufarr.size;++i){
        if(!(strcmp(ufarr.array[i].id,input->id))){
            return i;
        }
    }

    memcpy(&ufarr.array[ufarr.size],input,sizeof(struct userfunc));
    ufarr.array[ufarr.size].id = strdup(input->id);
    ++ufarr.size;
    return ufarr.size - 1;
}

void add_incomplete_jump(uint instrNo, uint iaddress)
{
    struct incomplete_jump * newij;


    if ( !(newij = malloc(sizeof(*newij))) )
    {
        perror("malloc()");
        exit(EXIT_FAILURE);
    }

    newij->iaddress = iaddress;
    newij->instrNo = instrNo;
    newij->next = NULL;
    
    if ( !ijhead )
    {
        if ( !(ijhead = malloc(sizeof(*ijhead))) )
        {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }

        ijhead->iaddress = iaddress;
        ijhead->instrNo = instrNo;
        ijhead->next = NULL;

        return;
    }

    struct incomplete_jump * itter = ijhead;

    while ( itter->next != NULL )
        itter = itter->next;
    
    itter->next = newij;
}

int init_tcode_file(void)
{
    int filefd;

    if( (filefd = open("target_code.txt", O_CREAT | O_TRUNC | O_WRONLY, 0664)) < 0 )
    {
        printf("Error oppening target code file! \nExiting...\n");
        exit(EXIT_FAILURE);
    }

    return filefd;
}

void patch_ijs(void)
{
    struct incomplete_jump * itter = ijhead;

    while ( itter )
    {
        assert( itter->iaddress );

        if ( itter->iaddress == currQuad )
            instructions[itter->instrNo].result->val = currInstr; //is currInstr at the end of the tcode? probably
        else
            instructions[itter->instrNo].result->val = quads[itter->iaddress].taddress; 

        itter = itter->next;
    }
}

void generate(void)
{
    target_code_file = init_tcode_file();

    // uint i;

    for (uint i = 1U; i < currQuad; ++i)
    {
        ++current_pquad;
        (*generators[quads[i].op])(quads + i);
    }
    patch_ijs();
}

void make_operand(struct expr * restrict expr, struct vmarg * restrict * restrict arg)
{
    if ( !expr )
    {
        *arg=NULL;
        return;
    }

    switch  ( expr->type )
    {
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e: //Not used?
        case newtable_e:

            (*arg)->val = expr->sym->offset;

            switch ( expr->sym->type )
            {
                case GLOBAL:

                    (*arg)->type = global_a;
                    break;

                case LOCAL:
                    (*arg)->type = local_a;
                    break;

                case FORMAL:

                    (*arg)->type = formal_a;
                    break;

                default:
                    assert(0);
            }

            break;

        case constbool_e:

            (*arg)->type = bool_a;
            (*arg)->val  = expr->boolConst;

            break;

        case conststring_e:

            (*arg)->type = string_a;
            (*arg)->val  = consts_newstring(expr->strConst);

            break;

        case constnum_e:

            (*arg)->type = number_a;
            (*arg)->val  = consts_newnum(expr->numConst);

            break;

        case nil_e:

            (*arg)->type = nil_a;
            break;

        case programfunc_e:
            struct userfunc * f = malloc(sizeof(struct userfunc));
            
            f->id = malloc(25*sizeof(char));
            strcpy(f->id, expr->sym->name);
            f->localSize = expr->sym->farg_cnt;
            f->address = currInstr;

            (*arg)->type = userfunc_a;
            (*arg)->val = userfuncs_newused(f);
            break;

        case libraryfunc_e:

            (*arg)->type = libfunc_a;
            (*arg)->val  = libfuncs_newused(expr->sym->name);

            break;

        default:
            assert(0);        
    }
}

void expand_instr_table(void){
    instructions = realloc(instructions, NEW_INSTR_SIZE);  // see that again!
    totalinstr += 512U;
}

void emit_tcode(struct vminstr *instr){
    if ( currInstr >= totalinstr )
        expand_instr_table();

    instructions[currInstr].opcode  = instr->opcode;
    instructions[currInstr].arg1    = instr->arg1;
    instructions[currInstr].arg2    = instr->arg2;
    instructions[currInstr].result  = instr->result;
    instructions[currInstr].srcLine = instr->srcLine;

    ++currInstr;
}

void dump_binary_file(void){
    int fd = open("binaryOutput", O_CREAT | O_WRONLY, 0666);
    uint32_t arg;
    uint32_t offset;
    uint32_t op;
    // printf("total instructions: %d\n", currInstr);

    // Write magic number
    arg = ALPHA_MAGICNUM;
    write(fd, (void*) &arg, 4);

    //Write strings array

    write(fd, (void*) &sarr.size, 4); //write size of strings array

    for(uint i = 0; i < sarr.size; ++i) {
        arg = strlen(sarr.array[i]);
        write(fd, (void*) &arg, 4); //write the size of the string first
        for(uint j = 0; j < strlen(sarr.array[i]); ++j) 
            write_string(fd, sarr.array[i]);
        
    }

    //Write numbers array

    write(fd, (void*) &carr.size, 4); //write size of numbers array
    double num;
    for(uint i = 0; i < carr.size; ++i) {
        write(fd, (void*) &carr.array[i], 8); //write each number
    }

    //Write user funcs array

    write(fd, (void*) &ufarr.size, 4); // write size of user funcs array

    for(uint i = 0; i < ufarr.size; ++i) {
        write(fd, (void*) &ufarr.array[i].address, 4); // write address
        write(fd, (void*) &ufarr.array[i].localSize, 4); // write local size
        write_string(fd, ufarr.array[i].id); // write id of func
    }

    //Write used lib funcs

    write(fd, (void*) &lfarr.size, 4); //write size of lib funcs array

    for(uint i = 0; i < lfarr.size; ++i) {
        write_string(fd, lfarr.array[i]);
    }

    //Write code

    write(fd, (void*) &currInstr, 4); // write total number of instructions

    for(int i = 1; i < currInstr - 1; ++i) {
        arg = instructions[i].opcode;
        write(fd, (void*) &arg, 1);

        if(!instructions[i].result) {
            arg = VM_ARG_NULL;
            write(fd, (void*) &arg, 4);
        }
        else {
            op = instructions[i].result->type;
            offset = instructions[i].result->val;
            arg = op << 28;
            arg |= offset & BIN_ARG_OFF_MASK;
            write(fd, (void*) &arg, 4);
        }
         
        if(!instructions[i].arg1) {
            arg = VM_ARG_NULL;
            write(fd, (void*) &arg, 4);
        }
        else {
            op = instructions[i].arg1->type;
            offset = instructions[i].arg1->val;
            arg = op << 28;
            arg |= offset & BIN_ARG_OFF_MASK;
            write(fd, (void*) &arg, 4);
        }    

        if(!instructions[i].arg2) {
            arg = VM_ARG_NULL;
            write(fd, (void*) &arg, 4);
        }
        else {
            op = instructions[i].arg2->type;
            offset = instructions[i].arg2->val;
            arg = op << 28;
            arg |= offset & BIN_ARG_OFF_MASK;
            write(fd, (void*) &arg, 4);
        }
    }
    
    close(fd);
    return;
}

void write_string(int fd, char* string) {
    char c;
    uint32_t size = strlen(string);

    write(fd, (void*) &size, 4); // write size of string first

    for(uint i = 0; i < size; ++i) {
        c = *(string + i);
        write(fd, (void*) &c, 1); // write each character individually
    }
}

void generate_op(vmopcode_t opcode, struct quad * quad)
{
    struct vminstr instr;

    instr.arg1 = malloc(sizeof(struct vmarg));
    instr.arg2 = malloc(sizeof(struct vmarg));
    instr.result = malloc(sizeof(struct vmarg));
    instr.srcLine = quad->line;
    
    quad->taddress = currInstr;
    instr.opcode = opcode;

    make_operand(quad->result, &instr.result);
    make_operand(quad->arg1, &instr.arg1);
    make_operand(quad->arg2, &instr.arg2);

    emit_tcode(&instr);
}

void generate_relational(vmopcode_t opcode, struct quad * quad)
{
    struct vminstr instr;

    quad->taddress = currInstr;
    instr.opcode = opcode;
    instr.arg1 = malloc(sizeof(struct vmarg));
    instr.arg2 = malloc(sizeof(struct vmarg));
    instr.result = malloc(sizeof(struct vmarg));
    instr.srcLine = quad->line;

    make_operand(quad->arg1, &instr.arg1);
    make_operand(quad->arg2, &instr.arg2);
    

    instr.result->type = label_a;

    if ( quad->label<current_pquad )
        instr.result->val = quads[quad->label].taddress;
    else
        add_incomplete_jump(currInstr, quad->label);

    emit_tcode(&instr);
}

void generate_ASSIGN(struct quad* quad) {generate_op(assign_v,quad);}
void generate_ADD(struct quad* quad)    {generate_op(add_v,   quad);}
void generate_SUB(struct quad* quad)    {generate_op(sub_v,   quad);}
void generate_MUL(struct quad* quad)    {generate_op(mul_v,   quad);}
void generate_DIV_O(struct quad* quad)  {generate_op(div_v,   quad);}
void generate_MOD(struct quad* quad)    {generate_op(mod_v,   quad);}
void generate_UMINUS(struct quad* quad) {quad->arg2 = newexpr_constnum(-1); generate_op(mul_v,quad);}

void generate_AND_O(struct quad* quad){assert(0);}
void generate_OR_O(struct quad* quad) {assert(0);}
void generate_NOT_O(struct quad* quad){assert(0);}

void generate_IF_EQ(struct quad* quad)       {generate_relational(jeq_v,quad);}
void generate_IF_NOTEQ(struct quad* quad)    {generate_relational(jne_v,quad);}
void generate_IF_LESSEQ(struct quad* quad)   {generate_relational(jle_v,quad);}
void generate_IF_GREATEREQ(struct quad* quad){generate_relational(jge_v,quad);}
void generate_IF_LESS(struct quad* quad)     {generate_relational(jlt_v,quad);}
void generate_IF_GREATER(struct quad* quad)  {generate_relational(jgt_v,quad);}

void generate_CALL(struct quad * quad)
{
    struct vminstr instr;

    quad->taddress = currInstr;
    instr.opcode = call_v;
    instr.result = NULL;
    instr.srcLine = quad->line;

    make_operand(quad->arg1, &instr.arg1);
    instr.arg2 = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_PARAM(struct quad * quad)
{
    struct vminstr instr;

    quad->taddress = currInstr;
    instr.opcode = pusharg_v;
    instr.result = NULL;
    instr.srcLine = quad->line;

    make_operand(quad->arg1, &instr.arg1);
    instr.arg2 = NULL;

    emit_tcode(&instr);
}
// TODO: make_retvaloperand(instr.arg1);

void generate_RET(struct quad* quad){
    quad->taddress=currInstr;
    struct vmarg *vmarg1;
    make_operand(quad->arg1,&vmarg1);
    
    // TODO: emit an incomplete jump to the end of the function
    struct vminstr instr;
    instr.opcode        = assign_v;
    
    instr.result->type  = retval_a;
    instr.result->val   = 0;
    
    instr.arg1          = vmarg1;
    instr.arg2          = NULL;
    instr.srcLine = quad->line;
    emit_tcode(&instr);
    // TODO: free
}

void generate_GETRETVAL(struct quad * quad)
{
    struct vminstr instr;
    instr.result = malloc(sizeof(struct vmarg));
    
    quad->taddress = currInstr;
    instr.opcode = assign_v;

    // make_operand(quad->result, &instr.result);
    instr.result->type=retval_a;
    instr.result->val=0;

    instr.arg1 = NULL;
    instr.arg2 = NULL;
    instr.srcLine = quad->line;

    emit_tcode(&instr);
    // TODO: free
}

void generate_FUNCSTART(struct quad* quad){
    quad->taddress=currInstr;

    struct vminstr instr;
    instr.arg1=malloc(sizeof(struct vmarg));

    instr.opcode        = funcenter_v;
    instr.result     = NULL;
    make_operand(quad->arg1,&instr.arg1);
    instr.arg2          = NULL;
    instr.srcLine = quad->line;

    emit_tcode(&instr);
    // TODO: free
}

void generate_FUNCEND(struct quad* quad){
    quad->taddress=currInstr;
    
    struct vminstr instr;
    instr.opcode        = funcexit_v;
    instr.result        = NULL;
    instr.arg1          = malloc(sizeof(struct vmarg));
    make_operand(quad->arg1,&instr.arg1);
    instr.arg2          = NULL;
    instr.srcLine = quad->line;

    emit_tcode(&instr);
}

void generate_TABLECREATE(struct quad* quad){
    quad->taddress=currInstr;
    
    struct vminstr instr;
    instr.opcode        = newtable_v;
    instr.arg1          = malloc(sizeof(struct vmarg));
    instr.arg2          = malloc(sizeof(struct vmarg));
    instr.result        = malloc(sizeof(struct vmarg));
    instr.srcLine = quad->line;
    make_operand(quad->result,&instr.result);
    make_operand(quad->arg1,&instr.arg1);
    make_operand(quad->arg2,&instr.arg2);
    
    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLEGETELEM(struct quad* quad){
    quad->taddress=currInstr;
    
    struct vminstr instr;
    instr.opcode        = tablegetelem_v;
    instr.arg1          = malloc(sizeof(struct vmarg));
    instr.arg2          = malloc(sizeof(struct vmarg));
    instr.result        = malloc(sizeof(struct vmarg));
    instr.srcLine       = quad->line;
    make_operand(quad->result,&instr.result);
    make_operand(quad->arg1,&instr.arg1);
    make_operand(quad->arg2,&instr.arg2);
    
    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLESETELEM(struct quad* quad){
    quad->taddress=currInstr;
    
    struct vminstr instr;
    instr.opcode        = tablesetelem_v;
    instr.arg1          = malloc(sizeof(struct vmarg));
    instr.arg2          = malloc(sizeof(struct vmarg));
    instr.result        = malloc(sizeof(struct vmarg));
    instr.srcLine       = quad->line;
    make_operand(quad->result,&instr.result);
    make_operand(quad->arg1,&instr.arg1);
    make_operand(quad->arg2,&instr.arg2);

    emit_tcode(&instr);
    // TODO: free
}

void generate_JUMP(struct quad* quad){
    quad->arg1 = newexpr_constbool(1);
    quad->arg2 = newexpr_constbool(1);
    generate_relational(jeq_v,quad);
}