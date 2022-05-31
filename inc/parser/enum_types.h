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


#endif  /* CS340_PROJECT_ENUM_TYPES_H */