#ifndef SYMTABLE_HASH_H
#define SYMTABLE_HASH_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>


struct binding {

    const char *key;

    uint scopeno;
    int  active;
    int  type;

    // types
    #define LOCAL     0
    #define GLOBAL    1
    #define FORMAL    2
    #define FUNC_LIB  3
    #define FUNC_USR  4

    struct binding *next;  // hashmap implementation with LinkedList
};

typedef struct _symtable {

    u_int64_t buckets;
    struct binding **map;

} * SymTable;


/**
 * @brief Creates a new symbol table
 * 
 * @return A pointer to the newly initialized symbol table
 */
SymTable SymTable_create(void);

void SymTable_destroy(SymTable st);

/**
 * @brief Inserts a new binding into the given symbol table
 * 
 * @param st a valid symbol table
 * @param id 
 * @param type LOCAL | GLOBAL | FORMAL | FUNC_LIB | FUNC_USR
 * @param scope 
 * @return int 
 */
int SymTable_insert(SymTable st, const char *key, int type, int scope);

struct binding *SymTable_lookup(SymTable st, const char *key, int scope);

void SymTable_print(SymTable st);


#endif
