#ifndef CS340_PROJECT_MEMORY_MANAGEMENT
#define CS340_PROJECT_MEMORY_MANAGEMENT

#include "alphavm.h"

typedef enum {

    undef_m,
    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m

} avm_memcell_t;

struct avm_table;

struct avm_memcell {

    avm_memcell_t type;

    union {

        double numVal;
        char * strVal;
        bool boolVal;
        struct avm_table * tableVal;
        uint funcVal;
        char * libfuncVal;
    };
};

struct avm_table_bucket {

    struct avm_memcell key;
    struct avm_memcell value;

    struct avm_table_bucket * next;
};

struct avm_table {

    #define AVM_TABLE_HASHSIZE 211

    uint refCounter;
    uint total;

    struct avm_table_bucket strIndexed[AVM_TABLE_HASHSIZE];
    struct avm_table_bucket numIndexed[AVM_TABLE_HASHSIZE];
};


#define AVM_STACKSIZE   4096U
#define AVM_WIPEOUT(m)  memset(&(m), 0, sizeof(m))

extern struct avm_memcell stack[AVM_STACKSIZE];

extern struct avm_memcell ax, bx, cx;
extern struct avm_memcell retval;
extern uint top, topsp;

struct avm_memcell * avm_translate_opperant(struct vmarg* arg, struct avm_memcell* reg);


extern struct avm_memcell stack[];
static void avm_initstack(void);

#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))

void avm_memcellclear(struct avm_memcell* input);
void memclear_string(struct avm_memcell* input);
void memclear_table(struct avm_memcell* input);

typedef void(*memclear_func_t)(struct avm_memcell*);
memclear_func_t memclearFuncs[]={
    0,
    memclear_string,
    0,
    memclear_table,
    0,
    0,
    0,
    0
};


//=============== TABLES ===============

void avm_tabledecrefcounter(struct avm_table* input);
void avm_tableincrefcounter(struct avm_table* input);


#endif