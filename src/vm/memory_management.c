#include "memory_management.h"
#include "alphav.h"

#include <string.h>
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

struct avm_memcell* translate_operand(struct vmarg* arg, struct avm_memcell* reg){
    switch (arg->type)
    {
    case global_a:  return &stack[AVM_STACKSIZE-1-arg->val];
    case local_a:   return &stack[topsp-arg->val];
    case formal_a:  return &stack[topsp+AVM_STACKENV_SIZE+1+arg->val];

    case retval_a:  return &retval;

    case number_a:{
        reg->type = number_m;
        reg->data.numVal = consts_getnum(arg->val);
        return reg;
    }
    
    case string_a:{
        reg->type = string_m;
        reg->data.strVal = strdup(consts_getstr(arg->val));
        return reg;
    }
    
    case bool_a:{
        reg->type = bool_m;
        reg->data.boolVal = arg->val;
        return reg;
    }

    case nil_e: reg->type = nil_m; return reg;

    case userfunc_e:{
        reg->type = userfunc_m;
        reg->data.funcVal = arg->val;
        return reg;
    }

    case libfunc_e:{
        reg->type = libfunc_m;
        reg->data.libfuncVal = consts_getlibfunc(arg->val);
        return reg;
    }

    default:
        assert(0);
    }
}