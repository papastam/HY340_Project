%{
    /*
    * TODO LIST
    *
    * break/continue lists                      > DONE
    * repeatcnt stack                           > pap
    * while icode emition                       > DONE
    * for icode emition                         > DONE
    * offset of variables                       > DONE
    * short circuit evaluation                  > chiotis
    * reuse of tempvars when they are lvalues   >
    * cleanup() code in case of error           > chiotis
    * table creation icode                      > DONE
    * functions icode                           > DONE
    * stack data structure                      > DONE
    * print compiler errors                     > 
    * create testfiles!!!!!                     > N/A
    * 
    * BUGS:
    * lvalue <- ID, xwnoume symbol kateftheian  >
    */

    #include <stdio.h>
    #include <assert.h>
    #include <string.h>
    #include <stdlib.h>

    #include "quads.h"
    #include "utils.h"
    #include "stack.h"

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
    int produce_icode = 1;
    // int loopcnt = 0;
    int prog_var_flag;
    int g_offset;
    long g_formaloff;
    Stack g_stack;

    // Stack loopcnt = Stack_create();
    Stack *loopcnt = NULL;

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
    struct function_contents *functcont;
    struct for_contents *forcont;
    struct stmt_t *stmtcont; 
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
%type <intVal> whilestart
%type <intVal> whilecond
%type <intVal> jumpandsavepos
%type <intVal> savepos

%type <functcont> methodcall
%type <functcont> normcall
%type <functcont> callsuffix

%type <forcont> forprefix

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

%type <stmtcont> statements
%type <stmtcont> stmt
%type <stmtcont> block

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
%right OPER_EQ

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
            $$->breaklist = mergelist($1->breaklist, $2->breaklist);
            $$->contlist = mergelist($1->contlist, $2->contlist);
            printReduction("statements","stmt statements", yylineno);
        }
    |
        {
            make_stmt(&$$);
            printReduction("statements","empty", yylineno);
        }
    ;

stmt:       
    expr PUNC_SEMIC
        { 
            #ifdef P3DEBUG 
            if ( $1 ) {

                // printf("\nStatement in line %d contains the expression:\n",yylineno);
                // printExpression($1); 
            }
            #endif 

            printReduction("stmt","expr PUNC_SEMIC", yylineno);
            resettemp();
            make_stmt(&$$);
        }
    | ifstmt
        {
            printReduction("stmt","ifstmt", yylineno);
            make_stmt(&$$);
        }
    | whilestmt
        {
            printReduction("stmt","whilestmt", yylineno);
            make_stmt(&$$);
        }
    | forstmt
        {
            printReduction("stmt","forstmt", yylineno);
            make_stmt(&$$);
        }
    | returnstmt
        {
            printReduction("stmt","returnstmt", yylineno);
            make_stmt(&$$);
        }
    | KEYW_BREAK PUNC_SEMIC
        {
            make_stmt(&$$);
            emit(jump, NULL, NULL, NULL, 0);
            $$->breaklist = newlist(getNextQuad()-1);

            #ifdef P2DEBUG
            if ( !scope )
                printf("\e[0;31mERROR [#%d]:\e[0m Can't have a break statement while not in a loop\n", yylineno);
            #endif

            printReduction("stmt","KEYW_BREAK PUNC_SEMIC", yylineno);
        }
    | KEYW_CONT PUNC_SEMIC
        {
            make_stmt(&$$);
            emit(jump, NULL, NULL, NULL, 0);
            $$->contlist = newlist(getNextQuad()-1);

            #ifdef P2DEBUG
            if ( !scope )
                printf("\e[0;31mERROR [#%d]:\e[0m Can't have a continue statement while not in a loop\n", yylineno);
            #endif

            printReduction("stmt","KEYW_CONT PUNC_SEMIC", yylineno);
        }
    | block
        {
            printReduction("stmt","block", yylineno);
            $$=$1;
        }
    | funcdef
        {
            printReduction("stmt","funcdef", yylineno);
            make_stmt(&$$);
        }
    | PUNC_SEMIC
        {
            printReduction("stmt"," PUNC_SEMIC", yylineno);
            make_stmt(&$$);
        }
    ;

expr:
    expr OPER_PLUS expr
        {
            $$ = new_expr(arithexpr_e);
            $$->sym = newtemp();
            emit(add,$$, $1, $3, 0);
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
            $$ = new_expr(boolexpr_e);
            $$->sym = newtemp();
            emit(if_less, $$, $1, $3,0);
            emit(assign, $$, newexpr_constbool(0), NULL,0);
            emit(jump,NULL,NULL,NULL,0);
            emit(assign, $$, newexpr_constbool(1), NULL,0);
            printReduction("expr","expr OPER_LET expr", yylineno);
        }
    | expr OPER_LEE expr
        {
            $$ = new_expr(boolexpr_e);
            $$->sym = newtemp();
            emit(if_lesseq, $$, $1, $3,0);
            emit(assign, $$, newexpr_constbool(0), NULL,0);
            emit(jump, NULL, NULL, NULL, 0);
            emit(assign, $$, newexpr_constbool(1), NULL,0);
            printReduction("expr","expr OPER_LEE expr", yylineno);
        }
    | expr OPER_EQ2 expr
        {
            $$ = new_expr(boolexpr_e);
            $$->sym = newtemp();
            emit(if_eq, $$, $1, $3,0);
            emit(assign, $$, newexpr_constbool(0), NULL,0);
            emit(jump,NULL,NULL,NULL,0);
            emit(assign, $$, newexpr_constbool(1), NULL,0);
            printReduction("expr","expr OPER_EQ2 expr", yylineno);
        }
    | expr OPER_NEQ expr
        {
            $$ = new_expr(boolexpr_e);
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
    | assignexpr
        {
            $$ = $1;
            printReduction("expr","assignexpr", yylineno);
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
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);


            if ( !res ){
            #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
            #endif
            }else if ( res->type == LIBFUNC || res->type == USERFUNC ){
            #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is a function.\n", yylineno, name, name);
            #endif
            }else{
                $2->sym=res;
            }

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
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);


                        if ( !res ){
            #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
            #endif
            }else if ( res->type == LIBFUNC || res->type == USERFUNC ){
            #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is a function.\n", yylineno, name, name);
            #endif
            }else{
                $1->sym=res;
            }

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
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);
            
            if ( !res ){
            #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
            #endif
            }else if ( res->type == LIBFUNC || res->type == USERFUNC ){
            #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is a function.\n", yylineno, name, name);
            #endif
            }else{
                $2->sym=res;
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
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);
            
            if ( !res ){
            #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is undefined.", yylineno, name, name);
            #endif
            }else if ( res->type == LIBFUNC || res->type == USERFUNC ){
            #ifdef P2DEBUG
                printf("\e[0;31mERROR [#%d]:\e[0m Operation \"++%s\" not allowed. %s is a function.\n", yylineno, name, name);
            #endif
            }else{
                $1->sym=res;
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

                struct SymbolTableEntry *e = SymTable_lookup_all_scopes(st, $1->strConst, scope);
                
                if ( ref_flag == REF_LOCAL ) {

                    if ( !e ) {

                        $1->sym = SymTable_insert(st, $1->strConst, (!prog_var_flag ? GLOBAL : LOCAL), scope, yylineno);
                        $1->sym->offset = g_offset++;
                    }
                    else if ( e->scope < scope )
                        print_static_analysis_error(yylineno, "Symbol %s can't be accessed from scope %d\n", $1->strConst, scope);
                    else if ( e->type == USERFUNC || e->type == LIBFUNC )
                        print_static_analysis_error(yylineno, "Symbol %s defined as a function\n", $1->strConst);
                    else if ( e->type == FORMAL && e->scope != scope )
                        print_static_analysis_error(yylineno, "Symbol %s can't be accessed from scope %d\n", $1->strConst, scope);
                    else {

                        $1->sym = e;
                        $1->sym->offset = g_offset++;
                    }
                }
                else if ( ref_flag == REF_GLOBAL) {  //:: ID

                    if ( !e ) {

                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m: Symbol %s is not defined\n", yylineno,$1->strConst);
                        #endif
                    }
                    else {

                        $1->sym = e;
                        $1->sym->offset = g_offset++;
                    }
                }
                else {  //ID

                    if ( !e ) {

                        $1->sym = SymTable_insert(st, $1->strConst, (!prog_var_flag ? GLOBAL : LOCAL), scope, yylineno);
                        sprintf("\e[1m[REF_NONE]:\e[0m offset = %ld\n", g_offset);
                        $1->sym->offset = g_offset++;

                        SymTable_print_elem($1->sym);
                    }
                    else if ( (e->type == LOCAL || e->type == USERFUNC) && e->scope != scope ) {
                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno,$1->strConst,scope);
                        #endif
                    }
                    else if ( e->type == USERFUNC || e->type == LIBFUNC ) {
                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s is defined as a function\n", yylineno ,$1->strConst);
                        #endif
                    }
                    else if ( e->type == FORMAL && e->scope != scope ) {
                        #ifdef P2DEBUG
                        printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno,$1->strConst,scope);
                        #endif
                    }
                    else {

                        printf(">>> WHY <<<\n");
                        $1->sym = e;
                        $1->sym->offset = g_offset++;
                    }
                }

                emit(assign, $1, emit_iftableitem($3), NULL, 0);
                $$ = new_expr(assignexpr_e);
                $$->sym = newtemp();
                emit(assign, $$, $1, NULL, 0);
                ref_flag = REF_NONE;                                        
            }

            printf("assignexpr: lvalue(%d, %s, %d) OPER_EQ expr(%d, %s)\n", $1->type, $1->strConst, $1->sym->scope, $3->type, $3->strConst);
        }
    ;

primary:
    lvalue
        {
            if ( $1->type == var_e ) {

                struct SymbolTableEntry *e = SymTable_lookup_all_scopes(st, $1->strConst, scope);

                if ( !e ) {

                    $$ = $1;
                    $$->sym = SymTable_insert(st, $1->strConst, (!prog_var_flag ? GLOBAL : LOCAL), scope, yylineno);
                    $$->sym->offset = g_offset++;
                }
                else if ( e->type == LOCAL && e->scope != scope )
                    print_static_analysis_error(yylineno, "Symbol %s cannot be accessed from scope %d\n", $1->strConst, scope);
                else if ( e->type == FORMAL && e->scope != scope )
                    print_static_analysis_error(yylineno, "Symbol %s cannot be accessed from scope %d\n", $1->strConst, scope);
                else if ( e->type == USERFUNC || e->type == LIBFUNC )
                    print_static_analysis_error(yylineno, "Symbol %s is defined as a function\n", $1->strConst);
                else {

                    $$ = $1;
                    $$->sym = e;
                }
            }
        }
    | call
        {
            $$ = $1;
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
        }
    | KEYW_LOCAL ID
        {
            ref_flag = REF_LOCAL;
            $$ = new_expr(var_e);
            $$->strConst = strdup($2);
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
            $$ = $1;
            // add code here
        }
    ;

member:
    lvalue PUNC_DOT ID
        {
            if ( $1->type == var_e )
                $1->sym = SymTable_lookup_add(st, $1->strConst, scope, yylineno);

            $$ = member_item($1, newexpr_conststr($3));
            printReduction("member","lvalue PUNC_DOT ID", yylineno);
        }
    | lvalue PUNC_LBRACKET expr PUNC_RBRACKET
        {
            if ( $1->type == var_e )
                $1->sym = SymTable_lookup_add(st, $1->strConst, scope, yylineno);

            $$ = member_item($1, $3);
        }
    | call PUNC_DOT ID
        {
            $$ = $1;
            // add code here
        }
    | call PUNC_LBRACKET expr PUNC_RBRACKET
        {
            $$ = $1;
            // add code here
        }
    ;

call:
    call PUNC_LPARENTH elist PUNC_RPARENTH
        {
            $$ = make_call($1, $3);
            printReduction("call","call PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);
        }
    | lvalue callsuffix
        {
            $$ = new_expr(nil_e);
            struct SymbolTableEntry *e = SymTable_lookup_all_scopes(st, $1->strConst, scope);


            if ( !e )
                print_static_analysis_error(yylineno, "Symbol %s is not defined\n", $1->strConst);
            else if ( e->type == LOCAL && e->scope != scope ) {

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

            if( $$->type == nil_e ) {

                printf("%s\n", $1->strConst);
                print_static_analysis_error(yylineno, "Function %s is not defined\n", $1->strConst);
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
            $$ = malloc(sizeof(struct function_contents));
            $$->elist = $2;
            $$->method = 0;
            $$->name = NULL;
        }
    ;
methodcall:
    PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH
        {
            $$=malloc(sizeof(struct function_contents));
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
            |indexed    { 
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
    PUNC_LBRACE
        {
            ++scope;

            if ( current_function ) {

                Stack_push(g_stack, g_offset);
                g_offset = 0UL;
            }

            printf("\e[31mBLOCK START\e[0m\n");
            printf("current_function = %s\n", current_function);
        }
    statements PUNC_RBRACE
        {
            if ( current_function ) {

                SymTable_hide(st, scope);
                Stack_pop(g_stack, &g_offset);
            }

            printf("\e[31mBLOCK END\e[0m\n");
            printf("current_function = %s\n", current_function);

            --scope;
            $$=$3;
        }
    ;

funcstart:
    {
        if(!loopcnt)
            loopcnt = Stack_create();
        else
            Stack_push(loopcnt,0);
    };

funcend:
    {
        Stack_pop(loopcnt,NULL);
    };

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
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);

            if ( res && res->scope >= scope ) {

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
                else if ( res->type == LOCAL ) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s already exists as a LOCAL variable!\n", yylineno,name);
                    #endif
                }
                else if ( res->type == USERFUNC ) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s already exists as a user function!\n", yylineno,name);
                    #endif
                }
                else if ( res->type == LIBFUNC ) {
                    #ifdef P2DEBUG
                    printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s already exists as a library function!\n", yylineno,name);
                    #endif
                }

                $$ = NULL;
            }
            else if( !res ){

                $$ = SymTable_insert(st, name, USERFUNC, scope, yylineno);
                emit(funcstart, newexpr_conststr(name), NULL, NULL, 0);
            }
            else{

                $$ = res;
                emit(funcstart, newexpr_conststr(name), NULL, NULL, 0);    
            }
        }
    ;

funcargs:
    PUNC_LPARENTH
        {
            ++scope;
            Stack_push(g_stack, g_offset);
            g_offset = 0UL;
            prog_var_flag = 1;
            printf("\e[32mFUNCARGS START\e[0m\n");
        }
    idlist
        {
            --scope;
            Stack_pop(g_stack, &g_offset);
            printf("\e[32mFUNCARGS END\e[0m\n");
        }
    PUNC_RPARENTH;

funcdef:
    funcprefix funcstart funcargs block funcend
        {
            printf("\e[33mFUNCDEF START\e[0m\n");
            if ( ($$ = $1) )
                emit(funcend, newexpr_conststr($1->name), NULL, NULL, 0);

            current_function = NULL;
            prog_var_flag = 0;
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
    ID ids
        {
            char *name = $1;
            struct SymbolTableEntry *res = SymTable_lookup_scope(st, name, scope);


            if ( !checkIfAllowed(name) )
                print_static_analysis_error(yylineno, "argument \e[1m%s\e[0m of function \e[1m%s\e[0m has the same name as an alpha_library_function\n",\
                            name, current_function);
            else {

                if ( res )
                    print_static_analysis_error(yylineno, "FORMAL variable '%s' has the same name as another FORMAL argument\n", name);
                else {

                    res = SymTable_insert(st, name, FORMAL, scope, yylineno);
                    res->offset = g_offset++;

                    SymTable_insert_func_arg(st, current_function, name);

                }
            }
        }
    |
    ;

ids:
    PUNC_COMMA ID
        {
            char *name = $2;
            struct SymbolTableEntry *res = SymTable_lookup_scope(st, name, scope);


            if ( !checkIfAllowed(name) )
                print_static_analysis_error(yylineno, "argument \e[1m%s\e[0m of function \e[1m%s\e[0m has the same name as an alpha_library_function\n",\
                            name, current_function);
            else {

                if ( res )
                    print_static_analysis_error(yylineno, "Formal variable '%s' has the same name as another formal variable!\n");
                else {

                    res = SymTable_insert(st, name, FORMAL, scope, yylineno);
                    res->offset = g_offset++;

                    SymTable_insert_func_arg(st, current_function, name);
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

loopstart:
    {
        // ++loopcnt->ci;
    };

loopend:
    {
        // --loopcnt->ci;
    };

whilestart:
    KEYW_WHILE
        {
            $$ = getNextQuad();
        }
    ;
whilecond:
    PUNC_LPARENTH expr PUNC_RPARENTH
        {
            emit(if_eq, NULL, $2, newexpr_constbool(1), getNextQuad() + 2U);
            $$ = getNextQuad();
            emit(jump, NULL, NULL, NULL, 0);
        }
    ;
whilestmt:
    whilestart loopstart whilecond stmt loopend
        {
            emit(jump, NULL, NULL, NULL, $1);
            patch_label($3, getNextQuad());
            
            patchlist($4->breaklist, getNextQuad());
            patchlist($4->contlist, $1);
        }
    ;

jumpandsavepos:
    {$$=getNextQuad();emit(jump,NULL,NULL,NULL,0);};

savepos:
    {$$=getNextQuad();};

forprefix:
    KEYW_FOR loopstart PUNC_LPARENTH elist savepos PUNC_SEMIC expr PUNC_SEMIC loopend
        {   
            $$=malloc(sizeof(struct for_contents));
            $$->test=$5;
            $$->enter=getNextQuad();
            emit(if_eq,$7,newexpr_constbool(1),NULL,0);
        }
    ;

forstmt:
    forprefix jumpandsavepos elist PUNC_RPARENTH jumpandsavepos stmt jumpandsavepos
        {
            patch_label($1->enter,$5+1);
            patch_label($2,getNextQuad());
            patch_label($5,$1->test);
            patch_label($7,$2+1);

            patchlist($6->breaklist, getNextQuad());
            patchlist($6->contlist, $2+1);
        
            printReduction("forstmt","KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt", yylineno);
        }
    ;
returnstmt:
    KEYW_RET PUNC_SEMIC
        {
            if ( !scope )
                print_static_analysis_error(yylineno, "return statement outside of function\n");

            emit(ret, NULL, NULL, NULL, 0);
        }
    | KEYW_RET expr PUNC_SEMIC
        {
            if ( !scope )
                print_static_analysis_error(yylineno, "return statement outside of function\n");

            emit(ret, NULL, $2, NULL, 0);
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
    assert( (g_stack = Stack_create()) );
    assert( (loopcnt = Stack_create()) );
    initFile();

    yyparse();

    if( produce_icode )
        print_quads();

    // SymTable_print_all(st);
    /* SymTable_print_scopes(st); */

    fclose(file);
}
