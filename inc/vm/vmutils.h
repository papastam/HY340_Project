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
typedef char* (*toString_func_t)(struct avm_memcell*);
extern toString_func_t toStringFuncs[];
char* number_toString(struct avm_memcell*);
char* string_toString(struct avm_memcell*);
char* bool_toString(struct avm_memcell*);
char* table_toString(struct avm_memcell*);
char* userfunc_toString(struct avm_memcell*);
char* libfunc_toString(struct avm_memcell*);
char* nil_toString(struct avm_memcell*);
char* undefined_toString(struct avm_memcell*);

char * avm_tostring(struct avm_memcell*);
//TODO

struct avm_memcell* avm_tablegetelem(struct avm_table* table, struct avm_memcell* index);
void avm_tablesetelem(struct avm_table* table, struct avm_memcell* index, struct avm_memcell* content);
struct avm_memcell* avm_tablenew();

void avm_warning(int line, const char * warformat, ...);
void avm_error(int line, const char * warformat, ...);
void avm_assign(struct avm_memcell* lv,struct avm_memcell* rv);

void avm_dec_top(void);
void avm_push_envvalue(unsigned val);

void avm_callibfunc(char* funcname);
void avm_callsaveeenvironment(void);


#endif