#include "debug_functions.h"
#include "target_code_generator.h"
#include "alphavm.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

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
        printf("\n========NUM CONSTS========\n[index] : value\n");

        for (i = 0U; i < carr.size; ++i)
            printf("[%d] : %f\n", i, carr.array[i]);
    }
    else
        printf("\n+++++NUM CONSTS EMPTY+++++\n");

    if ( sarr.size )
    {
        printf("\n========STR CONSTS========\n[index] : value\n");

        for (i = 0U; i < sarr.size; ++i)
            printf("[%d] : \"%s\"\n", i, sarr.array[i]);
    }
    else
        printf("\n+++++STR CONSTS EMPTY+++++\n");

    if ( ufarr.size )
    {
        printf("\n========USER FUNCS========\n[index] : address, size, id\n");

        for (i = 0U; i < ufarr.size; ++i)
            printf("[%d] : %-3d, %-3d, %s\n", i, ufarr.array[i].address, ufarr.array[i].localSize, ufarr.array[i].id);
    }
    else
        printf("\n+++++USER FUNCS EMPTY+++++\n");
    
    if ( lfarr.size )
    {
        printf("\n========LIB FUNCS========\n[index] : value\n");

        for (i = 0U; i < lfarr.size; ++i){
            printf("[%d] : \"%s\"\n", i, lfarr.array[i]);
        }
    }
    else
        printf("\n+++++LIB  FUNCS EMPTY+++++\n");
}

static void print_vmarg(struct vmarg * input){
    printf("| ");
    if(!input){
        printf("          N/A          ");
    }else{
        char argstr[64];
        memset(argstr, 0, 64UL);
        sprintf(argstr,"%d (%s),  [%d]",input->type,argtype_toString[input->type],input->val);
        printf("%-23s",argstr);
    }
}

void print_table(void){
    printf("\n====================================CONST TABLES========================================\n");
    print_const_tables();

    printf("\n========================================FINAL INSTRUCTIONS TABLE==================================================\n");
    printf("No  |     INSTRUCTION     |      RESULT|LABEL      |          ARG1          |          ARG2          | Src Line\n");
    printf("==================================================================================================================\n");

    char opcodestr[30];

    for(int i=1;i<currInstr;++i){

        memset(opcodestr, 0, 30UL);
        sprintf(opcodestr,"%d (%s)",instructions[i].opcode,op_toString[instructions[i].opcode]);

        printf("#%-3d| %-20s",i,opcodestr);
        print_vmarg(instructions[i].result);
        print_vmarg(instructions[i].arg1);
        print_vmarg(instructions[i].arg2);
        printf("|    %d\n",instructions[i].srcLine);
    }
    printf("==================================================================================================================\n");
    printf("    |                     | argv_type,   [value]   | argv_type,   [value]   | argv_type,   [value]   |\n\n");
}

void print_readable_instructions(void){
    print_table();

    // int checkfd = open("genparse_check/gen_check.txt", O_CREAT | O_TRUNC | O_WRONLY, 0666);
    // int saved_stdout = dup(0);
    // dup2(1,checkfd);

    // print_table();

    // dup2(saved_stdout,0);


}

