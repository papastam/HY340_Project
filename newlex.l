/**
 * @file lex.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-02-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/** Defintions **/

%{
    #define YY_DECL int yylex(void* token)

    #define KEYWORD     "keyword"
    #define OPERATOR    "operator"
    #define INT_CONST   "int-const"
    #define REAL_CONST  "real-const"
    #define STRING      "string"
    #define ID          "id"
    #define PUNM        "punm"
    #define COMM_ML     "comm-ml"
    #define COMM_SL     "comm-sl"


    struct alpha_token_t {

        unsigned int numLine;

        char *content;
        char *type;

        struct alpha_token_t *next;
    };

    int count = 0;

    int my_func(char *cont, struct alpha_token_t **token, char *type) {

        struct alpha_token_t *tkn = ((struct alpha_token_t *)(*token));
        // printf("yytext ---> %s\n", yytext);

        tkn->numLine = yylineno;
        tkn->content = strdup(cont);
        tkn->type    = type;
        tkn->next    = malloc(sizeof(struct alpha_token_t));

        if ( !tkn->next ) {

            perror("malloc() error");
            return EXIT_FAILURE;
        }

        tkn->next->next = NULL;
        *token = tkn->next;
    }
%}

digit       [0-9]
letter      [a-zA-Z]
string      \"[^\n"]*\"
id          {letter}+({letter}|{digit}|_)*
comm_sl     "//".*

%option yylineno
%x COMMENT

%%


"="                 { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"+"                 { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"-"                 { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"*"                 { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"/"                 { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"%"                 { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"=="                { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }  
"!="                { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"++"                { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"--"                { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
">"                 { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
">="                { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"<"                 { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }
"<="                { my_func(yytext, (struct alpha_token_t **)(&token), OPERATOR); }

"if"                { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"else"              { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"while"             { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"for"               { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"function"          { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"return"            { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"break"             { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"continue"          { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"and"               { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"not"               { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"or"                { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"local"             { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"true"              { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"false"             { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }
"nil"               { my_func(yytext, (struct alpha_token_t **)(&token), KEYWORD); }

{digit}+            { my_func(yytext, (struct alpha_token_t **)(&token), INT_CONST); }
{digit}+.{digit}+   { my_func(yytext, (struct alpha_token_t **)(&token), REAL_CONST); }
{string}            { my_func(yytext, (struct alpha_token_t **)(&token), STRING); }
{id}                { my_func(yytext, (struct alpha_token_t **)(&token), ID); }
{comm_sl}           { my_func(yytext, (struct alpha_token_t **)(&token), COMM_SL); }


"/*"                BEGIN(COMMENT);
<COMMENT>[^*]*
<COMMENT>"*"+[^*/]*
<COMMENT>"*"+"/"

"\n"        {}

%%


int yywrap(){}
int main(){

    int index;

    struct alpha_token_t token; 
    // struct alpha_token_t *prev;
    struct alpha_token_t *curr;


    // token.next = &token;

    yylex(&token);
    printf("\n");

    for (index = 0, curr = &token; curr; curr = curr->next, ++index) {

        printf("[%d] '%s'::%u -- %s\n", index, curr->content, curr->numLine, curr->type);
        free(curr->content);
    }


    return 0;
}