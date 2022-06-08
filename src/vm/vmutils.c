#include "vmutils.h"
#include "alphavm.h"
#include "mman.h"
#include "exec.h"

#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define error_msg "\033[0;31mError\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "
#define warrning_msg "\033[0;35mWarrning\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "

//========== TO BOOL DISPATCHER ==========
tobool_func_t toBoolFuncs[]={
    number_tobool,
    string_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undefined_tobool
};

unsigned char avm_tobool(struct avm_memcell* input){
    assert(input->type >= 0 && input->type < undef_m);
    return (*toBoolFuncs[input->type])(input);
};

unsigned char number_tobool(struct avm_memcell* input)    {return input->data.numVal != 0;}
unsigned char string_tobool(struct avm_memcell* input)    {return input->data.strVal[0] != 0;}
unsigned char bool_tobool(struct avm_memcell* input)      {return input->data.boolVal;}
unsigned char table_tobool(struct avm_memcell* input)     {return 1;}
unsigned char userfunc_tobool(struct avm_memcell* input)  {return 1;}
unsigned char libfunc_tobool(struct avm_memcell* input)   {return 1;}
unsigned char nil_tobool(struct avm_memcell* input)       {return 0;}
unsigned char undefined_tobool(struct avm_memcell* input) {assert(0);return 0;}


//========== TO STRING DISPATCHER ==========
toString_func_t toStringFuncs[]={
    number_toString,
    string_toString,
    table_toString,
    userfunc_toString,
    libfunc_toString,
    nil_toString,
    undefined_toString
};

char* avm_toString(struct avm_memcell* input){
    assert(input->type >= 0 && input->type < undef_m);
    return (*toStringFuncs[input->type])(input);
};

char* number_toString(struct avm_memcell* input)      {char* output;sprintf(output,"%lf", input->data.numVal);return output;}
char* string_toString(struct avm_memcell* input)      {return strdup(input->data.strVal);}
char* bool_toString(struct avm_memcell* input)        {return input->data.boolVal?"TRUE":"FALSE";}
char* table_toString(struct avm_memcell* input)       {char* output;return output;} //TODO
char* userfunc_toString(struct avm_memcell* input)    {return "TODO";}
char* libfunc_toString(struct avm_memcell* input)     {return "TODO";}
char* nil_toString(struct avm_memcell* input)         {return "NIL";}
char* undefined_toString(struct avm_memcell* input)   {return "UNDEFINED";}


void avm_warning(int line, const char * warformat, ...)
{

    va_list print_args;

    va_start(print_args, warformat);

    printf(warrning_msg, line);
    vprintf(warformat, print_args);

    va_end(print_args);
}

void avm_error(int line, const char * errformat, ...)
{

    va_list print_args;

    va_start(print_args, errformat);

    printf(error_msg, line);
    vprintf(errformat, print_args);

    va_end(print_args);
}

void avm_assign(struct avm_memcell* lv,struct avm_memcell* rv){
    if(lv==rv){
        return;
    }

    if(lv->type == table_m && rv->type == table_m && lv->data.tableVal == rv->data.tableVal){
        return;
    }
    
    if(rv->type ==undef_m){
        avm_warning(0,"assignment from undefined variable!");
    }

    avm_memcellclear(lv);
    memcpy(lv,rv,sizeof(struct avm_memcell));

    if(lv->type == string_m){
        lv->data.strVal = strdup(rv->data.strVal);
    }else if(lv->type == table_m){
        avm_tableincrefcounter(lv->data.tableVal);
    }
} 


void avm_dec_top(void){
    if(!top){
        avm_error(0,"Stack Overflow!");
        execution_finished = 1;
    }else{
        --top;
    }
    
}

void avm_push_envvalue(unsigned val){
    stack[top].type         = number_m;
    stack[top].data.numVal  = val;
    avm_dec_top();
}

void avm_callsaveeenvironment(void){
    avm_push_envvalue(avm_getTotalActuals());
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top+avm_getTotalActuals()+2);
    avm_push_envvalue(topsp);
}

unsigned avm_getTotalActuals(){
    return totalActuals;
}

struct avm_memcell * avm_getActual(unsigned i) {
    assert(i < avm_getTotalActuals);
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
} 


double consts_getnumber(uint index){/*TODO*/ return 0;}
char* consts_getstr(uint index){/*TODO*/ return NULL;}
double consts_getlibfunc(uint index){/*TODO*/ return 0;}

void avm_callibfunc(char* funcname){/*TODO*/}