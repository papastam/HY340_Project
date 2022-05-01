%{
    #include <stdio.h>
    #include <assert.h>
    #include <string.h>
    #include <stdlib.h>

    #include "../../inc/phase3/quads.h"
    #include "../../inc/phase2/utils.h"

    #define YYERROR_VERBOSE

    SymTable st;
    extern int yylineno;
    extern char* yytext;
    extern FILE* yyin;
    uint scope = 0;
    char* current_function;

    struct quad    *quads;
    unsigned int    total;
    unsigned int    currQuad;

    //0=not a referance,1=local referance, 2=global referance 
    int ref_flag;

    int yylex(void);
    int yyerror(const char *yaccerror);

%}

%union {
    int intVal; 
    double realVal;
    char* strVal; 
    unsigned char boolVal;
    struct SymbolTableEntry *symbol;
    struct expr *expression;
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
%token <strVal> STRING

%type <expression> assignexpr
%type <expression> expr
%type <expression> term
%type <expression> primary
%type <expression> lvalue
%type <expression> const
/*
%type <strVal> op
*/
%left PUNC_LPARENTH PUNC_RPARENTH 
%left PUNC_LBRACKET PUNC_RBRACKET 
%left PUNC_DOT PUNC_DOT2
%right KEYW_NOT OPER_PLUS2 OPER_MINUS2 UNARY_MINUS
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
            | KEYW_BREAK PUNC_SEMIC     {
                                            #ifdef P2DEBUG
                                            if(scope == 0)
                                                printf("\033[0;31mERROR [#%d]:\033[0m Can't have a break statement while not in a loop\n",yylineno);
                                            #endif
                                            printReduction("stmt","KEYW_BREAK PUNC_SEMIC", yylineno);
                                        }
            | KEYW_CONT PUNC_SEMIC      {
                                            #ifdef P2DEBUG
                                            if(scope == 0)
                                                printf("\033[0;31mERROR [#%d]:\033[0m Can't have a continue statement while not in a loop\n",yylineno);
                                            #endif
                                            printReduction("stmt","KEYW_CONT PUNC_SEMIC", yylineno);
                                        }
            | block                     {printReduction("stmt","block", yylineno);}
            | funcdef                   {printReduction("stmt","funcdef", yylineno);}
            | PUNC_SEMIC                {printReduction("stmt"," PUNC_SEMIC", yylineno);}
            ;

expr:       assignexpr                  { $$ = $1; printReduction("expr","assignexpr", yylineno);}
            | expr OPER_PLUS expr       {printReduction("expr","expr OPER_PLUS expr", yylineno);}
            | expr OPER_MINUS expr      {printReduction("expr","expr OPER_MINUS expr", yylineno);}
            | expr OPER_MUL expr        {printReduction("expr","expr OPER_MUL expr", yylineno);}
            | expr OPER_DIV expr        {printReduction("expr","expr OPER_DIV expr", yylineno);}
            | expr OPER_MOD expr        {printReduction("expr","expr OPER_MOD expr", yylineno);}
            | expr OPER_GRT expr        {printReduction("expr","expr OPER_GRT expr", yylineno);}
            | expr OPER_GRE expr        {printReduction("expr","expr OPER_GRE expr", yylineno);}
            | expr OPER_LET expr        {printReduction("expr","expr OPER_LET expr", yylineno);}
            | expr OPER_LEE expr        {printReduction("expr","expr OPER_LEE expr", yylineno);}
            | expr OPER_EQ2 expr        {printReduction("expr","expr OPER_EQ2 expr", yylineno);}
            | expr OPER_NEQ expr        {printReduction("expr","expr OPER_NEQ expr", yylineno);}
            | expr KEYW_AND expr        {printReduction("expr","expr KEYW_AND expr", yylineno);}
            | expr KEYW_OR expr         {printReduction("expr","expr KEYW_OR expr", yylineno);}
            | term                      { $$ = $1; printReduction("expr","term", yylineno);}
            ;

/*
op:         OPER_PLUS                   {$$ = "+"; printReduction("op","OPER_PLUS", yylineno);}
            | OPER_MINUS                {$$ = "-"; printReduction("op","OPER_MINUS", yylineno);}
            | OPER_MUL                  {$$ = "*"; printReduction("op","OPER_MUL", yylineno);}
            | OPER_DIV                  {$$ = "/"; printReduction("op","OPER_DIV", yylineno);}
            | OPER_MOD                  {$$ = "%"; printReduction("op","OPER_MOD", yylineno);}
            | OPER_GRT                  {$$ = ">"; printReduction("op","OPER_GRT", yylineno);}
            | OPER_GRE                  {$$ = ">="; printReduction("op","OPER_GRE", yylineno);}
            | OPER_LET                  {$$ = "<"; printReduction("op","OPER_LET", yylineno);}
            | OPER_LEE                  {$$ = "<="; printReduction("op","OPER_LEE", yylineno);}
            | OPER_EQ2                  {$$ = "=="; printReduction("op","OPER_EQ2", yylineno);}
            | OPER_NEQ                  {$$ = "!="; printReduction("op","OPER_NEQ", yylineno);}
            | KEYW_AND                  {$$ = "&&"; printReduction("op","KEYW_AND", yylineno);}
            | KEYW_OR                   {$$ = "||"; printReduction("op","KEYW_OR", yylineno);}
            ;
*/

term:       PUNC_LPARENTH expr PUNC_RPARENTH        {printReduction("term","PUNC_LPARENTH expr PUNC_RPARENTH", yylineno);}
            | OPER_MINUS expr %prec UNARY_MINUS     {printReduction("term","OPER_MINUS expr", yylineno);}
            | KEYW_NOT expr                         {printReduction("term","KEYW_NOT expr", yylineno);}
            | OPER_PLUS2 lvalue                     {
                                                        char* name = yylval.strVal;
                                                        struct SymbolTableEntry *res = search_all_scopes(st, name, scope);
                                                        if(!res) {
                                                            #ifdef P2DEBUG
                                                            printf("\033[0;31mERROR [#%d]:\033[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
                                                            #endif
                                                        }
                                                        else {
                                                            if(res->type == LIBFUNC || res->type == USERFUNC) {
                                                                #ifdef P2DEBUG
                                                                printf("\033[0;31mERROR [#%d]:\033[0m Operation \"++%s\" not allowed. %s is a function.\n", yylineno, name, name);
                                                                #endif
                                                            }
                                                        }
                                                        printReduction("term","OPER_PLUS2 lvalue", yylineno);
                                                    }
            | lvalue {
                        char* name = yylval.strVal;
                        struct SymbolTableEntry* res = search_all_scopes(st, name, scope);

                        if(!res) {
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR  [#%d]:\033[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
                            #endif
                        }
                        else {
                            if(res->type == LIBFUNC || res->type == USERFUNC) {
                                #ifdef P2DEBUG
                                printf("\033[0;31mERROR  [#%d]:\033[0m Operation \"++%s\" not allowed. \"%s\" is a function.", yylineno, name, name);
                                #endif
                            }
                        }
                    } OPER_PLUS2                     {printReduction("term","lvalue OPER_PLUS2", yylineno);}
            | OPER_MINUS2 lvalue                    {
                                                        char* name = yylval.strVal;
                                                        struct SymbolTableEntry *res = search_all_scopes(st, name, scope);
                                                        if(!res) {
                                                            #ifdef P2DEBUG
                                                            printf("\033[0;31mERROR [#%d]:\033[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
                                                            #endif
                                                        }
                                                        else {
                                                            if(res->type == LIBFUNC || res->type == USERFUNC) {
                                                                #ifdef P2DEBUG
                                                                printf("\033[0;31mERROR [#%d]:\033[0m Operation \"--%s\" not allowed. %s is a function.\n", yylineno, name, name);
                                                                #endif
                                                            }
                                                        }
                                                        printReduction("term","OPER_MINUS2 lvalue", yylineno);
                                                    }
            | lvalue OPER_MINUS2                    {
                                                        char* name = yylval.strVal;
                                                        struct SymbolTableEntry *res = search_all_scopes(st, name, scope);
                                                        if(!res) {
                                                            #ifdef P2DEBUG
                                                            printf("\033[0;31mERROR [#%d]:\033[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
                                                            #endif
                                                        }
                                                        else {
                                                            if(res->type == LIBFUNC || res->type == USERFUNC) {
                                                                #ifdef P2DEBUG
                                                                printf("\033[0;31mERROR [#%d]:\033[0m Operation \"%s--\" not allowed. %s is a function.\n", yylineno, name, name);
                                                                #endif
                                                            }
                                                        }
                                                        printReduction("term","lvalue OPER_MINUS2", yylineno);
                                                    }
            | primary                               {printReduction("term","primary", yylineno);}
            ;

assignexpr: lvalue {
                    if(ref_flag==1){//LOCAL ID
                        struct SymbolTableEntry *e = SymTable_lookup_scope(st, yylval.strVal, scope);

                        if(e==NULL){
                            struct SymbloTableEntry *new = SymTable_insert(st, yylval.strVal, (scope?LOCAL:GLOBAL), scope, yylineno);
                            #ifdef P2DEBUG
                            printf("\033[0;32mSuccess [#%d]:\033[0m Symbol %s has been added to the symbol table\n", yylineno,yylval.strVal);
                            #endif
                            $1->sym = new;
                        }else if(e->scopeno<scope){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s cannot be accessed from scope %d\n", yylineno,yylval.strVal,scope);
                            #endif
                        }else if(e->type==USERFUNC || e->type==LIBFUNC){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s defined as a function\n", yylineno,yylval.strVal);
                            #endif
                        }else if(e->type==FORMAL && e->scopeno!=scope){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s cannot be accessed from scope %d\n", yylineno,yylval.strVal,scope);
                            #endif
                        }else{//FOUND CASE
                            $1->sym = e;
                        }
                    }else if(ref_flag==2){//:: ID
                        struct SymbolTableEntry *e = SymTable_lookup_scope(st, yylval.strVal, 0U);

                        if(!e){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m: Symbol %s is not defined\n", yylineno,yylval.strVal);
                            #endif
                        }else{
                            $1->sym = e;
                        }
                    }else{//ID
                        struct SymbolTableEntry *e=search_all_scopes(st, yylval.strVal,scope);

                        if(e==NULL){
                            struct SymbolTableEntry *new=SymTable_insert(st, yylval.strVal, (scope?LOCAL:GLOBAL), scope, yylineno);
                            #ifdef P2DEBUG
                            printf("\033[0;32mSuccess [#%d]:\033[0m Symbol %s has been added to the symbol table\n", yylineno,yylval.strVal);
                            #endif
                            $1->sym = new;
                        }else if((e->type==LOCAL || e->type==USERFUNC) && e->scopeno!=scope){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s cannot be accessed from scope %d\n", yylineno,yylval.strVal,scope);
                            #endif
                        }else if(e->type==USERFUNC || e->type==LIBFUNC){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s is defined as a function\n", yylineno ,yylval.strVal);
                            #endif
                        }else if(e->type==FORMAL && e->scopeno!=scope){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s cannot be accessed from scope %d\n", yylineno,yylval.strVal,scope);
                            #endif
                        }else{
                            $1->sym = e;;
                        }
                    }
                    ref_flag=0;                                        
                    
                    } OPER_EQ expr                  { $$ = $4; printReduction("assignexpr","lvalue OPER_EQ expr", yylineno);};

primary:    lvalue                                  {
                                                        struct SymbolTableEntry *e=search_all_scopes(st, yylval.strVal,scope);

                                                        if(!e){
                                                            #ifdef P2DEBUG
                                                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s is not defined\n", yylineno,yylval.strVal);
                                                            #endif
                                                        }else if(e->type==LOCAL && e->scopeno!=scope){
                                                            #ifdef P2DEBUG
                                                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s cannot be accessed from scope %d\n", yylineno,yylval.strVal,scope);
                                                            #endif
                                                        }else if(e->type==FORMAL && e->scopeno!=scope){
                                                            #ifdef P2DEBUG
                                                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s cannot be accessed from scope %d\n", yylineno, yylval.strVal,scope);
                                                            #endif
                                                        }else if(e->type==USERFUNC || e->type==LIBFUNC){
                                                            #ifdef P2DEBUG
                                                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s is defined as a function\n", yylineno ,yylval.strVal);
                                                            #endif
                                                        }else{//SUCESS CASE!
                                                            $$ = $1;
                                                            $$->sym = e;    
                                                            printExpression($$);
                                                        }
                                                        
                                                        printReduction("primary","lvalue", yylineno);}
            | call                                  {printReduction("primary","call", yylineno);}
            | objectdef                             {printReduction("primary","objectdef", yylineno);}
            | PUNC_LPARENTH funcdef PUNC_RPARENTH   {printReduction("primary","PUNC_LPARENTH funcdef PUNC_RPARENTH", yylineno);}
            | const                                 { $$ = $1; printReduction("primary","const", yylineno);}
            ;

lvalue:     ID                                      {   ref_flag=0; 
                                                        $$ = new_expr(var_e);
                                                        printReduction("lvalue","ID", yylineno);}
            | KEYW_LOCAL ID                         {   ref_flag=1;
                                                        $$ = new_expr(var_e);
                                                        printReduction("lvalue","KEYW_LOCAL ID", yylineno);}
            | PUNC_COLON2 ID                        {   ref_flag=2;
                                                        $$ = new_expr(var_e);
                                                        printReduction("lvalue","PUNC_COLON2 ID", yylineno);}
            | member                                {   printReduction("lvalue","member", yylineno);}
            ;

member:     lvalue PUNC_DOT ID                          {printReduction("member","lvalue PUNC_DOT ID", yylineno);}
            | lvalue PUNC_LBRACKET expr PUNC_RBRACKET   {printReduction("member","lvalue PUNC_LBRACKET expr PUNC_RBRACKET", yylineno);}
            | call PUNC_DOT ID                          {printReduction("member","call PUNC_DOT ID", yylineno);}
            | call PUNC_LBRACKET expr PUNC_RBRACKET     {printReduction("member","call PUNC_LBRACKET expr PUNC_RBRACKET", yylineno);}
            ;

call:       call PUNC_LPARENTH elist PUNC_RPARENTH                                      {printReduction("call","call PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);}
            |lvalue {
                        struct SymbolTableEntry *e = search_all_scopes(st, yylval.strVal, scope);
                        if(e==NULL){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m: Symbol %s is not defined\n", yylineno,yylval.strVal);
                            #endif
                        }else if(e->type==LOCAL && e->scopeno!=scope){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s cannot be accessed from scope %d\n", yylineno,yylval.strVal,scope);
                            #endif
                        }else if(e->type!=USERFUNC && e->type!=LIBFUNC){
                            #ifdef P2DEBUG
                            printf("\033[0;31mERROR [#%d]:\033[0m: Symbol %s is not a function\n", yylineno,yylval.strVal);
                            #endif
                        }
                    }callsuffix                                                          {printReduction("call","lvalue callsuffix", yylineno);}
            | PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH     {printReduction("call","PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);}
            ;

callsuffix: normcall                                                {printReduction("callsuffix","normcall", yylineno);}
            |methodcall                                             {printReduction("callsuffix","methodcall", yylineno);}
            ;

normcall:   PUNC_LPARENTH elist PUNC_RPARENTH                       {printReduction("normcall","PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);};
methodcall: PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH          {printReduction("methodcall","PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);};

elistrep:   PUNC_COMMA expr elistrep                                {printReduction("elistrep","PUNC_COMMA expr elistrep", yylineno);}
            |                                                       {printReduction("elistrep","PUNC_COMMA expr", yylineno);}
            ;

elist:      expr elistrep                                           {printReduction("elist","expr elistrep", yylineno);}
            |                                                       {printReduction("elist","empty", yylineno);}
            ;

objectin:   elist                                                   {printReduction("objectin","elist", yylineno);}
            |indexed                                                {printReduction("objectin","indexed", yylineno);}
            ;
objectdef:  PUNC_LBRACKET objectin PUNC_RBRACKET                    {printReduction("objectdef","PUNC_LBRACKET objectin PUNC_RBRACKET", yylineno);};

indexed:    indexedelem indexrep                                    {printReduction("indexed","indexedelem indexrep", yylineno);}
            ;

indexedelem:PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE            {printReduction("indexedelem","PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE", yylineno);};

indexrep:   PUNC_COMMA indexedelem indexrep                         {printReduction("indexrep","PUNC_COMMA indexedelem", yylineno);}
            |                                                       {printReduction("indexrep","empty", yylineno);}
            ;

block:      PUNC_LBRACE {++scope;} statements PUNC_RBRACE           {SymTable_hide(st, scope); scope--;printReduction("block","PUNC_LBRACE statements PUNC_RBRACE", yylineno);}
            ;

funcdef:    KEYW_FUNC ID {
                            char* name = yylval.strVal;
                            current_function = strdup(name);
                            struct SymbolTableEntry* res = search_all_scopes(st, name, scope);
                            
                            if(res && res->scopeno>=scope) {
                            if(res->type == GLOBAL){
                                #ifdef P2DEBUG
                                printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s already exists as a GLOBAL variable!\n", yylineno,name);
                                #endif
                            }else if(res->type == FORMAL){
                                #ifdef P2DEBUG
                                printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s already exists as a FORMAL variable!\n", yylineno, name);
                                #endif
                            }else if(res->type == LOCAL){
                                #ifdef P2DEBUG
                                printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s already exists as a LOCAL variable!\n", yylineno,name);
                                #endif
                            }else if(res->type == USERFUNC){
                                #ifdef P2DEBUG
                                printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s already exists as a user function!\n", yylineno,name);
                                #endif
                            }else if(res->type == LIBFUNC){
                                #ifdef P2DEBUG
                                printf("\033[0;31mERROR [#%d]:\033[0m Symbol %s already exists as a library function!\n", yylineno,name);
                                #endif
                            }}
                            else {
                                SymTable_insert(st, name, USERFUNC, scope, yylineno);
                                #ifdef P2DEBUG
                                printf("\033[0;32mSuccess:\033[0m Symbol %s has been added to the symbol table\n",name);
                                #endif
                            }
                        }
                        PUNC_LPARENTH {scope++;} idlist {scope--;} PUNC_RPARENTH block   {printReduction("funcdef","KEYW_FUNC ID PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
            |KEYW_FUNC {
                        char* name = getFuncName();
                        current_function = strdup(name);
                        SymTable_insert(st, name, USERFUNC, scope, yylineno);
                        #ifdef P2DEBUG
                        printf("\033[0;32mSuccess:\033[0m Symbol %s has been added to the symbol table\n",name);
                        #endif
                    }
                    PUNC_LPARENTH {scope++;} idlist {scope--;} PUNC_RPARENTH block     {printReduction("funcdef","KEYW_FUNC PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
            ;

const:      CONST_INT                                               {   printReduction("const","CONST_INT", yylineno);
                                                                        $$ = new_expr(constnum_e);
                                                                        $$->numConst = yylval.intVal;
                                                                        printExpression($$);
                                                                    }
            | CONST_REAL                                            {printReduction("const","CONST_REAL", yylineno);
                                                                        $$ = new_expr(constnum_e);
                                                                        $$->numConst = yylval.realVal;                                                                    
                                                                    }    
            | STRING                                                {printReduction("const","STRING", yylineno);
                                                                        $$ = new_expr(conststring_e);
                                                                        $$->strConst = yylval.strVal;  
                                                                    }
            | KEYW_NIL                                              {printReduction("const","KEYW_NIL", yylineno);
                                                                        $$ = new_expr(nil_e);  
                                                                    }
            | KEYW_TRUE                                             {printReduction("const","KEYW_TRUE", yylineno);
                                                                        $$ = new_expr(constbool_e);
                                                                        $$->boolConst = yylval.realVal;  
                                                                    }
            | KEYW_FALSE                                            {printReduction("const","KEYW_FALSE", yylineno);
                                                                        $$ = new_expr(constbool_e);
                                                                        $$->boolConst = yylval.realVal;  
                                                                    }    
            ;

idlist:     ID {
                char* name = yylval.strVal;
                struct SymbolTableEntry* res = SymTable_lookup_scope(st, name, scope);
                
                if(!checkIfAllowed(name)){
                        #ifdef P2DEBUG  
                        printf("\033[0;31mERROR [#%d]:\033[0m Can't have a formal variable \"%s\". It has the same name as a LIBFUNC.\n",yylineno , name);
                        #endif
                }else {
                    if(res) {
                        #ifdef P2DEBUG
                        printf("\033[0;31mERROR [#%d]:\033[0m Can't have a formal variable \"%s\". It has the same name as another FORMAL variable\n",yylineno , name);
                        #endif
                    }
                    else{
                        SymTable_insert(st, name, FORMAL, scope, yylineno);
                        SymTable_insert_func_arg(st, current_function, name);
                        // SymTable_insert_func_arg(st)
                        #ifdef P2DEBUG
                        printf("\033[0;32mSuccess [#%d]:\033[0m Symbol %s has been added to the symbol table\n",yylineno ,name);
                        #endif
                    }
                }
            } ids                                                  {printReduction("idlist","ID ids", yylineno);}
            |                                                      {printReduction("idlist","empty", yylineno);}
            ;

ids:        PUNC_COMMA ID {
                            char* name = yylval.strVal;
                            struct SymbolTableEntry* res = SymTable_lookup_scope(st, name, scope);
                            
                            if(!checkIfAllowed(name)){
                                    #ifdef P2DEBUG
                                    printf("\033[0;31mERROR [#%d]:\033[0m Can't have a formal variable \"%s\". It has the same name as a LIBFUNC.\n",yylineno , name);
                                    #endif
                            }else {
                                if(res) {
                                    #ifdef P2DEBUG
                                    printf("\033[0;31mERROR [#%d]:\033[0m Can't have a formal variable \"%s\". It has the same name as another FORMAL variable\n",yylineno , name);
                                    #endif    
                                }
                                else{
                                    SymTable_insert(st, name, FORMAL, scope, yylineno);
                                    SymTable_insert_func_arg(st, current_function, name);
                                    #ifdef P2DEBUG
                                    printf("\033[0;32mSuccess [#%d]:\033[0m Symbol %s has been added to the symbol table\n",yylineno ,name);
                                    #endif
                                }
                            }
                        } ids                                       {printReduction("ids","PUNC_COMMA ID ids", yylineno);}
            |                                                       {printReduction("ids","empty", yylineno);}
            ;

ifstmt:     KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt           {printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);}
            |KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt KEYW_ELSE stmt           {printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt KEYW_ELSE stmt", yylineno);};
whilestmt:  KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt            {printReduction("whilestmt","KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);};
forstmt:    KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt            {printReduction("forstmt","KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt", yylineno);};
returnstmt: KEYW_RET PUNC_SEMIC         {
                                            #ifdef P2DEBUG
                                            if(scope == 0)
                                                printf("\033[0;31mERROR [#%d]:\033[0m Can't have a return statement outside a function\n",yylineno );
                                            #endif
                                            printReduction("returnstmt","KEYW_RET PUNC_SEMIC", yylineno);
                                        }
            |KEYW_RET expr PUNC_SEMIC           {
                                                    #ifdef P2DEBUG
                                                    if(scope == 0)
                                                        printf("\033[0;31mERROR [#%d]:\033[0m Can't have a return statement outside a function\n",yylineno );
                                                    #endif
                                                    printReduction("returnstmt","KEYW_RET expr PUNC_SEMIC", yylineno);
                                                }
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

    #ifdef P2DEBUG
    /* SymTable_print_all(st);
    SymTable_print_scopes(st); */
    #endif
}
