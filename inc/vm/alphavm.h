#ifndef CS340_PROJECT_ALPHAVM_H
#define CS340_PROJECT_ALPHAVM_H

#include <sys/types.h>
#include <stdbool.h>

typedef enum {

    assign_v,           add_v,              sub_v,
    mul_v,              div_v,              mod_v,
    uminus_v,           and_v,              or_v,
    not_v,              jeq_v,              jne_v,              
    jle_v,              jge_v,              jlt_v,
    jgt_v,              call_v,             pusharg_v,
    funcenter_v,        funcexit_v,         newtable_v,
    tablegetelem_v,     tablesetelem_v,     nop_v,

} vmopcode_t ;

typedef enum {

    number_m,
    string_m,
    bool_m,
    table_m,
    userfunc_m,
    libfunc_m,
    nil_m,
    under_m

} avm_memcell_t;

struct avm_table;

struct avm_memcell {

    avm_memcell_t type;

    union {

        double numVal;
        char * strVal;
        bool boolVal;
        struct avm_table * tableVal;
        uint funcVal;
        char * libfuncVal;
    };
};

struct avm_table_bucket {

    struct avm_memcell key;
    struct avm_memcell value;

    struct avm_table_bucket * next;
};

struct avm_table {

    #define AVM_TABLE_HASHSIZE 211

    uint refCounter;
    uint total;

    struct avm_table_bucket strIndexed[AVM_TABLE_HASHSIZE];
    struct avm_table_bucket numIndexed[AVM_TABLE_HASHSIZE];
};


#define AVM_STACKSIZE   4096U
#define AVM_WIPEOUT(m)  memset(&(m), 0, sizeof(m))

extern struct avm_memcell stack[AVM_STACKSIZE];

typedef enum {

    #define VM_ARG_NULL 0xf0000000

    label_a,
    global_a,
    formal_a,
    local_a,
    number_a,
    string_a,
    bool_a,
    nil_a,
    userfunc_a,
    libfunc_a,
    retval_a

} vmarg_t;

struct vmarg {

    vmarg_t type;
    uint val;
};

struct vminstr {

    vmopcode_t opcode;

    struct vmarg * result;
    struct vmarg * arg1;
    struct vmarg * arg2;
    uint srcLine;
};

struct userfunc {

    uint address;
    uint localSize;
    char * id;
};

typedef struct {

    uint size;
    double * array;

} __const_array_t;

typedef struct {

    uint size;
    char ** array;

} __string_array_t;

typedef struct {

    uint size;
    struct userfunc * array;

} __userfunc_array_t;

typedef __string_array_t __libfunc_array_t;


extern __string_array_t sarr;
extern __const_array_t  carr;

extern __userfunc_array_t ufarr;
extern __libfunc_array_t  lfarr;

extern struct vminstr * iarr;


#define CONSTANT_T_INIT_SIZE 512
#define ALPHA_MAGICNUM 0x14470c35U 

extern unsigned char   execution_finished;
extern unsigned        pc;
extern unsigned        currLine;
extern unsigned        codeSize;
extern struct vminstr* code;

/*************************************/


int vm_parse_bin_file(const char * filename) __attribute__((nonnull));
void execute_cycle(void);

double consts_getnumber(uint index);
double consts_getstr(uint index);
double consts_getlibfunc(uint index);

#endif  /** CS340_PROJECT_ALPHAVM_H **/