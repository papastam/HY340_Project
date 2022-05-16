#include "utils.h"
#include "quads.h"
#include "stack.h"

#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>


int unnamed_funcs = 0;
FILE* file;
int tempno = -1;
extern SymTable st;

uint scope = 0;
struct quad *quads;
unsigned int total=0;
unsigned int currQuad=0; //einai to quad sto opoio tha ginei to EPOMENO emit

extern int yylineno;
extern int produce_icode;

unsigned int programVarOff;
unsigned int functionLocalOff;
unsigned int formalArgOff;
unsigned int scopeSpaceCounter = 1U;

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
    "tablecreate",
    "tablegetelem",
    "tablesetelem",
    "jump"
};

#define TOTAL_LIB_FUNCS 12
char *libFuncs[TOTAL_LIB_FUNCS] = \
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
void printReduction(const char * restrict from,const char * restrict to, int line) {
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
    // if(label)
        fprintf(file, "%-6u\n", label);
    // else
    //     fprintf(file, "%-6s\n", "");
    
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
    if(opcode == if_eq || opcode == if_greater || opcode == if_greatereq || opcode == if_less || opcode == if_lesseq || opcode == if_noteq || opcode == and_o || opcode == or_o) {
        fprintf(file, "%-8d%-32s", itteration, opcode_prints[opcode]);
        print_expr_helper(arg1);
        print_expr_helper(arg2);
        print_label_helper(label);
        return;
    }
    if(opcode == getretval) {
        fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
        print_expr_helper(result);
        fprintf(file, "\n");
        return;
    }
    if(opcode == param || opcode == call || opcode == funcstart || opcode == funcend || opcode == ret) {
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
    if(opcode ==  add || opcode == sub || opcode == mul || opcode == div_o || opcode == mod || opcode == tablecreate || opcode == tablegetelem || opcode == tablesetelem) {
        fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
        print_expr_helper(result);
        print_expr_helper(arg1);
        print_expr_helper(arg2);
        fprintf(file, "\n");
    }
    //UNIMPLEMENTED: and_o, or_o
}

/**
 * @brief Function used to print all quads to the output file
 * 
 */
void print_quads()
{
    for (int i = 0; i < currQuad; ++i) {
        print_in_file(i, quads[i].op, quads[i].result, quads[i].arg1, quads[i].arg2, quads[i].label);
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

/**
 * @brief 
 * 
 * @param line 
 * @param errformat 
 * @param ... 
 * @return noreturn 
 */
void print_static_analysis_error(int line, const char *errformat, ...)
{
    #define error_msg "\e[1;91merror\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "

    va_list print_args;

    va_start(print_args, errformat);

    fprintf(stdout, error_msg, line);
    fprintf(stdout, errformat, print_args);

    va_end(print_args);

    produce_icode = 0;

    // cleanup_all();
    // exit(EXIT_FAILURE); //Dont exit!! On syntax error the analysis doesnt stop, only the output is not written
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

        printf("malloc error\n");
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
char* newtempname()
{
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
struct SymbolTableEntry* newtemp()
{
    char *name = newtempname();
    struct SymbolTableEntry* temp = SymTable_lookup_scope(st, name, scope);


    if ( !temp )
        temp = SymTable_insert(st, name, LOCAL, scope, yylineno);

    return temp;
}

/**
 * @brief reset temp counter
 * 
 */ 
inline void resettemp() {
    tempno = -1;
}

/**
 * @brief create a new bool expression
 * 
 * @param input 
 * @return struct expr* 
 */
struct expr* newexpr_constbool(unsigned input)
{
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
struct expr* newexpr_constnum(double input)
{
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
struct expr* newexpr_conststr(const char *input)
{
    struct expr *ret = new_expr(conststring_e);

    ret->strConst = strdup(input);
    return ret;
}

int istempexpr(struct expr *input)
{
    return input->sym && *(input->sym->name) == '_';
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
void patch_label(unsigned quad, unsigned label)
{
    quads[quad].label = label;
}

void make_stmt(struct stmt_t **s) {
    *s = (struct stmt_t*)malloc(sizeof(struct stmt_t));
    (*s)->breaklist = (*s)->contlist = 0;
}

int newlist (int i) {
    quads[i].label = 0;
    return i;
}

int mergelist(int l1, int l2) {
    if (!l1)
        return l2;    
    else if (!l2)
        return l1;
    else {
        int i = l1;
        while(quads[i].label)
            i = quads[i].label;
        quads[i].label = l2;
        return l1;
    }
}

void patchlist (int list, int label) {
    while(list) {
        int next = quads[list].label;
        quads[list].label = label;
        list = next;
    }
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
struct expr* member_item(struct expr * restrict lvalue, struct expr * restrict index)
{
    struct expr *ti = new_expr(tableitem_e);

    lvalue = emit_iftableitem(lvalue);
    ti->sym = lvalue->sym;
    ti->strConst = lvalue->strConst;

    if ( index->type != constnum_e )
        ti->index = newexpr_conststr(index->strConst);
    else {

        char tbuf[10];

        sprintf(tbuf, "%d", (int)(index->numConst));
        ti->index = newexpr_conststr(tbuf);
    }

    return ti;
}

/**
 * @brief emit a tablegetitem quad if needed
 * 
 * @param e 
 * @return struct expr* 
 */
struct expr* emit_iftableitem(struct expr *e)
{

    if ( e->type != tableitem_e )
        return e;

    struct expr *res = new_expr(var_e);

    res->sym = newtemp();
    emit(tablegetelem, res, e, e->index, 0);

    return res;
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

unsigned int getNextQuad()
{
    return currQuad;
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
struct expr* true_evaluation(struct expr* input) {

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
int checkIfAllowed(const char *name)
{
    for (int i = 0; i < TOTAL_LIB_FUNCS; ++i)
        if ( !strcmp(libFuncs[i], name) )
            return 0;

    return 1;
}

/**
 * @brief check if a expression is an arithmetic expression
 * 
 * @param input 
 * @return int 
 */
int arithexpr_check(struct expr *input)
{
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

/* scopespace_t curr_scope_space(void)
{
    if ( scopeSpaceCounter == 1U )
        return programvar;

    if ( !(scopeSpaceCounter % 2) )
        return formalarg;

    return functionlocal;
}

unsigned int curr_scope_off(void)
{
    switch ( curr_scope_space() ) {

        case programvar:
            return programVarOff;

        case functionlocal:
            return functionLocalOff;

        case formalarg:
            return formalArgOff;

        default:
            assert(0);
    }
}

void inc_curr_scope_off(void)
{
    switch ( curr_scope_space() ) {

        case programvar:

            ++programVarOff;
            break;

        case functionlocal:

            ++functionLocalOff;
            break;

        case formalarg:

            ++formalArgOff;
            break;

        default:
            assert(0);
    }
}

void enter_scope_space(void)
{
    ++scopeSpaceCounter;
}

void exit_scope_space(void)
{
    assert( scopeSpaceCounter > 1U );
    --scopeSpaceCounter;
} */