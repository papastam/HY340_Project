%{
    // #include "inc/enum_types.h"
    #include <assert.h>

    void printReduction(char* from,char* to, int line){
        printf("[#%d] Reduction: %s ---> %s",line, from, to);
    }

%}

%union {
    int intVal; 
    char* strVal; 
    double realVal;
}

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

program:    statements                  {printReduction("program","statements", yylineno);}
            ;

stmt:       expr PUNC_SEMIC             { $$ = $1; printReduction("stmt","expr PUNC_SEMIC", yylineno);}
            | ifstmt                    {printReduction("stmt","ifstmt", yylineno);}
            | whilestmt                 {printReduction("stmt","whilestmt", yylineno);}
            | forstmt                   {printReduction("stmt","forstmt", yylineno);}
            | returnstmt                {printReduction("stmt","returnstmt", yylineno);}
            | KEYW_BREAK PUNC_SEMIC     {printReduction("stmt","KEYW_BREAK PUNC_SEMIC", yylineno);}
            | KEYW_CONT PUNC_SEMIC      {printReduction("stmt","KEYW_CONT PUNC_SEMIC", yylineno);}
            | block                     {printReduction("stmt","block", yylineno);}
            | funcdef                   {printReduction("stmt","funcdef", yylineno);}
            | PUNC_SEMIC                {printReduction("stmt"," PUNC_SEMIC", yylineno);}
            |                           {printReduction("stmt","empty", yylineno);}
            ;

statements: stmt statements             {printReduction("statements","stmt statements", yylineno);}
            |                           {printReduction("statements","empty", yylineno);}
            ;

expr:       assignexpr                  {printReduction("expr","assignexpr", yylineno);}
            | expr op expr              {printReduction("expr","expr op expr", yylineno);}
            | term                      {printReduction("expr","term", yylineno);}
            ;

op:         OPER_PLUS                   {printReduction("op","OPER_PLUS", yylineno);}
            | OPER_MINUS                {printReduction("op","OPER_MINUS", yylineno);}
            | OPER_MUL                  {printReduction("op","OPER_MUL", yylineno);}
            | OPER_DIV                  {printReduction("op","OPER_DIV", yylineno);}
            | OPER_MOD                  {printReduction("op","OPER_MOD", yylineno);}
            | OPER_GRT                  {printReduction("op","OPER_GRT", yylineno);}
            | OPER_GRE                  {printReduction("op","OPER_GRE", yylineno);}
            | OPER_LET                  {printReduction("op","OPER_LET", yylineno);}
            | OPER_LEE                  {printReduction("op","OPER_LEE", yylineno);}
            | OPER_EQ2                  {printReduction("op","OPER_EQ2", yylineno);}
            | OPER_NEQ                  {printReduction("op","OPER_NEQ", yylineno);}
            | KEYW_AND                  {printReduction("op","KEYW_AND", yylineno);}
            | KEYW_OR                   {printReduction("op","KEYW_OR", yylineno);}
            ;

term:       PUNC_LPARENTH expr PUNC_RPARENTH        { $$ = $2; printReduction("term","PUNC_LPARENTH expr PUNC_RPARENTH", yylineno);}
            | OPER_MINUS expr                       { $$ = -$2; printReduction("term","OPER_MINUS expr", yylineno);}
            | KEYW_NOT expr                         { $$ = !$2; printReduction("term","KEYW_NOT expr", yylineno);}
            | OPER_PLUS2 lvalue                     { $$ = ++$2; printReduction("term","OPER_PLUS2 lvalue", yylineno);}
            | lvalue OPER_PLUS2                     { $$ = $1++; printReduction("term","lvalue OPER_PLUS2", yylineno);}
            | OPER_MINUS2 lvalue                    { $$ = --$2; printReduction("term","OPER_MINUS2 lvalue", yylineno);}
            | lvalue OPER_MINUS2                    { $$ = $1--; printReduction("term","lvalue OPER_MINUS2", yylineno);}
            | primary                               { $$ = $1; printReduction("term","primary", yylineno);}
            ;

assignexpr: lvalue OPER_EQ expr;                   { $1 = $3; printReduction("assignexpr","lvalue OPER_EQ2 expr", yylineno);}

primary:    lvalue                                  {printReduction("primary","lvalue", yylineno);}
            | call                                  {printReduction("primary","call", yylineno);}
            | objectdef                             {printReduction("primary","objectdef", yylineno);}
            | PUNC_LPARENTH funcdef PUNC_RPARENTH   {printReduction("primary","PUNC_LPARENTH funcdef PUNC_RPARENTH", yylineno);}
            | const                                 {printReduction("primary","const", yylineno);}
            ;

lvalue:     ID                                      {printReduction("lvalue","ID", yylineno);}
            | KEYW_LOCAL ID                         {printReduction("lvalue","KEYW_LOCAL ID", yylineno);}
            | PUNC_COLON2 ID                        {printReduction("lvalue","PUNC_COLON2 ID", yylineno);}
            | member                                {printReduction("lvalue","member", yylineno);}
            ;

member:     lvalue PUNC_DOT ID                          {printReduction("member","lvalue PUNC_DOT ID", yylineno);}
            | lvalue PUNC_LBRACKET expr PUNC_RBRACKET   {printReduction("member","lvalue PUNC_LBRACKET expr PUNC_RBRACKET", yylineno);}
            | call PUNC_DOT ID                          {printReduction("member","call PUNC_DOT ID", yylineno);}
            | call PUNC_LBRACKET expr PUNC_RBRACKET     {printReduction("member","call PUNC_LBRACKET expr PUNC_RBRACKET", yylineno);}
            ;

call:       call PUNC_LPARENTH elist PUNC_RPARENTH                                      {printReduction("call","call PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);}
            |lvalue callsuffix                                                          {printReduction("call","lvalue callsuffix ID", yylineno);}
            | PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH     {printReduction("call","PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);}
            ;

callsuffix: normcall                                                {printReduction("callsuffix","normcall", yylineno);}
            |methodcall                                             {printReduction("callsuffix","methodcall", yylineno);}
            ;

normcall:   PUNC_LPARENTH elist PUNC_RPARENTH                       {printReduction("normcall","PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);};
methodcall: PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH          {printReduction("methodcall","PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);};

elist:      expr elistrep                                           {printReduction("elist","expr elistrep", yylineno);}
            |                                                       {printReduction("elist","empty", yylineno);}
            ;

elistrep:   PUNC_COMMA expr elistrep                                {printReduction("elistrep","PUNC_COMMA expr elistrep", yylineno);}
            | PUNC_COMMA expr                                       {printReduction("elistrep","PUNC_COMMA expr", yylineno);}
            |                                                       {printReduction("elistrep","empty", yylineno);}
            ;

objectdef:  PUNC_LBRACKET objectin PUNC_RBRACKET                    {printReduction("objectdef","PUNC_LBRACKET objectin PUNC_RBRACKET", yylineno);};
objectin:   elist                                                   {printReduction("objectin","elist", yylineno);}
            |indexed                                                {printReduction("objectin","indexed", yylineno);}
            |                                                       {printReduction("objectin","empty", yylineno);}
            ;

indexed:    indexedelem                                             {printReduction("indexed","indexedelem", yylineno);}
            |indexedelem indexrep                                   {printReduction("indexed","indexedelem indexrep", yylineno);}
            |                                                       {printReduction("indexed","empty", yylineno);}
            ;
indexrep:   PUNC_COMMA indexedelem                                  {printReduction("indexrep","PUNC_COMMA indexedelem", yylineno);}

indexedelem:PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE            {printReduction("indexedelem","PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE", yylineno);};

block:      PUNC_LBRACKET statements PUNC_RBRACKET                  {printReduction("block","PUNC_LBRACKET statements PUNC_RBRACKET", yylineno);}
            |                                                       {printReduction("block","empty", yylineno);}
            ;

funcdef:    KEYW_FUNC ID PUNC_LPARENTH idlist PUNC_RPARENTH block   {printReduction("funcdef","KEYW_FUNC ID PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
            |KEYW_FUNC PUNC_LPARENTH idlist PUNC_RPARENTH block     {printReduction("funcdef","KEYW_FUNC PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
            ;

const:      CONST_INT                                               {printReduction("const","CONST_INT", yylineno);}
            | CONST_REAL                                            {printReduction("const","CONST_REAL", yylineno);}    
            | STRING                                                {printReduction("const","STRING", yylineno);}
            | KEYW_NIL                                              {printReduction("const","KEYW_NIL", yylineno);}
            | KEYW_TRUE                                             {printReduction("const","KEYW_TRUE", yylineno);}
            | KEYW_FALSE                                            {printReduction("const","KEYW_FALSE", yylineno);}    
            ;

idlist:     ID ids                                                  {printReduction("idlist","ID ids", yylineno);}
            |ID                                                     {printReduction("idlist","ID", yylineno);}
            |                                                       {printReduction("idlist","empty", yylineno);}
            ;

ids:        PUNC_COMMA ID ids                                       {printReduction("ids","PUNC_COMMA ID ids", yylineno);}
            | PUNC_COMMA ID                                         {printReduction("ids","PUNC_COMMA ID", yylineno);}
            |                                                       {printReduction("ids","empty", yylineno);}
            ;

ifstmt:     KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt           {printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);}
            |KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt KEYW_ELSE stmt           {printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt KEYW_ELSE stmt", yylineno);};
whilestmt:  KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt            {printReduction("whilestmt","KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);};
forstmt:    KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt            {printReduction("forstmt","KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt", yylineno);};
returnstmt: KEYW_RET PUNC_SEMIC         {printReduction("returnstmt","KEYW_RET PUNC_SEMIC", yylineno);}
            |KEYW_RET expr PUNC_SEMIC           {printReduction("returnstmt","KEYW_RET expr PUNC_SEMIC", yylineno);}
            ;

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
