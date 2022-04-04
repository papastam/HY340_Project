#include "../../inc/phase2/symtable.h"
#include <stdint.h>
#include <sys/types.h>


#define HASH_MULTIPLIER  65599U
#define BUCKETSNO        509U

static uint _hash(const char *key) {

    // hy255 assignment 3

    uint64_t index;
    uint32_t hash;


    for (index = 0UL; key[index]; ++index)
        hash = hash * HASH_MULTIPLIER + key[index];

    return hash % BUCKETSNO;
}

SymTable SymTable_create(void) {

    return NULL;
}

int SymTable_insert(SymTable st, const char *id, int type, int scope) {

    return 0;
}


