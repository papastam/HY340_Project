#include "execute_functions.h"
#include "memory_management.h"
#include "vmalpha.h"
#include "vmutils.h"

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


double add_impl(double x,double y){return x+y;}
double sub_impl(double x,double y){return x-y;}
double mul_impl(double x,double y){return x*y;}
double div_impl(double x,double y){return x/y;}
double mod_impl(double x,double y){return ((unsigned) x) % ((unsigned) y);}

arithmetic_func_t arithFuncs[]={
    add_impl,
    sub_impl,
    mul_impl,
    div_impl,
    mod_impl,
};

void execute_arithmetic(struct vminstr* input){
    
    struct avm_memcell* lv = avm_translate_opperant(input->result, NULL);
    struct avm_memcell* arg1 = avm_translate_opperant(input->arg1, &ax);
    struct avm_memcell* arg2 = avm_translate_opperant(input->arg2, &bx);
    
    // assert(lv && (&stack[N-1]))
    assert(arg1 && arg2);

    if(arg1->type != number_m || arg2->type != number_m){
        avm_error("Non numeric value used in arithmetic opperation!");
        execution_finished=1;   
    }else{
        arithmetic_func_t op = arithFuncs[input->opcode-add_v];
        avm_memcellclear(lv);
        lv->type        = number_m;
        lv->data.numVal = (*op)(arg1->data.numVal,arg2->data.numVal);
    }
}

void execute_assign(struct vminstr* input){
    struct avm_memcell* lv = avm_translate_opperant(&input->result, (struct avm_memcell*) 0);
    struct avm_memcell* rv = avm_translate_opperant(&input->arg1, &ax);

    // assert(lv &&)
    assert(rv);

    avm_assign(lv,rv);
}

// DEPRECATED \/ \/.
void execute_uminus(struct vminstr* input)  {assert(0);}
void execute_and(struct vminstr* input)     {assert(0);}
void execute_or(struct vminstr* input)      {assert(0);}
void execute_not(struct vminstr* input)     {assert(0);}
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

