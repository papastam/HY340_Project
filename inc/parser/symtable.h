#ifndef CS340_PROJECT_SYMTABLE_H
#define CS340_PROJECT_SYMTABLE_H

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

typedef unsigned uint;

struct func_arguments {

    const char *name;
    struct func_arguments *next;
};

typedef enum {

    GLOBAL,
    LOCAL,
    FORMAL,
    USERFUNC,
    LIBFUNC

} SymbolType;

typedef enum {

    programvar,
    functionlocal,
    formalarg

} scopespace_t;

struct SymbolTableEntry {

    const char * name;

    uint scope;
    uint line;
    uint offset;
    bool active;

    SymbolType type;
    scopespace_t space __attribute__((deprecated));

    struct SymbolTableEntry * nscope;  // next-scope
    struct SymbolTableEntry * next;    // hashmap implementation with LinkedList's on collisions

    uint local_cnt;
    uint formal_cnt;
    struct func_arguments * farg;
    uint ufaddress;
};

typedef struct _symtable {

    uint64_t buckets;

    struct SymbolTableEntry ** map;    // hash-map
    struct SymbolTableEntry ** slink;  // scope-link

} * SymTable;

/*************** FUNCTIONS ***************/

SymTable SymTable_create(void);


void SymTable_destroy(SymTable st);


struct SymbolTableEntry* SymTable_insert(SymTable restrict st, const char * restrict name, SymbolType type, uint scope, uint line);


struct SymbolTableEntry* SymTable_lookup_scope(SymTable restrict st, const char * restrict name, uint scope);


struct SymbolTableEntry* SymTable_lookup(SymTable restrict st, const char * restrict name, uint scope)\
    __attribute__((deprecated));

struct SymbolTableEntry * SymTable_lookup_type(SymTable restrict st, const char * restrict name, uint scope, SymbolType type);
struct SymbolTableEntry* SymTable_lookup_all_scopes(SymTable restrict st, const char *name, uint scope);

/**
 * @brief If the symbol with name 'name' is found inside the SymbolTable 'st, then a reference
 * it is returned, else a new symbol is created and placed inside the SymbolTable, and a 
 * reference to that new symbol is
 * 
 * @param st 
 * @param name 
 * @param scope 
 * @param line 
 * @return struct SymbolTableEntry* 
 */
struct SymbolTableEntry* SymTable_lookup_add(SymTable restrict st, const char * restrict name, SymbolType type,uint scope, uint line);


int SymTable_insert_func_arg(SymTable restrict st, const char * restrict func, const char * restrict arg);


void SymTable_hide(SymTable st, uint scope);


void SymTable_print_scopes(SymTable st);


void SymTable_print_all(SymTable st);


void SymTable_print_elem(struct SymbolTableEntry *e);


#endif  /* CS340_PROJECT_SYMTABLE_H */