#ifndef CS340_PROJECT_UTILS_H
#define CS340_PROJECT_UTILS_H

#include "quads.h"
#include <stdio.h>

#define P3DEBUG
// #define P2DEBUG

extern char *libFuncs[12];


struct expr * newexpr(expr_t inputtype);
void printReduction(const char * restrict from, const char * restrict to, int line);
void printExpression(const struct expr * printexp);
char * getFuncName(void);
int checkIfAllowed(const char * name);
struct SymbolTableEntry * search_all_scopes(SymTable restrict st, const char * restrict name, uint scope);
void print_in_file(int itteration, enum iopcode opcode, struct expr * restrict result, struct expr * restrict arg1, struct expr * restrict arg2, uint label);
void print_static_analysis_error(int line, const char * errformat, ...);


FILE * initFile(void);

int emit(enum iopcode opcode, struct expr * restrict result, struct expr * restrict arg1, struct expr * restrict arg2, uint label);
void expand_quad_table(void);

char * newtempname(void);
struct SymbolTableEntry * newtemp(void);
void resettemp(void);
int istempexpr(struct expr * input);
int istempname(struct SymbolTableEntry* sym);

void print_elist(struct expr * start);
void print_quads_term(void);
void print_quads(void);
uint getNextQuad(void);

void patch_label(uint quad, uint label);

int arithexpr_check(struct expr * input);

struct expr * newexpr_constbool(uint input);
struct expr * newexpr_constnum(double input);
struct expr * newexpr_conststr(const char * input);

struct expr * member_item(struct expr * restrict lvalue, struct expr * restrict name);
struct expr * emit_iftableitem(struct expr * e);

struct expr * make_call(struct expr * restrict lvalue, struct expr * restrict reversed_elist);

void make_stmt(struct stmt_t ** s);
int newlist(int i);
int mergelist(int l1, int l2);
void patch_list(int list, int label);
struct quad * quadtable_create(void);

int merge_bool_lists(int l1, int l2);

struct expr * emit_if_eval(struct expr * expression);
struct expr * evaluate(struct expr * expression);
struct expr * convert_to_constbool(struct expr * input);

#endif  /* CS340_PROJECT_UTILS_H */
