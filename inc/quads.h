#include "symtable.h"

enum iopcode{
    assign,             add,            sub,
    mul,                div,            mod,
    uminus,             and_o,          or_o,
    not_o,              if_eq,          if_noteq,
    if_lesseq,          if_gratereq,    if_less,
    if_grater,          call,           param,
    ret,                getretval,      funcstart,
    funcend,            tablecrate,     tablegetelem,
    tablesetelem,
};

enum expr_t{
    var_e,
    tableitem_e,

    progtamfunc_e,
    libraryfunc_e,
    
    arithexpr_e,
    boolexpr_e,
    assignexpr_e,
    newtable_e,
    
    costnum_e,
    constbool_e,
    conststring_e,
    
    nil_e,
};

struct expr{
    expr_t                      type;
    struct SymbolTableEntry*    sym;
    expr*                       index;
    double                      numConst;
    char*                       strConst;
    unsigned char               boolConst;
    expr*                       next;
};

struct quad{
    iopcode     op;
    expr*       result;
    expr*       arg1;
    expr*       arg2;
    unsigned    label;
    unsigned    line;
};

//These sould me moved (maybe?)
quad*           quads = (quad*) 0;
unsigned        total = 0;
unsigned int    currQuad = 0;

#define EXPAND_SIZE 1024
#define CURR_SIZE   (total*sizeof(quad))
#define NEW_SIZE    (EXPAND_SIZE*sizeof(quad)+CURR_SIZE)
