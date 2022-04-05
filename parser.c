/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/phase2/bison_parser.y"

    #include "enum_types.h"
    #include <assert.h>

    void printReduction(char* from,char* to, int line){
        printf("[#%d] Reduction: %s ---> %s",line, from, to);
    }


#line 80 "parser.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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



#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  69
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   584

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  31
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

#define YYUNDEFTOK  2
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    81,    81,    84,    85,    86,    87,    88,    89,    90,
      91,    92,    93,    94,    97,    98,   101,   102,   103,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   121,   122,   123,   124,   125,   126,   127,   128,
     131,   133,   134,   135,   136,   137,   140,   141,   142,   143,
     146,   147,   148,   149,   152,   153,   154,   157,   158,   161,
     162,   164,   165,   168,   169,   170,   173,   174,   175,   176,
     179,   180,   181,   183,   185,   187,   188,   191,   192,   195,
     196,   197,   198,   199,   200,   203,   204,   205,   208,   209,
     210,   213,   214,   215,   216,   217,   218
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "OPER_EQ", "OPER_PLUS", "OPER_MINUS",
  "OPER_MUL", "OPER_DIV", "OPER_MOD", "OPER_EQ2", "OPER_NEQ", "OPER_PLUS2",
  "OPER_MINUS2", "OPER_GRT", "OPER_GRE", "OPER_LET", "OPER_LEE",
  "PUNC_LBRACE", "PUNC_RBRACE", "PUNC_LBRACKET", "PUNC_RBRACKET",
  "PUNC_LPARENTH", "PUNC_RPARENTH", "PUNC_SEMIC", "PUNC_COMMA",
  "PUNC_COLON", "PUNC_COLON2", "PUNC_DOT", "PUNC_DOT2", "KEYW_IF",
  "KEYW_ELSE", "KEYW_WHILE", "KEYW_FOR", "KEYW_FUNC", "KEYW_RET",
  "KEYW_BREAK", "KEYW_CONT", "KEYW_AND", "KEYW_NOT", "KEYW_OR",
  "KEYW_LOCAL", "KEYW_TRUE", "KEYW_FALSE", "KEYW_NIL", "CONST_INT",
  "CONST_REAL", "ID", "COMM_SL", "COMM_ML", "COMM_NEST", "STRING",
  "$accept", "program", "stmt", "statements", "expr", "op", "term",
  "assignexpr", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "elistrep", "objectdef", "objectin",
  "indexed", "indexrep", "indexedelem", "block", "funcdef", "const",
  "idlist", "ids", "ifstmt", "whilestmt", "forstmt", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305
};
# endif

#define YYPACT_NINF (-125)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     146,   243,    51,    51,   102,    23,  -125,   -44,    15,    19,
      22,   -16,   188,    28,    31,   243,     0,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,    55,   146,  -125,   326,  -125,  -125,
    -125,   247,  -125,    84,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,   201,   306,    27,    73,    84,    73,   243,    42,
     290,  -125,    50,  -125,    52,    11,    53,  -125,   243,   243,
     243,    32,    58,  -125,   346,  -125,  -125,   545,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,  -125,
    -125,  -125,  -125,  -125,  -125,   243,   243,  -125,  -125,   243,
     243,    37,    40,  -125,  -125,  -125,   243,   243,    41,   366,
      68,   402,  -125,   243,  -125,  -125,    57,  -125,  -125,    72,
     415,   451,    76,    80,    86,    32,  -125,   545,    43,   471,
      87,  -125,    85,   489,    88,  -125,    72,   243,   366,  -125,
     243,   146,   146,   243,    66,  -125,    96,    94,  -125,  -125,
     243,  -125,  -125,   507,  -125,    95,    90,  -125,   525,    80,
     146,  -125,    96,   100,  -125,  -125,   146,   243,  -125,  -125,
    -125,  -125,   105,   146,  -125
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
      13,     0,     0,     0,    13,     0,    12,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    83,    84,    82,
      79,    80,    46,    81,     0,    13,     2,     0,    18,    16,
      39,    41,    49,    42,    43,    10,    11,    45,     4,     5,
       6,     7,    62,    33,     0,    35,     0,    37,     0,     0,
      65,    67,     0,    68,    70,     0,     0,    48,     0,     0,
      62,    87,     0,    95,     0,     8,     9,    34,    47,     1,
      14,    19,    20,    21,    22,    23,    28,    29,    24,    25,
      26,    27,     3,    30,    31,     0,     0,    36,    38,     0,
      62,     0,     0,    55,    57,    58,     0,    62,     0,    65,
       0,     0,    75,     0,    61,    66,     0,    71,    32,    44,
       0,     0,     0,    86,     0,    87,    96,    17,    40,     0,
       0,    50,     0,     0,     0,    52,     0,     0,    64,    73,
      62,    13,    13,     0,     0,    85,    76,     0,    51,    59,
      62,    53,    54,     0,    63,     0,    91,    93,     0,    89,
      13,    78,    76,     0,    74,    56,    13,    62,    88,    77,
      60,    92,     0,    13,    94
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -125,  -125,  -124,    12,    -1,  -125,  -125,  -125,  -125,     7,
    -125,    20,  -125,  -125,  -125,   -59,   -10,  -125,  -125,  -125,
    -125,    18,  -123,     1,  -125,    26,   -19,  -125,  -125,  -125,
    -125
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    24,    25,    49,    27,    85,    28,    29,    30,    31,
      32,    33,    93,    94,    95,    51,   104,    34,    52,    53,
     107,    54,    35,    36,    37,   114,   135,    38,    39,    40,
      41
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      43,   112,    57,    50,    55,    61,    56,   146,   147,    45,
      47,    64,    26,   151,    67,    71,    72,    73,    74,    75,
      76,    77,    46,    46,    78,    79,    80,    81,     1,   159,
      62,   120,   161,   108,     2,     3,    58,    70,   124,   164,
      59,    99,    42,    60,     5,   100,    68,   101,    83,     7,
      84,    65,    -1,    -1,    66,    69,    11,   110,   111,    99,
      11,    15,   102,    16,    17,    18,    19,    20,    21,    22,
     105,   145,    44,    23,    48,   109,   106,     7,   113,   115,
      83,   153,    84,   121,   117,   118,   122,   125,   119,    99,
     126,    16,    89,   130,    90,   123,    99,    22,   162,   133,
      91,    92,   128,    96,   134,    97,   140,     1,   136,   139,
     142,    98,   149,     2,     3,   150,   152,   155,   144,    48,
     156,     4,   160,     5,   129,     6,   143,   163,     7,    99,
     158,     8,   148,     9,    10,    11,    12,    13,    14,    99,
      15,   137,    16,    17,    18,    19,    20,    21,    22,     0,
       0,     1,    23,     0,     0,     0,    99,     2,     3,     0,
       0,     0,     0,     0,     0,     4,     0,     5,     0,     6,
       0,     0,     7,     0,     0,     8,     0,     9,    10,    11,
      12,    13,    14,     0,    15,     0,    16,    17,    18,    19,
      20,    21,    22,     1,     0,     0,    23,     0,     0,     2,
       3,     0,     0,     0,     0,     0,     1,    42,     0,     5,
       0,    63,     2,     3,     7,     0,     0,     0,    48,     0,
      42,     0,     5,     0,     0,     0,    15,     7,    16,    17,
      18,    19,    20,    21,    22,     0,     0,     0,    23,    15,
       0,    16,    17,    18,    19,    20,    21,    22,     1,     0,
       0,    23,     0,     0,     2,     3,    86,     0,    87,    88,
       0,     0,    42,     0,     5,     0,    89,     0,    90,     7,
       0,     0,     0,     0,    91,    92,     0,     0,     0,     0,
       0,    15,     0,    16,    17,    18,    19,    20,    21,    22,
       0,     0,     0,    23,    71,    72,    73,    74,    75,    76,
      77,     0,     0,    78,    79,    80,    81,     0,     0,     0,
       0,    72,     0,    82,   103,    76,    77,     0,     0,    78,
      79,    80,    81,     0,     0,     0,     0,    83,     0,    84,
      71,    72,    73,    74,    75,    76,    77,     0,     0,    78,
      79,    80,    81,    83,     0,    84,     0,     0,     0,    82,
      71,    72,    73,    74,    75,    76,    77,     0,     0,    78,
      79,    80,    81,    83,     0,    84,     0,     0,     0,   116,
      71,    72,    73,    74,    75,    76,    77,     0,     0,    78,
      79,    80,    81,    83,     0,    84,     0,     0,     0,     0,
     103,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    83,     0,    84,    71,    72,    73,    74,
      75,    76,    77,     0,     0,    78,    79,    80,    81,    71,
      72,    73,    74,    75,    76,    77,     0,   127,    78,    79,
      80,    81,     0,     0,     0,     0,     0,   131,     0,    83,
       0,    84,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    83,     0,    84,    71,    72,    73,    74,    75,
      76,    77,     0,     0,    78,    79,    80,    81,     0,     0,
       0,     0,     0,   132,     0,    71,    72,    73,    74,    75,
      76,    77,     0,     0,    78,    79,    80,    81,    83,     0,
      84,   138,     0,    71,    72,    73,    74,    75,    76,    77,
       0,     0,    78,    79,    80,    81,     0,     0,    83,   141,
      84,    71,    72,    73,    74,    75,    76,    77,     0,     0,
      78,    79,    80,    81,     0,   154,    83,     0,    84,    71,
      72,    73,    74,    75,    76,    77,     0,     0,    78,    79,
      80,    81,     0,     0,    83,     0,    84,     0,   157,    71,
      72,    73,    74,    75,    76,    77,     0,     0,    78,    79,
      80,    81,    83,     0,    84,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    83,     0,    84
};

static const yytype_int16 yycheck[] =
{
       1,    60,    46,     4,     5,    21,     5,   131,   132,     2,
       3,    12,     0,   136,    15,     4,     5,     6,     7,     8,
       9,    10,     2,     3,    13,    14,    15,    16,     5,   152,
      46,    90,   156,    22,    11,    12,    21,    25,    97,   163,
      21,    42,    19,    21,    21,    44,    46,    48,    37,    26,
      39,    23,     9,    10,    23,     0,    33,    58,    59,    60,
      33,    38,    20,    40,    41,    42,    43,    44,    45,    46,
      20,   130,    21,    50,    17,    22,    24,    26,    46,    21,
      37,   140,    39,    46,    85,    86,    46,    46,    89,    90,
      22,    40,    19,    21,    21,    96,    97,    46,   157,    23,
      27,    28,   103,    19,    24,    21,    21,     5,    22,    22,
      22,    27,    46,    11,    12,    19,    22,    22,   128,    17,
      30,    19,    22,    21,   106,    23,   127,    22,    26,   130,
     149,    29,   133,    31,    32,    33,    34,    35,    36,   140,
      38,   115,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,     5,    50,    -1,    -1,    -1,   157,    11,    12,    -1,
      -1,    -1,    -1,    -1,    -1,    19,    -1,    21,    -1,    23,
      -1,    -1,    26,    -1,    -1,    29,    -1,    31,    32,    33,
      34,    35,    36,    -1,    38,    -1,    40,    41,    42,    43,
      44,    45,    46,     5,    -1,    -1,    50,    -1,    -1,    11,
      12,    -1,    -1,    -1,    -1,    -1,     5,    19,    -1,    21,
      -1,    23,    11,    12,    26,    -1,    -1,    -1,    17,    -1,
      19,    -1,    21,    -1,    -1,    -1,    38,    26,    40,    41,
      42,    43,    44,    45,    46,    -1,    -1,    -1,    50,    38,
      -1,    40,    41,    42,    43,    44,    45,    46,     5,    -1,
      -1,    50,    -1,    -1,    11,    12,     9,    -1,    11,    12,
      -1,    -1,    19,    -1,    21,    -1,    19,    -1,    21,    26,
      -1,    -1,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,
      -1,    38,    -1,    40,    41,    42,    43,    44,    45,    46,
      -1,    -1,    -1,    50,     4,     5,     6,     7,     8,     9,
      10,    -1,    -1,    13,    14,    15,    16,    -1,    -1,    -1,
      -1,     5,    -1,    23,    24,     9,    10,    -1,    -1,    13,
      14,    15,    16,    -1,    -1,    -1,    -1,    37,    -1,    39,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    13,
      14,    15,    16,    37,    -1,    39,    -1,    -1,    -1,    23,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    13,
      14,    15,    16,    37,    -1,    39,    -1,    -1,    -1,    23,
       4,     5,     6,     7,     8,     9,    10,    -1,    -1,    13,
      14,    15,    16,    37,    -1,    39,    -1,    -1,    -1,    -1,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    37,    -1,    39,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    14,    15,    16,     4,
       5,     6,     7,     8,     9,    10,    -1,    25,    13,    14,
      15,    16,    -1,    -1,    -1,    -1,    -1,    22,    -1,    37,
      -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    39,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    14,    15,    16,    -1,    -1,
      -1,    -1,    -1,    22,    -1,     4,     5,     6,     7,     8,
       9,    10,    -1,    -1,    13,    14,    15,    16,    37,    -1,
      39,    20,    -1,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,    15,    16,    -1,    -1,    37,    20,
      39,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    14,    15,    16,    -1,    18,    37,    -1,    39,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    14,
      15,    16,    -1,    -1,    37,    -1,    39,    -1,    23,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    14,
      15,    16,    37,    -1,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    37,    -1,    39
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    11,    12,    19,    21,    23,    26,    29,    31,
      32,    33,    34,    35,    36,    38,    40,    41,    42,    43,
      44,    45,    46,    50,    52,    53,    54,    55,    57,    58,
      59,    60,    61,    62,    68,    73,    74,    75,    78,    79,
      80,    81,    19,    55,    21,    60,    62,    60,    17,    54,
      55,    66,    69,    70,    72,    55,    74,    46,    21,    21,
      21,    21,    46,    23,    55,    23,    23,    55,    46,     0,
      54,     4,     5,     6,     7,     8,     9,    10,    13,    14,
      15,    16,    23,    37,    39,    56,     9,    11,    12,    19,
      21,    27,    28,    63,    64,    65,    19,    21,    27,    55,
      74,    55,    20,    24,    67,    20,    24,    71,    22,    22,
      55,    55,    66,    46,    76,    21,    23,    55,    55,    55,
      66,    46,    46,    55,    66,    46,    22,    25,    55,    72,
      21,    22,    22,    23,    24,    77,    22,    76,    20,    22,
      21,    20,    22,    55,    67,    66,    53,    53,    55,    46,
      19,    73,    22,    66,    18,    22,    30,    23,    77,    73,
      22,    53,    66,    22,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    54,    54,    55,    55,    55,    56,
      56,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    57,    57,    57,    57,    57,    57,    57,    57,
      58,    59,    59,    59,    59,    59,    60,    60,    60,    60,
      61,    61,    61,    61,    62,    62,    62,    63,    63,    64,
      65,    66,    66,    67,    67,    67,    68,    69,    69,    69,
      70,    70,    70,    71,    72,    73,    73,    74,    74,    75,
      75,    75,    75,    75,    75,    76,    76,    76,    77,    77,
      77,    78,    78,    79,    80,    81,    81
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     1,     1,     1,     2,     2,
       1,     1,     1,     0,     2,     0,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     2,     2,     2,     2,     2,     2,     1,
       3,     1,     1,     1,     3,     1,     1,     2,     2,     1,
       3,     4,     3,     4,     4,     2,     6,     1,     1,     3,
       5,     2,     0,     3,     2,     0,     3,     1,     1,     0,
       1,     2,     0,     2,     5,     3,     0,     6,     5,     1,
       1,     1,     1,     1,     1,     2,     1,     0,     3,     2,
       0,     5,     7,     5,     9,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 81 "src/phase2/bison_parser.y"
                                        {printReduction("program","statements", yylineno);}
#line 1609 "parser.c"
    break;

  case 3:
#line 84 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","expr PUNC_SEMIC", yylineno);}
#line 1615 "parser.c"
    break;

  case 4:
#line 85 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","ifstmt", yylineno);}
#line 1621 "parser.c"
    break;

  case 5:
#line 86 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","whilestmt", yylineno);}
#line 1627 "parser.c"
    break;

  case 6:
#line 87 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","forstmt", yylineno);}
#line 1633 "parser.c"
    break;

  case 7:
#line 88 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","returnstmt", yylineno);}
#line 1639 "parser.c"
    break;

  case 8:
#line 89 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","KEYW_BREAK PUNC_SEMIC", yylineno);}
#line 1645 "parser.c"
    break;

  case 9:
#line 90 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","KEYW_CONT PUNC_SEMIC", yylineno);}
#line 1651 "parser.c"
    break;

  case 10:
#line 91 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","block", yylineno);}
#line 1657 "parser.c"
    break;

  case 11:
#line 92 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","funcdef", yylineno);}
#line 1663 "parser.c"
    break;

  case 12:
#line 93 "src/phase2/bison_parser.y"
                                        {printReduction("stmt"," PUNC_SEMIC", yylineno);}
#line 1669 "parser.c"
    break;

  case 13:
#line 94 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","empty", yylineno);}
#line 1675 "parser.c"
    break;

  case 14:
#line 97 "src/phase2/bison_parser.y"
                                        {printReduction("statements","stmt statements", yylineno);}
#line 1681 "parser.c"
    break;

  case 15:
#line 98 "src/phase2/bison_parser.y"
                                        {printReduction("statements","empty", yylineno);}
#line 1687 "parser.c"
    break;

  case 16:
#line 101 "src/phase2/bison_parser.y"
                                        {printReduction("expr","assignexpr", yylineno);}
#line 1693 "parser.c"
    break;

  case 17:
#line 102 "src/phase2/bison_parser.y"
                                        {printReduction("expr","expr op expr", yylineno);}
#line 1699 "parser.c"
    break;

  case 18:
#line 103 "src/phase2/bison_parser.y"
                                        {printReduction("expr","term", yylineno);}
#line 1705 "parser.c"
    break;

  case 19:
#line 106 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_PLUS", yylineno);}
#line 1711 "parser.c"
    break;

  case 20:
#line 107 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_MINUS", yylineno);}
#line 1717 "parser.c"
    break;

  case 21:
#line 108 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_MUL", yylineno);}
#line 1723 "parser.c"
    break;

  case 22:
#line 109 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_DIV", yylineno);}
#line 1729 "parser.c"
    break;

  case 23:
#line 110 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_MOD", yylineno);}
#line 1735 "parser.c"
    break;

  case 24:
#line 111 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_GRT", yylineno);}
#line 1741 "parser.c"
    break;

  case 25:
#line 112 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_GRE", yylineno);}
#line 1747 "parser.c"
    break;

  case 26:
#line 113 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_LET", yylineno);}
#line 1753 "parser.c"
    break;

  case 27:
#line 114 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_LEE", yylineno);}
#line 1759 "parser.c"
    break;

  case 28:
#line 115 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_EQ2", yylineno);}
#line 1765 "parser.c"
    break;

  case 29:
#line 116 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_NEQ", yylineno);}
#line 1771 "parser.c"
    break;

  case 30:
#line 117 "src/phase2/bison_parser.y"
                                        {printReduction("op","KEYW_AND", yylineno);}
#line 1777 "parser.c"
    break;

  case 31:
#line 118 "src/phase2/bison_parser.y"
                                        {printReduction("op","KEYW_OR", yylineno);}
#line 1783 "parser.c"
    break;

  case 32:
#line 121 "src/phase2/bison_parser.y"
                                                    {printReduction("term","PUNC_LPARENTH expr PUNC_RPARENTH", yylineno);}
#line 1789 "parser.c"
    break;

  case 33:
#line 122 "src/phase2/bison_parser.y"
                                                    {printReduction("term","OPER_MINUS expr", yylineno);}
#line 1795 "parser.c"
    break;

  case 34:
#line 123 "src/phase2/bison_parser.y"
                                                    {printReduction("term","KEYW_NOT expr", yylineno);}
#line 1801 "parser.c"
    break;

  case 35:
#line 124 "src/phase2/bison_parser.y"
                                                    {printReduction("term","OPER_PLUS2 lvalue", yylineno);}
#line 1807 "parser.c"
    break;

  case 36:
#line 125 "src/phase2/bison_parser.y"
                                                    {printReduction("term","lvalue OPER_PLUS2", yylineno);}
#line 1813 "parser.c"
    break;

  case 37:
#line 126 "src/phase2/bison_parser.y"
                                                    {printReduction("term","OPER_MINUS2 lvalue", yylineno);}
#line 1819 "parser.c"
    break;

  case 38:
#line 127 "src/phase2/bison_parser.y"
                                                    {printReduction("term","lvalue OPER_MINUS2", yylineno);}
#line 1825 "parser.c"
    break;

  case 39:
#line 128 "src/phase2/bison_parser.y"
                                                    {printReduction("term","primary", yylineno);}
#line 1831 "parser.c"
    break;

  case 40:
#line 131 "src/phase2/bison_parser.y"
                                                    {printReduction("assignexpr","lvalue OPER_EQ2 expr", yylineno);}
#line 1837 "parser.c"
    break;

  case 41:
#line 133 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","lvalue", yylineno);}
#line 1843 "parser.c"
    break;

  case 42:
#line 134 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","call", yylineno);}
#line 1849 "parser.c"
    break;

  case 43:
#line 135 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","objectdef", yylineno);}
#line 1855 "parser.c"
    break;

  case 44:
#line 136 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","PUNC_LPARENTH funcdef PUNC_RPARENTH", yylineno);}
#line 1861 "parser.c"
    break;

  case 45:
#line 137 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","const", yylineno);}
#line 1867 "parser.c"
    break;

  case 46:
#line 140 "src/phase2/bison_parser.y"
                                                    {printReduction("lvalue","ID", yylineno);}
#line 1873 "parser.c"
    break;

  case 47:
#line 141 "src/phase2/bison_parser.y"
                                                    {printReduction("lvalue","KEYW_LOCAL ID", yylineno);}
#line 1879 "parser.c"
    break;

  case 48:
#line 142 "src/phase2/bison_parser.y"
                                                    {printReduction("lvalue","PUNC_COLON2 ID", yylineno);}
#line 1885 "parser.c"
    break;

  case 49:
#line 143 "src/phase2/bison_parser.y"
                                                    {printReduction("lvalue","member", yylineno);}
#line 1891 "parser.c"
    break;

  case 50:
#line 146 "src/phase2/bison_parser.y"
                                                        {printReduction("member","lvalue PUNC_DOT ID", yylineno);}
#line 1897 "parser.c"
    break;

  case 51:
#line 147 "src/phase2/bison_parser.y"
                                                        {printReduction("member","lvalue PUNC_LBRACKET expr PUNC_RBRACKET", yylineno);}
#line 1903 "parser.c"
    break;

  case 52:
#line 148 "src/phase2/bison_parser.y"
                                                        {printReduction("member","call PUNC_DOT ID", yylineno);}
#line 1909 "parser.c"
    break;

  case 53:
#line 149 "src/phase2/bison_parser.y"
                                                        {printReduction("member","call PUNC_LBRACKET expr PUNC_RBRACKET", yylineno);}
#line 1915 "parser.c"
    break;

  case 54:
#line 152 "src/phase2/bison_parser.y"
                                                                                        {printReduction("call","call PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);}
#line 1921 "parser.c"
    break;

  case 55:
#line 153 "src/phase2/bison_parser.y"
                                                                                        {printReduction("call","lvalue callsuffix ID", yylineno);}
#line 1927 "parser.c"
    break;

  case 56:
#line 154 "src/phase2/bison_parser.y"
                                                                                        {printReduction("call","PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);}
#line 1933 "parser.c"
    break;

  case 57:
#line 157 "src/phase2/bison_parser.y"
                                                                    {printReduction("callsuffix","normcall", yylineno);}
#line 1939 "parser.c"
    break;

  case 58:
#line 158 "src/phase2/bison_parser.y"
                                                                    {printReduction("callsuffix","methodcall", yylineno);}
#line 1945 "parser.c"
    break;

  case 59:
#line 161 "src/phase2/bison_parser.y"
                                                                    {printReduction("normcall","PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);}
#line 1951 "parser.c"
    break;

  case 60:
#line 162 "src/phase2/bison_parser.y"
                                                                    {printReduction("methodcall","PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);}
#line 1957 "parser.c"
    break;

  case 61:
#line 164 "src/phase2/bison_parser.y"
                                                                    {printReduction("elist","expr elistrep", yylineno);}
#line 1963 "parser.c"
    break;

  case 62:
#line 165 "src/phase2/bison_parser.y"
                                                                    {printReduction("elist","empty", yylineno);}
#line 1969 "parser.c"
    break;

  case 63:
#line 168 "src/phase2/bison_parser.y"
                                                                    {printReduction("elistrep","PUNC_COMMA expr elistrep", yylineno);}
#line 1975 "parser.c"
    break;

  case 64:
#line 169 "src/phase2/bison_parser.y"
                                                                    {printReduction("elistrep","PUNC_COMMA expr", yylineno);}
#line 1981 "parser.c"
    break;

  case 65:
#line 170 "src/phase2/bison_parser.y"
                                                                    {printReduction("elistrep","empty", yylineno);}
#line 1987 "parser.c"
    break;

  case 66:
#line 173 "src/phase2/bison_parser.y"
                                                                    {printReduction("objectdef","PUNC_LBRACKET objectin PUNC_RBRACKET", yylineno);}
#line 1993 "parser.c"
    break;

  case 67:
#line 174 "src/phase2/bison_parser.y"
                                                                    {printReduction("objectin","elist", yylineno);}
#line 1999 "parser.c"
    break;

  case 68:
#line 175 "src/phase2/bison_parser.y"
                                                                    {printReduction("objectin","indexed", yylineno);}
#line 2005 "parser.c"
    break;

  case 69:
#line 176 "src/phase2/bison_parser.y"
                                                                    {printReduction("objectin","empty", yylineno);}
#line 2011 "parser.c"
    break;

  case 70:
#line 179 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexed","indexedelem", yylineno);}
#line 2017 "parser.c"
    break;

  case 71:
#line 180 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexed","indexedelem indexrep", yylineno);}
#line 2023 "parser.c"
    break;

  case 72:
#line 181 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexed","empty", yylineno);}
#line 2029 "parser.c"
    break;

  case 73:
#line 183 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexrep","PUNC_COMMA indexedelem", yylineno);}
#line 2035 "parser.c"
    break;

  case 74:
#line 185 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexedelem","PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE", yylineno);}
#line 2041 "parser.c"
    break;

  case 75:
#line 187 "src/phase2/bison_parser.y"
                                                                    {printReduction("block","PUNC_LBRACKET statements PUNC_RBRACKET", yylineno);}
#line 2047 "parser.c"
    break;

  case 76:
#line 188 "src/phase2/bison_parser.y"
                                                                    {printReduction("block","empty", yylineno);}
#line 2053 "parser.c"
    break;

  case 77:
#line 191 "src/phase2/bison_parser.y"
                                                                    {printReduction("funcdef","KEYW_FUNC ID PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
#line 2059 "parser.c"
    break;

  case 78:
#line 192 "src/phase2/bison_parser.y"
                                                                    {printReduction("funcdef","KEYW_FUNC PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
#line 2065 "parser.c"
    break;

  case 79:
#line 195 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","CONST_INT", yylineno);}
#line 2071 "parser.c"
    break;

  case 80:
#line 196 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","CONST_REAL", yylineno);}
#line 2077 "parser.c"
    break;

  case 81:
#line 197 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","STRING", yylineno);}
#line 2083 "parser.c"
    break;

  case 82:
#line 198 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","KEYW_NIL", yylineno);}
#line 2089 "parser.c"
    break;

  case 83:
#line 199 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","KEYW_TRUE", yylineno);}
#line 2095 "parser.c"
    break;

  case 84:
#line 200 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","KEYW_FALSE", yylineno);}
#line 2101 "parser.c"
    break;

  case 85:
#line 203 "src/phase2/bison_parser.y"
                                                                    {printReduction("idlist","ID ids", yylineno);}
#line 2107 "parser.c"
    break;

  case 86:
#line 204 "src/phase2/bison_parser.y"
                                                                    {printReduction("idlist","ID", yylineno);}
#line 2113 "parser.c"
    break;

  case 87:
#line 205 "src/phase2/bison_parser.y"
                                                                    {printReduction("idlist","empty", yylineno);}
#line 2119 "parser.c"
    break;

  case 88:
#line 208 "src/phase2/bison_parser.y"
                                                                    {printReduction("ids","PUNC_COMMA ID ids", yylineno);}
#line 2125 "parser.c"
    break;

  case 89:
#line 209 "src/phase2/bison_parser.y"
                                                                    {printReduction("ids","PUNC_COMMA ID", yylineno);}
#line 2131 "parser.c"
    break;

  case 90:
#line 210 "src/phase2/bison_parser.y"
                                                                    {printReduction("ids","empty", yylineno);}
#line 2137 "parser.c"
    break;

  case 91:
#line 213 "src/phase2/bison_parser.y"
                                                                    {printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);}
#line 2143 "parser.c"
    break;

  case 92:
#line 214 "src/phase2/bison_parser.y"
                                                                                    {printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt KEYW_ELSE stmt", yylineno);}
#line 2149 "parser.c"
    break;

  case 93:
#line 215 "src/phase2/bison_parser.y"
                                                                        {printReduction("whilestmt","KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);}
#line 2155 "parser.c"
    break;

  case 94:
#line 216 "src/phase2/bison_parser.y"
                                                                                                        {printReduction("forstmt","KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt", yylineno);}
#line 2161 "parser.c"
    break;

  case 95:
#line 217 "src/phase2/bison_parser.y"
                                        {printReduction("returnstmt","KEYW_RET PUNC_SEMIC", yylineno);}
#line 2167 "parser.c"
    break;

  case 96:
#line 218 "src/phase2/bison_parser.y"
                                                {printReduction("returnstmt","KEYW_RET expr PUNC_SEMIC", yylineno);}
#line 2173 "parser.c"
    break;


#line 2177 "parser.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 221 "src/phase2/bison_parser.y"


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
    
    if( !alpha_yylex(&token) )
        return 1;

    printf("\n");

    for (index = 0, curr = &token; (curr && curr->content); curr = curr->next, ++index) {

        printf("[%d] line::%u '%s' -- %s\n", index, curr->line, curr->content, _printable_lex_token(curr->type));
        free(curr->content);

        /** TODO: free(everything) */
    }


    return 0;
}
