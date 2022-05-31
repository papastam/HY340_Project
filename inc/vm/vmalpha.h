#ifndef CS340_PROJECT_VMALPHA_H
#define CS340_PROJECT_VMALPHA_H

enum vmopcode{
    assign_v,           add_v,              sub_v,
    mul_v,              div_v,              mod_v,
    uminus_v,           and_v,              or_v,
    not_v,              jump_v,             jeq_v, //added jump although it is not on lect13, slide17
    jne_v,              jle_v,              jge_v,
    jlt_v,              jgt_v,              call_v,
    pusharg_v,          funcenter_v,        funcexit_v,
    newtable_v,         tablegetelem_v,     tablesetelem_v,
    nop_v,
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
    struct vmarg     *result;
    struct vmarg     *arg1;
    struct vmarg     *arg2;
    unsigned    srcLine;
};

struct userfunc{
    unsigned    address;
    unsigned    localSize;
    char*      id;
};

extern double*     numConsts;
extern unsigned    totalNumConsts;

extern char**      stringConsts;
extern unsigned    totalStringConsts;

extern char**      namedLibfuncs;
extern unsigned    totalNamedLibfuncs;

extern struct userfunc*     userFuncs;
extern unsigned             totalUserFuncs;

#endif
