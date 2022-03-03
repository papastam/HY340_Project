/**  csd4273, csd4275, csd4569 **/


/** Definitions **/

%{
    #include "enum_types.h"
    #include <assert.h>
    #define YY_DECL int yylex(void *token)

    struct alpha_token_t {

        unsigned int line;
        unsigned int type;

        char *content;

        struct alpha_token_t *next;
    };

    int count = 0;
    int comment_count = 0;
    int ml_comm_start;


    void print_error(char *msg) {
        printf("\033[0;31mERROR: %s\n\033[0m", msg);
    }

    char *_printable_lex_token(int ltn) {  //lex token number

        assert( (ltn >= 0) && (ltn <= LEX_TOTAL_TOKENS) );
        return g_lex_prints[ltn];
    }

    int save_token(char *cont, void **token, unsigned int type) {


        struct alpha_token_t *tkn = ( (struct alpha_token_t *) *((struct alpha_token_t **)(token)) );
        char* content = strdup(cont);                                    //me to strtok pou paizei na ginei meta xalaei to cont

        int i;
        int t;


        if( type == COMM_ML )                  // mono an einai ml comment to theloume afto
            tkn->line = atoi(strtok(content, " "));  //prwto noumero tou string einai to start line
        else
            tkn->line = yylineno;                    //gia oles tis alles periptwseis theloume to yylineno

        tkn->content = strdup(cont);
        tkn->type    = type;
        tkn->next    = malloc(sizeof(*tkn));

        if ( !tkn->next ) {

            perror("malloc() error");
            return EXIT_FAILURE;
        }

        tkn->next->next = NULL;
        *((struct alpha_token_t **)(token)) = tkn->next;
        free(content);
    }
%}

digit       [0-9]
letter      [a-zA-Z]
id          {letter}+({letter}|{digit}|_)*
string      "\""(.|\n)*"\""
comm_sl     "//".*
unknown_start [!@#$%^&*_]

%option yylineno
%x COMMENT

%%


"="                 { save_token(yytext, &token, OPER_EQ); }
"+"                 { save_token(yytext, &token, OPER_PLUS); }
"-"                 { save_token(yytext, &token, OPER_MINUS); }
"*"                 { save_token(yytext, &token, OPER_MUL); }
"/"                 { save_token(yytext, &token, OPER_DIV); }
"%"                 { save_token(yytext, &token, OPER_MOD); }
"=="                { save_token(yytext, &token, OPER_EQ2); }  
"!="                { save_token(yytext, &token, OPER_NEQ); }
"++"                { save_token(yytext, &token, OPER_PLUS2); }
"--"                { save_token(yytext, &token, OPER_MINUS2); }
">"                 { save_token(yytext, &token, OPER_GRT); }
">="                { save_token(yytext, &token, OPER_GRE); }
"<"                 { save_token(yytext, &token, OPER_LET); }
"<="                { save_token(yytext, &token, OPER_LEE); }

"{"                 { save_token(yytext, &token, PUNC_LBRACE); }
"}"                 { save_token(yytext, &token, PUNC_RBRACE); }
"["                 { save_token(yytext, &token, PUNC_LBRACKET); }
"]"                 { save_token(yytext, &token, PUNC_RBRACKET); }
"("                 { save_token(yytext, &token, PUNC_LPARENTH); }
")"                 { save_token(yytext, &token, PUNC_RPARENTH); }
";"                 { save_token(yytext, &token, PUNC_SEMIC); }
","                 { save_token(yytext, &token, PUNC_COMMA); }
":"                 { save_token(yytext, &token, PUNC_COLON); }
"::"                { save_token(yytext, &token, PUNC_COLON2); }
"."                 { save_token(yytext, &token, PUNC_DOT); }
".."                { save_token(yytext, &token, PUNC_DOT2); }

"if"                { save_token(yytext, &token, KEYW_IF); }
"else"              { save_token(yytext, &token, KEYW_ELSE); }
"while"             { save_token(yytext, &token, KEYW_WHILE); }
"for"               { save_token(yytext, &token, KEYW_FOR); }
"function"          { save_token(yytext, &token, KEYW_FUNC); }
"return"            { save_token(yytext, &token, KEYW_RET); }
"break"             { save_token(yytext, &token, KEYW_BREAK); }
"continue"          { save_token(yytext, &token, KEYW_CONT); }
"and"               { save_token(yytext, &token, KEYW_AND); }
"not"               { save_token(yytext, &token, KEYW_NOT); }
"or"                { save_token(yytext, &token, KEYW_OR); }
"local"             { save_token(yytext, &token, KEYW_LOCAL); }
"true"              { save_token(yytext, &token, KEYW_TRUE); }
"false"             { save_token(yytext, &token, KEYW_FALSE); }
"nil"               { save_token(yytext, &token, KEYW_NIL); }

{digit}+            { save_token(yytext, &token, CONST_INT); }
{digit}+"."{digit}+ { save_token(yytext, &token, CONST_REAL); }
{id}                { save_token(yytext, &token, ID); }
{comm_sl}           { save_token(yytext, &token, COMM_SL); }

"/*"                {   
                        ml_comm_start = yylineno;
                        ++comment_count;
                        BEGIN(COMMENT);
                    }
<COMMENT>"/*"       {   comment_count++; }
<COMMENT>[^*/]*      
<COMMENT>"*"+[^*/]*
<COMMENT>"*"+"/"    {  
                        char text[20];
                        comment_count--;

                        if( comment_count > 0 )
                            save_token("nested comment", (&token), COMM_NEST);
                        else if( comment_count == 0 ) {

                            sprintf(text, "%d - %d", ml_comm_start, yylineno);
                            save_token(text, (&token), COMM_ML); 

                            BEGIN(INITIAL);
                        }
    
                    }
<COMMENT><<EOF>>    {
                        print_error("EOF reached without closing a comment!");
                        return 0;
                    }

"*/"                { print_error("Multi-line comment closing without it being opened!");return 0; }

{string}            { save_token(yytext, &token, STRING); }

[ \n]               /* eat all the space and new line characters*/
<INITIAL><<EOF>>    { return 1; }

{unknown_start}[^ \n]* { print_error("Unknown definition!");printf("%s\n",yytext); }


%%  

int yywrap(){}

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
    
    if( !yylex(&token) )
        return 1;

    printf("\n");

    for (index = 0, curr = &token; (curr && curr->content); curr = curr->next, ++index) {

        printf("[%d] line::%u '%s' -- %s\n", index, curr->line, curr->content, _printable_lex_token(curr->type));
        free(curr->content);

        /** TODO: free(everything) */
    }


    return 0;
}


