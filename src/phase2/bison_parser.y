%{
    #include "enum_types.h"
    #include <assert.h>

}%

%start program

%token OPER_EQ
%token OPER_PLUS
%token OPER_MINUS
%token OPER_MUL
%token OPER_DIV
%token OPER_MOD
%token OPER_EQ2
%token OPER_NEQ
%token OPER_PLUS2
%token OPER_MINUS2
%token OPER_GRT
%token OPER_GRE
%token OPER_LET
%token OPER_LEE

%token PUNC_LBRACE
%token PUNC_RBRACE
%token PUNC_LBRACKET
%token PUNC_RBRACKET
%token PUNC_LPARENTH
%token PUNC_RPARENTH
%token PUNC_SEMIC
%token PUNC_COMMA
%token PUNC_COLON
%token PUNC_COLON2
%token PUNC_DOT
%token PUNC_DOT2

%token KEYW_IF
%token KEYW_ELSE
%token KEYW_WHILE
%token KEYW_FOR
%token KEYW_FUNC
%token KEYW_RET
%token KEYW_BREAK
%token KEYW_CONT
%token KEYW_AND
%token KEYW_NOT
%token KEYW_OR
%token KEYW_LOCAL
%token KEYW_TRUE
%token KEYW_FALSE
%token KEYW_NIL

%token CONST_INT
%token CONST_REAL

%token ID
%token COMM_SL
%token COMM_ML
%token COMM_NEST
%token STRING

%left PUNC_LPARENTH, PUNC_RPARENTH 
%left PUNC_LBRACKET, PUNC_RBRACKET 
%left PUNC_DOT, PUNC_DOT2
%right KEYW_NOT, OPER_PLUS2, OPER_MINUS, OPER_MINUS2
%left OPER_MUL, OPER_DIV, OPER_MOD
%left OPER_PLUS
%right OPER_MINUS
%nonassoc OPER_LET, OPER_LEE, OPER_GRT, OPER_GRE
%nonassoc OPER_EQ2, OPER_NEQ
%left KEYW_AND
%left KEYW_OR
%left OPER_EQ

%%

program:    stmt*;

stmt:       expr PUNC_SEMIC
            | ifstmt
            | whilestmt
            | forstmt
            | returnstmt
            | KEYW_BREAK PUNC_SEMIC
            | KEYW_CONT PUNC_SEMIC
            | block
            | funcdef
            | PUNC_SEMIC
            ;

expr:       assignexpr
            | expr op expr
            | term
            ;

op:         OPER_PLUS
            | OPER_MINUS
            | OPER_MUL
            | OPER_DIV
            | OPER_MOD
            | OPER_GRT
            | OPER_GRE
            | OPER_LET 
            | OPER_LEE
            | OPER_EQ2
            | OPER_NEQ
            | KEYW_AND
            | KEYW_OR
            ;

term:       PUNC_LPARENTH expr PUNC_RPARENTH
            | OPER_MINUS expr
            | KEYW_NOT expr
            | OPER_PLUS2 lvalue
            | lvalue OPER_PLUS2
            | OPER_MINUS2 lvalue
            | lvalue OPER_MINUS2
            | primary
            ;

assignexpr: lvalue OPER_EQ2 expr;

primary:    lvalue
            | call
            | objectdef
            | PUNC_LPARENTH funcdef PUNC_RPARENTH
            | const
            ;

lvalue:     id
            | local id
            | PUNC_COLON2 id
            | member
            ;

member:     lvalue PUNC_DOT id
            | lvalue PUNC_LBRACKET expr PUNC_RBRACKET
            | call PUNC_DOT id
            | call PUNC_LBRACKET expr PUNC_RBRACKET
            ;

call:       call PUNC_LPARENTH elist PUNC_RPARENTH
            |lvalue callsuffix
            | PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH
            ;

callsuffix: normcall
            |methodcall
            ;

normcall:   PUNC_LPARENTH elist PUNC_RPARENTH;
methodcall: PUNC_DOT2 id PUNC_LPARENTH elist PUNC_RPARENTH;

elist:      PUNC_LBRACKET expr ( PUNC_COMMA expr )? PUNC_RBRACKET;

objectdef:  PUNC_LBRACKET ( elist | indexed ) PUNC_RBRACKET;
indexed:    indexedelem ( PUNC_COMMA indexedelem)*;
indexedelem: PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE;

block:      PUNC_LBRACKET expr* PUNC_RBRACKET;

funcdef:    KEYW_FUNC id PUNC_LPARENTH idlist PUNC_RPARENTH block;

const:      number
            | string
            | KEYW_NIL
            | KEYW_TRUE
            | KEYW_FALSE
            ;

idlist:     id ( PUNC_COMMA id)*;
            
ifstmt:     KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt ( KEYW_ELSE stmt )?;
whilestmt:  KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt;
forstmt:    KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt;
returnstmt: KEYW_RET expr PUNC_SEMIC;

%%

