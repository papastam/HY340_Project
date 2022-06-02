/* A Bison parser, made by GNU Bison 3.8.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_SRC_PARSER_ACOMP_H_INCLUDED
# define YY_YY_SRC_PARSER_ACOMP_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    OPER_EQ = 258,                 /* OPER_EQ  */
    OPER_PLUS = 259,               /* OPER_PLUS  */
    OPER_MINUS = 260,              /* OPER_MINUS  */
    OPER_MUL = 261,                /* OPER_MUL  */
    OPER_DIV = 262,                /* OPER_DIV  */
    OPER_MOD = 263,                /* OPER_MOD  */
    OPER_EQ2 = 264,                /* OPER_EQ2  */
    OPER_NEQ = 265,                /* OPER_NEQ  */
    OPER_PLUS2 = 266,              /* OPER_PLUS2  */
    OPER_MINUS2 = 267,             /* OPER_MINUS2  */
    OPER_GRT = 268,                /* OPER_GRT  */
    OPER_GRE = 269,                /* OPER_GRE  */
    OPER_LET = 270,                /* OPER_LET  */
    OPER_LEE = 271,                /* OPER_LEE  */
    PUNC_LBRACE = 272,             /* PUNC_LBRACE  */
    PUNC_RBRACE = 273,             /* PUNC_RBRACE  */
    PUNC_LBRACKET = 274,           /* PUNC_LBRACKET  */
    PUNC_RBRACKET = 275,           /* PUNC_RBRACKET  */
    PUNC_LPARENTH = 276,           /* PUNC_LPARENTH  */
    PUNC_RPARENTH = 277,           /* PUNC_RPARENTH  */
    PUNC_SEMIC = 278,              /* PUNC_SEMIC  */
    PUNC_COMMA = 279,              /* PUNC_COMMA  */
    PUNC_COLON = 280,              /* PUNC_COLON  */
    PUNC_COLON2 = 281,             /* PUNC_COLON2  */
    PUNC_DOT = 282,                /* PUNC_DOT  */
    PUNC_DOT2 = 283,               /* PUNC_DOT2  */
    KEYW_IF = 284,                 /* KEYW_IF  */
    KEYW_ELSE = 285,               /* KEYW_ELSE  */
    KEYW_WHILE = 286,              /* KEYW_WHILE  */
    KEYW_FOR = 287,                /* KEYW_FOR  */
    KEYW_FUNC = 288,               /* KEYW_FUNC  */
    KEYW_RET = 289,                /* KEYW_RET  */
    KEYW_BREAK = 290,              /* KEYW_BREAK  */
    KEYW_CONT = 291,               /* KEYW_CONT  */
    KEYW_AND = 292,                /* KEYW_AND  */
    KEYW_NOT = 293,                /* KEYW_NOT  */
    KEYW_OR = 294,                 /* KEYW_OR  */
    KEYW_LOCAL = 295,              /* KEYW_LOCAL  */
    KEYW_TRUE = 296,               /* KEYW_TRUE  */
    KEYW_FALSE = 297,              /* KEYW_FALSE  */
    KEYW_NIL = 298,                /* KEYW_NIL  */
    CONST_INT = 299,               /* CONST_INT  */
    CONST_REAL = 300,              /* CONST_REAL  */
    ID = 301,                      /* ID  */
    STRING = 302,                  /* STRING  */
    UNARY_MINUS = 303              /* UNARY_MINUS  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define OPER_EQ 258
#define OPER_PLUS 259
#define OPER_MINUS 260
#define OPER_MUL 261
#define OPER_DIV 262
#define OPER_MOD 263
#define OPER_EQ2 264
#define OPER_NEQ 265
#define OPER_PLUS2 266
#define OPER_MINUS2 267
#define OPER_GRT 268
#define OPER_GRE 269
#define OPER_LET 270
#define OPER_LEE 271
#define PUNC_LBRACE 272
#define PUNC_RBRACE 273
#define PUNC_LBRACKET 274
#define PUNC_RBRACKET 275
#define PUNC_LPARENTH 276
#define PUNC_RPARENTH 277
#define PUNC_SEMIC 278
#define PUNC_COMMA 279
#define PUNC_COLON 280
#define PUNC_COLON2 281
#define PUNC_DOT 282
#define PUNC_DOT2 283
#define KEYW_IF 284
#define KEYW_ELSE 285
#define KEYW_WHILE 286
#define KEYW_FOR 287
#define KEYW_FUNC 288
#define KEYW_RET 289
#define KEYW_BREAK 290
#define KEYW_CONT 291
#define KEYW_AND 292
#define KEYW_NOT 293
#define KEYW_OR 294
#define KEYW_LOCAL 295
#define KEYW_TRUE 296
#define KEYW_FALSE 297
#define KEYW_NIL 298
#define CONST_INT 299
#define CONST_REAL 300
#define ID 301
#define STRING 302
#define UNARY_MINUS 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 55 "src/parser/bison_parser.y"


    int intVal; 
    double realVal;
    char* strVal; 
    unsigned char boolVal;
    struct SymbolTableEntry *symbol;
    struct expr *expression;
    struct function_contents *functcont;
    struct for_contents *forcont;
    struct stmt_t *stmtcont; 

#line 176 "src/parser/acomp.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

#if !defined yyerror && !defined YYERROR_IS_DECLARED
void yyerror (const char *msg);
#endif
#if !defined yylex && !defined YYLEX_IS_DECLARED
int yylex (void);
#endif

int yyparse (void);


#endif /* !YY_YY_SRC_PARSER_ACOMP_H_INCLUDED  */
