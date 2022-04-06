#include "../../inc/phase2/symtable.h"

#include <assert.h>
#include <stdio.h>


int main(int argc, char **argv) {

    SymTable st;

    assert( (st = SymTable_create()) );
    SymTable_insert(st, "x", GLOBAL, 0U, 4U);
    SymTable_insert(st, "y", GLOBAL, 0U, 5U);
    SymTable_insert(st, "print", LIBFUNC, 0U, 42U);
    SymTable_insert(st, "index", LOCAL, 1U, 18U);
    SymTable_insert(st, "index", FORMAL, 2U, 58U);
    SymTable_insert(st, "y", LOCAL, 2U, 109U);

    printf("'index' - LOCAL ---> %s\n", SymTable_lookup(st, "index", LOCAL) ? "true" : "false");
    printf("'index' - FORMAL ---> %s\n", SymTable_lookup(st, "index", FORMAL) ? "true" : "false");
    printf("'index' - GLOBAL ---> %s\n", SymTable_lookup(st, "index", GLOBAL) ? "true" : "false");
    printf("'x' - FORMAL ---> %s\n", SymTable_lookup(st, "index", FORMAL) ? "true" : "false");


    SymTable_print(st);
    return 0;
}

