#ifndef CS340_PROJECT_EXECUTE_FUNCS
#define CS340_PROJECT_EXECUTE_FUNCS

#include "alphavm.h"

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v

typedef void (*execute_func_t)(struct vminstr*);
extern execute_func_t executeFuncs[];

typedef double(*arithmetic_func_t)(struct vminstr*)
double add_impl(double,double);
double sub_impl(double,double);
double mul_impl(double,double);
double div_impl(double,double);
double mod_impl(double,double);
extern arithmetic_func_t arithFuncs[];
void execute_arithmetic(struct vminstr*);


void execute_assign(struct vminstr*);

#define execute_add execute_arithmetic;
#define execute_sub execute_arithmetic;
#define execute_mul execute_arithmetic;
#define execute_div execute_arithmetic;
#define execute_mod execute_arithmetic;

// DEPRECATED \/ \/.
extern void execute_uminus(struct vminstr*);

extern void execute_and(struct vminstr*);
extern void execute_or(struct vminstr*);
extern void execute_not(struct vminstr*);
// DEPRECATED /\ /\.

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