#ifndef CS340_PROJECT_ALPHAVM_H
#define CS340_PROJECT_ALPHAVM_H

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
    unsigned val;
};

struct vminstr {

    vmopcode_t opcode;

    struct vmarg * result;
    struct vmarg * arg1;
    struct vmarg * arg2;
    unsigned srcLine;
};

struct userfunc {

    unsigned address;
    unsigned localSize;
    char * id;
};

extern double * numConsts;
extern unsigned numTableSize;
extern unsigned totalNumConsts;

extern char **  stringConsts;
extern unsigned strTableSize;
extern unsigned totalStringConsts;

extern char **  namedLibfuncs;
extern unsigned libfTableSize;
extern unsigned totalNamedLibfuncs;

extern struct userfunc * userFuncs;
extern unsigned userfTableSize;
extern unsigned totalUserFuncs;

#define CONSTANT_T_INIT_SIZE 512

/*************************************/

#define DEF_BINFILE_NAME "incode.abc"

int vm_parse_bin_file(const char * filename);

#endif  /** CS340_PROJECT_ALPHAVM_H **/