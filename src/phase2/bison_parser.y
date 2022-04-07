%{
    #include <stdio.h>
    #include <assert.h>
    #include <string.h>
    #include "symtable.c"
    #include "../../inc/phase2/symtable.h"

    #define YYERROR_VERBOSE

    SymTable st;
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    int unsigned scope = 0;
    int unnamed_funcs = 0;

    int yylex(void);
    int yyerror(const char* yaccerror);
    
    void printReduction(const char* from,const char* to, int line){
        printf("[#%d] Reduction: %s <--- %s;\n",line, from, to);
    }

    char* getFuncName() {
        char name[18];
        char number[10];
        strcpy(name, "function");
        sprintf(number, "%d", unnamed_funcs);
        unnamed_funcs++;
        strcat(name, number); 
        return strdup(name);
    }

    char* libFuncs[12] = {"print",
                          "input",
                          "objectmemberkeys",
                          "objecttotalmembers",
                          "objectcopy",
                          "totalarguments",
                          "argument",
                          "typeof",
                          "strtonum",
                          "sqrt",
                          "cos",
                          "sin"};   

    int checkIfAllowed(char* name) {
        for(int i = 0; i < 12; i++) {
            if(!strcmp(libFuncs[i], name)) {
                return 0;
            }
        }
        return 1;
    }
%}

%union {
    int intVal; 
    char* strVal; 
    double realVal;
}


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

%token <intVal> CONST_INT
%token <realVal> CONST_REAL

%token <strVal> ID
%token COMM_SL
%token COMM_ML
%token COMM_NEST
%token <strVal> STRING

%type <intVal> expr
%type <intVal> term
%type <intVal> assignexpr
%type <intVal> primary
%type <intVal> lvalue

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

%start program

%%

program:    statements                  {printReduction("program","statements", yylineno);}
            ;

statements: stmt statements             {printReduction("statements","stmt statements", yylineno);}
            |                           {printReduction("statements","empty", yylineno);}
            ;

stmt:       expr PUNC_SEMIC             {printReduction("stmt","expr PUNC_SEMIC", yylineno);}
            | ifstmt                    {printReduction("stmt","ifstmt", yylineno);}
            | whilestmt                 {printReduction("stmt","whilestmt", yylineno);}
            | forstmt                   {printReduction("stmt","forstmt", yylineno);}
            | returnstmt                {printReduction("stmt","returnstmt", yylineno);}
            | KEYW_BREAK PUNC_SEMIC     {printReduction("stmt","KEYW_BREAK PUNC_SEMIC", yylineno);}
            | KEYW_CONT PUNC_SEMIC      {printReduction("stmt","KEYW_CONT PUNC_SEMIC", yylineno);}
            | block                     {printReduction("stmt","block", yylineno);}
            | funcdef                   {printReduction("stmt","funcdef", yylineno);}
            | PUNC_SEMIC                {printReduction("stmt"," PUNC_SEMIC", yylineno);}
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

assignexpr: lvalue OPER_EQ expr                     { $1 = $3; printReduction("assignexpr","lvalue OPER_EQ expr", yylineno);};

primary:    lvalue                                  {printReduction("primary","lvalue", yylineno);}
            | call                                  {printReduction("primary","call", yylineno);}
            | objectdef                             {printReduction("primary","objectdef", yylineno);}
            | PUNC_LPARENTH funcdef PUNC_RPARENTH   {printReduction("primary","PUNC_LPARENTH funcdef PUNC_RPARENTH", yylineno);}
            | const                                 {printReduction("primary","const", yylineno);}
            ;

lvalue:     ID                                      {
                                                        if(scope==0U){SymTable_insert(st, $1, GLOBAL, scope, yylineno);}
                                                        else{SymTable_insert(st, $1, LOCAL, scope, yylineno);}
                                                        printReduction("lvalue","ID", yylineno);
                                                    }
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

elistrep:   PUNC_COMMA expr elistrep                                {printReduction("elistrep","PUNC_COMMA expr elistrep", yylineno);}
            | PUNC_COMMA expr                                       {printReduction("elistrep","PUNC_COMMA expr", yylineno);}
            |                                                       {printReduction("elistrep","empty", yylineno);}
            ;

elist:      expr elistrep                                           {printReduction("elist","expr elistrep", yylineno);}
            |                                                       {printReduction("elist","empty", yylineno);}
            ;

objectin:   elist                                                   {printReduction("objectin","elist", yylineno);}
            |indexed                                                {printReduction("objectin","indexed", yylineno);}
            |                                                       {printReduction("objectin","empty", yylineno);}
            ;
objectdef:  PUNC_LBRACKET objectin PUNC_RBRACKET                    {printReduction("objectdef","PUNC_LBRACKET objectin PUNC_RBRACKET", yylineno);};

indexed:    indexedelem indexrep                                    {printReduction("indexed","indexedelem indexrep", yylineno);}
            ;

indexedelem:PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE            {printReduction("indexedelem","PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE", yylineno);};

indexrep:   PUNC_COMMA indexedelem indexrep                         {printReduction("indexrep","PUNC_COMMA indexedelem", yylineno);}
            |                                                       {printReduction("indexrep","empty", yylineno);}
            ;

block:      PUNC_LBRACE {scope++;} statements PUNC_RBRACE           {SymTable_hide(st, scope); scope--;printReduction("block","PUNC_LBRACE statements PUNC_RBRACE", yylineno);}
            ;

funcdef:    KEYW_FUNC ID PUNC_LPARENTH {scope++;} idlist {scope--;} PUNC_RPARENTH block   {printReduction("funcdef","KEYW_FUNC ID PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
            |KEYW_FUNC PUNC_LPARENTH {scope++;} idlist {scope--;} PUNC_RPARENTH block     {printReduction("funcdef","KEYW_FUNC PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
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


int yyerror(const char* yaccerror){
    printf("ERROR: %s",yaccerror);
}

int main(int argc, char **argv) {

    int index;

    if ( argc != 2 ) {

        printf("\e[1;31merror\e[0m: no input file\n");
        return 0;
    }

    if ( !(yyin = fopen(argv[1], "r")) ) {

        perror("fopen()");
        return 1;
    }

    assert( (st = SymTable_create()) );


    yyparse();

    SymTable_print(st);
}
