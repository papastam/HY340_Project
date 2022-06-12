#include "exec.h"
#include "mman.h"
#include "alphavm.h"
#include "vmutils.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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

void execute_jne(struct vminstr * input)
{
    assert(input->result->type == label_a);

    struct avm_memcell * arg1 = avm_translate_operand(input->arg1, &ax);
    struct avm_memcell * arg2 = avm_translate_operand(input->arg2, &bx);
    unsigned char result = 0;


    if ( arg1->type == undef_m || arg2->type == undef_m )
        avm_error(input->srcLine, "comparison with undefined opperand!");
    else if ( arg1->type == nil_m || arg2->type == nil_m )
        result = !(arg1->type == nil_m && arg1->type == nil_m);
    else if ( arg1->type == bool_m || arg2->type == bool_m )
        result = avm_tobool(arg1) != avm_tobool(arg2);
    else if(arg1->type != arg2->type)
        avm_error(input->srcLine, "comparison between %s and %s is illegal!", typeString[arg1->type], typeString[arg2->type]);
    else
        result = avm_tobool(arg1) != avm_tobool(arg2);

    if ( !execution_finished && result )
        pc = input->result->val;
}

void execute_call(struct vminstr * input)
{
    struct avm_memcell * func = avm_translate_operand(input->arg1, &ax);
    
    assert(func);
    avm_callsaveenvironment();

    switch ( func->type )
    {
        case userfunc_m:

            pc = func->data.funcVal;

            assert(pc < AVM_ENDING_PC);
            assert(code[pc].opcode == funcenter_v);

            break;

        case string_m:

            avm_callibfunc(func->data.strVal);
            break;

        case libfunc_m:

            avm_callibfunc(func->data.libfuncVal);
            break;
        
        default:
        {
            char * s = avm_toString(func);
            avm_error(0,"call: cannot bind '%s' to function!", s);
            free(s);
            execution_finished = 1;
        }
    }
}

void execute_pusharg(struct vminstr * input)
{
    struct avm_memcell * arg = avm_translate_operand(input->arg1, &ax);

    avm_assign(&stack[top], arg);
    ++totalActuals;
    avm_dec_top();
}

void execute_funcenter(struct vminstr * input)
{
    struct avm_memcell * func = avm_translate_operand(input->arg1, &ax);

    assert(func);
    assert(pc == func->data.funcVal);

    totalActuals = 0;
    struct userfunc * funcinfo = avm_getfuncinfo(pc);
    topsp = top;
    top = top - funcinfo->localSize;
}

void execute_funcend(struct vminstr * input)
{
    unsigned oldTop = top;

    top   = avm_get_envvalue(topsp + AVM_SAVEDTOP_OFFSET);
    pc    = avm_get_envvalue(topsp + AVM_SAVEDPC_OFFSET);
    topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);

    while ( ++oldTop <= top )
        avm_memcellclear(&stack[oldTop]);
}

void execute_newtable(struct vminstr * input)
{
    struct avm_memcell * lv = avm_translate_operand(input->result, NULL);

    assert(lv);
    avm_memcellclear(lv);
    
    lv->type = table_m;
    lv->data.tableVal = avm_tablenew();
    avm_tableincrefcounter(lv->data.tableVal);
}

void execute_tablegetelem(struct vminstr* input)
{
    struct avm_memcell * lv = avm_translate_operand(input->result, NULL);
    struct avm_memcell * table = avm_translate_operand(input->arg1, NULL);
    struct avm_memcell * index = avm_translate_operand(input->arg2, &ax);


    // TODO assert()

    avm_memcellclear(lv);
    lv->type = nil_m;

    if ( table->type != table_m )
        avm_error(input->srcLine,"illegal use of type %s as table!", typeString[table->type]);
    else
    {
        struct avm_memcell * content = avm_tablegetelem(table->data.tableVal, index);

        if ( content )
            avm_assign(lv,content);
        else
        {
            char * ts = avm_toString(table);
            char * is = avm_toString(index);


            avm_warning(input->srcLine, "%s[%s] does not exist!", ts, is);
            free(ts);
            free(is);
        }
    }
}

void execute_tablesetelem(struct vminstr * input)
{
    struct avm_memcell * content = avm_translate_operand(input->result, &ax);
    struct avm_memcell * table = avm_translate_operand(input->arg1, NULL);
    struct avm_memcell * index = avm_translate_operand(input->arg2, &bx);


    //TODO assert

    if ( table->type != table_m )
        avm_error(input->srcLine,"illegal use of type %s as table!", typeString[table->type]);
    else
        avm_tablesetelem(table->data.tableVal, index, content);
}

void execute_nop(struct vminstr* input){

}

//================ LIBRARY FUNCTIONS ================

void libfunc_print(void) {
    uint n = avm_getTotalActuals();
    for(uint i = 0; i < n; ++i) {
        char* s = avm_toString(avm_getActual(i));
        char c = getc(s);
        while(c != '\0') {
            if(c == '\\') {
                char n_c = getc(s);
                if(n_c == 'n') 
                    putchar('\n');
                else if(n_c == 't')
                    putchar('\t');
                else if(n_c == '"')
                    putchar('"');
                else if(n_c == '\\')
                    putchar('\\');
                else {
                    putchar(c);
                    if(n_c != '\0')
                        putchar(n_c);
                    else
                        break;
                }
            }
            else    
                putchar(c);
            c = getc(s);
        }
        free(s);
    }
}

void libfunc_input(void) {
    avm_memcellclear(&retval);
    char* line = NULL;
    char* line2 = NULL;
    size_t len = 0;
    
    ssize_t length = getline(&line2, &len, stdin);
    line = line2;
    *(line + --length) = '\0'; // remove newline from end

    if(!strcmp(line, "nil")) {
        goto nil;
    }
    
    if(!strcmp(line, "true") || !strcmp(line, "false")) {
        goto boolean;
    }

    if(*line == '"' && *(line + length -1) == '"') {
        *(line + length - 1) = '\0';
        line++;
        goto string;
    }

    int dot_count = 0;
    char c;
    for(int i = 0; i < length; ++i) {
        c = *(line + i);
        if(c == 46) {
            if(dot_count != 0)
                goto string;
            ++dot_count;
        }
        else if(c < 48 || c > 57) {
            goto string;
            
        }
    }
    
    goto number; // if it does not jump to any labels above then its a number
    
    string:
    retval.type = string_m;
    retval.data.strVal = strdup(line);
    goto end;

    boolean:
    retval.type = bool_m;
    if(!strcmp(line, "true"))
        retval.data.boolVal = true;
    else    
        retval.data.boolVal = false;
    goto end;

    number:
    retval.type = number_m;
    retval.data.numVal = atof(line);
    goto end;

    nil:
    retval.type = nil_m;
    goto end;


    end:
    free(line2);
}

void libfunc_objectmemberkeys(void) {
    unsigned n = avm_getTotalActuals();
    if( n != 1) 
        avm_error(0, "One argument (not %d) expected for 'objectmemberkeys'", n);
    struct avm_memcell* arr = avm_getActual(0);
    if(arr->type != table_m)
        avm_error(0, "Argument of 'objectmemberkeys' must be of type table, not %s", typeString[arr->type]);
    
    struct avm_table* new_table = avm_tablenew();
    struct avm_memcell key, val;
    double index = 0;
    struct avm_table_bucket* bucket;
    for(uint i = 0; i < AVM_TABLE_HASHSIZE; ++i) {
        //get keys from numindexed array
        bucket = arr->data.tableVal->numIndexed[i];
        while(bucket){
            key.type = number_m;
            key.data.numVal = index++;
            val = bucket->key;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

        //get keys from strindexed array
        bucket = arr->data.tableVal->strIndexed[i];
        while(bucket) {
            key.type = number_m;
            key.data.numVal = index++;
            val = bucket->key;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

        //get keys from tableindexed array
        bucket = arr->data.tableVal->tableIndexed[i];
        while(bucket) {
            key.type = number_m;
            key.data.numVal = index++;
            val = bucket->key;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

        //get keys from usrfuindexed array
        bucket = arr->data.tableVal->usrfuIndexed[i];
        while(bucket) {
            key.type = number_m;
            key.data.numVal = index++;
            val = bucket->key;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

        //get keys from libfuindexed array
        bucket = arr->data.tableVal->libfuIndexed[i];
        while(bucket) {
            key.type = number_m;
            key.data.numVal = index++;
            val = bucket->key;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

    }

    //get keys from boolindexed array
    for(uint i = 0; i < 2; ++i) {
        bucket = arr->data.tableVal->boolIndexed[i];
        while(bucket) {
            key.type = number_m;
            key.data.numVal = index++;
            val = bucket->key;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }
    }

    avm_memcellclear(&retval);
    retval.type = table_m;
    retval.data.tableVal = new_table;
}

void libfunc_objecttotalmembers(void) {
    unsigned n = avm_getTotalActuals();
    if(n != 1) 
        avm_error(0, "One argument (not %d) expected fom 'objecttotalmembers'!", n);
    
    struct avm_memcell* arg = avm_getActual(0);
    if(arg->type != table_m)
        avm_error(0, "'objecttotalmembers' takes an argument of type table, not %s", typeString[arg->type]);

    avm_memcellclear(&retval);
    retval.type = number_m;
    retval.data.numVal = (double)arg->data.tableVal->total;
}

void libfunc_objectcopy(void) {
    unsigned n = avm_getTotalActuals();
    if( n != 1) 
        avm_error(0, "One argument (not %d) expected for 'objectcopy'", n);
    struct avm_memcell* arr = avm_getActual(0);
    if(arr->type != table_m)
        avm_error(0, "Argument of 'objectcopy' must be of type table, not %s", typeString[arr->type]);
    
    struct avm_table* new_table = avm_tablenew();
    struct avm_memcell key, val;
    struct avm_table_bucket* bucket;

    for(uint i = 0; i < AVM_TABLE_HASHSIZE; ++i) {
        //get keys from numindexed array
        bucket = arr->data.tableVal->numIndexed[i];
        while(bucket){
            key = bucket->key;
            val = bucket->value;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

        //get keys from strindexed array
        bucket = arr->data.tableVal->strIndexed[i];
        while(bucket) {
            key = bucket->key;
            val = bucket->value;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

        //get keys from tableindexed array
        bucket = arr->data.tableVal->tableIndexed[i];
        while(bucket) {
            key = bucket->key;
            val = bucket->value;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

        //get keys from usrfuindexed array
        bucket = arr->data.tableVal->usrfuIndexed[i];
        while(bucket) {
            key = bucket->key;
            val = bucket->value;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

        //get keys from libfuindexed array
        bucket = arr->data.tableVal->libfuIndexed[i];
        while(bucket) {
            key = bucket->key;
            val = bucket->value;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }

    }

    //get keys from boolindexed array
    for(uint i = 0; i < 2; ++i) {
        bucket = arr->data.tableVal->boolIndexed[i];
        while(bucket) {
            key = bucket->key;
            val = bucket->value;
            avm_tablesetelem(new_table, &key, &val);
            bucket = bucket->next;
        }
    }

    avm_memcellclear(&retval);
    retval.type = table_m;
    retval.data.tableVal = new_table;
}

void libfunc_totalarguments(void) {
    unsigned prev_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);

    if(!prev_topsp) { //if 0 then no previous activation record
        avm_error(0, "'totalarguments' called outside of function!");
        retval.type = nil_m;
    }
    else {
        retval.type = number_m;
        retval.data.numVal = avm_get_envvalue(prev_topsp + AVM_NUMACTUALS_OFFSET);
    }
}

void libfunc_argument(void) {
    unsigned prev_topsp = avm_get_envvalue(topsp + AVM_SAVEDTOPSP_OFFSET);
    avm_memcellclear(&retval);

    if(!prev_topsp) { //if 0 then no previous activation record
        avm_error(0, "'argument' called outside of function!");
        retval.type = nil_m;
    }
    else {
        unsigned n = avm_getTotalActuals(); //of argument function
        if(n != 1) {
            avm_error(0, "One argument (not %d) expected for 'argument'!", n);
            return;
        }
        struct avm_memcell* index = avm_getActual(0);
        unsigned total_actuals = avm_get_envvalue(prev_topsp + AVM_NUMACTUALS_OFFSET);
        if(index->type != number_m) 
            avm_error(0, "'argument' takes an argument of type number, not %s", typeString[index->type]);
        else if(index->data.numVal < 0 || index->data.numVal > total_actuals)
            avm_error(0, "Function has %d arguments, not %ld", n, index->data.numVal);
        else {
            retval.type = stack[prev_topsp + AVM_STACKENV_SIZE + 1 + (int)index->data.numVal].type;
    
            switch (retval.type)
            {
            case number_m:
                retval.data.numVal = stack[prev_topsp + AVM_STACKENV_SIZE + 1 + (int)index->data.numVal].data.numVal;
                break;
            case string_m:
                retval.data.strVal = stack[prev_topsp + AVM_STACKENV_SIZE + 1 + (int)index->data.numVal].data.strVal;
                break;
            case bool_m:
                retval.data.boolVal = stack[prev_topsp + AVM_STACKENV_SIZE + 1 + (int)index->data.numVal].data.boolVal;
                break;
            case table_m:
                retval.data.tableVal = stack[prev_topsp + AVM_STACKENV_SIZE + 1 + (int)index->data.numVal].data.tableVal;
                break;
            case userfunc_m:
                retval.data.funcVal = stack[prev_topsp + AVM_STACKENV_SIZE + 1 + (int)index->data.numVal].data.funcVal;
                break;
            case libfunc_m:
                retval.data.libfuncVal = stack[prev_topsp + AVM_STACKENV_SIZE + 1 + (int)index->data.numVal].data.libfuncVal;
                break;
            case nil_m:
            case undef_m:            
            default:
                break;
            }
        }
        
    }
}

void libfunc_typeof(void) {
    unsigned n = avm_getTotalActuals();
    if(n != 1)
        avm_error(0, "One argument (not %d) expected for 'typeof'!", n);
    else {
        avm_memcellclear(&retval);
        retval.type = string_m;
        retval.data.strVal = strdup(typeString[avm_getActual(0)->type]);
    }
}

void libfunc_strtonum(void) {
    unsigned n = avm_getTotalActuals();
    struct avm_memcell* arg = avm_getActual(0);
    if(n != 1)
        avm_error(0, "One argument (not %d) expected for 'strtonum'!", n);
    else if(arg->type != string_m)
        avm_error(0, "'strtonum' takes an argument of type string, not %s", typeString[arg->type]);
    else {
        avm_memcellclear(&retval);
        int res = atoi(arg->data.strVal);
        if(!res)
            retval.type = nil_m;
        else {
            retval.type = number_m;
            retval.data.numVal = res;
        }
    }
}

void libfunc_sqrt(void) {
    unsigned n = avm_getTotalActuals();
    struct avm_memcell* arg = avm_getActual(0);
    if(n != 1)
        avm_error(0, "One argument (not %d) expected for 'sqrt'!", n);
    else if(arg->type != number_m)
        avm_error(0, "'sqrt' takes an argument of type number, not %s", typeString[arg->type]);
    else if(arg->data.numVal < 0){
       avm_memcellclear(&retval);
       retval.type = nil_m;
    }
    else {
        avm_memcellclear(&retval);
        retval.type = number_m;
        retval.data.numVal = sqrt(arg->data.numVal); //If compiler has issues with math.h funcs, add -lm when using gcc
    }
}

void libfunc_cos(void) {
    unsigned n = avm_getTotalActuals();
    struct avm_memcell* arg = avm_getActual(0);
    if(n != 1)
        avm_error(0, "One argument (not %d) expected for 'cos'", n);
    else if(arg->type != number_m)
        avm_error(0, "'cos' takes an argument of type number, not %s", typeString[arg->type]);
    else {
        avm_memcellclear(&retval);
        retval.type = number_m;
        retval.data.numVal = cos(arg->data.numVal);
    }
}

void libfunc_sin(void) {
unsigned n = avm_getTotalActuals();
    struct avm_memcell* arg = avm_getActual(0);
    if(n != 1)
        avm_error(0, "One argument (not %d) expected for 'cos'", n);
    else if(arg->type != number_m)
        avm_error(0, "'sin' takes an argument of type number, not %s", typeString[arg->type]);
    else {
        avm_memcellclear(&retval);
        retval.type = number_m;
        retval.data.numVal = sin(arg->data.numVal);
    }
}
