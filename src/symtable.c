#include "symtable.h"

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


#define HASH_MULTIPLIER  65599U
#define BUCKETSNO        509U
#define MAXSCOPE         64U


static char *_printable_symbol_type(enum SymbolType type) {

    switch ( type ) {

        case GLOBAL:
            return "GLOBAL";

        case LOCAL:
            return "LOCAL";

        case FORMAL:
            return "FORMAL";

        case USERFUNC:
            return "USERFUNC";

        case LIBFUNC:
            return "LIBFUNC";

        default:
            return "UNKNOWN";
    }
}


static uint _hash(const char *name) {

    // hy255 assignment 3

    uint64_t index;
    uint32_t hash;


    for (index = 0UL, hash = 0UL; name[index]; ++index)
        hash = hash * HASH_MULTIPLIER + name[index];

    return hash % BUCKETSNO;
}

/////////////////////////////////////////////////

SymTable SymTable_create(void) {

    SymTable st;
    uint64_t index;


    if ( !(st = (SymTable) malloc(sizeof(*st))) )
        return NULL;

    st->buckets = BUCKETSNO;

    if ( !(st->map = (struct SymbolTableEntry **) malloc(BUCKETSNO * sizeof(*st->map))) ) {

        free(st);
        return NULL;
    }

    if ( !(st->slink = (struct SymbolTableEntry **) malloc(MAXSCOPE * sizeof(*st->slink))) ) {

        free(st->map);
        free(st);

        return NULL;
    }

    // init() hashmap
    for (index = 0UL; index < BUCKETSNO; ++index)
        st->map[index] = NULL;

    // init() scope lists
    for (index = 0UL; index < MAXSCOPE; ++index)
        st->slink[index] = NULL;

    SymTable_insert(st, "print", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "input", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "objectmemberkeys", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "objecttotalmembers", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "objectcopy", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "totalarguments", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "argument", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "typeof", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "strtonum", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "sqrt", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "cos", LIBFUNC, 0U, 0U);
    SymTable_insert(st, "sin", LIBFUNC, 0U, 0U);


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
            if(e->active)
                return e;


    return NULL;
}


struct SymbolTableEntry *SymTable_lookup_scope(SymTable st, const char *name, uint scope) {

    struct SymbolTableEntry *e;

    // printf("!!!!!!!!!!!!looking for %s in scope:%d\n",name, scope);
    for (e = st->slink[scope]; e; e = e->nscope)
        if ( !strcmp(e->name, name) )
            if(e->active)
                return e;

    return NULL;
}


struct SymbolTableEntry * SymTable_insert(SymTable st, const char *name, SymbolType type, uint scope, uint line) {

    struct SymbolTableEntry *e;
    uint hash;


    if ( !(e = (struct SymbolTableEntry *) malloc(sizeof(*e))) )
        return NULL;

    e->active = true;
    e->name = strdup(name);  // malloc()!
    e->scopeno = scope;
    e->type = type;
    e->line = line;
    e->farg = NULL;
    
    hash = _hash(name);
    e->next = st->map[hash];
    st->map[hash] = e;

    e->nscope = st->slink[scope];
    st->slink[scope] = e;


    return e;
}


int SymTable_insert_func_arg(SymTable st, const char * __restrict__ func, const char * __restrict__ arg) {

    struct SymbolTableEntry *e;
    struct func_arguments *fa;


    e = st->map[_hash(func)];

    for (; e; e = e->next)
        if ( !strcmp(e->name, func) )
            break;

    if ( !e )
        return -(EXIT_FAILURE);

    if ( !(fa = (struct func_arguments *) malloc(sizeof(*fa))) )
        return -(EXIT_FAILURE);

    fa->name = strdup(arg);
    fa->next = e->farg;
    e->farg = fa;

    return EXIT_SUCCESS;
}


void SymTable_hide(SymTable st, uint scope) {

    struct SymbolTableEntry *e;


    for (e = st->slink[scope]; e; e = e->nscope)
        e->active = false;
}


void SymTable_print_all(SymTable st) {

    struct SymbolTableEntry *e;
    uint64_t index;


    for (index = 0UL; index < BUCKETSNO; ++index) {

        if ( (e = st->map[index]) ) {

            printf("\e[1mmap[%lu]:\e[0m\n", index);

            for (; e; e = e->next) {

                printf("\t'%s' - %s\e[0m\n\tscope = %d\n\tline = %u\n\ttype = %s\n",\
                e->name, e->active ? "\e[1;92mACTIVE" : "\e[1;91mINACTIVE", e->scopeno, e->line,\
                _printable_symbol_type(e->type));

                if ( e->farg ) {

                    struct func_arguments *fa;

                    printf("\targs:");
                    for (fa = e->farg; fa; fa = fa->next)
                        printf(" %s", fa->name);

                    printf("\n");
                }

                printf("\n");
            }
        }
    }
}


void SymTable_print_elem(struct SymbolTableEntry *e) {

    printf("\t'%s' - %s\e[0m\n\tscope = %d\n\tline = %u\n\ttype = %s\n",\
    e->name, e->active ? "\e[1;92mACTIVE" : "\e[1;91mINACTIVE", e->scopeno, e->line,\
    _printable_symbol_type(e->type));

    if ( e->farg ) {

        struct func_arguments *fa;

        printf("\targs:");
        for (fa = e->farg; fa; fa = fa->next)
            printf(" %s", fa->name);

        printf("\n");
    }

    printf("\n");
}


void SymTable_print_scopes(SymTable st) {

    struct SymbolTableEntry *e;
    uint64_t index;


    for (index = 0UL; index < MAXSCOPE; ++index) {

        if ( (e = st->slink[index]) ) {

            printf("\e[1mscope-%lu:\e[0m\n", index);

            for (; e; e = e->nscope) {

                printf("\t'%s' - %s\e[0m\n\tline = %u\n\ttype = %s\n",\
                e->name, e->active ? "\e[1;92mACTIVE" : "\e[1;91mINACTIVE", e->line,\
                _printable_symbol_type(e->type));
            }
        }
    }
}

/** TODO: update() SymTable_destroy(...) */

