#include "mman.h"
#include "exec.h"
#include "vmutils.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

struct avm_memcell stack[AVM_STACKSIZE];

static void avm_initstack(void)
{
    memset(stack, 0, AVM_STACKSIZE * sizeof(*stack));
}

void avm_memcellclear(struct avm_memcell* input){
    if(input->type != undef_m){
        memclear_func_t f = memclearFuncs[input->type];
        if(f){
            (*f)(input);
        }
        input->type = undef_m;
    }
}

void memclear_string(struct avm_memcell * input){
    assert(input);
    free(input->data.strVal);
}

void memclear_table(struct avm_memcell* input){
    assert(input);
    avm_tabledecrefcounter(input->data.tableVal);
}


void avm_tabledecrefcounter(struct avm_table* input){

}

void avm_tableincrefcounter(struct avm_table* input){

}

struct avm_memcell * avm_translate_operand(struct vmarg * arg, struct avm_memcell* reg){
    switch (arg->type)
    {
    case global_a:  return &stack[AVM_STACKSIZE - 1U - arg->val];
    case local_a:   return &stack[topsp - arg->val];
    case formal_a:  return &stack[topsp + AVM_STACKENV_SIZE + 1U + arg->val];

    case retval_a:  return &retval;

    case number_a:{
        reg->type = number_m;
        reg->data.numVal = consts_getnumber(arg->val);
        return reg;
    }
    
    case string_a:{
        reg->type = string_m;
        reg->data.strVal = strdup(consts_getstr(arg->val));
        return reg;
    }
    
    case bool_a:
        reg->type = bool_m;
        reg->data.boolVal = arg->val;
        return reg;

    case nil_a:

        reg->type = nil_m;
        return reg;

    case userfunc_a:
        reg->type = userfunc_m;
        reg->data.funcVal = arg->val;
        return reg;

    case libfunc_a:{
        reg->type = libfunc_m;
        // reg->libfuncVal = consts_getlibfunc(arg->val);
        return reg;
    }

    default:
        assert(0);
    }
}

