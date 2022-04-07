#include "../../inc/phase2/symtable.h"

#include <assert.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char **argv) {

    SymTable st;

    assert( (st = SymTable_create()) );
    
    SymTable_print_scopes(st);
    // SymTable_hide(st, 2U);

    // SymTable_print(st);
    return 0;
}


