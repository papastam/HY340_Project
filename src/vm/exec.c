#include "exec.h"
#include "mman.h"
#include "alphavm.h"
#include "vmutils.h"

#include <assert.h>
#include <stdlib.h>

unsigned totalActuals=0;

char* typeString[]={
    "number",
    "string",
    "bool",
    "table",
    "userfunc",
    "nil",
    "undef"
};

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
    mod_impl
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
        lv->data.numVal = (*op)(arg1->data.numVal,arg2->data.numVal);
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
        result = (*op)(arg1->data.numVal,arg2->data.numVal);
    
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

    assert(input->result->type == label_a);

    struct avm_memcell* arg1 = avm_translate_operand(input->arg1,&ax);
    struct avm_memcell* arg2 = avm_translate_operand(input->arg2,&bx);

    unsigned char result = 0;
    if(arg1->type==undef_m || arg2->type==undef_m){
        avm_error(input->srcLine,"comparison with undefined opperand!");
    }else if(arg1->type == nil_m || arg2->type == nil_m){
        result = arg1->type == nil_m && arg1->type == nil_m;
    }else if(arg1->type == bool_m || arg2->type == bool_m){
        result = avm_tobool(arg1) == avm_tobool(arg2);
    }else if(arg1->type != arg2->type){
        avm_error(input->srcLine,"comparison between %s and %s is illegal!", typeString[arg1->type],typeString[arg2->type]);
    }else{
        result = avm_tobool(arg1) == avm_tobool(arg2);
    }

    if(!execution_finished && result){
        pc = input->result->val;
    }
}

void execute_jne(struct vminstr* input){

    assert(input->result->type == label_a);

    struct avm_memcell* arg1 = avm_translate_operand(input->arg1,&ax);
    struct avm_memcell* arg2 = avm_translate_operand(input->arg2,&bx);

    unsigned char result = 0;
    if(arg1->type==undef_m || arg2->type==undef_m){
        avm_error(input->srcLine,"comparison with undefined opperand!");
    }else if(arg1->type == nil_m || arg2->type == nil_m){
        result = !(arg1->type == nil_m && arg1->type == nil_m);
    }else if(arg1->type == bool_m || arg2->type == bool_m){
        result = avm_tobool(arg1) != avm_tobool(arg2);
    }else if(arg1->type != arg2->type){
        avm_error(input->srcLine,"comparison between %s and %s is illegal!", typeString[arg1->type],typeString[arg2->type]);
    }else{
        result = avm_tobool(arg1) != avm_tobool(arg2);
    }

    if(!execution_finished && result){
        pc = input->result->val;
    }
}

void execute_call(struct vminstr* input){
    struct avm_memcell* func = avm_translate_operand(&input->result, &ax);
    assert(func);
    avm_callsaveeenvironment();

    switch(func->type){
        case userfunc_m:{
            pc = func->data.funcVal;
            assert(pc < AVM_ENDING_PC);
            assert(code[pc].opcode == funcenter_v);
            break;
        }

        case string_m:  avm_callibfunc(func->data.strVal);      break;
        case libfunc_m: avm_callibfunc(func->data.libfuncVal);  break;
        
        default:{
            char* s = avm_toString(func);
            avm_error("call: cannot bind '%s' to function!",s);
            free(s);
            execution_finished = 1;
        }
    }
}

void execute_pusharg(struct vminstr* input){
    struct avm_memcell* arg = avm_translate_operand(input->arg1,&ax);

    avm_assign(&stack[top],arg);
    ++totalActuals;
    avm_dec_top();
}

void execute_funcenter(struct vminstr* input){

}

void execute_funcend(struct vminstr* input){

}

void execute_newtable(struct vminstr* input){
    struct avm_memcell* lv = avm_translate_operand(input->result, NULL);
    assert(lv); // && (&stack[N-1] >= lv && lv stack[top] || lv==&retval);

    avm_memcellclear(lv);
    
    lv->type            = table_m;
    lv->data.tableVal   = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(struct vminstr* input){
    struct avm_memcell* lv = avm_translate_operand(input->result, NULL);
    struct avm_memcell* table = avm_translate_operand(input->arg1, NULL);
    struct avm_memcell* index = avm_translate_operand(input->arg2, &ax);

    // TODO assert()

    avm_memcellclear(lv);
    lv->type = nil_m;

    if(table->type != table_m){
        avm_error(input->srcLine,"illegal use of type %s as table!",typeString[table->type]);
    }else{
        struct avm_memcell* content = avm_tablegetelem(table->data.tableVal, index);
        if(content){
            avm_assign(lv,content);
        }else{
            char* ts = avm_toString(table);
            char* is = avm_toString(index);
            avm_warning(input->srcLine, "%s[%s] does not exist!",ts,is);
            free(ts);
            free(is);
        }
    }
}

void execute_tablesetelem(struct vminstr* input){
    struct avm_memcell* content = avm_translate_operand(input->result, NULL);
    struct avm_memcell* table = avm_translate_operand(input->arg1, NULL);
    struct avm_memcell* index = avm_translate_operand(input->arg2, &ax);

    //TODO assert

    if(table->type != table_m){
        avm_error(input->srcLine,"illegal use of type %s as table!", typeString[table->type]);
    }else{
        avm_tablesetelem(table->data.tableVal, index, content);
    }
}

void execute_nop(struct vminstr* input){

}

//================ LIBRARY FUNCTIONS ================

void libfunc_print(void) {
    unsigned n = avm_getTotalActuals();
    for(uint i = 0; i < n; ++i) {
        char* s = avm_toString(avm_getActual(i));
        puts(s);
        free(s);
    }
}

void libfunc_input(void) {

    
}

void libfunc_objectmemberkeys(void) {
    
}

void libfunc_objecttotalmembers(void) {
    
}

void libfunc_objectcopy(void) {
    
}

void libfunc_totalarguments(void) {
    unsigned prev_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
}

void libfunc_argument(void) {
    
}

void libfunc_typeof(void) {
    unsigned n = avm_totalactuals();
    if(n != 1)
        avm_error(0, "One argument (not %d) expected for 'typeof'!", n); // Fix line number? where do i get it from?
    else {
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeString[avm_getActual(0)->type]);
    }
    
}

void libfunc_strtonum(void) {
    
}

void libfunc_sqrt(void) {
    
}

void libfunc_cos(void) {
    
}

void libfunc_sin(void) {
    
}
