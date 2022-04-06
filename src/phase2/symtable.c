#include "../../inc/phase2/symtable.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


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


struct SymbolTableEntry *SymTable_lookup(SymTable st, const char *name, uint scope) {

    struct SymbolTableEntry *e;


    if ( !(e = st->map[_hash(name)]) )
        return NULL;

    for (; e; e = e->next)
        if ( !strcmp(e->name, name) && (e->scopeno == scope) )
            return e;

    return NULL;
}


int SymTable_insert(SymTable st, const char *name, SymbolType type, uint scope, uint line) {

    struct SymbolTableEntry *e;
    uint hash;


    if ( SymTable_lookup(st, name, scope) ) {

        errno = 0;
        return -(EXIT_FAILURE);
    }

    if ( !(e = (struct SymbolTableEntry *) malloc(sizeof(*e))) )
        return -(EXIT_FAILURE);

    e->active = 1;
    e->name = strdup(name);  // malloc()!
    e->scopeno = scope;
    e->type = type;
    e->line = line;

    hash = _hash(name);
    e->next = st->map[hash];
    st->map[hash] = e;

    return EXIT_SUCCESS;
}


void SymTable_print(SymTable st) {

    struct SymbolTableEntry *e;
    uint64_t index;


    for (index = 0UL; index < BUCKETSNO; ++index) {

        printf("\e[1mmap[%lu]:\e[0m\n", index);

        for (e = st->map[index]; e; e = e->next)
            printf("\t'%s' - %s\e[0m\n\tscope = %d\n\tline = %u\n\n",\
            e->name, e->active ? "\e[1;92mACTIVE" : "\e[1;91mINACTIVE", e->scopeno, e->line);
    }
}


