#ifndef CS340_PROJECT_ENUM_TYPES_H
#define CS340_PROJECT_ENUM_TYPES_H


#define LEX_TOTAL_TOKENS  48

char *g_lex_prints[LEX_TOTAL_TOKENS] = \
{
    "OPER_EQ",\
    "OPER_PLUS", \
    "OPER_MINUS", \
    "OPER_MUL", \
    "OPER_DIV", \
    "OPER_MOD", \
    "OPER_EQ2", \
    "OPER_NEQ", \
    "OPER_PLUS2", \
    "OPER_MINUS2", \
    "OPER_GRT", \
    "OPER_GRE", \
    "OPER_LET", \
    "OPER_LEE", \
    "PUNC_LBRACE", \
    "PUNC_RBRACE", \
    "PUNC_LBRACKET", \
    "PUNC_RBRACKET", \
    "PUNC_LPARENTH", \
    "PUNC_RPARENTH", \
    "PUNC_SEMIC", \
    "PUNC_COMMA", \
    "PUNC_COLON", \
    "PUNC_COLON2", \
    "PUNC_DOT", \
    "PUNC_DOT2", \
    "KEYW_IF", \
    "KEYW_ELSE", \
    "KEYW_WHILE", \
    "KEYW_FOR", \
    "KEYW_FUNC", \
    "KEYW_RET", \
    "KEYW_BREAK", \
    "KEYW_CONT", \
    "KEYW_AND", \
    "KEYW_NOT", \
    "KEYW_OR", \
    "KEYW_LOCAL", \
    "KEYW_TRUE", \
    "KEYW_FALSE", \
    "KEYW_NIL", \
    "CONST_INT", \
    "CONST_REAL", \
    "ID", \
    "COMM_SL", \
    "COMM_ML", \
    "COMM_NEST", \
    "STRING"
};

#define OPER_EQ          0U  // equal
#define OPER_PLUS        1U
#define OPER_MINUS       2U
#define OPER_MUL         3U
#define OPER_DIV         4U
#define OPER_MOD         5U
#define OPER_EQ2         6U  // equal-equal
#define OPER_NEQ         7U
#define OPER_PLUS2       8U
#define OPER_MINUS2      9U
#define OPER_GRT        10U  // greater-than
#define OPER_GRE        11U  // greater-equal
#define OPER_LET        12U  // less-than
#define OPER_LEE        13U  // less-equal

#define PUNC_LBRACE     14U  // {
#define PUNC_RBRACE     15U  // }
#define PUNC_LBRACKET   16U  // [
#define PUNC_RBRACKET   17U  // ]
#define PUNC_LPARENTH   18U
#define PUNC_RPARENTH   19U
#define PUNC_SEMIC      20U
#define PUNC_COMMA      21U
#define PUNC_COLON      22U
#define PUNC_COLON2     23U  // ::
#define PUNC_DOT        24U
#define PUNC_DOT2       25U  // ..

#define KEYW_IF         26U
#define KEYW_ELSE       27U
#define KEYW_WHILE      28U
#define KEYW_FOR        29U
#define KEYW_FUNC       30U
#define KEYW_RET        31U
#define KEYW_BREAK      32U
#define KEYW_CONT       33U
#define KEYW_AND        34U
#define KEYW_NOT        35U
#define KEYW_OR         36U
#define KEYW_LOCAL      37U
#define KEYW_TRUE       38U
#define KEYW_FALSE      39U
#define KEYW_NIL        40U  // nil

#define CONST_INT       41U
#define CONST_REAL      42U

#define ID              43U
#define COMM_SL         44U
#define COMM_ML         45U
#define COMM_NEST       46U
#define STRING          47U


#endif  /* CS340_PROJECT_ENUM_TYPES_H */