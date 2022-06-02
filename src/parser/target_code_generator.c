#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "target_code_generator.h"
#include "utils.h"

#define INSTRUCTION_SIZE 16

/*  TODO List:
 *  generate_GERTETVAL
 *  gemetate_RET
 *  generate_JUMP
 *  emit_tcode
 *  push in a stack ijhead when on funcenter, and restore it when on funcexit
 * 
*/

int target_code_file;
uint current_pquad;

struct incomplete_jump * ijhead;
uint totalij;  //used?

struct vminstr * instructions;
uint totalinstr;
uint currInstr=1;

uint numTableSize   =0;
uint strTableSize   =0;
uint userfTableSize =0;
uint libfTableSize  =0;

double *            numConsts;
char **             stringConsts;
char **             namedLibfuncs;
struct userfunc *   userFuncs;

uint totalNumConsts;
uint totalStringConsts;
uint totalNamedLibfuncs;
uint totalUserFuncs;

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
        stringConsts = malloc(CONSTANT_T_INIT_SIZE*sizeof(char*));
    }else if(totalStringConsts >= strTableSize){
        strTableSize += CONSTANT_T_INIT_SIZE;
        stringConsts = realloc(stringConsts,strTableSize*sizeof(char*));
    }
    
    int i=0;
    for(i=0;i<totalStringConsts;++i){
        if(!(strcmp(stringConsts[i],input))){
            return i;
        }
    }

    if(totalStringConsts==256){printf("EROOR: STRING TABLE FILLED UP\n");exit(0);}
    stringConsts[totalStringConsts] = strdup(input);
    ++totalStringConsts;
}

int consts_newnum(double input){
    if(!numTableSize){
        numTableSize = CONSTANT_T_INIT_SIZE;
        numConsts = malloc(numTableSize*sizeof(double));
    }else if(totalNumConsts >= numTableSize){
        numTableSize += CONSTANT_T_INIT_SIZE;
        numConsts = realloc(numConsts,numTableSize*sizeof(double));
    }

    int i=0;
    for(i=0;i<totalNumConsts;++i){
        if(numConsts[i]==input){
            return i-1;
        }
    }

    if(totalNumConsts==256){printf("EROOR: STRING TABLE FILLED UP\n");exit(0);}
    numConsts[totalNumConsts] = input;
    ++totalNumConsts;
    return totalNumConsts-1;
}

int libfuncs_newused(const char* input){
    if(!libfTableSize){
        libfTableSize = CONSTANT_T_INIT_SIZE;
        namedLibfuncs = malloc(libfTableSize*sizeof(char*));
    }else if(totalNamedLibfuncs >= libfTableSize){
        libfTableSize += CONSTANT_T_INIT_SIZE;
        namedLibfuncs = realloc(namedLibfuncs,libfTableSize*sizeof(char*));
    }

    int i=0;
    for(i=0;i<totalNamedLibfuncs;++i){
        if(!(strcmp(namedLibfuncs[totalNamedLibfuncs],input))){
            return i;
        }
    }

    if(totalNamedLibfuncs==256){printf("EROOR: STRING TABLE FILLED UP\n");exit(0);}
    namedLibfuncs[totalNamedLibfuncs] = strdup(input);
    ++totalNamedLibfuncs;
}

int userfuncs_newused(struct userfunc* input){
    if(!userfTableSize){
        userfTableSize = CONSTANT_T_INIT_SIZE;
        userFuncs = malloc(userfTableSize*sizeof(struct userfunc));
    }else if(totalUserFuncs >= userfTableSize){
        userfTableSize += CONSTANT_T_INIT_SIZE;
        userFuncs = realloc(userFuncs,userfTableSize*sizeof(struct userfunc));
    }

    int i=0;
    for(i=0;i<totalUserFuncs;++i){
        if(!(strcmp(userFuncs[totalUserFuncs].id,input->id))){
            return i;
        }
    }

    if(totalUserFuncs==256){printf("EROOR: STRING TABLE FILLED UP\n");exit(0);}
    memcpy(&userFuncs[totalUserFuncs],input,sizeof(struct userfunc));
    userFuncs[totalUserFuncs].id = strdup(input->id);
    ++totalUserFuncs;
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
    
    if ( !ijhead )
    {
        if ( !(ijhead = malloc(sizeof(*ijhead))) )
        {
            perror("malloc()");
            exit(EXIT_FAILURE);
        }

        ijhead->iaddress = iaddress;
        ijhead->instrNo = instrNo;

        return;
    }

    struct incomplete_jump * itter = ijhead;

    while ( itter->next )
        itter = itter->next;
    
    itter->next = newij;
}

int init_tcode_file(void)
{
    int filefd;

    if( (filefd = open("target_code.txt", O_CREAT | O_TRUNC | O_WRONLY, 0664)) < 0 )
    {
        print_static_analysis_error(0, "Error oppening target code file! \nExiting...\n");
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
            instructions[itter->instrNo].result->val = currInstr; //is currInstr at the end of the tcode?
        else
            instructions[itter->instrNo].result->val = quads[itter->iaddress].taddres; 

        itter = itter->next;
    }
}

void generate(void)
{
    target_code_file = init_tcode_file();

    for (uint i = 1U; i < currQuad; ++i)
    {
        ++current_pquad;
        (*generators[quads[i].op])(quads + i);
    }
}

void make_operand(struct expr * restrict expr, struct vmarg * restrict * restrict arg)
{
    if ( !expr )
    {
        *arg=NULL;
        return;
    }

    switch  (expr->type )
    {
        case var_e:
        case tableitem_e:
        case arithexpr_e:
        case boolexpr_e: //Not used?
        case newtable_e:

            (*arg)->val =0;
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

            (*arg)->type = userfunc_a;
            // TODO: arg->val = expr->sym->taddress;
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
    instructions[currInstr].srcLine  = instr->srcLine;

    ++currInstr;
}

void dump_binary_file(void){
    return;
}

void generate_op(vmopcode_t opcode, struct quad * quad)
{
    struct vminstr instr;

    instr.arg1 = malloc(sizeof(struct vmarg));
    instr.arg2 = malloc(sizeof(struct vmarg));
    instr.result = malloc(sizeof(struct vmarg));

    quad->taddres = currInstr;
    instr.opcode = opcode;

    make_operand(quad->result, &instr.result);
    make_operand(quad->arg1, &instr.arg1);
    make_operand(quad->arg2, &instr.arg2);

    emit_tcode(&instr);
}

void generate_relational(vmopcode_t opcode, struct quad * quad)
{
    struct vminstr instr;

    quad->taddres = currInstr;
    instr.opcode = opcode;

    make_operand(quad->arg1, &instr.arg1);
    make_operand(quad->arg2, &instr.arg2);

    instructions->result->type = label_a;

    if ( quad->label<current_pquad )
        instructions->result->val = quads[quad->label].taddres;
    else
        add_incomplete_jump(currInstr, quad->label);

    emit_tcode(&instr);
}

void generate_ASSIGN(struct quad* quad){generate_op(assign_v,quad);}
void generate_ADD(struct quad* quad){generate_op(add_v,quad);}
void generate_SUB(struct quad* quad){generate_op(sub_v,quad);}
void generate_MUL(struct quad* quad){generate_op(mul_v,quad);}
void generate_DIV_O(struct quad* quad){generate_op(div_v,quad);}
void generate_MOD(struct quad* quad){generate_op(mod_v,quad);}
void generate_UMINUS(struct quad* quad){generate_op(uminus_v,quad);}

void generate_AND_O(struct quad* quad){
// NOT USED
}

void generate_OR_O(struct quad* quad){
// NOT USED
}

void generate_NOT_O(struct quad* quad){
// NOT USED
}

void generate_IF_EQ(struct quad* quad){generate_relational(jeq_v,quad);}
void generate_IF_NOTEQ(struct quad* quad){generate_relational(jne_v,quad);}
void generate_IF_LESSEQ(struct quad* quad){generate_relational(jle_v,quad);}
void generate_IF_GREATEREQ(struct quad* quad){generate_relational(jge_v,quad);}
void generate_IF_LESS(struct quad* quad){generate_relational(jlt_v,quad);}
void generate_IF_GREATER(struct quad* quad){generate_relational(jgt_v,quad);}

void generate_CALL(struct quad * quad)
{
    struct vminstr instr;

    quad->taddres = currInstr;
    instr.opcode = call_v;
    instr.result = NULL;

    make_operand(quad->arg1, &instr.arg1);
    instr.arg2 = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_PARAM(struct quad * quad)
{
    struct vminstr instr;

    quad->taddres = currInstr;
    instr.opcode = pusharg_v;
    instr.result = NULL;

    make_operand(quad->arg1, &instr.arg1);
    instr.arg2 = NULL;

    emit_tcode(&instr);
}
// TODO: make_retvaloperand(instr.arg1);

void generate_RET(struct quad* quad){
    quad->taddres=currInstr;
    struct vmarg *vmarg1;
    make_operand(quad->arg1,&vmarg1);
    
    // TODO: emit an incomplete jump to the end of the function
    struct vminstr instr;
    // instr.opcode        = ;
    // instr.result     = res_vmarg;
    // instr.arg1          = vmarg1;
    // instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_GETRETVAL(struct quad * quad)
{
    struct vminstr instr;
    
    quad->taddres = currInstr;
    instr.opcode = assign_v;

    make_operand(quad->result, &instr.result);
    // TODO: make_retvaloperand
    instr.arg2 = NULL;

    emit_tcode(&instr);
    // TODO: free
}

void generate_FUNCSTART(struct quad* quad){
    struct userfunc* f = malloc(sizeof(struct userfunc));
    strcpy(f->id, quad->arg1->sym->name);
    f->address = currInstr;
    quad->taddres=currInstr;

    userfuncs_newused(f);
    
    struct vminstr instr;
    instr.opcode        = funcenter_v;
    instr.result     = NULL;
    make_operand(quad->arg1,&instr.arg1);
    instr.arg2          = NULL;

    emit_tcode(&instr);
    // TODO: free
}

void generate_FUNCEND(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstr instr;
    instr.opcode        = funcexit_v;
    instr.result     = NULL;
    make_operand(quad->arg1,&instr.arg1);
    instr.arg2          = NULL;

    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLECREATE(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstr instr;
    instr.opcode        = newtable_v;
    make_operand(quad->result,&instr.result);
    make_operand(quad->arg1,&instr.arg1);
    make_operand(quad->arg2,&instr.arg2);
    
    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLEGETELEM(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstr instr;
    instr.opcode        = tablegetelem_v;
    make_operand(quad->result,&instr.result);
    make_operand(quad->arg1,&instr.arg1);
    make_operand(quad->arg2,&instr.arg2);
    
    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLESETELEM(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstr instr;
    instr.opcode        = tablesetelem_v;
    make_operand(quad->result,&instr.result);
    make_operand(quad->arg1,&instr.arg1);
    make_operand(quad->arg2,&instr.arg2);

    emit_tcode(&instr);
    // TODO: free
}

void generate_JUMP(struct quad* quad){
    generate_relational(jump_v,quad);
}