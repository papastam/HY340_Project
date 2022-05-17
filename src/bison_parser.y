%{
    /*
    * TODO LIST:
    *
    * break/continue lists                      > DONE
    * repeatcnt stack   (#TODO_REPSTACK)        > 
    * while icode emition                       > DONE
    * for icode emition                         > DONE
    * offset of variables                       > DONE
    * short circuit evaluation                  > pap
    * reuse of tempvars when they are lvalues   > b1s (all done ektos apo NOT/AND/OR (prepei na ftiaxtei h merikh apotimish))
    * cleanup() code in case of error           > chiotis
    * table creation icode                      > DONE
    * functions icode                           > DONE
    * stack data structure                      > DONE
    * print compiler errors (#TODO_ERRORS)      > 
    * create testfiles!!!!!                     > N/A
    * reorder quads.h                           >
    * 
    * 
    * FIXES:
    * fix arithexpr_checks (add checks on reductions to expr) (#TODO_ARITH)       >
    * fix evaluations at quad 0 (sentinel next = -1)                              > DONE (den ekana afto pou leei to todo, allo fix, alla doulevei)
    * 
    * BUGS:
    * lvalue <- ID, xwnoume symbol kateftheian  > DONE 
    * 
    * TESTS:
    * test if quads table expands when it reaches current size
    * 
    * BEFORE TURNIN:
    * remove testpap.asc gt peftei vrisidi! 
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
    void yyerror(const char *yaccerror);

    extern struct quad  *quads;
    extern unsigned int  total;
    extern unsigned int  currQuad;

    /*** string formatting ***/

    #define F_BOLD "\e[1m"
    #define F_RST  "\e[0m"
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

%start program

%right OPER_EQ
%left KEYW_OR
%left KEYW_AND
%nonassoc OPER_EQ2 OPER_NEQ
%nonassoc OPER_LET OPER_LEE OPER_GRT OPER_GRE
%right OPER_MINUS
%left OPER_PLUS
%left OPER_MUL OPER_DIV OPER_MOD
%right KEYW_NOT OPER_PLUS2 OPER_MINUS2 UNARY_MINUS
%left PUNC_DOT PUNC_DOT2
%left PUNC_LBRACKET PUNC_RBRACKET 
%left PUNC_LPARENTH PUNC_RPARENTH 

%%

program:
    statements
        {
            // add code here
        }
    ;

statements: 
    stmt statements
        {
            $$->breaklist = mergelist($1->breaklist, $2->breaklist);
            $$->contlist = mergelist($1->contlist, $2->contlist);
        }
    |
        {
            make_stmt(&$$);
        }
    ;

stmt:       
    expr PUNC_SEMIC
        {
            //TODO_PAP emit if boolexpr
            emit_if_eval($1);
            resettemp();
            make_stmt(&$$);
        }
    | ifstmt
        {
            make_stmt(&$$);
        }
    | whilestmt
        {
            make_stmt(&$$);
        }
    | forstmt
        {
            make_stmt(&$$);
        }
    | returnstmt
        {
            make_stmt(&$$);
        }
    | KEYW_BREAK PUNC_SEMIC
        {
            make_stmt(&$$);
            emit(jump, NULL, NULL, NULL, 0);
            $$->breaklist = newlist(getNextQuad() - 1);

            if ( !scope )
                print_static_analysis_error(yylineno, F_BOLD "break" F_RST " statement outside of loop\n");
        }
    | KEYW_CONT PUNC_SEMIC
        {
            make_stmt(&$$);
            emit(jump, NULL, NULL, NULL, 0);
            $$->contlist = newlist(getNextQuad() - 1);

            if ( !scope )
                print_static_analysis_error(yylineno, F_BOLD "continue" F_RST " statement outside of loop\n");
        }
    | block
        {
            $$ = $1;
        }
    | funcdef
        {
            make_stmt(&$$);
        }
    | PUNC_SEMIC
        {
            make_stmt(&$$);
        }
    ;

expr:
    expr OPER_PLUS expr
        {
            //TODO_ARITH check if both expressions is arith
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(add,$$, $1, $3, 0);
        }
    | expr OPER_MINUS expr
        {
            //TODO_ARITH check if both expressions is arith
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(sub,$$, $1, $3, 0);
        }
    | expr OPER_MUL expr
        {
            //TODO_ARITH check if both expressions is arith
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(mul,$$, $1, $3,0);
            printReduction("expr","expr OPER_MUL expr", yylineno);
        }
    | expr OPER_DIV expr
        {
            //TODO_ARITH check if both expressions is arith
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(div_o, $$, $1, $3, 0);
        
        }
    | expr OPER_MOD expr
        {
            //TODO_ARITH check if both expressions is arith
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(mod,$$, $1, $3, 0);
            // TODO: emit(mod)
        }
    | expr OPER_GRT expr
        {
            //TODO_ARITH check if both expressions is arith
            struct expr* eval1 = true_evaluation($1);
            struct expr* eval2 = true_evaluation($3);

            $$ = newexpr(boolexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_greater, $$, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);   
        }
    | expr OPER_GRE expr
        {
            //TODO_ARITH check if both expressions is arith
            $1 = evaluate($1);
            $3 = evaluate($3);

            $$ = newexpr(boolexpr_e);
            $$->sym = newtemp();

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_greatereq, $$, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);   
        }
    | expr OPER_LET expr
        {
            //TODO_ARITH check if both expressions is arith
            $1 = evaluate($1);
            $3 = evaluate($3);

            $$ = newexpr(boolexpr_e);
            $$->sym = istempexpr($1)? $1->sym : newtemp();

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_less, $$, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
    | expr OPER_LEE expr
        {
            //TODO_ARITH check if both expressions is arith
            $1 = evaluate($1);
            $3 = evaluate($3);

            $$ = newexpr(boolexpr_e);
            $$->sym = istempexpr($1)? $1->sym : newtemp();

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_lesseq, $$, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
    | expr OPER_EQ2 expr
        {
            $1 = evaluate($1);
            $3 = evaluate($3);

            $$ = newexpr(boolexpr_e);
            $$->sym = istempexpr($1)? $1->sym : newtemp();

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_eq, $$, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
    | expr OPER_NEQ expr
        {
            $1 = evaluate($1);
            $3 = evaluate($3);

            $$ = newexpr(boolexpr_e);
            $$->sym = istempexpr($1)? $1->sym : newtemp();

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_noteq, $$, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
    | expr KEYW_AND savepos expr
        {
            int additional_quads=0;
            if($1->type!=boolexpr_e){
                $1 = true_evaluation($1);
                additional_quads+=2;
            }
            if($4->type!=boolexpr_e){
                $4 = true_evaluation($4);
                // ++additional_quads;
            }

            patch_list($1->truelist, $3+additional_quads);
            $$ = newexpr(boolexpr_e);
            $$->truelist = $4->truelist;
            $$->falselist = merge_bool_lists($1->falselist, $4->falselist);
        }
    | expr KEYW_OR savepos expr
        {
            int additional_quads=0;
            if($1->type!=boolexpr_e){
                $1 = true_evaluation($1);
                additional_quads+=2;
            }
            if($4->type!=boolexpr_e){
                $4 = true_evaluation($4);
                // ++additional_quads;
            }

            patch_list($1->falselist, $3+additional_quads);
            $$ = newexpr(boolexpr_e);
            $$->truelist = merge_bool_lists($1->truelist, $4->truelist);
            $$->falselist = $4->falselist;
        }
    | term
        {
            $$ = $1;
        }
    | assignexpr
        {
            $$ = $1;
        }
    ;

term:
    PUNC_LPARENTH expr PUNC_RPARENTH
        {
            //TODO_PAP emit if boolexpr (???)
            $$=$2;
        }
    | OPER_MINUS expr %prec UNARY_MINUS
        {
            arithexpr_check($2); //TODO_ARITH fix this
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($2)? $2->sym : newtemp();
            emit(uminus, $$, $2, NULL, 0);
        }
    | KEYW_NOT expr
        {
            $$->truelist  = $2->falselist;
            $$->falselist = $2->truelist;
        }
    | OPER_PLUS2 lvalue
        {
            char *name = $2->strConst;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);


            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "++%s" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "++%s" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                $2->sym = res;

            arithexpr_check($2); // ? wtf is that ? stoopid bitchez

            if ( $2->type == tableitem_e ) {

                $$ = emit_iftableitem($2);
                emit(add, $$, newexpr_constnum(1), $$, 0);
                emit(tablesetelem, $2, $$, $2->index, 0);
            }
            else {

                emit(add, $2, newexpr_constnum(1), $2, 0);
                $$ = newexpr(arithexpr_e);
                $$->sym = newtemp();
                emit(assign, $$, $2, NULL, 0);
            }
        }
    | lvalue OPER_PLUS2
        {
            char *name = $1->strConst;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);


            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                $1->sym = res;

            arithexpr_check($1);  //TODO: print_error

            $$ = newexpr(arithexpr_e);
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
        }
    | OPER_MINUS2 lvalue
        {
            char *name = yylval.strVal;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);
            
            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "--%s" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "--%s" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                $2->sym = res;
            
            arithexpr_check($2);  //TODO: print_error

            if($2->type==tableitem_e) {
                $$ = emit_iftableitem($2);
                emit(sub, $$, newexpr_constnum(1), $$,0);
                emit(tablesetelem, $$, $2, $2->index,0);
            }else{
                emit(sub, $2, newexpr_constnum(1), $2,0);
                $$ = newexpr(arithexpr_e);
                $$->sym = newtemp();
                emit(assign, $$, $2, NULL,0);
            }
            printReduction("term","OPER_MINUS2 lvalue", yylineno);
        }
    | lvalue OPER_MINUS2
        {
            char *name = $1->strConst;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);
            
            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                $1->sym = res;

            arithexpr_check($1);  //TODO: print_error

            $$ = newexpr(arithexpr_e);
            $$->sym = newtemp();

            if( $1->type == tableitem_e ) {

                struct expr *val = emit_iftableitem($1);

                emit(assign, $$, val, NULL, 0);
                emit(sub, val, newexpr_constnum(1), val, 0);
                emit(tablesetelem, val, $1, $1->index, 0);
            }
            else{

                emit(assign,$$,$1,NULL,0);
                emit(sub,$1,newexpr_constnum(1),$1,0);
            }
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
            }else {

                //TODO_PAP   
                $3 = emit_if_eval($3);
                struct SymbolTableEntry *e = SymTable_lookup_all_scopes(st, $1->strConst, scope);

                // TODO: refactor code - avoid duplication
                
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
                        $1->sym->offset = g_offset++;

                        SymTable_print_elem($1->sym);
                    }
                    else if ( (e->type == LOCAL || e->type == FORMAL) && e->scope != scope )
                        print_static_analysis_error(yylineno, "Accessing " F_BOLD "%s" F_RST " from scope %d\n", $1->strConst, scope);
                    else if ( e->type == USERFUNC || e->type == LIBFUNC )
                        print_static_analysis_error(yylineno, F_BOLD "%s" F_RST " is defined as a function\n", $1->strConst);
                    else {

                        $1->sym = e;
                        $1->sym->offset = g_offset++;
                    }
                }

                emit(assign, $1, emit_iftableitem($3), NULL, 0);
                $$ = newexpr(assignexpr_e);
                $$->sym = newtemp();
                emit(assign, $$, $1, NULL, 0);
                ref_flag = REF_NONE;                                        
            }
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
                else if ( (e->type == LOCAL || e->type == FORMAL) && e->scope != scope )
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
        }
    | objectdef
        {
            $$ = $1;
        }
    | PUNC_LPARENTH funcdef PUNC_RPARENTH
        {
            $$ = newexpr(programfunc_e);
            $$->sym = $2;
        }
    | const
        {
            $$ = $1;
        }
    ;

lvalue:
    ID
        {
            ref_flag = REF_NONE; 
            $$ = newexpr(var_e);
            $$->strConst = strdup($1);
        }
    | KEYW_LOCAL ID
        {
            ref_flag = REF_LOCAL;
            $$ = newexpr(var_e);
            $$->strConst = strdup($2);
        }
    | PUNC_COLON2 ID
        {
            ref_flag = REF_GLOBAL;
            $$ = newexpr(var_e);
            $$->strConst = strdup($2);
        }
    | member
        {
            $$ = $1;
        }
    ;

member:
    lvalue PUNC_DOT ID
        {
            if ( $1->type == var_e )
                $1->sym = SymTable_lookup_add(st, $1->strConst, scope, yylineno);

            $$ = member_item($1, newexpr_conststr($3));
        }
    | lvalue PUNC_LBRACKET expr PUNC_RBRACKET
        {
            if ( $1->type == var_e )
                $1->sym = SymTable_lookup_add(st, $1->strConst, scope, yylineno);
            else
                //TODO_ERRORS
            $$ = member_item($1, $3);
        }
    | call PUNC_DOT ID
        {
            $$ = $1;
        }
    | call PUNC_LBRACKET expr PUNC_RBRACKET
        {
            //TODO_ERRORS check expr type
            $$ = $1;
        }
    ;

call:
    call PUNC_LPARENTH elist PUNC_RPARENTH
        {
            $$ = make_call($1, $3);
        }
    | lvalue callsuffix
        {
            $$ = newexpr(nil_e);
            struct SymbolTableEntry *e = SymTable_lookup_all_scopes(st, $1->strConst, scope);


            if ( !e )
                print_static_analysis_error(yylineno, "Symbol %s is not defined\n", $1->strConst);
            else if ( e->type == LOCAL && e->scope != scope )
                printf("\e[0;31mERROR [#%d]:\e[0m Symbol %s cannot be accessed from scope %d\n", yylineno,$1->strConst,scope);  // TODO: ask the fellas
            else if ( e->type != USERFUNC && e->type != LIBFUNC )
                print_static_analysis_error(yylineno, F_BOLD "%s" F_RST " is not a function\n", $1->strConst);
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

                printf("%s\n", $1->strConst);  // TODO: fix bug in print_static_analysis_error()
                print_static_analysis_error(yylineno, "Function %s is not defined\n", $1->strConst);
            }
        }
    | PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH
        {
            struct expr* func = newexpr(programfunc_e);

            func->sym = $2;
            $$=make_call(func, $5);
        }
    ;

callsuffix:
    normcall
        {
            $$ = $1;
        }
    |methodcall
        {
            $$ = $1;
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
        }
        ;

elistrep:
    PUNC_COMMA expr elistrep
        {
            //TODO_PAP emit if boolexpr_e
            $2 = emit_if_eval($2);
            $$ = $2;
            $$->next = $3;
        }
    |
        {
            $$ = NULL;
        }
    ;

elist:
    expr elistrep
        {
            //TODO_PAP emit if boolexpr_e
            $1 = emit_if_eval($1);
            $1->next = $2;
            $$ = $1;
        }
    |
        {
            $$ = NULL;
        }
    ;

objectin:
    elist
        {
            struct expr *t  = newexpr(newtable_e);
            struct expr *itter = $1;


            t->sym = istempexpr($1)? $1->sym : newtemp();
            emit(tablecreate, t, NULL, NULL, 0);

            for (int i = 0; itter; itter = itter->next, ++i)
                emit(tablesetelem, t, newexpr_constnum(i), itter, 0);

            $$ = t;
        }
    |indexed
        { 
            struct expr *t = newexpr(newtable_e);
            struct expr *itter = $1;


            t->sym = newtemp();
            emit(tablecreate, t, NULL, NULL, 0);
            for (int i = 0; itter; itter = itter->next, ++i)
                emit(tablesetelem, t, itter->index, itter, 0);

            $$=t;
        }
    ;

objectdef:
    PUNC_LBRACKET objectin PUNC_RBRACKET
        { 
            $$ = $2; 
        }
    ;

indexed:
    indexedelem indexrep
        {
            $$ = $1;
            $$->next = $2;
        }
    ;

indexedelem:
    PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE
        {
            //TODO_PAP emit if expr2 boolexpr_e
            $4 = emit_if_eval($4);
            //TODO_ERRORS check expr1 type
            $$ = $4;
            $$->index = $2;
        }
    ;

indexrep:
    PUNC_COMMA indexedelem indexrep
        {
            $$ = $2;
            $$->next = $3;
        }
    |
        {
            $$ = NULL;
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
        }
    statements PUNC_RBRACE
        {
            if ( current_function ) {

                SymTable_hide(st, scope);
                Stack_pop(g_stack, &g_offset);
            }

            --scope;
            $$ = $3;
        }
    ;

funcstart:
    {
        //TODO_REPSTACK store and reset loopcnt
        if(!loopcnt)
            loopcnt = Stack_create();
        else
            Stack_push(loopcnt,0);
    };

funcend:
    {
        //TODO_REPSTACK pop and reset loopcnt
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

                print_static_analysis_error(yylineno, "Symbol " F_BOLD "%s" " already exists\n", name);
                $$ = NULL;
            }
            else if( !res ) {

                $$ = SymTable_insert(st, name, USERFUNC, scope, yylineno);
                emit(funcstart, newexpr_conststr(name), NULL, NULL, 0);
            }
            else {

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
        }
    idlist
        {
            --scope;
            Stack_pop(g_stack, &g_offset);
        }
    PUNC_RPARENTH;

funcdef:
    funcprefix funcstart funcargs block funcend
        {
            if ( ($$ = $1) )
                emit(funcend, newexpr_conststr($1->name), NULL, NULL, 0);

            current_function = NULL;
            prog_var_flag = 0;
        }
    ;

const:
    CONST_INT
        {
            $$ = newexpr_constnum((double)(yylval.intVal));
        }
    | CONST_REAL
        {
            $$ = newexpr_constnum(yylval.realVal);
        }
    | STRING
        {
            $$ = newexpr_conststr($1);
        }
    | KEYW_NIL
        {
            $$ = newexpr(nil_e);
        }
    | KEYW_TRUE
        {
            $$ = newexpr_constbool(1);
        }
    | KEYW_FALSE
        {
            $$ = newexpr_constbool(0);
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
            // add code here
        }
    |
        {
            // add code here
        }
    ;

ifprefix:
    KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH
        {
            //TODO_PAP emit if boolexpr -> evlauate expr
            struct expr* evaluated_expr = evaluate($3);
            emit(if_eq, NULL, evaluated_expr, newexpr_constbool(1), currQuad + 2);
            $$ = currQuad;
            emit(jump,NULL,NULL,NULL,0);
        }
    ;

ifstmt:
    ifprefix stmt
        {
            patch_label($1, currQuad);
        }
    | ifprefix stmt KEYW_ELSE stmt
        {
            // add code here
        }
    ;

loopstart:
    {
        //TODO_REPSTACK increase current loopcnt
        // ++loopcnt->ci;
    };

loopend:
    {
        //TODO_REPSTACK decrease current loopcnt
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
            //TODO_PAP emit if boolexpr_e -> evaluate expr
            struct expr* evaluated_expr = evaluate($2);
            emit(if_eq, NULL, evaluated_expr, newexpr_constbool(1), getNextQuad() + 2U);
            $$ = getNextQuad();
            emit(jump, NULL, NULL, NULL, 0);
        }
    ;
whilestmt:
    whilestart loopstart whilecond stmt loopend
        {
            emit(jump, NULL, NULL, NULL, $1);
            patch_label($3, getNextQuad());
            
            patch_list($4->breaklist, getNextQuad());
            patch_list($4->contlist, $1);
        }
    ;

jumpandsavepos:
    {
        $$ = getNextQuad();
        emit(jump, NULL, NULL, NULL, 0);
    }
    ;

savepos:
    {
        $$ = getNextQuad();
    }
    ;

forprefix:
    KEYW_FOR loopstart PUNC_LPARENTH elist savepos PUNC_SEMIC expr PUNC_SEMIC loopend
        {   
            $$ = malloc(sizeof(struct for_contents));
            $$->test = $5;
            $$->enter = getNextQuad();
            
            //TODO_PAP emit if boolexpr_e -> evaluate expr
            struct expr* evaluated_expr = evaluate($7);
            emit(if_eq, evaluated_expr, newexpr_constbool(1), NULL, 0);
        }
    ;

forstmt:
    forprefix jumpandsavepos elist PUNC_RPARENTH jumpandsavepos stmt jumpandsavepos
        {
            patch_label($1->enter, $5 + 1);
            patch_label($2, getNextQuad());
            patch_label($5, $1->test);
            patch_label($7, $2 + 1);

            patch_list($6->breaklist, getNextQuad());
            patch_list($6->contlist, $2 + 1);
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
            $2 = emit_if_eval($2);
            if ( !scope )
                print_static_analysis_error(yylineno, "return statement outside of function\n");

            emit(ret, NULL, $2, NULL, 0);
        }
    ;

%%


void yyerror(const char *yaccerror){
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
