#ifndef CS340_PROJECT_VMUTILS
#define CS340_PROJECT_VMUTILS

#include "vmtypes.h"

//========== TO BOOL DISPATCHER ==========
typedef unsigned char (*tobool_func_t)(struct avm_memcell*);
extern tobool_func_t toBoolFuncs[];
unsigned char number_tobool(struct avm_memcell*);
unsigned char string_tobool(struct avm_memcell*);
unsigned char bool_tobool(struct avm_memcell*);
unsigned char table_tobool(struct avm_memcell*);
unsigned char userfunc_tobool(struct avm_memcell*);
unsigned char libfunc_tobool(struct avm_memcell*);
unsigned char nil_tobool(struct avm_memcell*);
unsigned char undefined_tobool(struct avm_memcell*);

unsigned char avm_tobool(struct avm_memcell*);

//========== TO STRING DISPATCHER ==========
typedef char* (*toString_func_t)(struct avm_memcell *);
extern toString_func_t toStringFuncs[];
char* number_toString(struct avm_memcell *);
char* string_toString(struct avm_memcell *);
char* bool_toString(struct avm_memcell *);
char* table_toString(struct avm_memcell *);
char* userfunc_toString(struct avm_memcell *);
char* libfunc_toString(struct avm_memcell *);
char* nil_toString(struct avm_memcell *);
char* undefined_toString(struct avm_memcell *);

char* avm_toString(struct avm_memcell *);



void avm_warning(int line, const char * warformat, ...);
void avm_error(int line, const char * warformat, ...);
void avm_assign(struct avm_memcell* lv,struct avm_memcell* rv);

void avm_dec_top(void);
void avm_push_envvalue(unsigned val);
unsigned avm_get_envvalue(unsigned i);

void avm_callibfunc(char* funcname);
void avm_callsaveenvironment(void);

struct userfunc* avm_getfuncinfo(unsigned address);

typedef void (*library_func_t)(void);
library_func_t avm_getlibraryfunc(char* id);
void avm_calllibfunc(char* id);

unsigned avm_getTotalActuals();


struct avm_memcell* avm_getActual(unsigned i);
#endif