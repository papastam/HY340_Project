#ifndef CS340_PROJECT_MEMORY_MANAGEMENT
#define CS340_PROJECT_MEMORY_MANAGEMENT

#include "vmtypes.h"

extern struct avm_memcell stack[AVM_STACKSIZE];
extern struct avm_memcell ax, bx, cx;
extern struct avm_memcell retval;
extern uint top, topsp;

struct avm_memcell * avm_translate_operand(struct vmarg* arg, struct avm_memcell* reg);

void avm_initstack(void);

#define AVM_WIPEOUT(m) memset(&(m), 0, sizeof(m))
#define AVM_STACKENV_SIZE 4

void avm_memcellclear(struct avm_memcell* mc);
void memclear_string(struct avm_memcell* mc);
void memclear_table(struct avm_memcell* mc);

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


void avm_tabledecrefcounter(struct avm_table * t);
void avm_tableincrefcounter(struct avm_table * t);
struct avm_table * avm_tablenew(void);
struct avm_memcell *avm_tablegetelem(struct avm_table * restrict table, struct avm_memcell * restrict key);
void avm_tablesetelem(struct avm_table * restrict table, struct avm_memcell * restrict key, struct avm_memcell * restrict content);



double consts_getnumber(uint index);
char* consts_getstr(uint index);
double consts_getlibfunc(uint index);

#endif