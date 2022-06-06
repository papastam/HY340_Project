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
};

void execute_assign(struct vminstr* input){

}

void execute_add(struct vminstr* input){

}

void execute_sub(struct vminstr* input){

}

void execute_mul(struct vminstr* input){

}

void execute_div(struct vminstr* input){

}

void execute_mod(struct vminstr* input){

}

// DEPRECATED \/ \/.
void execute_uminus(struct vminstr* input){

}

void execute_and(struct vminstr* input){

}

void execute_or(struct vminstr* input){

}

void execute_not(struct vminstr* input){

}

// DEPRECATED /\ /\.
void execute_jeq(struct vminstr* input){

}

void execute_jne(struct vminstr* input){

}

void execute_jle(struct vminstr* input){

}

void execute_jge(struct vminstr* input){

}

void execute_jlt(struct vminstr* input){

}

void execute_jgt(struct vminstr* input){

}

void execute_call(struct vminstr* input){

}

void execute_pusharg(struct vminstr* input){

}

void execute_funcenter(struct vminstr* input){

}

void execute_funcend(struct vminstr* input){

}

void execute_newtable(struct vminstr* input){

}

void execute_tablegetelem(struct vminstr* input){

}

void execute_tablesetelem(struct vminstr* input){

}

void execute_nop(struct vminstr* input){

}

