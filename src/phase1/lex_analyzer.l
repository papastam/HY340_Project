/**  csd4273, csd4275, csd4569 **/


/** Definitions **/

%{
    #include "inc/enum_types.h"
    #include <assert.h>
    #include "parser.h"

    
    // #define YY_DECL int yylex(void *token)

    #define ERR_STRING "\e[0;31mERROR\e[37m:\e[0m"

    struct alpha_token_t {

        unsigned int line;
        unsigned int type;

        char *content;

        struct alpha_token_t *next;
    } token2;

    void* token = &token2;

    int count = 0;
    int comment_count = 0;
    int ml_comm_start;


    void print_error(char *msg) {

        printf(ERR_STRING ":\e[0m\e[93m%d\e[0m [%s]\e[91m --->\e[0m '%s'\n", yylineno, msg, yytext);
        exit(EXIT_FAILURE);
    }

    char *_printable_lex_token(int ltn) {  //lex token number

        assert( (ltn >= 0) && (ltn <= LEX_TOTAL_TOKENS) );
        return g_lex_prints[ltn];
    }

    int save_token(char *cont, void **token, unsigned int type) {


        struct alpha_token_t *tkn = ( (struct alpha_token_t *) *((struct alpha_token_t **)(token)) );
        char* content = strdup(cont);                                    //me to strtok pou paizei na ginei meta xalaei to cont


        if( type == COMM_ML )                  // mono an einai ml comment to theloume afto
            tkn->line = atoi(strtok(content, " "));  //prwto noumero tou string einai to start line
        else
            tkn->line = yylineno;                    //gia oles tis alles periptwseis theloume to yylineno

        if ( type == STRING ) {

            char *tbuf;

            int index;
            int limit;


            for (++yytext, index = 1, limit = yyleng - 1; index < limit; ++index);  // counting

            if ( !(tbuf = malloc(index + 1)) ) {  // including '\0'

                perror("malloc()");
                exit(EXIT_FAILURE);
            }

            tbuf[index] = '\0';

            for (index = 0; index < limit; ++index, ++yytext) {

                if ( *yytext != '\\' )
                    tbuf[index] = *yytext;
                else {

                    int t = *(yytext + 1);

                    if ( t == 'n' ) {

                        tbuf[index] = '\n';
                        ++yytext;
                    }
                    else if ( t == 't' ) {

                        tbuf[index] = '\t';
                        ++yytext;
                    }
                    else if ( t == '\\' ) {

                        tbuf[index] = '\\';
                        ++yytext;
                    }
                    else if ( t == '\"' ) {

                        tbuf[index] = '\"';
                        ++yytext;
                    }
                    else
                        tbuf[index] = '\\';
                }
            }

            tbuf[index] = 0;
            tkn->content = tbuf;
        }
        else
            tkn->content = strdup(cont);

        tkn->type    = type;
        tkn->next    = malloc(sizeof(*tkn));

        if ( !tkn->next ) {

            perror("malloc()");
            exit(EXIT_FAILURE);
        }

        tkn->next->next = NULL;
        *((struct alpha_token_t **)(token)) = tkn->next;
        free(content);
    }
%}

digit       [0-9]
letter      [a-zA-Z]
string      \"(\\.|[^"\\])*\"
id          {letter}+({letter}|{digit}|_)*
comm_sl     "//".*
unknown_start [@#$^&_] 
ending      [ \n;]

%option outfile = "lex.c"
%option yylineno
%option noyywrap
%x COMMENT

%%

"="                 { save_token(yytext, &token, OPER_EQ); return OPER_EQ; }
"+"                 { save_token(yytext, &token, OPER_PLUS); return OPER_PLUS; }
"-"                 { save_token(yytext, &token, OPER_MINUS); return OPER_MINUS; }
"*"                 { save_token(yytext, &token, OPER_MUL); return OPER_MUL; }
"/"                 { save_token(yytext, &token, OPER_DIV); return OPER_DIV; }
"%"                 { save_token(yytext, &token, OPER_MOD); return OPER_MOD; }
"=="                { save_token(yytext, &token, OPER_EQ2); return OPER_EQ2; }  
"!="                { save_token(yytext, &token, OPER_NEQ); return OPER_NEQ; }
"++"                { save_token(yytext, &token, OPER_PLUS2); return OPER_PLUS2; }
"--"                { save_token(yytext, &token, OPER_MINUS2); return OPER_MINUS2; }
">"                 { save_token(yytext, &token, OPER_GRT); return OPER_GRT; }
">="                { save_token(yytext, &token, OPER_GRE); return OPER_GRE; }
"<"                 { save_token(yytext, &token, OPER_LET); return OPER_LET; }
"<="                { save_token(yytext, &token, OPER_LEE); return OPER_LEE; }

"{"                 { save_token(yytext, &token, PUNC_LBRACE); return PUNC_LBRACE; }
"}"                 { save_token(yytext, &token, PUNC_RBRACE); return PUNC_RBRACE; }
"["                 { save_token(yytext, &token, PUNC_LBRACKET); return PUNC_LBRACKET; }
"]"                 { save_token(yytext, &token, PUNC_RBRACKET); return PUNC_RBRACKET; }
"("                 { save_token(yytext, &token, PUNC_LPARENTH); return PUNC_LPARENTH; }
")"                 { save_token(yytext, &token, PUNC_RPARENTH); return PUNC_RPARENTH; }
";"                 { save_token(yytext, &token, PUNC_SEMIC); return PUNC_SEMIC; }
","                 { save_token(yytext, &token, PUNC_COMMA); return PUNC_COMMA; }
":"                 { save_token(yytext, &token, PUNC_COLON); return PUNC_COLON; }
"::"                { save_token(yytext, &token, PUNC_COLON2); return PUNC_COLON2; }
"."                 { save_token(yytext, &token, PUNC_DOT); return PUNC_DOT; }
".."                { save_token(yytext, &token, PUNC_DOT2); return PUNC_DOT2; }

"if"                { save_token(yytext, &token, KEYW_IF); return KEYW_IF; }
"else"              { save_token(yytext, &token, KEYW_ELSE); return KEYW_ELSE; }
"while"             { save_token(yytext, &token, KEYW_WHILE); return KEYW_WHILE; }
"for"               { save_token(yytext, &token, KEYW_FOR); return KEYW_FOR; }
"function"          { save_token(yytext, &token, KEYW_FUNC); return KEYW_FUNC; }
"return"            { save_token(yytext, &token, KEYW_RET); return KEYW_RET; }
"break"             { save_token(yytext, &token, KEYW_BREAK); return KEYW_BREAK; }
"continue"          { save_token(yytext, &token, KEYW_CONT); return KEYW_CONT; }
"and"               { save_token(yytext, &token, KEYW_AND); return KEYW_AND; }
"not"               { save_token(yytext, &token, KEYW_NOT); return KEYW_NOT; }
"or"                { save_token(yytext, &token, KEYW_OR); return KEYW_OR; }
"local"             { save_token(yytext, &token, KEYW_LOCAL); return KEYW_LOCAL; }
"true"              { save_token(yytext, &token, KEYW_TRUE); return KEYW_TRUE; }
"false"             { save_token(yytext, &token, KEYW_FALSE); return KEYW_FALSE; }
"nil"               { save_token(yytext, &token, KEYW_NIL); return KEYW_NIL; }

{digit}+            { save_token(yytext, &token, CONST_INT); yylval.intVal = atoi(yytext); return CONST_INT; }
{digit}+"."{digit}+ { save_token(yytext, &token, CONST_REAL); yylval.realVal = atof(yytext); return CONST_REAL; } //atof gyrnaei double
{id}                { save_token(yytext, &token, ID); yylval.strVal = strdup(yytext); return ID; }
{comm_sl}           { save_token(yytext, &token, COMM_SL); return COMM_SL; }
{string}            { save_token(yytext, &token, STRING); yylval.strVal = strdup(yytext) ;return STRING; }
\"[^ \"]*           { print_error("wrong-string"); }
{digit}{letter}     { print_error("Unaccepted Identifier!");}

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
<COMMENT><<EOF>>    { print_error("EOF reached without closing a comment!"); }

"*/"                { print_error("Multi-line comment closing without it being opened!"); }

[ \n]               /* eat all the space and new line characters*/
<INITIAL><<EOF>>    { return 0; }

{unknown_start}[^ \n]* { print_error("Unknown definition!");}
![^=]                  { print_error("Unknown definition!");}


%%  
