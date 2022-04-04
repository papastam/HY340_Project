#include "../../inc/phase2/symtable.h"

#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>


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

    SymTable st;

    if ( !(st = (SymTable) malloc(sizeof(*st))) )
        return NULL;

    st->buckets = BUCKETSNO;

    if ( !(st->map = (struct binding **) malloc(BUCKETSNO * sizeof(struct binding *))) ) {

        free(st);
        return NULL;
    }

    for (uint64_t index = 0UL; index < BUCKETSNO; ++index)
        st->map[index] = NULL;

    return st;
}

void SymTable_destroy(SymTable st) {

    struct binding *cb;  // current binding
    struct binding *pb;  // previous binding

    uint64_t index;

    for (index = 0UL; index < BUCKETSNO; ++index) {

        cb = st->map[index];

        while ( cb ) {

            pb = cb;
            cb = cb->next;

            free(pb->key);  // stupid warnings
            free(pb);
        }
    }

    free(st->map);
    free(st);
}

int SymTable_insert(SymTable st, const char *key, int type, int scope) {

    struct binding *b;
    uint hash;


    if ( !(b = (struct binding *) malloc(sizeof(*b))) )
        return -(EXIT_FAILURE);

    b->active = 0;
    b->key = strdup(key);
    b->scopeno = scope;
    b->type = type;

    hash = _hash(key);
    b->next = st->map[hash];
    st->map[hash] = b;

    return 0;
}

void SymTable_print(SymTable st) {

    //
}


