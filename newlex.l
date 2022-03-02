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

    // int replace_special_c(char *str){
        
        
        
        
    //     char* newyytext=malloc(yyleng);
    //     for(int i=0;i<yyleng;i++){
    //         if(*str=='\\'){
    //             printf("found it\n");
    //         }else{
    //             newyytext=str;
    //             newyytext++;
    //         }
    //         str++;
    //     }
    //     newyytext="\0";
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
%}

digit       [0-9]
letter      [a-zA-Z]
string      \"[^\n"]*\"
id          {letter}+({letter}|{digit}|_)*
comm_sl     "//".*

%option yylineno
%x COMMENT STR

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
<COMMENT><<EOF>>    {printf("ERROR: EOF reached without closing a comment!\n");return 0;}

"\""                {BEGIN(STR);}
<STR>[^\\n"]*       {my_func(yytext, (struct alpha_token_t **)(&token), "STRING");}
<STR>"\""           {BEGIN(INITIAL);}
<STR>"\\"           {printf("TODO:look ahead and add special char");}
<STR><<EOF>>        {printf("ERROR: EOF reached without closing a string!\n");return 0;}

"\\"                {printf("found a \\\n");}
" \n"               /* eat all the space and new line characters*/
<INITIAL><<EOF>>    {return 1;}
[^ \n]*             {printf("unknown definition, %s\n", yytext);}

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