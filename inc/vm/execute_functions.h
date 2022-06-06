#ifndef CS340_PROJECT_EXECUTE_FUNCS
#define CS340_PROJECT_EXECUTE_FUNCS

#include "alphavm.h"

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v

typedef void (*execute_func_t)(struct vminstr*);
extern execute_func_t executeFuncs[];

extern void execute_assign(struct vminstr*);

extern void execute_add(struct vminstr*);
extern void execute_sub(struct vminstr*);
extern void execute_mul(struct vminstr*);
extern void execute_div(struct vminstr*);
extern void execute_mod(struct vminstr*);
// extern void execute_uminus(struct vminstr*);

// extern void execute_and(struct vminstr*);
// extern void execute_or(struct vminstr*);
// extern void execute_not(struct vminstr*);

extern void execute_jeq(struct vminstr*);
extern void execute_jne(struct vminstr*);
extern void execute_jle(struct vminstr*);
extern void execute_jge(struct vminstr*);
extern void execute_jlt(struct vminstr*);
extern void execute_jgt(struct vminstr*);

extern void execute_call(struct vminstr*);
extern void execute_pusharg(struct vminstr*);
extern void execute_funcenter(struct vminstr*);
extern void execute_funcend(struct vminstr*);

extern void execute_newtable(struct vminstr*);
extern void execute_tablegetelem(struct vminstr*);
extern void execute_tablesetelem(struct vminstr*);

extern void execute_nop(struct vminstr*);
#endif