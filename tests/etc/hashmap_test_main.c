#include "../../inc/phase2/symtable.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {

    SymTable st;

    assert( (st = SymTable_create()) );
    printf("insert('print'): %s\n", !SymTable_insert(st, "print", LIBFUNC, 0U, 42U) ? "true" : "false");
    printf("insert('x') - 0s: %s\n", !SymTable_insert(st, "x", GLOBAL, 0U, 4U) ? "true" : "false");
    printf("insert('y') - 0s: %s\n", !SymTable_insert(st, "y", GLOBAL, 0U, 5U) ? "true" : "false");
    printf("insert('y') - 1s: %s\n", !SymTable_insert(st, "index", LOCAL, 1U, 18U) ? "true" : "false");
    printf("insert('index') - 2s: %s\n", !SymTable_insert(st, "index", FORMAL, 2U, 58U) ? "true" : "false");
    printf("insert('y') - 2s: %s\n", !SymTable_insert(st, "y", LOCAL, 2U, 109U) ? "true" : "false");
    printf("insert('userfunc') - 2s: %s\n", !SymTable_insert(st, "userfunc", USERFUNC, 2U, 124U, "x", "y", "z", NULL) ? "true" : "false");

    printf("--- lookup() ---\n");
    printf("'index' - LOCAL ---> %s\n", SymTable_lookup_scope(st, "index", 1U) ? "true" : "false");
    printf("'index' - FORMAL ---> %s\n", SymTable_lookup_scope(st, "index", 2U) ? "true" : "false");
    printf("'index' - GLOBAL ---> %s\n", SymTable_lookup_scope(st, "index", 0U) ? "true" : "false");
    printf("'x' - FORMAL ---> %s\n", SymTable_lookup_scope(st, "x", FORMAL) ? "true" : "false");
    printf("'input' - LIBFUNC ---> %s\n", SymTable_lookup_scope(st, "input", 0U) ? "true" : "false");
    printf("'print' - LIBFUNC ---> %s\n", SymTable_lookup_scope(st, "print", 0U) ? "true" : "false");

    SymTable_hide(st, 0U);

    SymTable_print(st);
    return 0;
}


