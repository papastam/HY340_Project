#include "memory_management.h"
//implements the memory management defined in lecture 13


void avm_memcellclear(struct avm_memcell* input){
    if(input->type != undef_m){
        memclear_func_t f = memclearFuncs[input->type];
        if(f){
            (*f)(input);
        }
        input->type = undef_m;
    }
}

void memclear_string(struct avm_memcell* input){
    assert(input->data.strVal);
    free(input->data.strVal);
}

void memclear_table(struct avm_memcell* input){
    assert(input->data.tableVal);
    avm_tabledecrefcounter(input->data.tableVal);
}