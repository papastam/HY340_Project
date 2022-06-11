#ifndef CS340_PROJECT_ALPHAVM_H
#define CS340_PROJECT_ALPHAVM_H

#include "vmtypes.h"

extern __string_array_t sarr;
extern __const_array_t  carr;

extern __userfunc_array_t ufarr;
extern __libfunc_array_t  lfarr;

extern struct vminstr * code;


#define CONSTANT_T_INIT_SIZE 512
#define ALPHA_MAGICNUM 0x14470c35U 

extern uint execution_finished;
extern uint pc;
extern uint currLine;
extern uint codeSize;

extern struct vminstr * code;
#define AVM_ENDING_PC codeSize

/*************************************/


int vm_parse_bin_file(const char * filename) __attribute__((nonnull));
void init_stack(void);
int avm_execute_cycle(void);

#endif  /** CS340_PROJECT_ALPHAVM_H **/