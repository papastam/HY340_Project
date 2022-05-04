#include "../../inc/phase2/utils.h"
#include "../../inc/phase3/quads.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int unnamed_funcs = 0;
FILE* file;
int tempno = 0;
extern SymTable st;

uint scope = 0;
struct quad *quads;
unsigned int total=0;
unsigned int currQuad=0;

extern int yylineno;

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
    if(printexp->type==var_e || printexp->type==arithexpr_e){
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

void expand_quad_table(){
    quads = realloc(quads,NEW_SIZE);
    total+=EXPAND_SIZE;
}

int emit(enum iopcode opcode, struct expr* result, struct expr* arg1, struct expr* arg2,uint label) {
    // print_in_file(opcode, result, arg1, arg2);
    if(currQuad==total){
        expand_quad_table();
    }
    quads[currQuad].op=opcode;
    quads[currQuad].result=result;
    quads[currQuad].arg1=arg1;
    quads[currQuad].arg2=arg2;
    quads[currQuad].label=label;
    quads[currQuad].line=yylineno;

    return currQuad++;
}

void print_in_file(enum iopcode opcode, struct expr* result, struct expr* arg1, struct expr* arg2, unsigned label) {
    //I assume that arg1, arg2 and result have the same type so only one check is needed
    if(arg1->type != constbool_e && arg1->type != constnum_e && arg1->type != conststring_e) {
        fprintf(file, "%-8d%-16s%-16s%-16s%-16s%-6u\n", currQuad++, opcode_prints[opcode], result->sym->name, arg1->sym->name, arg2->sym->name, label);
    }
    else if(arg1->type == constbool_e) {
        fprintf(file, "%-8d%-16s%-16c%-16c%-16c%-6u\n", currQuad++, opcode_prints[opcode], result->boolConst, arg1->boolConst, arg2->boolConst, label);
    }
    else if(arg1->type == constnum_e) {
        fprintf(file, "%-8d%-16s%-16lf%-16lf%-16lf%-6u\n", currQuad++, opcode_prints[opcode], result->numConst, arg1->numConst, arg2->numConst, label);
    }
    else if(arg1->type == conststring_e) {
        fprintf(file, "%-8d%-16s%-16s%-16s%-16s%-6u\n", currQuad++, opcode_prints[opcode], result->strConst, arg1->strConst, arg2->strConst, label);
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

char* newtempname() {
    char name[10];
    char number[8];
    strcpy(name, "_t");
    sprintf(number, "%d", tempno++);
    strcat(name, number);
    return strdup(name);
}

struct SymbolTableEntry* newtemp(){
    char *name = newtempname();
    struct SymbolTableEntry* temp =  SymTable_lookup_scope(st,name,scope);
    if(!temp){
        temp = SymTable_insert(st,name,LOCAL,scope,yylineno);
    }
    return temp;
}

void resettemp() {
    tempno = 0;
}

//DEBUG
void print_elist(struct expr* start){
    struct expr* itter = start;
    int i=0;
    #ifdef P3DEBUG
    printf("--------Expression list:--------\n");
    while(itter){
        printf("--------#%d--------\n",i);
        printExpression(itter);
        itter=itter->next;
        ++i;
    }
    #endif
}

void print_quads() {
    for(int i = 0; i < total; i++) {
        print_in_file(quads[i].op, quads[i].result, quads[i].arg1, quads[i].arg2, quads[i].label);
    }
}

struct expr* newexpr_constbool(unsigned input){
    //TODO
}

struct expr* newexpr_constnum(unsigned input){
    //TODO
}

struct expr* newexpr_conststr(char* input){
    //TODO
}

//TODO: print jump and other opcodes differently
void print_quads_term() {
    printf("\n-------------------------------QUADS: (total:%d)-------------------------------\n",currQuad);
    printf("%-8s%-16s%-16s%-16s%-16s%-6s\n","quad#", "opcode", "result", "arg1", "arg2", "label");
    for(int i = 0; i < currQuad; i++) {
        if(quads[i].label == 0) {

            //I assume that arg1, arg2 and result have the same type so only one check is needed
            if(quads[i].arg1->type != constbool_e && quads[i].arg1->type != constnum_e && quads[i].arg1->type != conststring_e) {
                printf("%-8d%-16s%-16s%-16s%-16s\n", i++, opcode_prints[quads[i].op], quads[i].result->sym->name, quads[i].arg1->sym->name, quads[i].arg2->sym->name);
            }
            else if(quads[i].arg1->type == constbool_e) {
                printf("%-8d%-16s%-16c%-16c%-16c\n", i++, opcode_prints[quads[i].op], quads[i].result->boolConst, quads[i].arg1->boolConst, quads[i].arg2->boolConst);
            }
            else if(quads[i].arg1->type == constnum_e) {
                printf("%-8d%-16s%-16lf%-16lf%-16lf\n", i++, opcode_prints[quads[i].op], quads[i].result->numConst, quads[i].arg1->numConst, quads[i].arg2->numConst);
            }
            else if(quads[i].arg1->type == conststring_e) {
                printf("%-8d%-16s%-16s%-16s%-16s\n", i++, opcode_prints[quads[i].op], quads[i].result->strConst, quads[i].arg1->strConst, quads[i].arg2->strConst);
            }
        }
        else {
            if(quads[i].arg1->type != constbool_e && quads[i].arg1->type != constnum_e && quads[i].arg1->type != conststring_e) {
                printf("%-8d%-16s%-16s%-16s%-16s%-6u\n", i++, opcode_prints[quads[i].op], quads[i].result->sym->name, quads[i].arg1->sym->name, quads[i].arg2->sym->name, quads[i].label);
            }
            else if(quads[i].arg1->type == constbool_e) {
                printf("%-8d%-16s%-16c%-16c%-16c%-6u\n", i++, opcode_prints[quads[i].op], quads[i].result->boolConst, quads[i].arg1->boolConst, quads[i].arg2->boolConst, quads[i].label);
            }
            else if(quads[i].arg1->type == constnum_e) {
                printf("%-8d%-16s%-16lf%-16lf%-16lf%-6u\n", i++, opcode_prints[quads[i].op], quads[i].result->numConst, quads[i].arg1->numConst, quads[i].arg2->numConst, quads[i].label);
            }
            else if(quads[i].arg1->type == conststring_e) {
                printf("%-8d%-16s%-16s%-16s%-16s%-6u\n", i++, opcode_prints[quads[i].op], quads[i].result->strConst, quads[i].arg1->strConst, quads[i].arg2->strConst, quads[i].label);
            }
        }
    }
}