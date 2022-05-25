#include "target_code_generator.h"
#include "quads.h"

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