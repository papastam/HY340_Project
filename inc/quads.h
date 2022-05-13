#ifndef CS340_PROJECT_QUADS_H
#define CS340_PROJECT_QUADS_H

#include "symtable.h"

enum iopcode {

    assign,             add,            sub,
    mul,                div_o,          mod,
    uminus,             and_o,          or_o,
    not_o,              if_eq,          if_noteq,
    if_lesseq,          if_greatereq,   if_less,
    if_greater,         call,           param,
    ret,                getretval,      funcstart,
    funcend,            tablecreate,    tablegetelem,
    tablesetelem,       jump,
};

typedef enum expr_enum {

    var_e,
    tableitem_e,

    programfunc_e,
    libraryfunc_e,
    
    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,
    
    constnum_e, 
    constbool_e,
    conststring_e,

    // real_eavl_e,
    
    nil_e,
} expr_t;


struct expr {

    expr_t                      type;
    struct SymbolTableEntry*    sym;
    struct expr*                index;
    double                      numConst;
    char*                       strConst;
    unsigned int                boolConst;
    struct expr*                next;
};

struct function_contents {

    struct expr*    elist;
    uint            method;
    char*           name;
};

struct quad{

    enum iopcode    op;
    struct expr    *result;
    struct expr    *arg1;
    struct expr    *arg2;
    unsigned        label;
    unsigned        line;
};

//These sould me moved (maybe?)
extern struct quad    *quads;
extern unsigned int    total;
extern unsigned int    currQuad;

#define EXPAND_SIZE 1024
#define CURR_SIZE   (total*sizeof(struct quad))
#define NEW_SIZE    (EXPAND_SIZE*sizeof(struct quad)+CURR_SIZE)

/*************** FUNCTIONS ***************/

#endif  /* CS340_PROJECT_QUADS */