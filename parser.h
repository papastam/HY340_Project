/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    OPER_EQ = 258,
    OPER_PLUS = 259,
    OPER_MINUS = 260,
    OPER_MUL = 261,
    OPER_DIV = 262,
    OPER_MOD = 263,
    OPER_EQ2 = 264,
    OPER_NEQ = 265,
    OPER_PLUS2 = 266,
    OPER_MINUS2 = 267,
    OPER_GRT = 268,
    OPER_GRE = 269,
    OPER_LET = 270,
    OPER_LEE = 271,
    PUNC_LBRACE = 272,
    PUNC_RBRACE = 273,
    PUNC_LBRACKET = 274,
    PUNC_RBRACKET = 275,
    PUNC_LPARENTH = 276,
    PUNC_RPARENTH = 277,
    PUNC_SEMIC = 278,
    PUNC_COMMA = 279,
    PUNC_COLON = 280,
    PUNC_COLON2 = 281,
    PUNC_DOT = 282,
    PUNC_DOT2 = 283,
    KEYW_IF = 284,
    KEYW_ELSE = 285,
    KEYW_WHILE = 286,
    KEYW_FOR = 287,
    KEYW_FUNC = 288,
    KEYW_RET = 289,
    KEYW_BREAK = 290,
    KEYW_CONT = 291,
    KEYW_AND = 292,
    KEYW_NOT = 293,
    KEYW_OR = 294,
    KEYW_LOCAL = 295,
    KEYW_TRUE = 296,
    KEYW_FALSE = 297,
    KEYW_NIL = 298,
    CONST_INT = 299,
    CONST_REAL = 300,
    ID = 301,
    COMM_SL = 302,
    COMM_ML = 303,
    COMM_NEST = 304,
    STRING = 305
  };
#endif
/* Tokens.  */
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
#define COMM_SL 302
#define COMM_ML 303
#define COMM_NEST 304
#define STRING 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
