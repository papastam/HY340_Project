/**  csd4273, csd4275, csd4569 **/


/** Definitions **/

%{
    #include <assert.h>
    #include "parser.h"

    #define ERR_STRING "\e[0;31mERROR\e[37m:\e[0m"

%}

byte [0|1]{4}


/* digit       [0-9]
letter      [a-zA-Z]
string      \"(\\.|[^"\\])*\"
id          {letter}+({letter}|{digit}|_)*
comm_sl     "//".*
unknown_start [@#$^&_]  */

%option outfile = "tcode_lex.c"
%option yylineno
%option noyywrap

%%

