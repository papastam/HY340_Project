#ifndef CS340_PROJECT_P2UTILS_H
#define CS340_PROJECT_P2UTILS_H

#include "../phase3/quads.h"

#include <stdio.h>

#define P3DEBUG
// #define P2DEBUG

extern char *libFuncs[12];


struct expr* new_expr(expr_t inputtype);
void printReduction(const char * __restrict__ from, const char * __restrict__ to, int line);
void printExpression(const struct expr *printexp);
char* getFuncName(void);
int checkIfAllowed(const char *name);
struct SymbolTableEntry *search_all_scopes(SymTable st, const char *name, uint scope);
void print_in_file(int itteration, enum iopcode opcode, struct expr* result, struct expr* arg1, struct expr* arg2, unsigned label);
FILE* initFile();

int emit(enum iopcode opcode, struct expr* result, struct expr* arg1, struct expr* arg2,uint label);
void expand_quad_table();

char* newtempname();
struct SymbolTableEntry* newtemp();
void resettemp();
int istempexpr(struct expr* input);

void print_elist(struct expr* start);
void print_quads_term();
extern void print_quads();

void patch_label(unsigned quad, unsigned label);

struct expr* true_evaluation(struct expr* input);
int arithexpr_check(struct expr* input);

struct expr* newexpr_constbool(unsigned input);
struct expr* newexpr_constnum(double input);
struct expr* newexpr_conststr(const char* input);

struct expr* member_item(struct expr* lvalue,struct expr* name);
struct expr* emit_iftableitem(struct expr* e);

struct SymbolTableEntry* table_lookupandadd(SymTable st, char* name, int scope);

struct expr* make_call(struct expr* lvalue,struct expr* reversed_elist);

#endif  /* CS340_PROJECT_P2UTILS_H */