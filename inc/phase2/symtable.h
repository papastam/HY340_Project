#ifndef SYMTABLE_HASH_H
#define SYMTABLE_HASH_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>


typedef unsigned uint;

struct func_arguments {

    const char *name;
    struct func_arguments *next;
};

typedef enum SymbolType {

    GLOBAL,
    LOCAL,
    FORMAL,
    USERFUNC,
    LIBFUNC
} SymbolType;

char *symbolTypePrints[5] = {
    "GLOBAL",
    "LOCAL",
    "FORMAL",
    "USERFUNC",
    "LIBFUNC"
};

struct SymbolTableEntry {

    const char *name;

    uint scopeno;
    uint line;
    bool active;

    SymbolType type;

    struct SymbolTableEntry *nscope;
    struct SymbolTableEntry *next;    // hashmap implementation with LinkedList's on collisions

    struct func_arguments *farg;
};

typedef struct _symtable {

    uint64_t buckets;

    struct SymbolTableEntry **map;
    struct SymbolTableEntry **slink;

} * SymTable;


/*************** FUNCTIONS ***************/

SymTable SymTable_create(void);

void SymTable_destroy(SymTable st);

int SymTable_insert(SymTable __restrict__ st, const char * __restrict__ name, SymbolType type, uint scope, uint line);

struct SymbolTableEntry *SymTable_lookup_scope(SymTable __restrict__ st, const char * __restrict__ name, uint scope);

struct SymbolTableEntry *SymTable_lookup(SymTable __restrict__ st, const char * __restrict__ name, uint scope) __attribute__((deprecated));

int SymTable_insert_func_arg(SymTable st, const char * __restrict__ func, const char * __restrict__ arg);

void SymTable_hide(SymTable st, uint scope);

void SymTable_print_scopes(SymTable st);

void SymTable_print(SymTable st);


#endif
