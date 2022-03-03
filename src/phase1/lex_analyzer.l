/**     TODO:
    1. non-closing comments, nested comments
    2. non-closing strings
    3. special characters in strings 
 **/
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

/** Definitions **/

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
    int ml_comm_start;
    // char* redstring=(char*) malloc(100*sizeof(char));


    // int red_string(char* input){
    //     char* stringitter=redstring;
    //     printf("Appending \"%s\" to \"%s\",&input,&stringitter");
    //     while(&stringitter!='\0'){
    //         stringitter++;
    //     }
        
    //     while(&input!='\0'){
    //         stringitter=input;
    //         stringitter++;
    //         input++;
    //     }

    //     printf("Result \"%s\",redstring");

    //     free(stringitter);
    // }

    // int reset_string(){
    //     free(redstring);
    //     redstring=(char*) malloc(100*sizeof(char));
    // }

    int my_func(char *cont, struct alpha_token_t **token, char *type) {

        struct alpha_token_t *tkn = ((struct alpha_token_t *)(*token));
        // printf("yytext ---> %s\n", yytext);
        char* content = strdup(cont);                   //me to strtok pou paizei na ginei meta xalaei to cont
        if(strcmp(type, "comm-ml") == 0)                // mono an einai ml comment to theloume afto
            tkn->numLine = atoi(strtok(content, " "));  //prwto noumero tou string einai to start line
        else
            tkn->numLine = yylineno;                    //gia oles tis alles periptwseis theloume to yylineno
        tkn->content = strdup(cont);
        tkn->type    = type;
        tkn->next    = malloc(sizeof(struct alpha_token_t));

        if ( !tkn->next ) {

            perror("malloc() error");
            return EXIT_FAILURE;
        }

        tkn->next->next = NULL;
        *token = tkn->next;
        free(content);
    }


    void print_error(char* msg) {
        printf("\033[0;31mERROR: %s\n\033[0m", msg);
    }
%}

digit       [0-9]
letter      [a-zA-Z]
string      \"[^\n"]*\"
id          {letter}+({letter}|{digit}|_)*
comm_sl     "//".*

%option yylineno
%x COMMENT STR

%%


"="                 { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR EQUAL"); }
"+"                 { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR PLUS"); }
"-"                 { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR MINUS"); }
"*"                 { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR STAR"); }
"/"                 { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR SLASH"); }
"%"                 { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR MODULO"); }
"=="                { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR EQUAL_EQUAL"); }  
"!="                { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR NOT_EQUAL"); }
"++"                { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR PLUS_PLUS"); }
"--"                { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR MINUS_MINUS"); }
">"                 { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR GREATER"); }
">="                { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR GREATER_EQUAL"); }
"<"                 { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR LESS"); }
"<="                { my_func(yytext, (struct alpha_token_t **)(&token), "OPERATOR LESS_EQUAL"); }

"if"                { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD IF"); }
"else"              { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD ELSE"); }
"while"             { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD WHILE"); }
"for"               { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD FOR"); }
"function"          { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD FUNCTION"); }
"return"            { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD RETURN"); }
"break"             { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD BREAK"); }
"continue"          { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD CONTINUE"); }
"and"               { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD AND"); }
"not"               { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD NOT"); }
"or"                { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD OR"); }
"local"             { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD LOCAL"); }
"true"              { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD TRUE"); }
"false"             { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD FALSE"); }
"nil"               { my_func(yytext, (struct alpha_token_t **)(&token), "KEYWORD NIL"); }
[_]+({digit}|{letter}|_)*                { printf("problem, %s\n", yytext);}

{digit}+            { my_func(yytext, (struct alpha_token_t **)(&token), INT_CONST); }
{digit}+"."{digit}+ { my_func(yytext, (struct alpha_token_t **)(&token), REAL_CONST); }
{id}                { my_func(yytext, (struct alpha_token_t **)(&token), ID); }
{comm_sl}           { my_func(yytext, (struct alpha_token_t **)(&token), COMM_SL); }

"/*"                {   ml_comm_start = yylineno;
                        BEGIN(COMMENT);}
<COMMENT>[^*]*      
<COMMENT>"*"+[^*/]*
<COMMENT>"*"+"/"    {   char text[20];
                        sprintf(text, "%d - %d", ml_comm_start, yylineno);
                        my_func(text, (struct alpha_token_t **)(&token), COMM_ML); 
                        BEGIN(INITIAL);
                    }
<COMMENT><<EOF>>    {print_error("EOF reached without closing a comment!");return 0;}

"\""                {BEGIN(STR);printf("STNG!");}
<STR>[^\\n"]*       {}
<STR>"\""           {BEGIN(INITIAL);}
<STR>"\\"           {char special=input();}
<STR><<EOF>>        {printf("ERROR: EOF reached without closing a string!\n");return 0;}

"\\"                {printf("found a \\\n");}
[ \n]               /* eat all the space and new line characters*/
<INITIAL><<EOF>>    {return 1;}


%%

int yywrap(){}

int main(){

    int index;

    struct alpha_token_t token; 
    // struct alpha_token_t *prev;
    struct alpha_token_t *curr;


    // token.next = &token;

    if(!yylex(&token)){
        return 0;
    }

    printf("\n");

    for (index = 0, curr = &token; curr && curr->content != NULL; curr = curr->next, ++index) {

        printf("[%d] line::%u '%s' -- %s\n", index, curr->numLine, curr->content, curr->type);
        free(curr->content);
    }


    return 0;
}