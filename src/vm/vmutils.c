#include "vmutils.h"
#include "alphavm.h"
#include "mman.h"
#include "exec.h"

#include <assert.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>

#define error_msg "\033[0;31mError\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "
#define warning_msg "\033[0;35mWarning\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "
#define debug_msg  "\033[0;37mDebug\e[0;1m\e[0m ---> "

FILE * vm_parsed_file;

//========== TO BOOL DISPATCHER ==========
tobool_func_t toBoolFuncs[]={
    number_tobool,
    string_tobool,
    bool_tobool,
    table_tobool,
    userfunc_tobool,
    libfunc_tobool,
    nil_tobool,
    undefined_tobool
};

uint recur_table_print;
FILE * gmstream;

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
    bool_toString,
    table_toString,
    userfunc_toString,
    libfunc_toString,
    nil_toString,
    undefined_toString
};

char * avm_toString(struct avm_memcell* input){
    assert(input->type >= 0 && input->type < undef_m);
    return strdup((*toStringFuncs[input->type])(input));
};

char * number_toString(struct avm_memcell* input)      {char output[18];sprintf(output,"%G", input->data.numVal);return strdup(output);}
char * string_toString(struct avm_memcell* input)      {return strdup(input->data.strVal);}
char * bool_toString(struct avm_memcell* input)        {return input->data.boolVal?"TRUE":"FALSE";}

void __print_complete(FILE * restrict memstream, struct avm_memcell * restrict mc)
{
    switch ( mc->type )
    {
        case undef_m:

            fprintf(memstream, "undefined]\n");
            break;

        case number_m:

            fprintf(memstream, "%G}, \n", mc->data.numVal);
            break;

        case bool_m:

            fprintf(memstream, "%s}, ", (mc->data.boolVal ? "true" : "false"));
            break;

        case table_m:

            ++recur_table_print;
            gmstream = memstream;

            table_toString(mc);

            fprintf(memstream, "}, ");

            --recur_table_print;

            break;

        case userfunc_m:

            fprintf(memstream, "%s}, ", avm_getfuncinfo(mc->data.funcVal)->id);
            break;

        case string_m:
        case libfunc_m:

            fprintf(memstream, "%s}, ", mc->data.strVal);
            break;

        case nil_m:

            fprintf(memstream, "nil}, ");
            break;
    }

    return;
}

char * table_toString(struct avm_memcell * input)
{
    size_t outsize;

    char * output;
    FILE * mstream;


    if ( !recur_table_print )
    {
        if ( !(mstream = open_memstream(&output, &outsize)) )
        {
            perror("open_memstream()");
            return NULL;
        }
    }
    else
        mstream = gmstream;

    struct avm_table_bucket * (*ptr)[AVM_TABLE_HASHSIZE];
    struct avm_table * t;

    struct avm_memcell * key;
    struct avm_memcell * val;

    uint j;
    uint i;
    uint l;


    t = input->data.tableVal;
    ptr = &t->strIndexed;
    l = AVM_TABLE_HASHSIZE;

    for (i = 0U; i < 6U; ++i)
    {
        if ( i == 5 )
            l = 2U;

        for (j = 0U; j < l; ++j)
        {
            if ( !ptr[i][j] )
                continue;

            key = &ptr[i][j]->key;
            val = &ptr[i][j]->value;

            switch ( key->type )
            {
                case undef_m:

                    fprintf(mstream, "{key: undefined, val: undefined}, ");
                    break;

                case number_m:

                    fprintf(mstream, "{key: %G, val: ", key->data.numVal);
                    __print_complete(mstream, val);

                    break;

                case bool_m:

                    fprintf(mstream, "{key: %s, val: ", (key->data.boolVal) ? "true" : "false");
                    __print_complete(mstream, val);

                    break;

                case table_m:

                    fprintf(mstream, "{key: ");

                    ++recur_table_print;
                    gmstream = mstream;

                    table_toString(key);

                    --recur_table_print;

                    fprintf(mstream, ", val: ");
                    __print_complete(mstream, val);

                    break;

                case userfunc_m:

                    fprintf(mstream, "{key: %s, val: ", avm_getfuncinfo(key->data.funcVal)->id);
                    __print_complete(mstream, val);

                    break;

                case string_m:
                case libfunc_m:

                    fprintf(mstream, "{key: %s, val: ", key->data.strVal);
                    __print_complete(mstream, val);

                    break;

                case nil_m:

                    fprintf(mstream, "{key: nil, val: nil}, ");
                    break;
            }
        }
    }

    fflush_unlocked(mstream);

    if ( !recur_table_print )
        fclose(mstream);

    return output;  // free output when done using it
}

char * userfunc_toString(struct avm_memcell* input)    {return avm_getfuncinfo(input->data.funcVal)->id;}
char * libfunc_toString(struct avm_memcell* input)     {return input->data.libfuncVal;}
char * nil_toString(struct avm_memcell* input)         {return "NIL";}
char * undefined_toString(struct avm_memcell* input)   {return "UNDEFINED";}


void avm_warning(int line, const char * warformat, ...)
{
    va_list print_args;

    va_start(print_args, warformat);

    printf(warning_msg, line);
    vprintf(warformat, print_args);
    printf("\n");
    va_end(print_args);
}

void avm_error(int line, const char * errformat, ...)
{

    va_list print_args;

    va_start(print_args, errformat);

    printf(error_msg, line);
    vprintf(errformat, print_args);

    va_end(print_args);
    printf("\n");

    execution_finished = 1;
}

void avm_debug(const char * debugormat, ...){
    if(!AVMDEBUG){return;}

    va_list print_args;

    va_start(print_args, debugormat);

    printf(debug_msg);
    vprintf(debugormat, print_args);

    va_end(print_args);
    printf("\n");
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
    }else if(lv->type == libfunc_m){
        lv->data.libfuncVal = strdup(rv->data.libfuncVal);
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

unsigned avm_get_envvalue(unsigned i){ 
    assert(stack[i].type==number_m);
    unsigned val = (unsigned)stack[i].data.numVal;
    assert(stack[i].data.numVal==(double)val);
    return val;
}


void avm_callsaveenvironment(void){
    avm_push_envvalue(totalActuals);
    avm_push_envvalue(pc+1);
    avm_push_envvalue(top+totalActuals+2);
    avm_push_envvalue(topsp);
}

unsigned avm_getTotalActuals(){
    return avm_get_envvalue(topsp + AVM_NUMACTUALS_OFFSET);
}

struct avm_memcell * avm_getActual(unsigned i) {
    assert(i < avm_getTotalActuals());
    return &stack[topsp + AVM_STACKENV_SIZE + 1 + i];
} 

struct userfunc* avm_getfuncinfo(unsigned address){
    
    for(uint i=0; i < ufarr.size; ++i){
        if(ufarr.array[i].address == address)
            return &ufarr.array[i];        
    }

    return NULL;
}

double consts_getnumber(uint index){
    return carr.array[index];
}

char* consts_getstr(uint index){
    return sarr.array[index];
}

char* consts_getlibfunc(uint index){
    return lfarr.array[index];
}

uint consts_getuserfuncaddr(uint index){
    return ufarr.array[index].address;
}

char* consts_getuserfuncid(uint index){
    return ufarr.array[index].id;
}

library_func_t  avm_getlibraryfunc(char* id){
    if(!strcmp(id,"print"))                     {return libfunc_print;
    }else if(!strcmp(id,"input"))               {return libfunc_input;
    }else if(!strcmp(id,"objectmemberkeys"))    {return libfunc_objectmemberkeys;
    }else if(!strcmp(id,"objecttotalmembers"))  {return libfunc_objecttotalmembers;
    }else if(!strcmp(id,"objectcopy"))          {return libfunc_objectcopy;
    }else if(!strcmp(id,"totalarguments"))      {return libfunc_totalarguments;
    }else if(!strcmp(id,"argument"))            {return libfunc_argument;
    }else if(!strcmp(id,"typeof"))              {return libfunc_typeof;
    }else if(!strcmp(id,"strtonum"))            {return libfunc_strtonum;
    }else if(!strcmp(id,"sqrt"))                {return libfunc_sqrt;
    }else if(!strcmp(id,"cos"))                 {return libfunc_cos;
    }else if(!strcmp(id,"sin"))                 {return libfunc_sin;
    }else{return NULL;}
}

void avm_callibfunc(char* funcname){
    library_func_t f = avm_getlibraryfunc(funcname);
    
    if(!f){
        avm_error(0, "unsupported lib func '%s' called!", funcname);
        execution_finished = 1;
    }else{
        topsp = top;
        totalActuals = 0;
        (*f)();
        if(!execution_finished){
            execute_funcend((struct vminstr*) 0);
        }
    }
}

//============= PARSER DEBUG =============


char * op_toString[] =\
{
    "assign_v",           "add_v",              "sub_v",
    "mul_v",              "div_v",              "mod_v",
    "uminus_v",           "and_v",              "or_v",
    "not_v",              "jeq_v",              "jne_v",              
    "jle_v",              "jge_v",              "jlt_v",
    "jgt_v",              "call_v",             "pusharg_v",
    "funcenter_v",        "funcexit_v",         "newtable_v",
    "tablegetelem_v",     "tablesetelem_v",     "nop_v",
    };

static char * argtype_toString[] =\
{
    "label_a",
    "global_a",
    "formal_a",
    "local_a",
    "number_a",
    "string_a",
    "bool_a",
    "nil_a",
    "userfunc_a",
    "libfunc_a",
    "retval_a"
};

static void print_const_tables(void)
{
    uint i;

    if ( carr.size )
    {
        fprintf(vm_parsed_file,"\n========NUM CONSTS========\n[index] : value\n");

        for (i = 0U; i < carr.size; ++i)
            fprintf(vm_parsed_file,"[%d] : %f\n", i, carr.array[i]);
    }
    else
        fprintf(vm_parsed_file,"\n+++++NUM CONSTS EMPTY+++++\n");

    if ( sarr.size )
    {
        fprintf(vm_parsed_file,"\n========STR CONSTS========\n[index] : value\n");

        for (i = 0U; i < sarr.size; ++i)
            fprintf(vm_parsed_file,"[%d] : \"%s\"\n", i, sarr.array[i]);
    }
    else
        fprintf(vm_parsed_file,"\n+++++STR CONSTS EMPTY+++++\n");

    if ( ufarr.size )
    {
        fprintf(vm_parsed_file,"\n========USER FUNCS========\n[index] : address, local_size, actuals, id\n");

        for (i = 0U; i < ufarr.size; ++i)
            fprintf(vm_parsed_file,"[%d] : %-3d, %-3d, %-3d, %s\n", i, ufarr.array[i].address, ufarr.array[i].localSize, ufarr.array[i].totalFormals, ufarr.array[i].id);
    }
    else
        fprintf(vm_parsed_file,"\n+++++USER FUNCS EMPTY+++++\n");
    
    if ( lfarr.size )
    {
        fprintf(vm_parsed_file,"\n========LIB FUNCS========\n[index] : value\n");

        for (i = 0U; i < lfarr.size; ++i){
            fprintf(vm_parsed_file,"[%d] : \"%s\"\n", i, lfarr.array[i]);
        }
    }
    else
        fprintf(vm_parsed_file,"\n+++++LIB  FUNCS EMPTY+++++\n");
}

static void print_vmarg(struct vmarg * input){
    fprintf(vm_parsed_file,"| ");
    if(!input){
        fprintf(vm_parsed_file,"          N/A          ");
    }else{
        char argstr[64];
        memset(argstr, 0, 64UL);
        sprintf(argstr,"%d (%s),  [%d]", input->type, argtype_toString[input->type], input->val);
        fprintf(vm_parsed_file,"%-23s",argstr);
    }
}

void print_readable_instructions(void){
    vm_parsed_file = fopen("output_comparison/vm_parsed.txt", "w");

    fprintf(vm_parsed_file,"\n====================================CONST TABLES========================================\n");
    print_const_tables();

    fprintf(vm_parsed_file,"\n========================================FINAL INSTRUCTIONS TABLE==================================================\n");
    fprintf(vm_parsed_file,"No  |     INSTRUCTION     |      RESULT|LABEL      |          ARG1          |          ARG2          | Src Line\n");
    fprintf(vm_parsed_file,"==================================================================================================================\n");

    char opcodestr[30];

    for(int i=1;i<AVM_ENDING_PC;++i){

        memset(opcodestr, 0, 30UL);
        sprintf(opcodestr,"%d (%s)",code[i].opcode,op_toString[code[i].opcode]);

        fprintf(vm_parsed_file,"#%-3d| %-20s",i,opcodestr);
        print_vmarg(code[i].result);
        print_vmarg(code[i].arg1);
        print_vmarg(code[i].arg2);
        fprintf(vm_parsed_file,"|    %d\n",code[i].srcLine);
    }
    fprintf(vm_parsed_file,"==================================================================================================================\n");
    fprintf(vm_parsed_file,"    |                     | argv_type,   [value]   | argv_type,   [value]   | argv_type,   [value]   |\n\n");

    fclose(vm_parsed_file);
}
