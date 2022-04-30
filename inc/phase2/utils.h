#ifndef CS340_PROJECT_P2UTILS_H
#define CS340_PROJECT_P2UTILS_H

#include "../phase3/quads.h"

// #define P2DEBUG

extern char *libFuncs[12];


struct expr* new_expr(expr_t inputtype);
void printReduction(const char * __restrict__ from, const char * __restrict__ to, int line);
void printSymbol(const struct SymbolTableEntry *printsym);
void printExpression(const struct expr *printexp);
char* getFuncName(void);
int checkIfAllowed(const char *name);
struct SymbolTableEntry *search_all_scopes(SymTable st, const char *name, uint scope);


#endif  /* CS340_PROJECT_P2UTILS_H */