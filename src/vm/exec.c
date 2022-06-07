#include "exec.h"
#include "mman.h"
#include "alphavm.h"
#include "vmutils.h"

#include <assert.h>
#include <stddef.h>

//========== ARITHMETIC FUNCTIONS DISPATCHER ==========
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
    
    struct avm_memcell* lv = avm_translate_operand(input->result, NULL);
    struct avm_memcell* arg1 = avm_translate_operand(input->arg1, &ax);
    struct avm_memcell* arg2 = avm_translate_operand(input->arg2, &bx);
    
    // assert(lv && (&stack[N-1]))
    assert(arg1 && arg2);

    if(arg1->type != number_m || arg2->type != number_m){
        avm_error(0,"Non numeric value used in arithmetic opperation!");
        execution_finished=1;   
    }else{
        arithmetic_func_t op = arithFuncs[input->opcode-add_v];
        avm_memcellclear(lv);
        lv->type        = number_m;
        lv->numVal = (*op)(arg1->numVal,arg2->numVal);
    }
}

//========== COMPARISON FUNCTIONS DISPATCHER ==========
int jle_impl(double x,double y){return x<=y?1:0;}
int jge_impl(double x,double y){return x>=y?1:0;}
int jlt_impl(double x,double y){return x<y?1:0;}
int jgt_impl(double x,double y){return x>y?1:0;}

comp_func_t compFuncs[]={
    jle_impl,
    jge_impl,
    jlt_impl,
    jgt_impl,
};

void execute_comp(struct vminstr* input){
    int result=0;

    struct avm_memcell* arg1 = avm_translate_operand(input->arg1, &ax);
    struct avm_memcell* arg2 = avm_translate_operand(input->arg2, &bx);
    
    assert(arg1 && arg2);

    if(arg1->type != number_m || arg2->type != number_m){
        avm_error(0,"Non numeric value used in comparison!");
        execution_finished=1;   
    }else{
        comp_func_t op = compFuncs[input->opcode-jle_v];
        result = (*op)(arg1->numVal,arg2->numVal);
    
        if(execution_finished && result){
            pc = input->result->val;
        }
    }
        
}

//================= EXECUTE FUNCTIONS =================
execute_func_t executeFuncs[]={
    execute_assign,
    execute_add,
    execute_sub,
    execute_mul,
    execute_div,
    execute_mod,
    NULL,
    NULL,
    NULL,
    NULL,
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
    struct avm_memcell* lv = avm_translate_operand(input->result, (struct avm_memcell*) 0);
    struct avm_memcell* rv = avm_translate_operand(input->arg1, &ax);

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
