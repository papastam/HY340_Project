#include "../../inc/phase2/symtable.h"

#include <stdarg.h>
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

//////////////////////////////////////////

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

    for (index = 0UL; index < BUCKETSNO; ++index)
        st->map[index] = NULL;

    for (index = 0UL; index < MAXSCOPE; ++index)
        st->slink[index] = NULL;

    SymTable_insert(st, "lol", LIBFUNC, 0U, 0U, "dab", NULL);
    SymTable_insert(st, "print", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "input", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "objectmemberkeys", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "objecttotalmembers", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "objectcopy", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "totalarguments", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "argument", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "typeof", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "strtonum", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "sqrt", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "cos", LIBFUNC, 0U, 0U, NULL);
    SymTable_insert(st, "sin", LIBFUNC, 0U, 0U, NULL);


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


struct SymbolTableEntry *SymTable_lookup_scope(SymTable st, const char *name, uint scope) {

    struct SymbolTableEntry *e;


    e = st->slink[scope];

    for (; e; e = e->nscope)
        if ( !strcmp(e->name, name) )
            return e;

    return NULL;
}


int SymTable_insert(SymTable st, const char *name, SymbolType type, uint scope, uint line, ...) {

    struct SymbolTableEntry *e;
    uint hash;


    if ( (e = SymTable_lookup_scope(st, name, scope)) ) {

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

    if ( !st->slink[scope] ) {

        st->slink[scope] = e;
        e->nscope = NULL;
    }
    else {

        e->nscope = st->slink[scope];
        st->slink[scope] = e;
    }

    if ( (type == LIBFUNC) || (type == USERFUNC) ) {

        struct func_arguments *fa;
        const char *t;
        va_list vargs;


        va_start(vargs, line);

        if ( !(t = va_arg(vargs, typeof(fa->name))) )
            return EXIT_SUCCESS;

        if ( !(e->farg = (typeof(e->farg)) malloc(sizeof(*e->farg))) ) {

            /** TODO: real error handling */

            perror("malloc()");
            exit(EXIT_FAILURE);
        }

        fa = e->farg;
        fa->name = strdup(t);

        while ( (t = va_arg(vargs, typeof(fa->name))) ) {

            if ( !(fa->next = (typeof(fa->next)) malloc(sizeof(*fa->next))) ) {

                /** TODO: real error handling */

                perror("malloc()");
                exit(EXIT_FAILURE);
            }

            fa = fa->next;
            fa->name = strdup(t);
        }

        fa->next = NULL;
        va_end(vargs);
    }
    else
        e->farg = NULL;


    return EXIT_SUCCESS;
}


void SymTable_print(SymTable st) {

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


