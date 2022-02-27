/*** Definition Section can be
accessed inside yylex() and main() ***/

%{
#define YY_DECL int yylex(void* tokenarr)

int tokencnt=0;

typedef struct alpha_token_t {
  unsigned int     numline;
  unsigned int     numToken;
  char          *content;
  char          *type;
  struct alpha_token_t *alpha_yylex;
}alpha_token;

#define YY_USER_INIT alpha_token* tokenindex=(alpha_token*) tokenarr

%}

%option yylineno
%option outfile="lex.c"
%option prefix="alpha_yy"

/*** Regex Declarations ***/
if "if"
else "else"
while "while"
for "for"
function "function"
return "return"
break "break"
continue "continue"
and "and"
not "not"
or "or"
local "local"
true "true"
false "false"
nil "nil"

equals "="
plus "+"
minus "-"
multiply "*"
slash "/"
percent "%"
eqeq "=="
noteq "!="
increment "++"
decrement "--"
bigger ">"
bigereq ">="
less "<"
lesseq "<="

integer [0-9]*

real [0-9]*.[0-9]*

string \"[^\n"]*\"

lcurlybracket "{"
rcurlybracket "}"
lbracket "["
rbracket "]"
lparenthesis "("
rparenthesis ")"
semicolumn ";"
comma ","
colon ":"
dcolon "::"
fstop "."
dfstop ".."

id  [a-zA-Z][a-zA-Z_0-9]*


/*** Rule Section ***/
%%
{id} {tokenindex->alpha_yylex=malloc(sizeof(alpha_token));tokenindex=tokenindex->alpha_yylex;tokenindex->numline=yylineno;tokenindex->numToken=tokencnt++;printf("scanned an id");}


%%

/*** Code Section ***/
int alpha_yywrap(){}
int main(int argc,char* argv[]){

if(argc<2){printf("Please specify the input file!\n");return -1;}

FILE *fp;
fp = fopen(argv[1],"r");
yyin = fp;

alpha_token* tokenarr;
tokenarr = malloc(sizeof(alpha_token));

alpha_yylex(tokenarr);
printf("exiting\n");

do{
  printf("#%d \n",tokenarr->numline);


}while(tokenarr->alpha_yylex);


return 0;
}
