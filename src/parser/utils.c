#include "utils.h"
#include "quads.h"
#include "target_code_generator.h"
#include "stack.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>


int unnamed_funcs = 0;
FILE * file;
int tempno = -1;
int prog_var_flag;
int offset;
extern SymTable st;

struct quad * quads;

uint scope;
uint total;
uint currQuad = 1U; //einai to quad sto opoio tha ginei to EPOMENO emit

extern int yylineno;
extern int produce_icode;

#define ALPHA_TOTAL_EXPRTYPES 12
char * exp_type_prints[ALPHA_TOTAL_EXPRTYPES] = \
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

#define ALPHA_TOTAL_OPCODES 26
char* opcode_prints[ALPHA_TOTAL_OPCODES] = \
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

#define ALPHA_TOTAL_LIBFUNCS 12
char * libFuncs[ALPHA_TOTAL_LIBFUNCS] = \
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

#define ALPHA_TOTAL_TMPVAR_NAMES 50
char * tmp_var_names[ALPHA_TOTAL_TMPVAR_NAMES] = \
{
    "_t0", "_t1", "_t2", "_t3", "_t4", "_t5", "_t6",
    "_t7", "_t8", "_t9", "_t10", "_t11", "_t12",
    "_t13", "_t14", "_t15", "_t16", "_t17", "_t18",
    "_t19", "_t20", "_t21", "_t22", "_t23", "_t24",
    "_t25", "_t26", "_t27", "_t28", "_t29", "_t30",
    "_t31", "_t32", "_t33", "_t34", "_t35", "_t36",
    "_t37", "_t38", "_t39", "_t40", "_t41", "_t42",
    "_t43", "_t44", "_t45", "_t46", "_t47", "_t48",
    "_t49"
};


//--------------------------------------------------------------------------
//----------------------------------PRINTS----------------------------------
//--------------------------------------------------------------------------

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

        fprintf(file, "%-16s", "NIL");
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
        fprintf(file, "%-6u", label);
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
void print_in_file(int itteration, enum iopcode opcode, struct expr* result, struct expr* arg1, struct expr* arg2, uint label, uint srcline) {
    if(opcode == jump) {
        fprintf(file, "%-8d%-64s%-6u", itteration, opcode_prints[opcode], label);
        
    }
    if(opcode == assign) {
        fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
        print_expr_helper(result);
        print_expr_helper(arg1);
        fprintf(file, "                      ");
        
    }
    if(opcode == if_eq || opcode == if_greater || opcode == if_greatereq || opcode == if_less || opcode == if_lesseq || opcode == if_noteq || opcode == and_o || opcode == or_o) {
        fprintf(file, "%-8d%-32s", itteration, opcode_prints[opcode]);
        print_expr_helper(arg1);
        print_expr_helper(arg2);
        print_label_helper(label);
        
    }
    if(opcode == getretval) {
        fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
        print_expr_helper(result);
        fprintf(file, "                                      ");
        
        
    }
    if(opcode == param || opcode == call || opcode == funcstart || opcode == funcend || opcode == ret) {
        fprintf(file, "%-8d%-32s", itteration, opcode_prints[opcode]);
        print_expr_helper(arg1);
        fprintf(file, "                      ");

        
    }
    if(opcode == uminus || opcode == not_o) {
        fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
        print_expr_helper(result);
        print_expr_helper(arg1);
        fprintf(file, "                      ");        
    }
    if(opcode ==  add || opcode == sub || opcode == mul || opcode == div_o || opcode == mod || opcode == tablecreate || opcode == tablegetelem || opcode == tablesetelem) {
        fprintf(file, "%-8d%-16s", itteration, opcode_prints[opcode]);
        print_expr_helper(result);
        print_expr_helper(arg1);
        print_expr_helper(arg2);
        fprintf(file, "      ");
    }
    fprintf(file, "%-6u\n", srcline);

    //UNIMPLEMENTED: and_o, or_o
}

/**
 * @brief Function used to print all quads to the output file
 * 
 */
void print_quads(void)
{
    for (uint i = 1U; i < currQuad; ++i)
        print_in_file(i, quads[i].op, quads[i].result, quads[i].arg1, quads[i].arg2, quads[i].label, quads[i].line);
}

/**
 * @brief Initialize the output file
 * 
 * @return FILE* 
 */
FILE * initFile(void)
{
    file = fopen("output.txt", "w");
    int width = fprintf(file, "%-8s%-16s%-16s%-16s%-16s%-6s%-6s\n","quad#", "opcode", "result", "arg1", "arg2", "label", "srcline");
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
void print_elist(struct expr * start)
{
    int i = 0;

    printf("--------Expression list:--------\n");

    while ( start ) {

        printf("--------#%d--------\n", i++);
        printExpression(start);
        start = start->next;
    }
}

/**
 * @brief Prints compiler errors
 * 
 * @param line 
 * @param errformat 
 * @param ... 
 * @return noreturn 
 */
void print_static_analysis_error(int line, const char * errformat, ...)
{
    #define error_msg "\e[1;91merror\e[93m::\e[92;1m%d\e[0;1m\e[0m ---> "

    va_list print_args;

    va_start(print_args, errformat);

    printf(error_msg, line);
    vprintf(errformat, print_args);

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
struct expr * newexpr(expr_t inputtype)
{
    struct expr *ret;


    if ( !(ret = (struct expr *) malloc(sizeof(*ret))) ) {

        printf("malloc error\n");
        exit(EXIT_FAILURE);
    }

    memset((void *) ret, 0, sizeof(struct expr));

    ret->type = inputtype;

    if ( inputtype == boolexpr_e ) {

        ret->truelist  = 0U;
        ret->falselist = 0U;
    }

    return ret;
}

/**
 * @brief get the next available temp variable name
 * 
 * @return char* 
 */
char * newtempname(void)
{
    // _txx --> up to 99 temp variables + 4-chars only + \0

    /* char *final = malloc(5UL);

    sprintf(final, "_t%d", ++tempno);
    return final; */

    return tmp_var_names[++tempno];
}

/**
 * @brief get a new temp variable
 * 
 * @return struct SymbolTableEntry* 
 */
struct SymbolTableEntry * newtemp(void)
{
    char * name = newtempname();
    struct SymbolTableEntry * temp = SymTable_lookup_scope(st, name, scope);


    if ( !temp )
        temp = SymTable_insert(st, name, (!prog_var_flag ? GLOBAL : LOCAL), scope, yylineno);

    temp->offset = offset++;

    return temp;
}

/**
 * @brief reset temp counter
 * 
 */ 
void resettemp(void)
{
    tempno = -1;
}

/**
 * @brief create a new bool expression
 * 
 * @param input 
 * @return struct expr* 
 */
struct expr * newexpr_constbool(uint input)
{
    struct expr * ret = newexpr(constbool_e);

    ret->boolConst = input;
    return ret;
}

/**
 * @brief create a new num expression
 * 
 * @param input 
 * @return struct expr* 
 */
struct expr * newexpr_constnum(double input)
{
    struct expr * ret = newexpr(constnum_e);

    ret->numConst = input;
    return ret;
}

/**
 * @brief create a new string expression
 * 
 * @param input 
 * @return struct expr* 
 */
struct expr * newexpr_conststr(const char * input)
{
    struct expr * ret = newexpr(conststring_e);

    ret->strConst = strdup(input);
    return ret;
}

int istempexpr(struct expr * input)
{
    if ( input->type != var_e )
        return 0;
    return istempname(input->sym); 
}

int istempname(struct SymbolTableEntry* sym){
    return *(sym->name) == '_';
}

int merge_bool_lists(int l1, int l2)
{
    assert(l1!=l2 || l1==0);
    if ( !l1 ) 
        return l2;

    if ( !l2 )
        return l1;

    if ( l1 > l2 ) {

        int i = l1;

        while ( quads[i].label )
            i = quads[i].label;

        quads[i].label = l2;

        return l1;

    }
    
    if ( l1 < l2 ) {

        int i = l2;

        while(quads[i].label)
            i = quads[i].label;

        quads[i].label = l1;

        return l2;
    }
}

struct expr* append_elist(struct expr* input, struct expr* list){
    if(!list){
        return input;
    }

    struct expr* itter = list;

    while(itter->next){
        itter = itter->next;
    }

    itter->next = input;

    return list;
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
int emit(enum iopcode opcode, struct expr * restrict result, struct expr * restrict arg1, struct expr * restrict arg2, uint label)
{
    if ( currQuad >= total )
        expand_quad_table();

    //TODO
    // assert(arg1 && arg1->type!=boolexpr_e);
    // assert(arg2 && arg2->type!=boolexpr_e);
    // assert(result && result->type!=boolexpr_e);

    quads[currQuad].op     = opcode;
    quads[currQuad].result = result;
    quads[currQuad].arg1   = arg1;
    quads[currQuad].arg2   = arg2;
    quads[currQuad].label  = label;
    quads[currQuad].line   = yylineno;

    return ++currQuad;
}

struct quad * quadtable_create(void)
{
    return calloc(QUADS_INIT_SIZE, sizeof(struct quad));
}

/**
 * @brief expand the quads table
 * 
 */
void expand_quad_table(void)
{
    quads = realloc(quads, NEW_SIZE);
    total += EXPAND_SIZE;
}

/**
 * @brief patch a specific quad with a given label
 * 
 * @param quad 
 * @param label 
 */
void patch_label(uint quad, uint label)
{
    quads[quad].label = label;
}

void make_stmt(struct stmt_t ** s)
{
    if ( !(*s = (struct stmt_t *) calloc(1UL, sizeof(struct stmt_t))) ) {

        perror("calloc()");
        exit(EXIT_FAILURE);
    }
}

int newlist(int i)
{
    quads[i].label = 0U;
    return i;
}

int mergelist(int l1, int l2)
{
    if ( !l1 )
        return l2;

    if ( !l2 )
        return l1;

    int i = l1;

    while ( quads[i].label )
        i = quads[i].label;

    quads[i].label = l2;


    return l1;
}

void patch_list(int list, int label)
{
    while ( list ) {

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
    struct expr * ti = newexpr(tableitem_e);

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

    struct expr *res = newexpr(var_e);

    res->sym = newtemp();
    res->strConst = (char *)res->sym->name;  // added

    emit(tablegetelem, res, e, e->index, 0U);


    return res;
}


//--------------------------------------------------------------------------
//--------------------------------FUNCTIONS---------------------------------
//--------------------------------------------------------------------------

/**
 * @brief Used to emit the quads for a function call
 * 
 * @param lvalue 
 * @param reversed_elist 
 * @return struct expr* 
 */
struct expr* make_call(struct expr * restrict lvalue, struct expr * restrict reversed_elist)
{
    while ( reversed_elist ) {

        emit(param, NULL, reversed_elist, NULL, 0U);
        reversed_elist = reversed_elist->next;
    }

    emit(call, NULL, emit_iftableitem(lvalue), NULL, 0U);

    struct expr * result = newexpr(var_e);

    result->sym = istempexpr(lvalue) ? lvalue->sym : newtemp();
    emit(getretval, result, NULL, NULL, 0U);


    return result;
}

uint getNextQuad()
{
    return currQuad;
}


//--------------------------------------------------------------------------
//----------------------------------MISC------------------------------------
//--------------------------------------------------------------------------

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
    for (int i = 0; i < ALPHA_TOTAL_LIBFUNCS; ++i)
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

//--------------------------------------------------------------------------
//-----------------------SHORT CIRCUIT EVALUATION---------------------------
//--------------------------------------------------------------------------


struct expr* emit_eval(struct expr *expression)
{
    struct expr *ret = expression;

    expression = evaluate(expression);
    // if ( expression->type == boolexpr_e ) {

    ret = newexpr(var_e);
    ret->sym = newtemp();
    
    patch_list(expression->truelist, getNextQuad());
    patch_list(expression->falselist, getNextQuad() + 2U);
    
    emit(assign, ret, newexpr_constbool(1U), NULL, 0U);
    emit(jump, NULL, NULL, NULL, getNextQuad() + 2U);
    emit(assign, ret, newexpr_constbool(0U), NULL, 0U);
    // }

    return ret;
}

/**
 * @brief evaluate the expression and emit the required quads 
 * 
 * @param input 
 * @return struct expr* (boolexpr_e)
 */
struct expr* evaluate(struct expr* input) {
    if (input->type == boolexpr_e )
        return input;
    
    struct expr* ret = newexpr(boolexpr_e);

    if(input->nottag==1){
        ret->falselist=getNextQuad();
        ret->truelist=getNextQuad()+1;
    }else{
        ret->truelist=getNextQuad();
        ret->falselist=getNextQuad()+1;
    }

    emit(if_eq,NULL,input ,newexpr_constbool(1),0);
    emit(jump,NULL,NULL,NULL,0);

    return ret;
}

/**
 * @brief Convert any given expression into a evaluated constbool
 * 
 * @param input 
 * @return struct expr* 
 */
struct expr * convert_to_constbool(struct expr * input){
    struct expr * eval;

    if(input->type == programfunc_e || input->type == libraryfunc_e || input->type == tableitem_e) {
        eval = newexpr_constbool(1);
    }else if(input->type == nil_e) {
        eval = newexpr_constbool(0);
    }else if(input->type == constnum_e) {
        eval = (input->numConst ? newexpr_constbool(1) : newexpr_constbool(0));
    }else if(input->type == conststring_e) {
        if(!strcmp(input->strConst, ""))
            eval = newexpr_constbool(0);
        else  
            eval = newexpr_constbool(1);
    }else if(input->type == constbool_e){
        eval =  newexpr_constbool(input->boolConst);
    }else{
        eval = newexpr_constbool(0);
    }
    
    return eval;
}
