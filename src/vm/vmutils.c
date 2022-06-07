#include "vmutils.h"
#include "alphavm.h"
#include "memory_management.h"

#include <string.h>
#include <stdarg.h>
#include <stdio.h>

unsigned totalActuals=0;

void avm_warning(int line, const char * warformat, ...)
{
    #define error_msg "\033[0;35mWarrning\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "

    va_list print_args;

    va_start(print_args, warformat);

    printf(error_msg, line);
    vprintf(warformat, print_args);

    va_end(print_args);
}

void avm_error(int line, const char * errformat, ...)
{
    #define error_msg "\033[0;31mError\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "

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
        avm_error("Stack Overflow!");
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
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top+totalActuals+2);
    avm_push_envvalue(topsp);
}

char* avm_tostring(struct avm_memcell* input){
    char* output;

    switch (innput->type){

    case number_m:
        sprintf(output,"%f", input->data.numVal);
        return output;

    case string_m:
        return strdup(input->data.strVal);

    case bool:
        sprintf(output,"%s", input->data.boolVal?"TRUE":"FALSE");
        return output;

    case userfunc_m:
        sprintf(output,"%d", input->data.funcVal);
        return output;

    case libfunc_m:
        sprintf(output,"%s", input->data.libfuncVal);
        return output;

    default: assert(0);
    }
}

void avm_callibfunc(char* funcname)