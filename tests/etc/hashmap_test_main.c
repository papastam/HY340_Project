#include "../../inc/phase2/symtable.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {

    SymTable st;

    assert( (st = SymTable_create()) );
    SymTable_insert(st, "x", GLOBAL, 0U, 4U);
    SymTable_insert(st, "y", GLOBAL, 0U, 5U);
    printf("insert('print'): %s\n", !SymTable_insert(st, "print", LIBFUNC, 0U, 42U) ? "true" : "false");
    SymTable_insert(st, "index", LOCAL, 1U, 18U);
    SymTable_insert(st, "index", FORMAL, 2U, 58U);
    SymTable_insert(st, "y", LOCAL, 2U, 109U);

    printf("--- lookup() ---\n");
    printf("'index' - LOCAL ---> %s\n", SymTable_lookup(st, "index", 1U) ? "true" : "false");
    printf("'index' - FORMAL ---> %s\n", SymTable_lookup(st, "index", 2U) ? "true" : "false");
    printf("'index' - GLOBAL ---> %s\n", SymTable_lookup(st, "index", 0U) ? "true" : "false");
    printf("'x' - FORMAL ---> %s\n", SymTable_lookup(st, "x", FORMAL) ? "true" : "false");
    printf("'input' - LIBFUNC ---> %s\n", SymTable_lookup(st, "input", 0U) ? "true" : "false");
    printf("'print' - LIBFUNC ---> %s\n", SymTable_lookup(st, "print", 0U) ? "true" : "false");



    SymTable_print(st);
    return 0;
}


