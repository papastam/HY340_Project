#include <fcntl.h>
#include <unistd.h>

#include "../inc/target_code_generator.h"
#include "../inc/quads.h"
#include "../inc/utils.h"
#include "../../vm/inc/vmalpha.h"

#define INSTRUCTION_SIZE 16

/*
 *  TODO List:
 *  generate_GERTETVAL
 *  gemetate_RET
 *  generate_JUMP
 *  emit_tcode
 * 
*/

int target_code_file;

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

void generate (void){
    target_code_file = init_tcode_file();
    for(unsigned i=0;i<currQuad;i++){
        (*generators[quads[i].op])(quads+i);
    }
}

void make_operand(struct expr* expr, struct vmarg* arg){
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

void emit_tcode(struct vminstruction *instr){
    //write() the four fields in the target_code_file
    //the three vmarg* can be null (in this case write 4bytes of 0s)
}

void generate_ASSIGN(struct quad* quad){
    struct vmarg *l_vmarg;
    struct vmarg *r_vmarg;
    make_operand(quad->result,l_vmarg);
    make_operand(quad->arg1,r_vmarg);
    
    struct vminstruction instr;
    instr.opcode        = assign_v;
    instr.res_label     = l_vmarg;
    instr.arg1          = r_vmarg;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free 
}
             
void generate_ADD(struct quad* quad){
    struct vmarg *res_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->result,res_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = add_v;
    instr.res_label     = res_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}
         
void generate_SUB(struct quad* quad){
    struct vmarg *res_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->result,res_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);

    struct vminstruction instr;
    instr.opcode        = sub_v;
    instr.res_label     = res_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_MUL(struct quad* quad){
    struct vmarg *res_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->result,res_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = mul_v;
    instr.res_label     = res_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_DIV_O(struct quad* quad){
    struct vmarg *res_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->result,res_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = div_v;
    instr.res_label     = res_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_MOD(struct quad* quad){
    struct vmarg *res_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->result,res_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = mod_v;
    instr.res_label     = res_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_UMINUS(struct quad* quad){
    struct vmarg *res_vmarg;
    struct vmarg *vmarg1;
    make_operand(quad->result,res_vmarg);
    make_operand(quad->arg1,vmarg1);
    
    struct vminstruction instr;
    instr.opcode        = uminus;
    instr.res_label     = res_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_AND_O(struct quad* quad){
// NOT USED
}

void generate_OR_O(struct quad* quad){
// NOT USED
}

void generate_NOT_O(struct quad* quad){
// NOT USED
}

void generate_IF_EQ(struct quad* quad){
    struct vmarg *label_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->label,label_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = jeq_v;
    instr.res_label     = label_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_IF_NOTEQ(struct quad* quad){
    struct vmarg *label_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->label,label_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = jne_v;
    instr.res_label     = label_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_IF_LESSEQ(struct quad* quad){
    struct vmarg *label_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->label,label_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = jle_v;
    instr.res_label     = label_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_IF_GREATEREQ(struct quad* quad){
    struct vmarg *label_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->label,label_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = jge_v;
    instr.res_label     = label_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_IF_LESS(struct quad* quad){
    struct vmarg *label_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->label,label_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = jle_v;
    instr.res_label     = label_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_IF_GREATER(struct quad* quad){
    struct vmarg *label_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->label,label_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = jgt_v;
    instr.res_label     = label_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_CALL(struct quad* quad){
    struct vmarg *vmarg1;
    make_operand(quad->arg1,vmarg1);
    
    struct vminstruction instr;
    instr.opcode        = call_v;
    instr.res_label     = NULL;
    instr.arg1          = vmarg1;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_PARAM(struct quad* quad){
    struct vmarg *vmarg1;
    make_operand(quad->arg1,vmarg1);
    
    struct vminstruction instr;
    // TODO: instr.opcode        = ; ????????????????
    instr.res_label     = NULL;
    instr.arg1          = vmarg1;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_RET(struct quad* quad){
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
    struct vmarg *res_vmarg;
    make_operand(quad->result,res_vmarg);
    
    struct vminstruction instr;
    // TODO: instr.opcode        = ; ????????????
    instr.res_label     = res_vmarg;
    instr.arg1          = NULL;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_FUNCSTART(struct quad* quad){
    struct vmarg *vmarg1;
    make_operand(quad->arg1,vmarg1);
    
    struct vminstruction instr;
    instr.opcode        = funcenter_v;
    instr.res_label     = NULL;
    instr.arg1          = vmarg1;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_FUNCEND(struct quad* quad){
    struct vmarg *vmarg1;
    make_operand(quad->arg1,vmarg1);
    
    struct vminstruction instr;
    instr.opcode        = funcexit_v;
    instr.res_label     = NULL;
    instr.arg1          = vmarg1;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLECREATE(struct quad* quad){
    struct vmarg *res_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->result,res_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = funcexit_v;
    instr.res_label     = NULL;
    instr.arg1          = vmarg1;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLEGETELEM(struct quad* quad){
    struct vmarg *res_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->result,res_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = tablegetelem_v;
    instr.res_label     = res_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_TABLESETELEM(struct quad* quad){
    struct vmarg *res_vmarg;
    struct vmarg *vmarg1;
    struct vmarg *vmarg2;
    make_operand(quad->result,res_vmarg);
    make_operand(quad->arg1,vmarg1);
    make_operand(quad->arg2,vmarg2);
    
    struct vminstruction instr;
    instr.opcode        = tablesetelem_v;
    instr.res_label     = res_vmarg;
    instr.arg1          = vmarg1;
    instr.arg2          = vmarg2;
    emit_tcode(&instr);
    // TODO: free
}

void generate_JUMP(struct quad* quad){
    struct vmarg *label_vmarg;
    make_operand(quad->label,label_vmarg);
    
    struct vminstruction instr;
    instr.opcode        = jump_v;
    instr.res_label     = label_vmarg;
    instr.arg1          = NULL;
    instr.arg2          = NULL;
    emit_tcode(&instr);
    // TODO: free
}