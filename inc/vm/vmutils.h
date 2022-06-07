#ifndef CS340_PROJECT_VMUTILS
#define CS340_PROJECT_VMUTILS

#include "vmtypes.h"

void avm_warning(int line, const char * warformat, ...);
void avm_error(int line, const char * warformat, ...);
void avm_assign(struct avm_memcell* lv,struct avm_memcell* rv);

void avm_dec_top(void);
void avm_push_envvalue(unsigned val);

char * avm_tostring(struct avm_memcell*);
void avm_callibfunc(char* funcname);
void avm_callsaveeenvironment(void);


#endif