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
int emit(enum iopcode, struct expr* result, struct expr* arg1, struct expr* arg2);
void print_in_file(enum iopcode, struct expr* result, struct expr* arg1, struct expr* arg2);
FILE* initFile();


#endif  /* CS340_PROJECT_P2UTILS_H */