#include "../../inc/phase2/symtable.h"

#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>


#define HASH_MULTIPLIER  65599U
#define BUCKETSNO        509U


static uint _hash(const char *name) {

    // hy255 assignment 3

    uint64_t index;
    uint32_t hash;


    for (index = 0UL; name[index]; ++index)
        hash = hash * HASH_MULTIPLIER + name[index];

    return hash % BUCKETSNO;
}

SymTable SymTable_create(void) {

    SymTable st;

    if ( !(st = (SymTable) malloc(sizeof(*st))) )
        return NULL;

    st->buckets = BUCKETSNO;

    if ( !(st->map = (struct SymbolTableEntry **) malloc(BUCKETSNO * sizeof(st->map))) ) {

        free(st);
        return NULL;
    }

    for (uint64_t index = 0UL; index < BUCKETSNO; ++index)
        st->map[index] = NULL;

    return st;
}

void SymTable_destroy(SymTable st) {

    struct SymbolTableEntry *cb;  // current
    struct SymbolTableEntry *pb;  // previous

    uint64_t index;

    for (index = 0UL; index < BUCKETSNO; ++index) {

        cb = st->map[index];

        while ( cb ) {

            pb = cb;
            cb = cb->next;

            free((void *)(pb->name));  // stupid warnings
            free(pb);
        }
    }

    free(st->map);
    free(st);
}

int SymTable_insert(SymTable st, const char *name, SymbolType type, int scope) {

    struct SymbolTableEntry *b;
    uint hash;


    if ( !(b = (struct SymbolTableEntry *) malloc(sizeof(*b))) )
        return -(EXIT_FAILURE);

    b->active = 0;
    b->name = strdup(name);  // malloc()!
    b->scopeno = scope;
    b->type = type;

    hash = _hash(name);
    b->next = st->map[hash];
    st->map[hash] = b;

    return 0;
}

void SymTable_print(SymTable st) {

    //
}


