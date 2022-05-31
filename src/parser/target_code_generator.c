#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <stdlib.h>

#include "target_code_generator.h"
#include "quads.h"
#include "utils.h"
#include "vmalpha.h"

#define INSTRUCTION_SIZE 16

/*
 *  TODO List:
 *  generate_GERTETVAL
 *  gemetate_RET
 *  generate_JUMP
 *  emit_tcode
 *  push in a stack ijhead when on funcenter, and restore it when on funcexit
 * 
*/

int target_code_file;
uint current_pquad;

struct incomplete_jump *ijhead;
uint totalij;  //used?

void add_incomplete_jump(uint instrNo, uint iaddress)
{
    struct incomplete_jump newij;
    newij.iaddress = iaddress;
    newij.instrNo = instrNo;
    
    struct incomplete_jump *itter = ijhead;

    while(itter)
        itter = itter->next;
    
    itter->next = &newij;
}

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

int init_tcode_file(){
    int filefd=0;
    if(!(filefd = open("target_code.txt", O_CREAT | O_TRUNC | O_WRONLY, 777))){
        print_static_analysis_error(0,"Error oppening target code file! \nExiting...\n");
        return 0;
    }
    return filefd;
}

void patch_ijs(){
    struct incomplete_jump *itter;
    while (itter){
        assert(itter->iaddress!=0);
        if(itter->iaddress==currQuad)
            instructions[itter->instrNo].res_label = currInstr; //is currInstr at the end of the tcode?
        else
            instructions[itter->instrNo].res_label = quads[itter->iaddress].taddres; 
    }
}

void generate(void){
    target_code_file = init_tcode_file();
    for(uint i=0;i<currQuad;i++){
        current_pquad++;
        (*generators[quads[i].op])(quads+i);
    }
}

void make_operand(struct expr* expr, struct vmarg* arg){
    if(!expr){
        arg=NULL;
        return;
    }
    switch(expr->type){
        case var_e:
        case tableitem_e:
        case boolexpr_e: //Not used?
        case newtable_e:{

            arg->val = expr->sym->offset;

            switch (expr->sym->space){
            case GLOBAL:    arg->type = global_a; break;
            case LOCAL:     arg->type = local_a; break;
            case FORMAL:    arg->type = formal_a; break;
            default:
                assert(0);
            }
            break;
        }
        case constbool_e:
            arg->type = bool_a;
            arg->val  = expr->boolConst;
            break;

        case conststring_e:
            arg->type = string_a;
            arg->val  = consts_newstring(expr->strConst);
            break;

        case constnum_e:
            arg->type = number_a;
            arg->val  = consts_newnum(expr->numConst);
            break;

        case nil_e:
            arg->type = nil_a;
            break;

        case programfunc_e:
            arg->type = userfunc_a;
            // TODO: arg->val  = expr->sym->taddress;
            break;

        case libraryfunc_e:
            arg->type = libfunc_a;
            arg->val  = libfuncs_newused(expr->sym->name);
            break;

        default: assert(0);        
    }
}

void expand_instr_table(void)
{
    instructions = realloc(instructions, NEW_INSTR_SIZE);
    totalinstr += INSTRUCTION_EXPAND_SIZE;
}

void emit_tcode(struct vminstruction *instr){
    if ( currInstr >= totalinstr )
        expand_instr_table();
    //write() the four fields in the target_code_file
    //the three vmarg* can be null (in this case write 4bytes of 0s)
}

void generate_op(enum vmopcode opcode, struct quad *quad){
    quad->taddres=currInstr;

    struct vminstruction instr;
    instr.opcode        = opcode;
    make_operand(quad->result,instr.res_label);
    make_operand(quad->arg1,instr.arg1);
    make_operand(quad->arg2,instr.arg2);

    emit_tcode(&instr);
}

void generate_relational(enum vmopcode opcode, struct quad *quad){
    quad->taddres=currInstr;

    struct vminstruction instr;
    instr.opcode        = opcode;
    make_operand(quad->arg1,instr.arg1);
    make_operand(quad->arg2,instr.arg2);

    instructions->res_label->type = label_a;
    if(quad->label<current_pquad){
        instructions->res_label = quads[quad->label].taddres;
    }else{
        add_incomplete_jump(currInstr,quad->label);
    }

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

void generate_CALL(struct quad* quad){
    quad->taddres=currInstr;

    struct vminstruction instr;
    instr.opcode        = call_v;
    instr.res_label     = NULL;
    make_operand(quad->arg1,instr.arg1);
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_PARAM(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstruction instr;
    instr.opcode        = pusharg_v;
    instr.res_label     = NULL;
    make_operand(quad->arg1,instr.arg1);
    instr.arg2          = NULL;
    emit_tcode(&instr);
}
    // TODO: make_retvaloperand(instr.arg1);

void generate_RET(struct quad* quad){
    quad->taddres=currInstr;
    struct vmarg *vmarg1;
    make_operand(quad->arg1,vmarg1);
    
    // TODO: emit an incomplete jump to the end of the function
    struct vminstruction instr;
    // instr.opcode        = ;
    // instr.res_label     = res_vmarg;
    // instr.arg1          = vmarg1;
    // instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_GETRETVAL(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstruction instr;
    instr.opcode        = assign; 
    make_operand(quad->result,instr.res_label);
    // TODO: make_retvaloperand
    instr.arg2          = NULL;

    emit_tcode(&instr);
    // TODO: free
}

void generate_FUNCSTART(struct quad* quad){
    struct userfunc f;
    f.id = quad->result->sym->name;
    f.address = currInstr;
    quad->taddres=currInstr;
    


    
    struct vminstruction instr;
    instr.opcode        = funcenter_v;
    instr.res_label     = NULL;
    make_operand(quad->arg1,instr.arg1);
    instr.arg2          = NULL;

    emit_tcode(&instr);
    // TODO: free
}

void generate_FUNCEND(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstruction instr;
    instr.opcode        = funcexit_v;
    instr.res_label     = NULL;
    make_operand(quad->arg1,instr.arg1);
    instr.arg2          = NULL;

    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLECREATE(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstruction instr;
    instr.opcode        = newtable_v;
    make_operand(quad->result,instr.res_label);
    make_operand(quad->arg1,instr.arg1);
    make_operand(quad->arg2,instr.arg2);
    
    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLEGETELEM(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstruction instr;
    instr.opcode        = tablegetelem_v;
    make_operand(quad->result,instr.res_label);
    make_operand(quad->arg1,instr.arg1);
    make_operand(quad->arg2,instr.arg2);
    
    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLESETELEM(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstruction instr;
    instr.opcode        = tablesetelem_v;
    make_operand(quad->result,instr.res_label);
    make_operand(quad->arg1,instr.arg1);
    make_operand(quad->arg2,instr.arg2);

    emit_tcode(&instr);
    // TODO: free
}

void generate_JUMP(struct quad* quad){
    quad->taddres=currInstr;
    
    struct vminstruction instr;
    instr.opcode        = jump_v;
    make_operand(quad->label,instr.res_label);
    instr.arg1          = NULL;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}