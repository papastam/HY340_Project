#ifndef CS340_PROJECT_MEMORY_MANAGEMENT
#define CS340_PROJECT_MEMORY_MANAGEMENT

#include "vmtypes.h"

extern struct avm_memcell stack[AVM_STACKSIZE];
extern struct avm_memcell ax, bx, cx;
extern struct avm_memcell retval;
extern uint top, topsp;

struct avm_memcell * avm_translate_opperant(struct vmarg* arg, struct avm_memcell* reg);


static void avm_initstack(void);

#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_STACKENV_SIZE 4

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