#ifndef CS340_PROJECT_EXEC
#define CS340_PROJECT_EXEC

#include "vmtypes.h"

#define AVM_MAX_INSTRUCTIONS (unsigned) nop_v
#define AVM_NUMACTUALS_OFFSET 4
#define AVM_SAVEDPC_OFFSET 3
#define AVM_SAVEDTOP_OFFSET 2
#define AVM_SAVEDTOPSP_OFFSET 1

extern unsigned totalActuals;

//========== ARITHMETIC FUNCTIONS DISPATCHER ==========
typedef double(*arithmetic_func_t)(double,double);
double add_impl(double,double);
double sub_impl(double,double);
double mul_impl(double,double);
double div_impl(double,double);
double mod_impl(double,double);

void execute_arithmetic(struct vminstr*);
extern arithmetic_func_t arithFuncs[];

//========== COMPARISON FUNCTIONS DISPATCHER ==========
typedef int(*comp_func_t)(double,double);
int jle_impl(double,double);
int jge_impl(double,double);
int jlt_impl(double,double);
int jgt_impl(double,double);
extern comp_func_t compFuncs[];
void execute_comp(struct vminstr*);


//================= EXECUTE FUNCTIONS =================
typedef void (*execute_func_t)(struct vminstr*);
extern execute_func_t executeFuncs[];

void execute_assign(struct vminstr*);

#define execute_add execute_arithmetic
#define execute_sub execute_arithmetic
#define execute_mul execute_arithmetic
#define execute_div execute_arithmetic
#define execute_mod execute_arithmetic

void execute_uminus(struct vminstr*) __attribute_deprecated__;

void execute_and(struct vminstr*) __attribute_deprecated__;
void execute_or(struct vminstr*) __attribute_deprecated__;
void execute_not(struct vminstr*) __attribute_deprecated__;

void execute_jeq(struct vminstr*);
void execute_jne(struct vminstr*);


#define execute_jle execute_comp
#define execute_jge execute_comp
#define execute_jlt execute_comp
#define execute_jgt execute_comp

void execute_call(struct vminstr*);
void execute_pusharg(struct vminstr*);
void execute_funcenter(struct vminstr*);
void execute_funcend(struct vminstr*);

void execute_newtable(struct vminstr*);
void execute_tablegetelem(struct vminstr*);
void execute_tablesetelem(struct vminstr*);

void execute_nop(struct vminstr*);

#endif  /** CS340_PROJECT_EXEC **/