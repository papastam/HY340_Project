#include "../../inc/phase2/utils.h"
#include "../../inc/phase3/quads.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int unnamed_funcs = 0;
FILE* file;
int tempno = -1;
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



//--------------------------------------------------------------------------
//----------------------------------PRINTS----------------------------------
//--------------------------------------------------------------------------

/**
 * @brief Debug function used in Phase 2 to print every reduction as it happens
 * 
 * @param from 
 * @param to 
 * @param line 
 */
void printReduction(const char * __restrict__ from,const char * __restrict__ to, int line) {
    #ifdef P2DEBUG
    printf("[#%d] Reduction: %s <--- %s;\n",line, from, to);
    #endif
}

/**
 * @brief Print a single expression in the terminal
 * 
 * @param printexp 
 */
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

/**
 * @brief Helper function for print_in_file to print the contents of the expression based on its type
 * 
 * @param expr 
 */
void print_expr_helper(struct expr* expr) {
    if(!expr) {
        fprintf(file, "%-16s", "");
        return;
    }
    else if(expr->type == nil_e) {

        fprintf(file, "%-16s", "");
        return;
    }
    
    switch(expr->type) {
        case constbool_e :
            fprintf(file, "%-16s", expr->boolConst ? "TRUE" : "FALSE");
            break;
        case constnum_e :
            fprintf(file, "%-16lf", expr->numConst);
            break;
        case conststring_e :
            fprintf(file, "%-16s", expr->strConst);
            break;
        default :
            fprintf(file, "%-16s", expr->sym->name);
            break;
    }
}

/**
 * @brief Helper function for print_in_file
 * 
 * @param label 
 */
void print_label_helper(uint label) {
    if(label)
        fprintf(file, "%-6u\n", label);
    else
        fprintf(file, "%-6s\n", "");
    
}

/**
 * @brief Print function used to print the quads based on their opcode 
 * 
 * @param itteration 
 * @param opcode 
 * @param result 
 * @param arg1 
 * @param arg2 
 * @param label 
 */
void print_in_file(int itteration, enum iopcode opcode, struct expr* result, struct expr* arg1, struct expr* arg2, unsigned label) {
    if(opcode == jump) {
        fprintf(file, "%-8d%-64s%-6u\n", itteration, opcode_prints[opcode], label);
        return;
    }
    if(opcode == assign) {
        fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
        print_expr_helper(result);
        print_expr_helper(arg1);
        fprintf(file, "\n");
        return;
    }
    if(opcode == if_eq || opcode == if_greater || opcode == if_greatereq || opcode == if_less || opcode == if_lesseq || opcode == if_noteq) {
        fprintf(file, "%-8d%-32s", itteration, opcode_prints[opcode]);
        print_expr_helper(arg1);
        print_expr_helper(arg2);
        print_label_helper(label);
        return;
    }
    if(opcode == funcstart || opcode == getretval) {
        fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
        print_expr_helper(result);
        fprintf(file, "\n");
        return;
    }
    if(opcode == tablecreate || opcode == param || opcode == call || opcode == funcstart || opcode == funcend || opcode == ret) {
        fprintf(file, "%-8d%-32s", itteration, opcode_prints[opcode]);
        print_expr_helper(arg1);
        fprintf(file, "\n");
        return;
    }
    if(opcode == uminus || opcode == not_o) {
        fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
        print_expr_helper(result);
        print_expr_helper(arg1);
        fprintf(file, "\n");
        return;
    }
    

    //general case
    fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
    print_expr_helper(result);
    print_expr_helper(arg1);
    print_expr_helper(arg2);
    print_label_helper(label);
}

/**
 * @brief Function used to print all quads to the output file
 * 
 */
void print_quads() {
    for(int i = 0; i < currQuad; i++) {
        print_in_file(i+1,quads[i].op, quads[i].result, quads[i].arg1, quads[i].arg2, quads[i].label);
    }
}

/**
 * @brief Initialize the output file
 * 
 * @return FILE* 
 */
FILE* initFile() {
    file = fopen("output.txt", "w");
    int width = fprintf(file, "%-8s%-16s%-16s%-16s%-16s%-6s\n","quad#", "opcode", "result", "arg1", "arg2", "label");
    for(int i = 0; i < width - 1; i++) {
        fprintf(file, "-");
    }
    fprintf(file, "\n");
    return file;
}

/**
 * @brief Debug function used to print expression lists
 * 
 * @param start 
 */
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









//--------------------------------------------------------------------------
//-------------------------------SYMBOL TABLE-------------------------------
//--------------------------------------------------------------------------

/**
 * @brief search a symbol in all scopes from the current scope
 * 
 * @param st 
 * @param name 
 * @param scope 
 * @return struct SymbolTableEntry* 
 */
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

/**
 * @brief get the next available function name for unnamed functions 
 * 
 * @return char* 
 */
char *getFuncName(void) {

    char name[18];
    char number[10];
    strcpy(name, "function");
    sprintf(number, "%d", unnamed_funcs++);
    strcat(name, number);
    return strdup(name);
}

/**
 * @brief check if the given name is a library function
 * 
 * @param name 
 * @return int 
 */
int checkIfAllowed(const char *name) {
    for(int i = 0; i < 12; i++) {
        if(!strcmp(libFuncs[i], name)) {
            return 0;
        }
    }
    return 1;
}








//--------------------------------------------------------------------------
//-------------------------------EXPRESSIONS--------------------------------
//--------------------------------------------------------------------------

/**
 * @brief create a new expression
 * 
 * @param inputtype 
 * @return struct expr* 
 */
struct expr* new_expr(expr_t inputtype) {

    struct expr *ret;


    if ( !(ret = (struct expr *) malloc(sizeof(*ret))) ) {

        printf("tsibos\n");
        exit(EXIT_FAILURE);
    }

    ret->type = inputtype;

    return ret;
}

/**
 * @brief get the next available temp variable name
 * 
 * @return char* 
 */
char* newtempname() {

    // _txx --> up to 99 temp variables + 4-chars only + \0

    char *final = malloc(5UL);

    sprintf(final, "_t%d", ++tempno);
    return final;
}

/**
 * @brief get a new temp variable
 * 
 * @return struct SymbolTableEntry* 
 */
struct SymbolTableEntry* newtemp(){
    char *name = newtempname();
    struct SymbolTableEntry* temp =  SymTable_lookup_scope(st,name,scope);
    if(!temp){
        temp = SymTable_insert(st,name,LOCAL,scope,yylineno);
    }
    return temp;
}

/**
 * @brief reset temp counter
 * 
 */
void resettemp() {
    tempno = -1;
}

/**
 * @brief create a new bool expression
 * 
 * @param input 
 * @return struct expr* 
 */
struct expr* newexpr_constbool(unsigned input){
    struct expr* ret = new_expr(constbool_e);
    ret->boolConst = input;
    return ret;
}

/**
 * @brief create a new num expression
 * 
 * @param input 
 * @return struct expr* 
 */
struct expr* newexpr_constnum(unsigned input){
    struct expr *ret = new_expr(constnum_e);
    ret->numConst = input;
    return ret;
}

/**
 * @brief create a new string expression
 * 
 * @param input 
 * @return struct expr* 
 */
struct expr* newexpr_conststr(const char* input){
    struct expr *ret = new_expr(conststring_e);
    ret->strConst = strdup(input);
    return ret;
}











//--------------------------------------------------------------------------
//-----------------------------------QUADS----------------------------------
//--------------------------------------------------------------------------

/**
 * @brief emit a new quad to the quads list
 * 
 * @param opcode 
 * @param result 
 * @param arg1 
 * @param arg2 
 * @param label 
 * @return int 
 */
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

    return ++currQuad;
}

/**
 * @brief expand the quads table
 * 
 */
void expand_quad_table(){
    quads = realloc(quads,NEW_SIZE);
    total+=EXPAND_SIZE;
}

/**
 * @brief patch a specific quad with a given label
 * 
 * @param quad 
 * @param label 
 */
void patch_label(unsigned quad, unsigned label){
    quads[quad].label=label;
}











//--------------------------------------------------------------------------
//----------------------------------TABLES----------------------------------
//--------------------------------------------------------------------------

/**
 * @brief create a tableitem expression for a table item
 * 
 * @param lvalue 
 * @param name 
 * @return struct expr* 
 */
struct expr* member_item(struct expr* lvalue,struct expr* name){
    lvalue = emit_iftableitem(lvalue);
    struct expr* ti = new_expr(tableitem_e);
    ti->sym = lvalue->sym;
    ti->index = newexpr_conststr(name->strConst);
    return ti;
}

/**
 * @brief emit a tablegetitem quad if needed
 * 
 * @param e 
 * @return struct expr* 
 */
struct expr* emit_iftableitem(struct expr* e){
    if(e->type!= tableitem_e){
        return e;
    }else{
        struct expr* res = new_expr(var_e);
        res->sym = newtemp();
        emit(tablegetelem,res,e,e->index,0);
        return res;
    }

}

/**
 * @brief lookup a table and add it if it does not exist
 * 
 * @param st 
 * @param name 
 * @param scope 
 * @return struct SymbolTableEntry* 
 */
struct SymbolTableEntry* table_lookupandadd(SymTable st, char* name, int scope){
    struct SymbolTableEntry *e=search_all_scopes(st, name,scope);

    if(!e){
        struct SymbolTableEntry *new = SymTable_insert(st, name, (scope?LOCAL:GLOBAL), scope, yylineno);
        #ifdef P2DEBUG
        printf("\033[0;32mSuccess [#%d]:\033[0m Symbol %s has been added to the symbol table\n", yylineno, name);
        #endif
        return new;
    }else if(e->type==LOCAL && e->scopeno!=scope){
        #ifdef P2DEBUG
        printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s cannot be accessed from scope %d\n", yylineno, name, scope);
        #endif
    }else if(e->type==FORMAL && e->scopeno!=scope){
        #ifdef P2DEBUG
        printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s cannot be accessed from scope %d\n", yylineno, name,scope);
        #endif
    }else if(e->type==USERFUNC || e->type==LIBFUNC){
        #ifdef P2DEBUG
        printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s is defined as a function\n", yylineno ,name);
        #endif
    }else{//SUCESS CASE!
        return e;
        // printExpression($$);
    }

    return NULL;
}











//--------------------------------------------------------------------------
//--------------------------------FUNCTIONS---------------------------------
//--------------------------------------------------------------------------

/**
 * @brief Used to emmit the quads for a function call
 * 
 * @param lvalue 
 * @param reversed_elist 
 * @return struct expr* 
 */
struct expr* make_call(struct expr* lvalue,struct expr* reversed_elist){
    struct expr* func = emit_iftableitem(lvalue);
    while(reversed_elist){
        emit(param,NULL,reversed_elist,NULL,0);
        reversed_elist=reversed_elist->next;
    }
    emit(call,NULL,func,NULL,0);
    struct expr* result = new_expr(var_e);
    result->sym = newtemp();
    emit(getretval,result,NULL,NULL,0);
    return result;
}










//--------------------------------------------------------------------------
//----------------------------------MISC------------------------------------
//--------------------------------------------------------------------------

/**
 * @brief evaluate an expression
 * 
 * @param input 
 * @return struct expr* 
 */
struct expr* true_evaluation(struct expr* input){
    struct expr* ret = NULL;
    if(input->type == programfunc_e || input->type == libraryfunc_e || input->type == tableitem_e) {
        ret = newexpr_constbool(1);
    }
    else if(input->type == nil_e) {
        ret = newexpr_constbool(0);
    }

    if(input->type == constnum_e) {
        ret = (input->numConst ? newexpr_constbool(1) : newexpr_constbool(0));
    }
    if(input->type == conststring_e) {
        if(!strcmp(input->strConst, ""))
            ret = newexpr_constbool(0);
        else  
            ret = newexpr_constbool(1);
    }
}

/**
 * @brief check if a expression is an arithmetic expression
 * 
 * @param input 
 * @return int 
 */
int arithexpr_check(struct expr* input){
    if( input->type == constbool_e ||
        input->type == conststring_e ||
        input->type == nil_e ||
        input->type == newtable_e ||
        input->type == programfunc_e ||
        input->type == libraryfunc_e ||
        input->type == boolexpr_e)
        return 0;
    
    return 1;
}