#include "../../inc/phase2/utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int unnamed_funcs = 0;
int quadno = 1;
FILE* file;

char *exp_type_prints[12] = \
{ 
    "var_e",
    "tableitem_e",
    "programfunc_e",
    "libraryfunc_e",
    "arithexpr_e",
    "boolexpr_e",
    "assignexpr_e",
    "newtable_e",
    "constnum_e",
    "constbool_e",
    "conststring_e",
    "nil_e"
};

char* opcode_prints[26] = \
{
    "assign",
    "add",
    "sub",
    "mul",
    "div_o",
    "mod",
    "uminus",
    "and_o",
    "or_o",
    "not_o",
    "if_eq",
    "if_noteq",
    "if_lesseq",
    "if_greatereq",
    "if_less",
    "if_greater",
    "call",
    "param",
    "ret",
    "getretval",
    "funcstart",
    "funcend",
    "tablecrate",
    "tablegetelem",
    "tablesetelem",
    "jump"
};

char *libFuncs[12] = \
{
    "print", 
    "input", 
    "objectmemberkeys", 
    "objecttotalmembers",
    "objectcopy",
    "totalarguments", 
    "argument", 
    "typeof",
    "strtonum",
    "sqrt", 
    "cos", 
    "sin"
};



struct expr* new_expr(expr_t inputtype) {

    struct expr *ret;


    if ( !(ret = (struct expr *) malloc(sizeof(*ret))) ) {

        printf("tsibos\n");
        exit(EXIT_FAILURE);
    }

    ret->type = inputtype;

    return ret;
}

void printReduction(const char * __restrict__ from,const char * __restrict__ to, int line) {
    #ifdef P2DEBUG
    printf("[#%d] Reduction: %s <--- %s;\n",line, from, to);
    #endif
}

void printExpression(const struct expr *printexp) {

    #ifdef P3DEBUG
    printf("Expression:\nType = %s\n",exp_type_prints[printexp->type]);
    if(printexp->type==var_e){
        printf("Symbol:");
        SymTable_print_elem(printexp->sym);
    }else if(printexp->type==constnum_e)
        printf("Number Value: %f\n",printexp->numConst);
    else if(printexp->type==constbool_e)
        printf("Bool Value: %d\n",printexp->boolConst);
    else if(printexp->type==conststring_e)
        printf("String Value: %s\n",printexp->strConst);
    #endif
}

char *getFuncName(void) {

    char name[18];
    char number[10];
    strcpy(name, "function");
    sprintf(number, "%d", unnamed_funcs++);
    strcat(name, number);

    return strdup(name);
}


int checkIfAllowed(const char *name) {
    for(int i = 0; i < 12; i++) {
        if(!strcmp(libFuncs[i], name)) {
            return 0;
        }
    }
    return 1;
}

struct SymbolTableEntry *search_all_scopes(SymTable st, const char *name, uint scope) {
    
    struct SymbolTableEntry *e=NULL;
    
    for(int i=scope;i>=0;i--){
    
        e = SymTable_lookup_scope(st, name,i);

        if(e){
            return e;
        }
    }

    return NULL;
}

int emit(enum iopcode opcode, struct expr* result, struct expr* arg1, struct expr* arg2) {
    print_in_file(opcode, result, arg1, arg2);
}

void print_in_file(enum iopcode opcode, struct expr* result, struct expr* arg1, struct expr* arg2) {
    //I assume that arg1, arg2 and result have the same type so only one check is needed
    if(arg1->type != constbool_e && arg1->type != constnum_e && arg1->type != conststring_e) {
        fprintf(file, "%-8d%-16s%-16s%-16s%-16s%-6s\n", quadno++, opcode_prints[opcode], result->sym->name, arg1->sym->name, arg2->sym->name, "label");
    }
    else if(arg1->type == constbool_e) {
        fprintf(file, "%-8d%-16s%-16c%-16c%-16c%-6s\n", quadno++, opcode_prints[opcode], result->boolConst, arg1->boolConst, arg2->boolConst, "label");
    }
    else if(arg1->type == constnum_e) {
        fprintf(file, "%-8d%-16s%-16lf%-16lf%-16lf%-6s\n", quadno++, opcode_prints[opcode], result->numConst, arg1->numConst, arg2->numConst, "label");
    }
    else if(arg1->type == conststring_e) {
        fprintf(file, "%-8d%-16s%-16s%-16s%-16s%-6s\n", quadno++, opcode_prints[opcode], result->strConst, arg1->strConst, arg2->strConst, "label");
    }
    
}

FILE* initFile() {
    file = fopen("output.txt", "w");
    int width = fprintf(file, "%-8s%-16s%-16s%-16s%-16s%-6s\n","quad#", "opcode", "result", "arg1", "arg2", "label");
    for(int i = 0; i < width - 1; i++) {
        fprintf(file, "-");
    }
    fprintf(file, "\n");
    return file;
}

