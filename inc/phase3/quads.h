#ifndef CS340_PROJECT_QUADS
#define CS340_PROJECT_QUADS
#include "../phase2/symtable.h"

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

char *exp_type_prints[12] = \
{
    "var_e",
    "tableitem_e",
    "progtamfunc_e",
    "libraryfunc_e",
    "arithexpr_e",
    "boolexpr_e",
    "assignexpr_e",
    "newtable_e",
    "costnum_e",
    "constbool_e",
    "conststring_e",
    "nil_e",
};

struct expr{
    enum expr_t                 type;
    struct SymbolTableEntry*    sym;
    struct expr*                index;
    double                      numConst;
    char*                       strConst;
    unsigned char               boolConst;
    struct expr*                next;
};

struct quad{
    enum iopcode    op;
    struct expr*    result;
    struct expr*    arg1;
    struct expr*    arg2;
    unsigned        label;
    unsigned        line;
};

//These sould me moved (maybe?)
struct quad*    quads = (struct quad*) 0;
unsigned        total = 0;
unsigned int    currQuad = 0;

#define EXPAND_SIZE 1024
#define CURR_SIZE   (total*sizeof(struct quad))
#define NEW_SIZE    (EXPAND_SIZE*sizeof(struct quad)+CURR_SIZE)

/*************** FUNCTIONS ***************/

void printReduction(const char* from,const char* to, int line);
void printSymbol(const struct SymbolTableEntry *printsym);
void printExpression(const struct expr *printexp);

#endif