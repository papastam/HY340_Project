#ifndef CS340_PROJECT_VMUTILS
#define CS340_PROJECT_VMUTILS

void avm_warning(int line, const char * warformat, ...);
void avm_assign(struct avm_memcell* lv,struct avm_memcell* rv);

#endif