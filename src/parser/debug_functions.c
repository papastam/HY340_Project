#include "debug_functions.h"
#include "target_code_generator.h"

#include <stdio.h>
#include <stdlib.h>

char* op_toString[]={
    "assign_v",           "add_v",              "sub_v",
    "mul_v",              "div_v",              "mod_v",
    "uminus_v",           "and_v",              "or_v",
    "not_v",              "jump_v",             "jeq_v", //added jump although it is not on lect13, slide17
    "jne_v",              "jle_v",              "jge_v",
    "jlt_v",              "jgt_v",              "call_v",
    "pusharg_v",          "funcenter_v",        "funcexit_v",
    "newtable_v",         "tablegetelem_v",     "tablesetelem_v",
    "nop_v",
    };

char* argtype_toString[]={
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

void print_vmarg(struct vmarg * input){
    printf("| ");
    if(!input){
        printf("          N/A          ");
    }else{
        char* argstr=malloc(23*sizeof(char));
        sprintf(argstr,"%d (%s),  [%d]",input->type,argtype_toString[input->type],input->val);
        printf("%-23s",argstr);
    }
}

void print_readable_instructions(void){
    printf("\n====================================FINAL INSTRUCTIONS TABLE========================================\n");
    printf("No|     INSTRUCTION     |          ARG1          |          ARG2          |      RESULT|LABEL       \n");
    printf("====================================================================================================\n");
    for(int i=1;i<currInstr;++i){
        char* opcodestr = malloc(20*sizeof(char));
        sprintf(opcodestr,"%d (%s)",instructions[i].opcode,op_toString[instructions[i].opcode]);

        printf("#%d| %-20s",i,opcodestr);
        print_vmarg(instructions[i].arg1);
        print_vmarg(instructions[i].arg2);
        print_vmarg(instructions[i].result);
        printf("\n");
    }
    printf("====================================================================================================\n");
    printf("  |                     | argv_type,   [value]   | argv_type,   [value]   | argv_type,   [value]   \n\n");
}
