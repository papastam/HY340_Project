%{
    /*
    * TODO LIST:
    *  - Formal arguements offset is messed up              > FIXED
    *  - Temp variables offset is also messed up            > FIXED (?) 
    *  - GLOBALs and LOCALs have the same offset counter?
    *
    *  BROKEN TESTFILES:
    * p3t_calls.asc                 > DONE
    * p3t_if_else.asc               > DONE (Removed true evaluation)
    * p3t_flow_control.asc          > DONE (Same as above)
    * p3t_flow_control_error.asc    > DONE
    * p3t_relational.asc            > DONE
    * backpatch0.asc                > DONE
    * backpatch3.asc                > DONE
    * p3t_assignments_objects.asc   > DONE
    * p3t_basic_expr.asc            > DONE
    */

    #include <stdio.h>
    #include <assert.h>
    #include <string.h>
    #include <stdlib.h>

    #include "quads.h"
    #include "utils.h"
    #include "stack.h"
    #include "target_code_generator.h"
    #include "debug_functions.h"

    #define YYERROR_VERBOSE

    SymTable st;
    extern int yylineno;
    extern char * yytext;
    extern FILE * yyin;
    extern uint scope;
    char * current_function;
    extern FILE* file;

    #define REF_NONE   0
    #define REF_LOCAL  1
    #define REF_GLOBAL 2

    int ref_flag;
    int produce_icode = 1;
    int loopcnt;

    Stack offset_stack;
    Stack loopcnt_stack;

    int yylex(void);
    void yyerror(const char *yaccerror);

    extern int offset;
    extern int prog_var_flag;
    extern struct quad * quads;
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
%type <intVal> returnstmt

%type <functcont> methodcall
%type <functcont> normcall
%type <functcont> callsuffix

%type <forcont> forprefix

%type <symbol> funcprefix
%type <symbol> funcdef

%type <expression> member
%type <expression> assignexpr
%type <expression> expr
/* %type <expression> boolexpr */
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
%type <expression> ids

%type <stmtcont> statements
%type <stmtcont> stmt
%type <stmtcont> block
%type <stmtcont> ifstmt

%start program

%right OPER_EQ
%left KEYW_OR KEYW_AND
%nonassoc OPER_EQ2 OPER_NEQ
%nonassoc OPER_LET OPER_LEE OPER_GRT OPER_GRE
%left OPER_PLUS OPER_MINUS
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
            $$->retlist = mergelist($1->retlist, $2->retlist);
        }
    |
        {
            make_stmt(&$$);
        }
    ;

stmt:
    expr PUNC_SEMIC
        {
            if($1->type==boolexpr_e){
                emit_eval($1);
            }
            resettemp();
            make_stmt(&$$);

            // printExpression($1);
        }
    | ifstmt
        {
            $$=$1;
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
            $$->retlist = newlist($1);
        }
    | KEYW_BREAK PUNC_SEMIC
        {
            make_stmt(&$$);
            emit(jump, NULL, NULL, NULL, 0);
            $$->breaklist = newlist(getNextQuad() - 1);

            if ( !loopcnt )
                print_static_analysis_error(yylineno, F_BOLD "break" F_RST " statement outside of loop\n");
        }
    | KEYW_CONT PUNC_SEMIC
        {
            make_stmt(&$$);
            emit(jump, NULL, NULL, NULL, 0);
            $$->contlist = newlist(getNextQuad() - 1);

            if ( !loopcnt )
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
            if(!arithexpr_check($1) || !arithexpr_check($3))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(add,$$, $1, $3, 0);
        }
    | expr OPER_MINUS expr
        {
            if(!arithexpr_check($1) || !arithexpr_check($3))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(sub,$$, $1, $3, 0);
        }
    | expr OPER_MUL expr
        {
            if(!arithexpr_check($1) || !arithexpr_check($3))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(mul,$$, $1, $3,0);
        }
    | expr OPER_DIV expr
        {
            if(!arithexpr_check($1) || !arithexpr_check($3))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            if($3->type == constnum_e && $3->numConst == 0) 
                print_static_analysis_error(yylineno, "Division with 0 is not allowed.\n");
            
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(div_o, $$, $1, $3, 0);
        
        }
    | expr OPER_MOD expr
        {
            if(!arithexpr_check($1) || !arithexpr_check($3))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($1) ? $1->sym : newtemp();
            emit(mod,$$, $1, $3, 0);
        }
    | expr KEYW_AND {if($1->type!=boolexpr_e)$1 = evaluate($1);} savepos expr
        {
            int additional_quads=0;
            if($5->type!=boolexpr_e){
                $5 = evaluate($5);
                // additional_quads+=2;
            }


            patch_list($1->truelist, $4+additional_quads);
            $$ = newexpr(boolexpr_e);
            $$->truelist = $5->truelist;
            $$->falselist = merge_bool_lists($1->falselist, $5->falselist);
        }
    | expr KEYW_OR {if($1->type!=boolexpr_e)$1 = evaluate($1);} savepos expr
        {
            int additional_quads=0;
            
            if($5->type!=boolexpr_e){
                $5 = evaluate($5);
                // additional_quads+=s2;
            }

            patch_list($1->falselist, $4+additional_quads);
            $$ = newexpr(boolexpr_e);
            $$->truelist = merge_bool_lists($1->truelist, $5->truelist);
            $$->falselist = $5->falselist;
        }
    | expr OPER_GRT expr
        {
            if(!arithexpr_check($1) || !arithexpr_check($3))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            $$ = newexpr(boolexpr_e);

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_greater, NULL, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);   
        }
    | expr OPER_GRE expr
        {
            if(!arithexpr_check($1) || !arithexpr_check($3))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            $$ = newexpr(boolexpr_e);

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_greatereq, NULL, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);   
        }
    | expr OPER_LET expr
        {
            if(!arithexpr_check($1) || !arithexpr_check($3))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            $$ = newexpr(boolexpr_e);

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_less, NULL, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
    | expr OPER_LEE expr
        {
            if(!arithexpr_check($1) || !arithexpr_check($3))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            $$ = newexpr(boolexpr_e);

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_lesseq, NULL, $1, $3, 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
    | expr OPER_EQ2 {if($1->type==boolexpr_e)$1 = emit_eval($1);} expr
        {

            if($4->type==boolexpr_e)
                $4 = emit_eval($4);

            $$ = newexpr(boolexpr_e);

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_eq, NULL, $1, $4, 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
    | expr OPER_NEQ {if($1->type==boolexpr_e)$1 = emit_eval($1);} expr
        {
            if($4->type==boolexpr_e)
                $4 = emit_eval($4);

            $$ = newexpr(boolexpr_e);

            $$->truelist = getNextQuad();
            $$->falselist = getNextQuad() + 1;
            emit(if_noteq, NULL, $1, $4, 0);
            
            emit(jump, NULL, NULL, NULL, 0);
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

/* boolexpr:
    
    | expr
        {
            $$ = evaluate($1);
        }
    | PUNC_LPARENTH boolexpr PUNC_RPARENTH
        {
            $$=$2;       
        } 
    ; */

term:
    PUNC_LPARENTH expr PUNC_RPARENTH
        {
            if($2->type==boolexpr_e)
                $$ = emit_eval($2);
            $$=$2;
        }
    | OPER_MINUS expr %prec UNARY_MINUS
        {
            if(!arithexpr_check($2))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");
            $$ = newexpr(arithexpr_e);
            $$->sym = istempexpr($2)? $2->sym : newtemp();
            emit(uminus, $$, $2, NULL, 0);
        }
    | KEYW_NOT expr
        {
            // In this approach, if expr is a boolexpr, flip the lists, otherwise tag it and let the other reductions handle it
            // if($2->type == boolexpr_e){
            //     $$ = $2;
                
            //     int temptruelist  = $2->falselist;
            //     int tempfalselist = $2->truelist;
            
            //     $$->truelist    = tempfalselist;
            //     $$->falselist   = temptruelist;
            // }else
            //     $$ = $2;
            //     $$ -> nottag=1;

            // INITIAL APPROACH: we changed it because this way if the stack has expr and not expr, not expr is reduced and emited.
            // This way the second part of the end is evaluated first, wich is wrong

            // if($2->type != boolexpr_e){
            //     $2 = evaluate($2);
            // }   

            if($2->type!=boolexpr_e){
                $2 = evaluate($2);
            }
            $$ = $2;
            
            int temptruelist  = $2->truelist;
            int tempfalselist = $2->falselist;
        
            $$->truelist    = tempfalselist;
            $$->falselist   = temptruelist;
        }
    | OPER_PLUS2 lvalue
        {
            if(!arithexpr_check($2))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");

            char *name = $2->strConst;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);


            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "++%s" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "++%s" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                $2->sym = res;


            if ( $2->type == tableitem_e ) {

                $$ = emit_iftableitem($2);
                emit(add, $$, $$, newexpr_constnum(1), 0);
                emit(tablesetelem, $$, $2, $2->index, 0);
            }
            else {

                emit(add, $2, newexpr_constnum(1), $2, 0);
                $$ = $2;
            }
        }
    | lvalue OPER_PLUS2
        {
            if(!arithexpr_check($1))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");            
            
            char *name = $1->strConst;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);


            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                $1->sym = res;


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
            if(!arithexpr_check($2))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");
            
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, $2->sym->name, scope);
            

            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "--%s" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, $2->sym->name, $2->sym->name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "--%s" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, $2->sym->name, $2->sym->name);
            else
                $2->sym = res;
            

            if($2->type==tableitem_e) {
                $$ = emit_iftableitem($2);
                emit(sub, $$, $$, newexpr_constnum(1), 0);
                emit(tablesetelem, $$, $2, $2->index,0);
            }else{
                emit(sub, $2, $2, newexpr_constnum(1), 0);
                $$ = $2;
            }
        }
    | lvalue OPER_MINUS2
        {
            if(!arithexpr_check($1))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");

            char *name = $1->strConst;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);
            
            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                $1->sym = res;


            $$ = newexpr(arithexpr_e);
            $$->sym = newtemp();

            if( $1->type == tableitem_e ) {

                struct expr *val = emit_iftableitem($1);

                emit(assign, $$, val, NULL, 0);
                emit(sub, val, val, newexpr_constnum(1), 0);
                emit(tablesetelem, val, $1, $1->index, 0);
            }
            else{

                emit(assign,$$,$1,NULL,0);
                emit(sub, $1, $1, newexpr_constnum(1),0);
            }
        }
    | primary
        {
            $$ = $1;
        }
    ;

primary:
    lvalue
        {
            if ( $1->type == var_e ) {

                if ( ($1->sym->type == LOCAL || $1->sym->type == FORMAL) && $1->sym->scope > scope )
                    print_static_analysis_error(yylineno, "Symbol %s cannot be accessed from scope %d\n", $1->strConst, scope);
                // else if ( $1->sym->type == USERFUNC || $1->sym->type == LIBFUNC )
                //     print_static_analysis_error(yylineno, "Symbol %s is defined as a function\n", $1->strConst);
                else {

                    $$ = $1;
                    $$->sym = $1->sym;
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

assignexpr:
    lvalue OPER_EQ expr
        {
            if ( $1->type == tableitem_e ) {

                emit(tablesetelem, emit_iftableitem($3), $1, $1->index, 0);
                $$ = emit_iftableitem($1);
                $$->type = var_e;//It was assignexpr_e but there is no reason for that
            }
            else {

                if($3->type==boolexpr_e){
                    $3 = emit_eval($3);
                }
                

                
                if ( ref_flag == REF_LOCAL ) {

                    
                    if ( $1->sym->scope < scope )
                        print_static_analysis_error(yylineno, "Symbol %s can't be accessed from scope %d\n", $1->strConst, scope);
                    else if ( $1->sym->type == USERFUNC || $1->sym->type == LIBFUNC )
                        print_static_analysis_error(yylineno, "Symbol %s defined as a function\n", $1->strConst);
                    else if ( $1->sym->type == FORMAL && $1->sym->scope > scope )
                        print_static_analysis_error(yylineno, "Symbol %s can't be accessed from scope %d\n", $1->strConst, scope);
                }
                else {  //ID
                    if ( ($1->sym->type == LOCAL || $1->sym->type == FORMAL) && $1->sym->scope > scope )
                        print_static_analysis_error(yylineno, "Accessing " F_BOLD "%s" F_RST " from scope %d\n", $1->strConst, scope);
                    else if ( $1->sym->type == USERFUNC || $1->sym->type == LIBFUNC )
                        print_static_analysis_error(yylineno, F_BOLD "%s" F_RST " is defined as a function\n", $1->strConst);
                }

                emit(assign, $1, emit_iftableitem($3), NULL, 0U);
                $$ = newexpr(var_e);//It was assignexpr_e but there is no reason for thatexpr_e
                $$->sym = newtemp();
                emit(assign, $$, $1, NULL, 0U);
                ref_flag = REF_NONE;               
            }
        }
    ;

lvalue:
    ID
        {
            struct SymbolTableEntry* e = SymTable_lookup_all_scopes(st, $1, scope); 
            if(!e) {
                e = SymTable_insert(st, $1, (!prog_var_flag ? GLOBAL : LOCAL), scope, yylineno);
                e->offset = offset++;
            }

            if(e->type==USERFUNC){
                $$ = newexpr(programfunc_e);
            }else if(e->type==LIBFUNC){
                $$ = newexpr(libraryfunc_e);
            }else{
                $$ = newexpr(var_e);
                ref_flag = REF_NONE; 
                $$->strConst = strdup($1);
            }
            $$->sym = e;
        }
    | KEYW_LOCAL ID
        {
            struct SymbolTableEntry* e = SymTable_lookup_all_scopes(st, $2, scope); 
            if(!e || e->scope < scope) {
                e = SymTable_insert(st, $2, LOCAL, scope, yylineno);
                e->offset = offset++;
            }
            
            if(e->type==userfunc_a){
                $$ = newexpr(programfunc_e);
            }else if(e->type==libfunc_a){
                $$ = newexpr(libfunc_a);
            }else{
                $$ = newexpr(var_e);
                ref_flag = REF_LOCAL;
                $$->strConst = strdup($2);
            }
            $$->sym = e;
        }
    | PUNC_COLON2 ID
        {            
            struct SymbolTableEntry* e = SymTable_lookup_type(st, $2, scope, GLOBAL); 
            if(!e ||  e->type!=GLOBAL) {
                print_static_analysis_error(yylineno, "Global variable \"%s\" undeclared! \n", $2);
            }else{

                if(e->type==userfunc_a){
                    $$ = newexpr(programfunc_e);
                }else if(e->type==libfunc_a){
                    $$ = newexpr(libraryfunc_e);
                }else{
                    $$ = newexpr(var_e);
                    ref_flag = REF_GLOBAL;
                    $$->strConst = strdup($2);
                }
            }
            $$->sym = e;
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
                $1->sym = SymTable_lookup_add(st, $1->strConst, -1, scope, yylineno);

            $$ = member_item($1, newexpr_conststr($3));
        }
    | lvalue PUNC_LBRACKET expr PUNC_RBRACKET
        {
            if ( $1->type == var_e )
                $1->sym = SymTable_lookup_add(st, $1->strConst, -1, scope, yylineno);
            // else
            //     print_static_analysis_error(yylineno, "%s is not a variable\n", $1->sym->name);
            $$ = member_item($1, $3);
        }
    | call PUNC_DOT ID
        {
            $$ = $1;
        }
    | call PUNC_LBRACKET expr PUNC_RBRACKET
        {
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
            
            // if($1->type!=programfunc_e && $1->type!=libraryfunc_e){
            //     print_static_analysis_error(yylineno, F_BOLD "%s" F_RST " is not a function\n", $1->strConst);
            // }else{   
            
                struct SymbolTableEntry * e;
                if(!istempname($1->sym))
                    e = SymTable_lookup_all_scopes(st, $1->sym->name, scope);
                else
                    e = $1->sym;

                if ( !e )
                    print_static_analysis_error(yylineno, "Symbol %s is not defined\n", $1->strConst);
                else if ( e->type == LOCAL && e->scope > scope )
                    print_static_analysis_error(yylineno, "Symbol %s cannot be accessed from scope %d\n", $1->strConst,scope);
                else {

                    $1->sym = e;
                    $1 = emit_iftableitem($1);
                    struct expr* elist = $2->elist;

                    if ( $2->method ) {

                        struct expr *t = $1;

                        $1 = emit_iftableitem(member_item(t, newexpr_conststr($2->name)));
                        
                        elist = append_elist(t,elist);
                    }


                    $$ = make_call($1, elist);
                // }
            }

            if( $$->type == nil_e ) {
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
    | methodcall
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
            if($2->type==boolexpr_e)
                $2 = emit_eval($2);
            
            $$ = append_elist($2, $3);
        }
    |
        {
            $$ = NULL;
        }
    ;

elist:
    expr elistrep
        {
            if($1->type==boolexpr_e)
                $1 = emit_eval($1);
            
            
            $$ = append_elist($1, $2);
        }
    |
        {
            $$ = NULL;
        }
    ;

objectin:
    elist
        {
            struct expr * t  = newexpr(newtable_e);
            struct expr * itter = $1;


            if ( $1 )
                t->sym = istempexpr($1) ? $1->sym : newtemp();
            else
                t->sym = newtemp();

            emit(tablecreate, t, NULL, NULL, 0);

            for (uint i = 0U; itter; itter = itter->next, ++i)
                emit(tablesetelem, itter, t, newexpr_constnum(i), 0U);

            $$ = t;
        }
    | indexed
        { 
            struct expr *t = newexpr(newtable_e);
            struct expr *itter = $1;


            t->sym = newtemp();
            emit(tablecreate, t, NULL, NULL, 0);
            for (int i = 0; itter; itter = itter->next, ++i)
                emit(tablesetelem, itter, t, itter->index, 0);

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
            if($4->type==boolexpr_e)
                $4 = emit_eval($4);
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

blockprefix:
    PUNC_LBRACE
        {
            ++scope;

            if ( current_function ) {

                Stack_push(offset_stack, offset);
                offset = 0;
            }
        }
    ;

block:
    blockprefix statements PUNC_RBRACE
        {
            $$ = $2;
            $$->local_cnt = offset;

            if ( current_function ) {

                SymTable_hide(st, scope);
                Stack_pop(offset_stack, &offset);
            }

            --scope;
        }
    ;

funcstart:
    {
        Stack_push(loopcnt_stack, loopcnt);
        loopcnt = 0;
    };

funcend:
    {
        Stack_pop(loopcnt_stack, &loopcnt);
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
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);

            if ( res && res->scope >= scope ) {

                print_static_analysis_error(yylineno, "Symbol " F_BOLD "%s" " already exists\n", name);
                $$ = NULL;
            }
            else {

                $$ = SymTable_insert(st, name, USERFUNC, scope, yylineno);

                struct expr* newfunc= newexpr(programfunc_e);
                newfunc->sym = $$;
                emit(jump, NULL, NULL, NULL,0);
                emit(funcstart, NULL, newfunc, NULL, 0);
            }
        }
    ;

funcargs:
    PUNC_LPARENTH
        {
            ++scope;
            Stack_push(offset_stack, offset);
            offset = 0UL;
            ++prog_var_flag;
        }
    idlist
        {
            --scope;
            Stack_pop(offset_stack, &offset);
        }
    PUNC_RPARENTH;

funcdef:
    funcprefix savepos funcstart funcargs block funcend
        {
            // if ( ($$ = $1) )
            struct expr* funcending = newexpr(programfunc_e);
            funcending->sym = $1;
            funcending->sym->local_cnt = $5->local_cnt;

            patch_list($5->retlist,getNextQuad());
            emit(funcend, NULL, funcending, NULL, 0);
            patch_label($2-2,getNextQuad());

            current_function = NULL;
            --prog_var_flag;
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
            char * name = $1;
            struct SymbolTableEntry * res = SymTable_lookup_scope(st, name, scope);


            if ( !checkIfAllowed(name) )
                print_static_analysis_error(yylineno, "argument \e[1m%s\e[0m of function \e[1m%s\e[0m has the same name as an alpha_library_function\n",\
                            name, current_function);
            else {

                if ( res )
                    print_static_analysis_error(yylineno, "FORMAL variable '%s' has the same name as another FORMAL argument\n", name);
                else {

                    res = SymTable_insert(st, name, FORMAL, scope, yylineno);
                    res->offset = offset++;

                    SymTable_insert_func_arg(st, current_function, name);
                }
            }
            
            struct expr* list = $2;
            while(list){
                struct SymbolTableEntry *added;
                if ( !checkIfAllowed(list->strConst) )
                    print_static_analysis_error(yylineno, "argument \e[1m%s\e[0m of function \e[1m%s\e[0m has the same name as an alpha_library_function\n",\
                            list->strConst, current_function);
                else {
                    res = SymTable_insert(st, list->strConst, FORMAL, scope, yylineno);
                    res->offset = offset++;

                    SymTable_insert_func_arg(st, current_function, list->strConst);
                }
            list = list->next;
            }
        }            
    |
    ;

ids:
    PUNC_COMMA ID ids
        {
            $$  = newexpr_conststr($2);
            $$->next = $3;            


            // char *name = $2;
            // struct SymbolTableEntry *res = SymTable_lookup_scope(st, name, scope);


            // if ( !checkIfAllowed(name) )
            //     print_static_analysis_error(yylineno, "argument \e[1m%s\e[0m of function \e[1m%s\e[0m has the same name as an alpha_library_function\n",\
            //                 name, current_function);
            // else {

            //     if ( res )
            //         print_static_analysis_error(yylineno, "Formal variable '%s' has the same name as another formal variable!\n");
            //     else {

            //         res = SymTable_insert(st, name, FORMAL, scope, yylineno);
            //         res->offset = offset++;

            //         SymTable_insert_func_arg(st, current_function, name);
            //     }
            // }
        }
    |
        {
            $$ = NULL;
        }
    ;

ifprefix:
    KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH
        {
            struct expr* evaluated_expr = emit_eval($3);
            emit(if_eq, NULL, evaluated_expr, newexpr_constbool(1), currQuad + 2);
            $$ = currQuad;
            emit(jump,NULL,NULL,NULL,0);
        }
    ;

ifstmt:
    ifprefix stmt
        {
            patch_label($1, currQuad);
            $$ = $2;
        }
    | ifprefix stmt KEYW_ELSE jumpandsavepos stmt
        {
            patch_label($1, $4+1);
            patch_label($4, currQuad);
            
            make_stmt(&$$);
            $$->breaklist = mergelist($2->breaklist,$5->breaklist);
            $$->contlist  = mergelist($2->contlist,$5->contlist);
            $$->retlist   = mergelist($2->retlist,$5->retlist);
            $$->local_cnt = $2->local_cnt + $5->local_cnt;

        }
    ;

loopstart:
    {
        ++loopcnt;
    };

loopend:
    {
        --loopcnt;
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
            struct expr* evaluated_expr = emit_eval($2);
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
    KEYW_FOR loopstart PUNC_LPARENTH elist savepos PUNC_SEMIC expr PUNC_SEMIC 
        {   
            struct expr* evaluated_expr = emit_eval($7);
            
            $$ = malloc(sizeof(struct for_contents));
            $$->test = $5;
            $$->enter = getNextQuad();
            
            emit(if_eq, NULL, evaluated_expr, newexpr_constbool(1), 0);
        }
    ;

forstmt:
    forprefix jumpandsavepos elist PUNC_RPARENTH jumpandsavepos stmt jumpandsavepos loopend
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
            if ( !prog_var_flag )
                print_static_analysis_error(yylineno, "return statement outside of function\n");

            emit(ret, NULL, NULL, NULL, 0);
            $$ = currQuad;
            emit(jump,NULL,NULL,NULL, 0);

        }
    | KEYW_RET expr PUNC_SEMIC
        {
            if($2->type==boolexpr_e)
                $2 = emit_eval($2);
            if ( !prog_var_flag )
                print_static_analysis_error(yylineno, "return statement outside of function\n");
 
            emit(ret, NULL, $2, NULL, 0);
            $$ = currQuad;
            emit(jump,NULL,NULL,NULL, 0);
        }
    ;

%%

void yyerror(const char *yaccerror){
    print_static_analysis_error(yylineno, "ERROR: %s\n", yaccerror);
}

int main(int argc, char **argv) {

    int index;
    // yydebug = 1;

    if ( argc != 2 ) {

        printf("\e[1;31merror\e[0m: no input file\n");
        return 0;
    }

    if ( !(yyin = fopen(argv[1], "r")) ) {

        perror("fopen()");
        return 1;
    }

    assert( (st = SymTable_create()) );
    assert( (offset_stack = Stack_create()) );
    assert( (loopcnt_stack = Stack_create()) );
    assert( (quads = quadtable_create()) );
    initFile();

    yyparse();

    if(!produce_icode )
        exit(0);
        
    print_quads();
    
    // SymTable_print_all(st);
    /* SymTable_print_scopes(st); */

    generate();
    print_readable_instructions();
    dump_binary_file();

    fclose(file);
}
