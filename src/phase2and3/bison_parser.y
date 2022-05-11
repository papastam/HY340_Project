%{
    /*
    * TODO LIST
    *
    * break/continue lists
    * repeatcnt stack
    * while icode emition
    * for icode emition  ---> CHIOTIS
    * offset of variables ---> CHIOTIS
    * short circuit evaluation
    * reuse of tempvars when they are lvalues
    * 
    * DONE
    * table creation icode
    * functions icode
    */

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
    extern uint scope;
    char *current_function;
    extern FILE* file;

    #define REF_NONE   0
    #define REF_LOCAL  1
    #define REF_GLOBAL 2

    int ref_flag;

    int yylex(void);
    int yyerror(const char *yaccerror);

    extern struct quad  *quads;
    extern unsigned int  total;
    extern unsigned int  currQuad;

%}

%union {
    int intVal; 
    double realVal;
    char* strVal; 
    unsigned char boolVal;
    struct SymbolTableEntry *symbol;
    struct expr *expression;
    struct function_contents *fcont;
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

%type <strVal> funcname

%type <intVal> ifprefix

%type <fcont> methodcall
%type <fcont> normcall
%type <fcont> callsuffix

%type <symbol> funcprefix
%type <symbol> funcdef

%type <expression> member
%type <expression> assignexpr
%type <expression> expr
%type <expression> term
%type <expression> primary
%type <expression> lvalue
%type <expression> const
%type <expression> objectdef
%type <expression> objectin
%type <expression> elistrep 
%type <expression> elist
%type <expression> indexed
%type <expression> indexedelem
%type <expression> indexrep
%type <expression> call

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

program:
    statements
        {
            printReduction("program","statements", yylineno);
        }
    ;

statements: 
    stmt statements
        {
            printReduction("statements","stmt statements", yylineno);
        }
    |
        {
            printReduction("statements","empty", yylineno);
        }
    ;

stmt:       
    expr PUNC_SEMIC
        { 
            #ifdef P3DEBUG 
            if ( $1 ) {

                printf("\nStatement in line %d contains the expression:\n",yylineno);
                printExpression($1); 
            }
            #endif 

            printReduction("stmt","expr PUNC_SEMIC", yylineno);
            resettemp();
        }
    | ifstmt
        {
            printReduction("stmt","ifstmt", yylineno);
        }
    | whilestmt
        {
            printReduction("stmt","whilestmt", yylineno);
        }
    | forstmt
        {
            printReduction("stmt","forstmt", yylineno);
        }
    | returnstmt
        {
            printReduction("stmt","returnstmt", yylineno);
        }
    | KEYW_BREAK PUNC_SEMIC
        {
            #ifdef P2DEBUG
            if ( !scope )
                printf("\e[0;31mERROR [#%d]:\e[0m Can't have a break statement while not in a loop\n", yylineno);
            #endif

            printReduction("stmt","KEYW_BREAK PUNC_SEMIC", yylineno);
        }
    | KEYW_CONT PUNC_SEMIC
        {
            #ifdef P2DEBUG
            if ( !scope )
                printf("\e[0;31mERROR [#%d]:\e[0m Can't have a continue statement while not in a loop\n", yylineno);
            #endif

            printReduction("stmt","KEYW_CONT PUNC_SEMIC", yylineno);
        }
    | block
        {
            printReduction("stmt","block", yylineno);
        }
    | funcdef
        {
            printReduction("stmt","funcdef", yylineno);
        }
    | PUNC_SEMIC
        {
            printReduction("stmt"," PUNC_SEMIC", yylineno);
        }
    ;

expr:
    assignexpr
        {
                    $$ = $1;
                    printReduction("expr","assignexpr", yylineno);
        }
    | expr OPER_PLUS expr
        {
            $$ = new_expr(arithexpr_e);
            $$->sym = newtemp();
            emit(add,$$, $1, $3,0);
            printReduction("expr","expr OPER_PLUS expr", yylineno);
        }
    | expr OPER_MINUS expr
        {
            $$ = new_expr(arithexpr_e);
            $$->sym = newtemp();
            emit(sub,$$, $1, $3,0);
            printReduction("expr","expr OPER_MINUS expr", yylineno);
        }
    | expr OPER_MUL expr
        {
            $$ = new_expr(arithexpr_e);
            $$->sym = newtemp();
            emit(mul,$$, $1, $3,0);
            printReduction("expr","expr OPER_MUL expr", yylineno);
        }
    | expr OPER_DIV expr
        {
            $$ = new_expr(arithexpr_e);
            $$->sym = newtemp(); emit(div_o,$$, $1, $3,0);
            printReduction("expr","expr OPER_DIV expr", yylineno);
        
        }
    | expr OPER_MOD expr
        {
            $$ = new_expr(arithexpr_e);
            $$->sym = newtemp(); emit(mod,$$, $1, $3,0);
            printReduction("expr","expr OPER_MOD expr", yylineno);
        }
    | expr OPER_GRT expr
        {
            $$ = new_expr(constbool_e);
            $$->sym = newtemp();
            emit(if_greater, $$, $1, $3,0);
            emit(assign, $$, newexpr_constbool(0), NULL,0);
            emit(jump,NULL,NULL,NULL,0);
            emit(assign, $$, newexpr_constbool(1), NULL,0);
            printReduction("expr","expr OPER_GRT expr", yylineno);
        }
    | expr OPER_GRE expr
        {
            $$ = new_expr(constbool_e);
            $$->sym = newtemp();
            emit(if_greatereq, $$, $1, $3,0);
            emit(assign, $$, newexpr_constbool(0), NULL,0);
            emit(jump,NULL,NULL,NULL,0);emit(assign, $$, newexpr_constbool(1), NULL,0);
            printReduction("expr","expr OPER_GRE expr", yylineno);
        }
    | expr OPER_LET expr
        {
            $$ = new_expr(constbool_e);
            $$->sym = newtemp();
            emit(if_less, $$, $1, $3,0);
            emit(assign, $$, newexpr_constbool(0), NULL,0);
            emit(jump,NULL,NULL,NULL,0);
            emit(assign, $$, newexpr_constbool(1), NULL,0);
            printReduction("expr","expr OPER_LET expr", yylineno);
        }
    | expr OPER_LEE expr
        {
            $$ = new_expr(constbool_e);
            $$->sym = newtemp();
            emit(if_lesseq, $$, $1, $3,0);
            emit(assign, $$, newexpr_constbool(0), NULL,0);
            emit(jump, NULL, NULL, NULL, 0);
            emit(assign, $$, newexpr_constbool(1), NULL,0);
            printReduction("expr","expr OPER_LEE expr", yylineno);
        }
    | expr OPER_EQ2 expr
        {
            $$ = new_expr(constbool_e);
            $$->sym = newtemp();
            emit(if_eq, $$, $1, $3,0);
            emit(assign, $$, newexpr_constbool(0), NULL,0);
            emit(jump,NULL,NULL,NULL,0);
            emit(assign, $$, newexpr_constbool(1), NULL,0);
            printReduction("expr","expr OPER_EQ2 expr", yylineno);
        }
    | expr OPER_NEQ expr
        {
            $$ = new_expr(constbool_e);
            $$->sym = newtemp();
            emit(if_noteq, $$, $1, $3,0);
            emit(assign, $$, newexpr_constbool(0), NULL,0);
            emit(jump,NULL,NULL,NULL,0);
            emit(assign, $$, newexpr_constbool(1), NULL,0);
            printReduction("expr","expr OPER_NEQ expr", yylineno);
        }
    | expr KEYW_AND expr
        {
            printReduction("expr","expr KEYW_AND expr", yylineno);
        }
    | expr KEYW_OR expr
        {
            printReduction("expr","expr KEYW_OR expr", yylineno);
        }
    | term
        {
            $$ = $1;
            printReduction("expr","term", yylineno);
        }
    ;

term:
    PUNC_LPARENTH expr PUNC_RPARENTH
        {
            printReduction("term","PUNC_LPARENTH expr PUNC_RPARENTH", yylineno);
        }
    | OPER_MINUS expr %prec UNARY_MINUS
        {
            arithexpr_check($2);
            $$ = new_expr(arithexpr_e);
            $$->sym = newtemp();
            emit(uminus, $$, $2, NULL, 0);
            printReduction("term","OPER_MINUS expr", yylineno);
        }
    | KEYW_NOT expr
        {
            printReduction("term","KEYW_NOT expr", yylineno);
        }
    | OPER_PLUS2 lvalue
        {
            char *name = $2->strConst;
            struct SymbolTableEntry *res = search_all_scopes(st, name, scope);


            #ifdef P2DEBUG
            if ( !res )
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                    printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is a function.\n", yylineno, name, name);
            #endif

            arithexpr_check($2); // ? wtf is that ? stoopid bitchez

            if ( $2->type == tableitem_e ) {

                $$ = emit_iftableitem($2);
                emit(add, $$, newexpr_constnum(1), $$, 0);
                emit(tablesetelem, $2, $$, $2->index, 0);
            }
            else {

                emit(add, $2, newexpr_constnum(1), $2, 0);
                $$ = new_expr(arithexpr_e);
                $$->sym = newtemp();
                emit(assign, $$, $2, NULL,0);
            }

            printReduction("term","OPER_PLUS2 lvalue", yylineno);
        }
    | lvalue OPER_PLUS2
        {
            char *name = yylval.strVal;
            struct SymbolTableEntry *res = search_all_scopes(st, name, scope);


            #ifdef P2DEBUG
            if ( !res )
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
            else if (res->type == LIBFUNC || res->type == USERFUNC)
                    printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is a function.\n", yylineno, name, name);
            #endif

            arithexpr_check($1);

            $$ = new_expr(arithexpr_e);
            $$->sym = newtemp();

            if ( $1->type == tableitem_e ) {

                struct expr *val = emit_iftableitem($1);

                emit(assign, $$, val, NULL, 0);
                emit(add, val, newexpr_constnum(1), val, 0);
                emit(tablesetelem, val, $1, $1->index, 0);
            }
            else {

                emit(assign, $$, $1, NULL, 0);
                emit(add, $1, newexpr_constnum(1), $1, 0);
            }

            printReduction("term","lvalue OPER_PLUS2", yylineno);
        }
    | OPER_MINUS2 lvalue
        {
            char* name = yylval.strVal;
            struct SymbolTableEntry *res = search_all_scopes(st, name, scope);
            if(!res) {
                #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
                #endif
            }
            else {
                if(res->type == LIBFUNC || res->type == USERFUNC) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Operation \"--%s\" not allowed. %s is a function.\n", yylineno, name, name);
                    #endif
                }
            }
            
            arithexpr_check($2);
            if($2->type==tableitem_e) {
                $$ = emit_iftableitem($2);
                emit(sub, $$, newexpr_constnum(1), $$,0);
                emit(tablesetelem, $$, $2, $2->index,0);
            }else{
                emit(sub, $2, newexpr_constnum(1), $2,0);
                $$ = new_expr(arithexpr_e);
                $$->sym = newtemp();
                emit(assign, $$, $2, NULL,0);
            }
            printReduction("term","OPER_MINUS2 lvalue", yylineno);
        }
    | lvalue OPER_MINUS2
        {
            char* name = yylval.strVal;
            struct SymbolTableEntry *res = search_all_scopes(st, name, scope);
            if(!res) {
                #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
                #endif
            }
            else {
                if(res->type == LIBFUNC || res->type == USERFUNC) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Operation \"%s--\" not allowed. %s is a function.\n", yylineno, name, name);
                    #endif
                }
            }

            arithexpr_check($1);
            $$ = new_expr(arithexpr_e);
            $$->sym = newtemp();
            if($1->type==tableitem_e){
                struct expr* val = emit_iftableitem($1);
                emit(assign,$$,val,NULL,0);
                emit(sub,val,newexpr_constnum(1),val,0);
                emit(tablesetelem,val,$1,$1->index,0);
            }else{
                emit(assign,$$,$1,NULL,0);
                emit(sub,$1,newexpr_constnum(1),$1,0);
            }
            printReduction("term","lvalue OPER_MINUS2", yylineno);
        }
    | primary
        {
            $$ = $1;
            printReduction("term","primary", yylineno);
        }
    ;

assignexpr:
    lvalue OPER_EQ expr
        {
            if ( $1->type == tableitem_e ) {

                emit(tablesetelem, $1, $1->index, $3, 0);
                $$ = emit_iftableitem($1);
                $$->type = assignexpr_e;
            }
            else {

                struct SymbolTableEntry *e = search_all_scopes(st, $1->strConst, scope);
                
                if ( ref_flag == REF_LOCAL ) {

                    if ( !e ) {

                        #ifdef P2DEBUG
                        printf("\e[0;32mSuccess [#%d]:\e[0m Symbol %s has been added to the symbol table\n", yylineno,$1->strConst);
                        #endif
                        $1->sym = SymTable_insert(st, $1->strConst, (scope ? LOCAL : GLOBAL), scope, yylineno);
                    }
                    else if ( e->scopeno < scope ) {
                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno,$1->strConst,scope);
                        #endif
                    }
                    else if ( e->type == USERFUNC || e->type == LIBFUNC ) {
                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s defined as a function\n", yylineno,$1->strConst);
                        #endif
                    }else if ( e->type == FORMAL && e->scopeno != scope ) {
                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno,$1->strConst,scope);
                        #endif
                    }
                    else
                        $1->sym = e;
                }
                else if ( ref_flag == REF_GLOBAL) {  //:: ID

                    if ( !e ) {

                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m: Symbol %s is not defined\n", yylineno,$1->strConst);
                        #endif
                    }
                    else
                        $1->sym = e;
                }
                else {  //ID

                    if ( !e ) {

                        #ifdef P2DEBUG
                        printf("\e[0;32mSuccess [#%d]:\e[0m Symbol %s has been added to the symbol table\n", yylineno,$1->strConst);
                        #endif

                        $1->sym = SymTable_insert(st, $1->strConst, (scope ? LOCAL : GLOBAL), scope, yylineno);
                    }
                    else if ( (e->type == LOCAL || e->type == USERFUNC) && e->scopeno != scope ) {
                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno,$1->strConst,scope);
                        #endif
                    }
                    else if ( e->type == USERFUNC || e->type == LIBFUNC ) {
                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s is defined as a function\n", yylineno ,$1->strConst);
                        #endif
                    }
                    else if ( e->type == FORMAL && e->scopeno != scope ) {
                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno,$1->strConst,scope);
                        #endif
                    }
                    else
                        $1->sym = e;
                }

                emit(assign, $1, emit_iftableitem($3), NULL, 0);
                $$ = new_expr(assignexpr_e);
                $$->sym = newtemp();
                emit(assign, $$, $1, NULL, 0);
                ref_flag = REF_NONE;                                        
            }

            printf("assignexpr: lvalue(%d, %s, %d) OPER_EQ expr(%d, %s)\n", $1->type, $1->strConst, $1->sym->scopeno, $3->type, $3->strConst);
            printReduction("assignexpr","lvalue OPER_EQ expr", yylineno);
        }
        ;

primary:
    lvalue
        {
            printf("primary: lvalue = [%d, %s]\n", $1->type, $1->strConst);
            if ( $1->type == var_e ) {

                struct SymbolTableEntry *e = search_all_scopes(st, yylval.strVal, scope);

                if ( !e ) {

                    $$ = $1;
                    $$->sym = SymTable_insert(st, yylval.strVal, (scope ? LOCAL : GLOBAL), scope, yylineno);
                }
                else if ( e->type == LOCAL && e->scopeno != scope ) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno,yylval.strVal,scope);
                    #endif
                }
                else if ( e->type == FORMAL && e->scopeno != scope ) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno, yylval.strVal,scope);
                    #endif
                }
                else if ( e->type == USERFUNC || e->type == LIBFUNC ) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s is defined as a function\n", yylineno ,yylval.strVal);
                    #endif
                }
                else {

                    $$ = $1;
                    $$->sym = e;    
                }
            }
        
            printReduction("primary","lvalue", yylineno);
        }
    | call
        {
            printReduction("primary","call", yylineno);
        }
    | objectdef
        {
            $$ = $1;
            printReduction("primary","objectdef", yylineno);
        }
    | PUNC_LPARENTH funcdef PUNC_RPARENTH
        {
            $$ = new_expr(programfunc_e);
            $$->sym = $2;
            printReduction("primary","PUNC_LPARENTH funcdef PUNC_RPARENTH", yylineno);
        }
    | const
        {
            $$ = $1;
            printReduction("primary","const", yylineno);
        }
    ;

lvalue:
    ID
        {
            ref_flag = REF_NONE; 
            $$ = new_expr(var_e);
            $$->strConst = strdup($1);
            printReduction("lvalue","ID", yylineno);
        }
    | KEYW_LOCAL ID
        {
            ref_flag = REF_LOCAL;
            $$ = new_expr(var_e);
            $$->strConst = strdup($2);
            printReduction("lvalue","KEYW_LOCAL ID", yylineno);
        }
    | PUNC_COLON2 ID
        {
            ref_flag = REF_GLOBAL;
            $$ = new_expr(var_e);
            $$->strConst = strdup($2);
            printReduction("lvalue","PUNC_COLON2 ID", yylineno);
        }
    | member
        {
            // add code here
        }
    ;

member:
    lvalue PUNC_DOT ID
        {
            if ( $1->type == var_e )
                $1->sym = table_lookupandadd(st, $1->strConst, scope);

            $$ = member_item($1, newexpr_conststr($3));
            printReduction("member","lvalue PUNC_DOT ID", yylineno);
        }
    | lvalue PUNC_LBRACKET expr PUNC_RBRACKET
        {
            if ( $1->type == var_e )
                $1->sym = table_lookupandadd(st, $1->strConst, scope);

            $$ = member_item($1, $3);
        }
    | call PUNC_DOT ID
        {
            // add code here
        }
    | call PUNC_LBRACKET expr PUNC_RBRACKET
        {
            // add code here
        }
    ;

call:
    call PUNC_LPARENTH elist PUNC_RPARENTH
        {
            $$=make_call($1,$3);
            printReduction("call","call PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);
        }
    | lvalue callsuffix
        {
            $$ = NULL;
            struct SymbolTableEntry *e = search_all_scopes(st, $1->strConst, scope);


            if ( !e ) {
                #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m: Symbol %s is not defined\n", yylineno,$1->strConst);
                #endif
            }
            else if ( e->type == LOCAL && e->scopeno != scope ) {

                #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno,$1->strConst,scope);
                #endif
            }
            else if ( e->type != USERFUNC && e->type != LIBFUNC ) {

                #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m: Symbol %s is not a function\n", yylineno,$1->strConst);
                #endif
            }
            else {

                $1->sym = e;
                $1 = emit_iftableitem($1);

                if ( $2->method ) {

                    struct expr *t = $1;
                    $1 = emit_iftableitem(member_item(t, newexpr_conststr($2->name)));
                    $2->elist->next = t;
                }

                $$ = make_call($1, $2->elist);
            }

            printReduction("call","lvalue callsuffix", yylineno);
        }
    | PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH
        {
            struct expr* func = new_expr(programfunc_e);

            func->sym = $2;
            $$=make_call(func, $5);
            printReduction("call","PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);
        }
    ;

callsuffix:
    normcall
        {
            $$ = $1;
            printReduction("callsuffix","normcall", yylineno);
        }
    |methodcall
        {
            $$ = $1;
            printReduction("callsuffix","methodcall", yylineno);
        }
    ;

normcall:
    PUNC_LPARENTH elist PUNC_RPARENTH
        {
            $$->elist = $2;
            $$->method = 0;
            $$->name = NULL;
            printReduction("normcall","PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);
        }
    ;
methodcall:
    PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH
        {
            $$->elist = $4;
            $$->method = 1;
            $$->name = $2;
            printReduction("methodcall","PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);
        }
        ;

elistrep:
    PUNC_COMMA expr elistrep
        {
            $$ = $2;
            $$->next = $3;
            printReduction("elistrep","PUNC_COMMA expr elistrep", yylineno);
        }
    |
        {
                $$ = NULL;
                printReduction("elistrep","PUNC_COMMA expr", yylineno);
        }
    ;

elist:
    expr elistrep
        {
            $1->next = $2;
            $$ = $1;
            printReduction("elist","expr elistrep", yylineno);
        }
    |
        {
            $$ = NULL;
            printReduction("elist","empty", yylineno);
        }
    ;

objectin:
    elist
        {
            struct expr *t  = new_expr(newtable_e);
            struct expr *itter = $1;


            t->sym = newtemp();
            emit(tablecreate, t, NULL, NULL, 0);

            for (int i = 0; itter; itter = itter->next, ++i)
                emit(tablesetelem, t, newexpr_constnum(i), itter, 0);

            $$ = t;

            // if($$)$$ = $1;else{$$=new_expr(nil_e);} 
            printReduction("objectin","elist", yylineno);
        }
            |indexed                                                { 
                                                                        struct expr *t  = new_expr(newtable_e);
                                                                        struct expr *itter=$1;
                                                                        t->sym = newtemp();
                                                                        emit(tablecreate, t, NULL, NULL, 0);
                                                                        for (int i = 0; itter; itter = itter->next, ++i)
                                                                            emit(tablesetelem, t, itter->index, itter, 0);
                                                                        $$=t;

                                                                        // if($$)$$ = $1;else{$$=new_expr(nil_e);} 
                                                                        printReduction("objectin","indexed", yylineno);
                                                                    }
            ;

objectdef:
    PUNC_LBRACKET objectin PUNC_RBRACKET
        { 
            $$ = $2; 
            printReduction("objectdef","PUNC_LBRACKET objectin PUNC_RBRACKET", yylineno);
        }
    ;

indexed:
    indexedelem indexrep
        {
            $$ = $1;
            $$->next = $2;
            printReduction("indexed","indexedelem indexrep", yylineno);
        }
    ;

indexedelem:
    PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE
        {
            $$ = $4;
            $$->index = $2;
            printReduction("indexedelem","PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE", yylineno);
        }
    ;

indexrep:
    PUNC_COMMA indexedelem indexrep
        {
            $$ = $2;
            $$->next = $3;
            printReduction("indexrep","PUNC_COMMA indexedelem", yylineno);
        }
    |
        {
            $$ = NULL;
            printReduction("indexrep","empty", yylineno);
        }
    ;

block:
    PUNC_LBRACE {++scope;} statements PUNC_RBRACE
        {
            /** TODO: put ++scope here */
            SymTable_hide(st, scope);
            --scope;
            printReduction("block","PUNC_LBRACE statements PUNC_RBRACE", yylineno);
        }
    ;

funcname:
    ID
        {
            $$ = $1;
        }
    |
        {
            char *name = getFuncName();
            $$ = strdup(name);
        }
    ;

funcprefix:
    KEYW_FUNC funcname
        {
            char *name = $2;
            current_function = $2;
            struct SymbolTableEntry* res = search_all_scopes(st, name, scope);
            
            if ( res && res->scopeno >= scope ) {

                if ( res->type == GLOBAL ) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s already exists as a GLOBAL variable!\n", yylineno,name);
                    #endif
                }
                else if ( res->type == FORMAL ) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s already exists as a FORMAL variable!\n", yylineno, name);
                    #endif
                }
                else if ( res->type == LOCAL){
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s already exists as a LOCAL variable!\n", yylineno,name);
                    #endif
                }
                else if ( res->type == USERFUNC){
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s already exists as a user function!\n", yylineno,name);
                    #endif
                }
                else if ( res->type == LIBFUNC){
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s already exists as a library function!\n", yylineno,name);
                    #endif
                }

                $$=NULL;
            }
            else if( !res ){

                struct SymbolTableEntry *new = SymTable_insert(st, name, USERFUNC, scope, yylineno);
                #ifdef P2DEBUG
                printf("\e[0;32mSuccess:\e[0m Symbol %s has been added to the symbol table\n",name);
                #endif
                $$=new;
                emit(funcstart,newexpr_conststr(name),NULL,NULL,0);
            }
            else{

                $$=res;
                emit(funcstart,newexpr_conststr(name),NULL,NULL,0);    
            }
        }
    ;

funcargs:
    PUNC_LPARENTH {scope++;} idlist {scope--;} PUNC_RPARENTH;

funcdef:
    funcprefix funcargs block
        {
            if ( ($$ = $1) )
                emit(funcend, newexpr_conststr($1->name), NULL, NULL, 0);

            printReduction("funcdef","KEYW_FUNC ID PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);
        }
    ;

const:
    CONST_INT
        {
            printReduction("const","CONST_INT", yylineno);
            $$ = newexpr_constnum((double)(yylval.intVal));
        }
    | CONST_REAL
        {
            printReduction("const","CONST_REAL", yylineno);
            $$ = newexpr_constnum(yylval.realVal);
        }
    | STRING
        {
            printReduction("const","STRING", yylineno);
            $$ = newexpr_conststr($1);
            printf("\e[31mdebug\e[0m: yylval.strVal = %s (%d)\n", yylval.strVal, *((char *)(yylval.strVal)));
        }
    | KEYW_NIL
        {
            printReduction("const","KEYW_NIL", yylineno);
            $$ = new_expr(nil_e);
        }
    | KEYW_TRUE
        {
            printReduction("const","KEYW_TRUE", yylineno);
            $$ = newexpr_constbool(yylval.realVal);
        }
    | KEYW_FALSE
        {
            printReduction("const","KEYW_FALSE", yylineno);
            $$ = newexpr_constbool(yylval.realVal);
        }
    ;

idlist:
    ID
        {
                char* name = yylval.strVal;
                struct SymbolTableEntry* res = SymTable_lookup_scope(st, name, scope);


                if ( !checkIfAllowed(name) ) {

                        #ifdef P2DEBUG  
                        printf("\e[0;31mERROR [#%d]:\e[0m Can't have a formal variable \"%s\". It has the same name as a LIBFUNC.\n",yylineno , name);
                        #endif
                }
                else {
                    if ( res ) {

                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Can't have a formal variable \"%s\". It has the same name as another FORMAL variable\n",yylineno , name);
                        #endif
                    }
                    else {
                        SymTable_insert(st, name, FORMAL, scope, yylineno);
                        SymTable_insert_func_arg(st, current_function, name);
                        // SymTable_insert_func_arg(st)
                        #ifdef P2DEBUG
                        printf("\e[0;32mSuccess [#%d]:\e[0m Symbol %s has been added to the symbol table\n",yylineno ,name);
                        #endif
                    }
                }
        }
    ids
        {
            printReduction("idlist","ID ids", yylineno);
        }
    |
        {
            printReduction("idlist","empty", yylineno);
        }
    ;

ids:
    PUNC_COMMA ID
        {
            char *name = yylval.strVal;
            struct SymbolTableEntry *res = SymTable_lookup_scope(st, name, scope);


            if ( !checkIfAllowed(name) ) {

                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Can't have a formal variable \"%s\". It has the same name as a LIBFUNC.\n",yylineno , name);
                    #endif
            }
            else {

                if ( res ) {

                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Can't have a formal variable \"%s\". It has the same name as another FORMAL variable\n",yylineno , name);
                    #endif    
                }
                else {

                    SymTable_insert(st, name, FORMAL, scope, yylineno);
                    SymTable_insert_func_arg(st, current_function, name);

                    #ifdef P2DEBUG
                    printf("\e[0;32mSuccess [#%d]:\e[0m Symbol %s has been added to the symbol table\n",yylineno ,name);
                    #endif
                }
            }
        }
    ids
        {
            printReduction("ids","PUNC_COMMA ID ids", yylineno);
        }
    |
        {
            printReduction("ids","empty", yylineno);
        }
    ;

ifprefix:
    KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH
        {
            emit(if_eq, NULL, $3, newexpr_constbool(1), currQuad + 2);
            $$ = currQuad;
            emit(jump,NULL,NULL,NULL,0);
        }
    ;

ifstmt:
    ifprefix stmt
        {
            patch_label($1,currQuad);
            printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);
        }
    | ifprefix stmt KEYW_ELSE stmt
        {
            printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt KEYW_ELSE stmt", yylineno);
        }
    ;
whilestmt:
    KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt
        {
            printReduction("whilestmt","KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);
        }
    ;
forstmt:
    KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt
        {
            printReduction("forstmt","KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt", yylineno);
        }
    ;
returnstmt:
    KEYW_RET PUNC_SEMIC
        {
            #ifdef P2DEBUG
            if ( !scope )
                printf("\e[0;31mERROR [#%d]:\e[0m Can't have a return statement outside a function\n",yylineno );
            #endif

            emit(ret, NULL, NULL, NULL, 0);
            printReduction("returnstmt","KEYW_RET PUNC_SEMIC", yylineno);
        }
    | KEYW_RET expr PUNC_SEMIC
        {
            #ifdef P2DEBUG
            if ( !scope )
                printf("\e[0;31mERROR [#%d]:\e[0m Can't have a return statement outside a function\n",yylineno );
            #endif

            emit(ret, NULL, $2, NULL, 0);
            printReduction("returnstmt","KEYW_RET expr PUNC_SEMIC", yylineno);
        }
    ;


%%


int yyerror(const char *yaccerror){
    printf("ERROR: %s\n",yaccerror);
}

int main(int argc, char **argv) {

    int index;
    yydebug = 1;

    if ( argc != 2 ) {

        printf("\e[1;31merror\e[0m: no input file\n");
        return 0;
    }

    if ( !(yyin = fopen(argv[1], "r")) ) {

        perror("fopen()");
        return 1;
    }

    assert( (st = SymTable_create()) );
    initFile();

    if(!yyparse())
        print_quads();

    #ifdef P2DEBUG
    /* SymTable_print_all(st); */
    /* SymTable_print_scopes(st);  */
    #endif

    #ifdef P3DEBUG
    #endif

    fclose(file);
}
