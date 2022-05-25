#include "../inc/target_code_generator.h"
#include "../inc/quads.h"
#include "../../vm/inc/vmalpha.h"


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

void generate (void){
    for(unsigned i=0;i<currQuad;i++){
        (*generators[quads[i].op])(quads+i);
    }
}

void make_oppertant(struct expr* expr, struct vmarg* arg){
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

void generate_ASSIGN(struct quad* quad){
    
}
             
void generate_ADD(struct quad* quad){

}
         
void generate_SUB(struct quad* quad){

}

void generate_MUL(struct quad* quad){

}

void generate_DIV_O(struct quad* quad){

}

void generate_MOD(struct quad* quad){

}

void generate_UMINUS(struct quad* quad){

}

void generate_AND_O(struct quad* quad){

}

void generate_OR_O(struct quad* quad){

}

void generate_NOT_O(struct quad* quad){

}

void generate_IF_EQ(struct quad* quad){

}

void generate_IF_NOTEQ(struct quad* quad){

}

void generate_IF_LESSEQ(struct quad* quad){

}

void generate_IF_GREATEREQ(struct quad* quad){

}

void generate_IF_LESS(struct quad* quad){

}

void generate_IF_GREATER(struct quad* quad){

}

void generate_CALL(struct quad* quad){

}

void generate_PARAM(struct quad* quad){

}

void generate_RET(struct quad* quad){

}

void generate_GETRETVAL(struct quad* quad){

}

void generate_FUNCSTART(struct quad* quad){

}

void generate_FUNCEND(struct quad* quad){

}

void generate_TABLECREATE(struct quad* quad){

}

void generate_TABLEGETELEM(struct quad* quad){

}

void generate_TABLESETELEM(struct quad* quad){

}

void generate_JUMP(struct quad* quad){

