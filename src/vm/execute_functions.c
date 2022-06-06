#include "execute_functions.h"

execute_func_t executeFuncs[]={
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    execute_uminus,
    execute_and,
    execute_or,
    execute_not,
    execute_jeq,
    execute_jne,
    execute_jle,
    execute_jge,
    execute_jlt,
    execute_jgt,
    execute_call,
    execute_pusharg,
    execute_funcenter,
    execute_funcend,
    execute_newtable,
    execute_tablegetelem,
    execute_tablesetelem,
    execute_nop
}