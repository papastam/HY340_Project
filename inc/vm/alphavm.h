#ifndef CS340_PROJECT_ALPHAVM_H
#define CS340_PROJECT_ALPHAVM_H

#include <sys/types.h>

typedef enum {

    assign_v,           add_v,              sub_v,
    mul_v,              div_v,              mod_v,
    uminus_v,           and_v,              or_v,
    not_v,              jump_v,             jeq_v, //added jump although it is not on lect13, slide17
    jne_v,              jle_v,              jge_v,
    jlt_v,              jgt_v,              call_v,
    pusharg_v,          funcenter_v,        funcexit_v,
    newtable_v,         tablegetelem_v,     tablesetelem_v,
    nop_v,

} vmopcode_t ;

enum vmarg_t {

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
};

struct vmarg {

    enum vmarg_t type;
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

    uint address;  // papastamo are you sure for unsigned int ?????
    uint localSize;
    char * id;
};

extern double * numConsts;
extern uint numTableSize;
extern uint totalNumConsts;

extern char **  stringConsts;
extern uint strTableSize;
extern uint totalStringConsts;

extern char **  namedLibfuncs;
extern uint libfTableSize;
extern uint totalNamedLibfuncs;  // don't think these are required in VM

extern struct userfunc * userFuncs;
extern uint userfTableSize;
extern uint totalUserFuncs;

#define CONSTANT_T_INIT_SIZE 512
#define ALPHA_MAGICNUM 0x14470c35U 

/*************************************/


int vm_parse_bin_file(const char * filename) __attribute__((nonnull));

#endif  /** CS340_PROJECT_ALPHAVM_H **/