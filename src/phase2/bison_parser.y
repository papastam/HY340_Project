%{
    #include "enum_types.h"
    #include <assert.h>

%}

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

%left PUNC_LPARENTH PUNC_RPARENTH 
%left PUNC_LBRACKET PUNC_RBRACKET 
%left PUNC_DOT PUNC_DOT2
%right KEYW_NOT OPER_PLUS2 OPER_MINUS2
%left OPER_MUL OPER_DIV OPER_MOD
%left OPER_PLUS
%right OPER_MINUS
%nonassoc OPER_LET OPER_LEE OPER_GRT OPER_GRE
%nonassoc OPER_EQ2 OPER_NEQ
%left KEYW_AND
%left KEYW_OR
%left OPER_EQ

%%

program:    statements;

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
            |;

statements: stmt statements
            |;

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

lvalue:     ID
            | KEYW_LOCAL ID
            | PUNC_COLON2 ID
            | member
            ;

member:     lvalue PUNC_DOT ID
            | lvalue PUNC_LBRACKET expr PUNC_RBRACKET
            | call PUNC_DOT ID
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
methodcall: PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH;

elist:      expr elistrep
            |;

elistrep:   PUNC_COMMA expr elistrep
            | PUNC_COMMA expr
            |;

objectdef:  PUNC_LBRACKET objectin PUNC_RBRACKET;
objectin:   elist
            |indexed
            |;

indexed:    indexedelem
            |indexedelem indexrep
            |;
indexrep:   PUNC_COMMA indexedelem

indexedelem:PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE;

block:      PUNC_LBRACKET statements PUNC_RBRACKET
            |;

funcdef:    KEYW_FUNC ID PUNC_LPARENTH idlist PUNC_RPARENTH block
            |KEYW_FUNC PUNC_LPARENTH idlist PUNC_RPARENTH block;

const:      CONST_INT
            | CONST_REAL
            | STRING
            | KEYW_NIL
            | KEYW_TRUE
            | KEYW_FALSE
            ;

idlist:     ID ids
            |ID
            |;

ids:        PUNC_COMMA ID ids
            | PUNC_COMMA ID
            |;
            
ifstmt:     KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt 
            |KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt KEYW_ELSE stmt;
whilestmt:  KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt;
forstmt:    KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt;
returnstmt: KEYW_RET PUNC_SEMIC
            |KEYW_RET expr PUNC_SEMIC;

%%

int main(int argc, char **argv) {

    int index;

    struct alpha_token_t token; 
    struct alpha_token_t *curr;


    if ( argc != 2 ) {

        printf("\e[1;31merror\e[0m: no input file\n");
        return 0;
    }

    if ( !(yyin = fopen(argv[1], "r")) ) {

        perror("fopen()");
        return 1;
    }
    
    if( !alpha_yylex(&token) )
        return 1;

    printf("\n");

    for (index = 0, curr = &token; (curr && curr->content); curr = curr->next, ++index) {

        printf("[%d] line::%u '%s' -- %s\n", index, curr->line, curr->content, _printable_lex_token(curr->type));
        free(curr->content);

        /** TODO: free(everything) */
    }


    return 0;
}
