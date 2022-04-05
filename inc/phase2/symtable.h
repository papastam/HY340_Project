#ifndef SYMTABLE_HASH_H
#define SYMTABLE_HASH_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


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

struct SymbolTableEntry {

    const char *name;

    uint scopeno;
    int  active;
    int  line;

    SymbolType type;

    struct SymbolTableEntry *next;  // hashmap implementation with LinkedList
};

typedef struct _symtable {

    u_int64_t buckets;
    struct SymbolTableEntry **map;

} * SymTable;


/**
 * @brief Creates a new symbol table
 * 
 * @return A pointer to the newly initialized symbol table
 */
SymTable SymTable_create(void);

void SymTable_destroy(SymTable st);

/**
 * @brief Inserts a new SymbolTableEntry into the given symbol table
 * 
 * @param st a valid symbol table
 * @param id 
 * @param type LOCAL | GLOBAL | FORMAL | FUNC_LIB | FUNC_USR
 * @param scope 
 * @return int 
 */
int SymTable_insert(SymTable st, const char *name, SymbolType type, int scope, int line);

struct SymbolTableEntry *SymTable_lookup(SymTable st, const char *name, int scope);

void SymTable_print(SymTable st);


#endif
