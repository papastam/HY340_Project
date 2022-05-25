#ifndef CS340_PROJECT_VMALPHA_H

enum vmopcode{
    assign_v,           add_v,              sub_v,
    mul_v,              div_v,              mod_v,
    uminus_v,           and_v,              or_v,
    not_v,              jeq_v,              jne_v,
    jle_v,              jge,                jlt_v,
    jgt_v,              call_v,             pusharg_v,
    funcenter_v,        funcexit_v,         newtable_v,
    tablegetelem_v,     tablesetelem_v,     nop_v,
};

enum vmarg_t{
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

struct vmarg{
    enum vmarg_t     type;
    unsigned    val;
};

struct vminstr{
    enum vmopcode    opcode;
    enum vmarg_t     result;
    enum vmarg_t     arg1;
    enum vmarg_t     arg2;
    unsigned    srcLine;
};

struct userfunc{
    unsigned    address;
    unsigned    localSize;
    char*      id;
};

double*     numConsts;
unsigned    totalNumConsts;

char**      stringConsts;
unsigned    totalStringConsts;

char**      namedLibfuncs;
unsigned    totalNamedLibfuncs;

struct userfunc*   userFuncs;
unsigned    totalUserFuncs;
#endif