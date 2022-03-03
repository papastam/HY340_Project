/**  csd4273, csd4275, csd4569 **/


/** Definitions **/

%{
    #define YY_DECL int yylex(void* token)

    struct alpha_token_t {

        unsigned int numLine;

        char *content;
        char *type;

        struct alpha_token_t *next;
    };

    int count = 0;
    int comment_count = 0;
    int ml_comm_start;


    int my_func(char *cont, struct alpha_token_t **token, char *type) {

        struct alpha_token_t *tkn = ((struct alpha_token_t *)(*token));
        char* content = strdup(cont);                   //me to strtok pou paizei na ginei meta xalaei to cont


        if( !strcmp(type, "COMM_ML") )                   // mono an einai ml comment to theloume afto
            tkn->numLine = atoi(strtok(content, " "));   //prwto noumero tou string einai to start line
        else
            tkn->numLine = yylineno;                     //gia oles tis alles periptwseis theloume to yylineno

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
unknown_start [!@#$%^&*_]

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
"{"                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION LEFT_BRACE"); }
"}"                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION RIGHT_BRACE"); }
"["                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION LEFT_BRACKET"); }
"]"                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION RIGHT_BRACE"); }
"("                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION LEFT_PARENTHESIS"); }
")"                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION RIGHT_PARENTHESIS"); }
";"                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION SEMICOLON"); }
","                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION COMMA"); }
":"                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION COLON"); }
"::"                { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION DOUBLE_COLON"); }
"."                 { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION DOT"); }
".."                { my_func(yytext, (struct alpha_token_t **)(&token), "PUNCTUATION DOUBLE_DOT"); }

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

{digit}+            { my_func(yytext, (struct alpha_token_t **)(&token), "INT_CONST"); }
{digit}+"."{digit}+ { my_func(yytext, (struct alpha_token_t **)(&token), "REAL_CONST"); }
{id}                { my_func(yytext, (struct alpha_token_t **)(&token), "ID"); }
{comm_sl}           { my_func(yytext, (struct alpha_token_t **)(&token), "COMM_SL"); }

"/*"                {   
                        ml_comm_start = yylineno;
                        comment_count++;
                        BEGIN(COMMENT);}
<COMMENT>"/*"       {   comment_count++;}
<COMMENT>[^*/]*      
<COMMENT>"*"+[^*/]*
<COMMENT>"*"+"/"    {  
                        char text[20];
                        comment_count--;

                        if( comment_count > 0 )
                            my_func("nested comment", (struct alpha_token_t **)(&token), "NESTED COMMENT");
                        else if( comment_count == 0 ) {

                            sprintf(text, "%d - %d", ml_comm_start, yylineno);
                            my_func(text, (struct alpha_token_t **)(&token), "COMM_ML"); 
                            
                            BEGIN(INITIAL);
                        }
    
                    }
<COMMENT><<EOF>>    {
                        print_error("EOF reached without closing a comment!");
                        return 0;
                    }

"*/"                { print_error("Multi-line comment closing without it being opened!");return 0; }

"\""                { BEGIN(STR); }
<STR>[^\n"]*        { my_func(yytext, (struct alpha_token_t **)(&token), "STRING"); }
<STR>"\""           { BEGIN(INITIAL); }
<STR>"\\"           { printf("TODO:look ahead and add special char"); }
<STR><<EOF>>        {
                        print_error("EOF reached without closing a string!");
                        return 0;
                    }

[ \n]               /* eat all the space and new line characters*/
<INITIAL><<EOF>>    {return 1;}

{unknown_start}[^ \n]* {print_error("Unknown definition!");printf("%s\n",yytext);}


%%  

int yywrap(){}

int main(int argc, char **argv){

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

        printf("[%d] line::%u '%s' -- %s\n", index, curr->numLine, curr->content, curr->type);
        free(curr->content);

        /** TODO: free(everything) */
    }


    return 0;
}