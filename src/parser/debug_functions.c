#include "debug_functions.h"
#include "target_code_generator.h"
#include "alphavm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

FILE * outpout_file;

static char * op_toString[] =\
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
        fprintf(outpout_file,"\n========NUM CONSTS========\n[index] : value\n");

        for (i = 0U; i < carr.size; ++i)
            fprintf(outpout_file,"[%d] : %f\n", i, carr.array[i]);
    }
    else
        fprintf(outpout_file,"\n+++++NUM CONSTS EMPTY+++++\n");

    if ( sarr.size )
    {
        fprintf(outpout_file,"\n========STR CONSTS========\n[index] : value\n");

        for (i = 0U; i < sarr.size; ++i)
            fprintf(outpout_file,"[%d] : \"%s\"\n", i, sarr.array[i]);
    }
    else
        fprintf(outpout_file,"\n+++++STR CONSTS EMPTY+++++\n");

    if ( ufarr.size )
    {
        fprintf(outpout_file,"\n========USER FUNCS========\n[index] : address, size, id\n");

        for (i = 0U; i < ufarr.size; ++i)
            fprintf(outpout_file,"[%d] : %-3d, %-3d, %s\n", i, ufarr.array[i].address, ufarr.array[i].localSize, ufarr.array[i].id);
    }
    else
        fprintf(outpout_file,"\n+++++USER FUNCS EMPTY+++++\n");
    
    if ( lfarr.size )
    {
        fprintf(outpout_file,"\n========LIB FUNCS========\n[index] : value\n");

        for (i = 0U; i < lfarr.size; ++i){
            fprintf(outpout_file,"[%d] : \"%s\"\n", i, lfarr.array[i]);
        }
    }
    else
        fprintf(outpout_file,"\n+++++LIB  FUNCS EMPTY+++++\n");
}

static void print_vmarg(struct vmarg * input){
    fprintf(outpout_file,"| ");
    if(!input){
        fprintf(outpout_file,"          N/A          ");
    }else{
        char argstr[64];
        memset(argstr, 0, 64UL);
        sprintf(argstr,"%d (%s),  [%d]", input->type, argtype_toString[input->type], input->val);
        fprintf(outpout_file,"%-23s",argstr);
    }
}

void print_readable_instructions(void){
    outpout_file = fopen("output_comparison/parser_generated.txt", "w");

    fprintf(outpout_file,"\n====================================CONST TABLES========================================\n");
    print_const_tables();

    fprintf(outpout_file,"\n========================================FINAL INSTRUCTIONS TABLE==================================================\n");
    fprintf(outpout_file,"No  |     INSTRUCTION     |      RESULT|LABEL      |          ARG1          |          ARG2          | Src Line\n");
    fprintf(outpout_file,"==================================================================================================================\n");

    char opcodestr[30];

    for(int i=1;i<currInstr;++i){

        memset(opcodestr, 0, 30UL);
        sprintf(opcodestr,"%d (%s)",instructions[i].opcode,op_toString[instructions[i].opcode]);

        fprintf(outpout_file,"#%-3d| %-20s",i,opcodestr);
        print_vmarg(instructions[i].result);
        print_vmarg(instructions[i].arg1);
        print_vmarg(instructions[i].arg2);
        fprintf(outpout_file,"|    %d\n",instructions[i].srcLine);
    }
    fprintf(outpout_file,"==================================================================================================================\n");
    fprintf(outpout_file,"    |                     | argv_type,   [value]   | argv_type,   [value]   | argv_type,   [value]   |\n\n");

    fclose(outpout_file);
}