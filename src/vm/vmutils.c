#include "vmutils.h"
#include "alphavm.h"
#include "memory_management.h"

#include <string.h>
#include <stdarg.h>

void avm_warning(int line, const char * warformat, ...)
{
    #define error_msg "\033[0;35mWarrning\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "

    va_list print_args;

    va_start(print_args, warformat);

    printf(error_msg, line);
    vprintf(warformat, print_args);

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