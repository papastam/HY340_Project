#include "../../inc/phase2/utils.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int unnamed_funcs;

char *libFuncs[12] = {"print", "input", "objectmemberkeys", "objecttotalmembers", \
                        "objectcopy", "totalarguments", "argument", "typeof", \
                        "strtonum", "sqrt", "cos", "sin"};


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

    void printSymbol(const struct SymbolTableEntry *printsym) {
        #ifdef P3DEBUG
        printf("Symbol:\nType: %s",symbolTypePrints[printsym->type]);
        #endif
    }

    void printExpression(const struct expr *printexp) {

        #ifdef P3DEBUG
        printf("Expression:\nType = %s\n",exp_type_prints[printexp->type]);
        printSymbol(printexp->sym);
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

