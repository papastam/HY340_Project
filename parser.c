/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

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

    #include "inc/enum_types.h"
    #include <assert.h>
    #include <stdio.h>

    void printReduction(char* from,char* to, int line){
        printf("[#%d] Reduction: %s ---> %s",line, from, to);
    }


#line 82 "parser.c"

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

#include "parser.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_OPER_EQ = 3,                    /* OPER_EQ  */
  YYSYMBOL_OPER_PLUS = 4,                  /* OPER_PLUS  */
  YYSYMBOL_OPER_MINUS = 5,                 /* OPER_MINUS  */
  YYSYMBOL_OPER_MUL = 6,                   /* OPER_MUL  */
  YYSYMBOL_OPER_DIV = 7,                   /* OPER_DIV  */
  YYSYMBOL_OPER_MOD = 8,                   /* OPER_MOD  */
  YYSYMBOL_OPER_EQ2 = 9,                   /* OPER_EQ2  */
  YYSYMBOL_OPER_NEQ = 10,                  /* OPER_NEQ  */
  YYSYMBOL_OPER_PLUS2 = 11,                /* OPER_PLUS2  */
  YYSYMBOL_OPER_MINUS2 = 12,               /* OPER_MINUS2  */
  YYSYMBOL_OPER_GRT = 13,                  /* OPER_GRT  */
  YYSYMBOL_OPER_GRE = 14,                  /* OPER_GRE  */
  YYSYMBOL_OPER_LET = 15,                  /* OPER_LET  */
  YYSYMBOL_OPER_LEE = 16,                  /* OPER_LEE  */
  YYSYMBOL_PUNC_LBRACE = 17,               /* PUNC_LBRACE  */
  YYSYMBOL_PUNC_RBRACE = 18,               /* PUNC_RBRACE  */
  YYSYMBOL_PUNC_LBRACKET = 19,             /* PUNC_LBRACKET  */
  YYSYMBOL_PUNC_RBRACKET = 20,             /* PUNC_RBRACKET  */
  YYSYMBOL_PUNC_LPARENTH = 21,             /* PUNC_LPARENTH  */
  YYSYMBOL_PUNC_RPARENTH = 22,             /* PUNC_RPARENTH  */
  YYSYMBOL_PUNC_SEMIC = 23,                /* PUNC_SEMIC  */
  YYSYMBOL_PUNC_COMMA = 24,                /* PUNC_COMMA  */
  YYSYMBOL_PUNC_COLON = 25,                /* PUNC_COLON  */
  YYSYMBOL_PUNC_COLON2 = 26,               /* PUNC_COLON2  */
  YYSYMBOL_PUNC_DOT = 27,                  /* PUNC_DOT  */
  YYSYMBOL_PUNC_DOT2 = 28,                 /* PUNC_DOT2  */
  YYSYMBOL_KEYW_IF = 29,                   /* KEYW_IF  */
  YYSYMBOL_KEYW_ELSE = 30,                 /* KEYW_ELSE  */
  YYSYMBOL_KEYW_WHILE = 31,                /* KEYW_WHILE  */
  YYSYMBOL_KEYW_FOR = 32,                  /* KEYW_FOR  */
  YYSYMBOL_KEYW_FUNC = 33,                 /* KEYW_FUNC  */
  YYSYMBOL_KEYW_RET = 34,                  /* KEYW_RET  */
  YYSYMBOL_KEYW_BREAK = 35,                /* KEYW_BREAK  */
  YYSYMBOL_KEYW_CONT = 36,                 /* KEYW_CONT  */
  YYSYMBOL_KEYW_AND = 37,                  /* KEYW_AND  */
  YYSYMBOL_KEYW_NOT = 38,                  /* KEYW_NOT  */
  YYSYMBOL_KEYW_OR = 39,                   /* KEYW_OR  */
  YYSYMBOL_KEYW_LOCAL = 40,                /* KEYW_LOCAL  */
  YYSYMBOL_KEYW_TRUE = 41,                 /* KEYW_TRUE  */
  YYSYMBOL_KEYW_FALSE = 42,                /* KEYW_FALSE  */
  YYSYMBOL_KEYW_NIL = 43,                  /* KEYW_NIL  */
  YYSYMBOL_CONST_INT = 44,                 /* CONST_INT  */
  YYSYMBOL_CONST_REAL = 45,                /* CONST_REAL  */
  YYSYMBOL_ID = 46,                        /* ID  */
  YYSYMBOL_COMM_SL = 47,                   /* COMM_SL  */
  YYSYMBOL_COMM_ML = 48,                   /* COMM_ML  */
  YYSYMBOL_COMM_NEST = 49,                 /* COMM_NEST  */
  YYSYMBOL_STRING = 50,                    /* STRING  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_stmt = 53,                      /* stmt  */
  YYSYMBOL_statements = 54,                /* statements  */
  YYSYMBOL_expr = 55,                      /* expr  */
  YYSYMBOL_op = 56,                        /* op  */
  YYSYMBOL_term = 57,                      /* term  */
  YYSYMBOL_assignexpr = 58,                /* assignexpr  */
  YYSYMBOL_primary = 59,                   /* primary  */
  YYSYMBOL_lvalue = 60,                    /* lvalue  */
  YYSYMBOL_member = 61,                    /* member  */
  YYSYMBOL_call = 62,                      /* call  */
  YYSYMBOL_callsuffix = 63,                /* callsuffix  */
  YYSYMBOL_normcall = 64,                  /* normcall  */
  YYSYMBOL_methodcall = 65,                /* methodcall  */
  YYSYMBOL_elist = 66,                     /* elist  */
  YYSYMBOL_elistrep = 67,                  /* elistrep  */
  YYSYMBOL_objectdef = 68,                 /* objectdef  */
  YYSYMBOL_objectin = 69,                  /* objectin  */
  YYSYMBOL_indexed = 70,                   /* indexed  */
  YYSYMBOL_indexrep = 71,                  /* indexrep  */
  YYSYMBOL_indexedelem = 72,               /* indexedelem  */
  YYSYMBOL_block = 73,                     /* block  */
  YYSYMBOL_funcdef = 74,                   /* funcdef  */
  YYSYMBOL_const = 75,                     /* const  */
  YYSYMBOL_idlist = 76,                    /* idlist  */
  YYSYMBOL_ids = 77,                       /* ids  */
  YYSYMBOL_ifstmt = 78,                    /* ifstmt  */
  YYSYMBOL_whilestmt = 79,                 /* whilestmt  */
  YYSYMBOL_forstmt = 80,                   /* forstmt  */
  YYSYMBOL_returnstmt = 81                 /* returnstmt  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




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

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
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
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
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

#if !defined yyoverflow

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
#endif /* !defined yyoverflow */

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

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

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
       0,    82,    82,    85,    86,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    98,    99,   102,   103,   104,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   122,   123,   124,   125,   126,   127,   128,   129,
     132,   134,   135,   136,   137,   138,   141,   142,   143,   144,
     147,   148,   149,   150,   153,   154,   155,   158,   159,   162,
     163,   165,   166,   169,   170,   171,   174,   175,   176,   177,
     180,   181,   182,   184,   186,   188,   189,   192,   193,   196,
     197,   198,   199,   200,   201,   204,   205,   206,   209,   210,
     211,   214,   215,   216,   217,   218,   219
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "OPER_EQ", "OPER_PLUS",
  "OPER_MINUS", "OPER_MUL", "OPER_DIV", "OPER_MOD", "OPER_EQ2", "OPER_NEQ",
  "OPER_PLUS2", "OPER_MINUS2", "OPER_GRT", "OPER_GRE", "OPER_LET",
  "OPER_LEE", "PUNC_LBRACE", "PUNC_RBRACE", "PUNC_LBRACKET",
  "PUNC_RBRACKET", "PUNC_LPARENTH", "PUNC_RPARENTH", "PUNC_SEMIC",
  "PUNC_COMMA", "PUNC_COLON", "PUNC_COLON2", "PUNC_DOT", "PUNC_DOT2",
  "KEYW_IF", "KEYW_ELSE", "KEYW_WHILE", "KEYW_FOR", "KEYW_FUNC",
  "KEYW_RET", "KEYW_BREAK", "KEYW_CONT", "KEYW_AND", "KEYW_NOT", "KEYW_OR",
  "KEYW_LOCAL", "KEYW_TRUE", "KEYW_FALSE", "KEYW_NIL", "CONST_INT",
  "CONST_REAL", "ID", "COMM_SL", "COMM_ML", "COMM_NEST", "STRING",
  "$accept", "program", "stmt", "statements", "expr", "op", "term",
  "assignexpr", "primary", "lvalue", "member", "call", "callsuffix",
  "normcall", "methodcall", "elist", "elistrep", "objectdef", "objectin",
  "indexed", "indexrep", "indexedelem", "block", "funcdef", "const",
  "idlist", "ids", "ifstmt", "whilestmt", "forstmt", "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

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
static const yytype_uint8 yydefgoto[] =
{
       0,    24,    25,    49,    27,    85,    28,    29,    30,    31,
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

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
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

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
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

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
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


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


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

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


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




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
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
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
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
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
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






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
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
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

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
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
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
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
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

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
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
  case 2: /* program: statements  */
#line 82 "src/phase2/bison_parser.y"
                                        {printReduction("program","statements", yylineno);}
#line 1351 "parser.c"
    break;

  case 3: /* stmt: expr PUNC_SEMIC  */
#line 85 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","expr PUNC_SEMIC", yylineno);}
#line 1357 "parser.c"
    break;

  case 4: /* stmt: ifstmt  */
#line 86 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","ifstmt", yylineno);}
#line 1363 "parser.c"
    break;

  case 5: /* stmt: whilestmt  */
#line 87 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","whilestmt", yylineno);}
#line 1369 "parser.c"
    break;

  case 6: /* stmt: forstmt  */
#line 88 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","forstmt", yylineno);}
#line 1375 "parser.c"
    break;

  case 7: /* stmt: returnstmt  */
#line 89 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","returnstmt", yylineno);}
#line 1381 "parser.c"
    break;

  case 8: /* stmt: KEYW_BREAK PUNC_SEMIC  */
#line 90 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","KEYW_BREAK PUNC_SEMIC", yylineno);}
#line 1387 "parser.c"
    break;

  case 9: /* stmt: KEYW_CONT PUNC_SEMIC  */
#line 91 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","KEYW_CONT PUNC_SEMIC", yylineno);}
#line 1393 "parser.c"
    break;

  case 10: /* stmt: block  */
#line 92 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","block", yylineno);}
#line 1399 "parser.c"
    break;

  case 11: /* stmt: funcdef  */
#line 93 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","funcdef", yylineno);}
#line 1405 "parser.c"
    break;

  case 12: /* stmt: PUNC_SEMIC  */
#line 94 "src/phase2/bison_parser.y"
                                        {printReduction("stmt"," PUNC_SEMIC", yylineno);}
#line 1411 "parser.c"
    break;

  case 13: /* stmt: %empty  */
#line 95 "src/phase2/bison_parser.y"
                                        {printReduction("stmt","empty", yylineno);}
#line 1417 "parser.c"
    break;

  case 14: /* statements: stmt statements  */
#line 98 "src/phase2/bison_parser.y"
                                        {printReduction("statements","stmt statements", yylineno);}
#line 1423 "parser.c"
    break;

  case 15: /* statements: %empty  */
#line 99 "src/phase2/bison_parser.y"
                                        {printReduction("statements","empty", yylineno);}
#line 1429 "parser.c"
    break;

  case 16: /* expr: assignexpr  */
#line 102 "src/phase2/bison_parser.y"
                                        {printReduction("expr","assignexpr", yylineno);}
#line 1435 "parser.c"
    break;

  case 17: /* expr: expr op expr  */
#line 103 "src/phase2/bison_parser.y"
                                        {printReduction("expr","expr op expr", yylineno);}
#line 1441 "parser.c"
    break;

  case 18: /* expr: term  */
#line 104 "src/phase2/bison_parser.y"
                                        {printReduction("expr","term", yylineno);}
#line 1447 "parser.c"
    break;

  case 19: /* op: OPER_PLUS  */
#line 107 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_PLUS", yylineno);}
#line 1453 "parser.c"
    break;

  case 20: /* op: OPER_MINUS  */
#line 108 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_MINUS", yylineno);}
#line 1459 "parser.c"
    break;

  case 21: /* op: OPER_MUL  */
#line 109 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_MUL", yylineno);}
#line 1465 "parser.c"
    break;

  case 22: /* op: OPER_DIV  */
#line 110 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_DIV", yylineno);}
#line 1471 "parser.c"
    break;

  case 23: /* op: OPER_MOD  */
#line 111 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_MOD", yylineno);}
#line 1477 "parser.c"
    break;

  case 24: /* op: OPER_GRT  */
#line 112 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_GRT", yylineno);}
#line 1483 "parser.c"
    break;

  case 25: /* op: OPER_GRE  */
#line 113 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_GRE", yylineno);}
#line 1489 "parser.c"
    break;

  case 26: /* op: OPER_LET  */
#line 114 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_LET", yylineno);}
#line 1495 "parser.c"
    break;

  case 27: /* op: OPER_LEE  */
#line 115 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_LEE", yylineno);}
#line 1501 "parser.c"
    break;

  case 28: /* op: OPER_EQ2  */
#line 116 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_EQ2", yylineno);}
#line 1507 "parser.c"
    break;

  case 29: /* op: OPER_NEQ  */
#line 117 "src/phase2/bison_parser.y"
                                        {printReduction("op","OPER_NEQ", yylineno);}
#line 1513 "parser.c"
    break;

  case 30: /* op: KEYW_AND  */
#line 118 "src/phase2/bison_parser.y"
                                        {printReduction("op","KEYW_AND", yylineno);}
#line 1519 "parser.c"
    break;

  case 31: /* op: KEYW_OR  */
#line 119 "src/phase2/bison_parser.y"
                                        {printReduction("op","KEYW_OR", yylineno);}
#line 1525 "parser.c"
    break;

  case 32: /* term: PUNC_LPARENTH expr PUNC_RPARENTH  */
#line 122 "src/phase2/bison_parser.y"
                                                    { yyval = yyvsp[-1]; printReduction("term","PUNC_LPARENTH expr PUNC_RPARENTH", yylineno);}
#line 1531 "parser.c"
    break;

  case 33: /* term: OPER_MINUS expr  */
#line 123 "src/phase2/bison_parser.y"
                                                    { yyval = -yyvsp[0]; printReduction("term","OPER_MINUS expr", yylineno);}
#line 1537 "parser.c"
    break;

  case 34: /* term: KEYW_NOT expr  */
#line 124 "src/phase2/bison_parser.y"
                                                    { yyval = !yyvsp[0]; printReduction("term","KEYW_NOT expr", yylineno);}
#line 1543 "parser.c"
    break;

  case 35: /* term: OPER_PLUS2 lvalue  */
#line 125 "src/phase2/bison_parser.y"
                                                    { yyval = ++yyvsp[0]; printReduction("term","OPER_PLUS2 lvalue", yylineno);}
#line 1549 "parser.c"
    break;

  case 36: /* term: lvalue OPER_PLUS2  */
#line 126 "src/phase2/bison_parser.y"
                                                    { yyval = yyvsp[-1]++; printReduction("term","lvalue OPER_PLUS2", yylineno);}
#line 1555 "parser.c"
    break;

  case 37: /* term: OPER_MINUS2 lvalue  */
#line 127 "src/phase2/bison_parser.y"
                                                    { yyval = --yyvsp[0]; printReduction("term","OPER_MINUS2 lvalue", yylineno);}
#line 1561 "parser.c"
    break;

  case 38: /* term: lvalue OPER_MINUS2  */
#line 128 "src/phase2/bison_parser.y"
                                                    { yyval = yyvsp[-1]--; printReduction("term","lvalue OPER_MINUS2", yylineno);}
#line 1567 "parser.c"
    break;

  case 39: /* term: primary  */
#line 129 "src/phase2/bison_parser.y"
                                                    { yyval = yyvsp[0]; printReduction("term","primary", yylineno);}
#line 1573 "parser.c"
    break;

  case 40: /* assignexpr: lvalue OPER_EQ2 expr  */
#line 132 "src/phase2/bison_parser.y"
                                                    { yyvsp[-2] = yyvsp[0]; printReduction("assignexpr","lvalue OPER_EQ2 expr", yylineno);}
#line 1579 "parser.c"
    break;

  case 41: /* primary: lvalue  */
#line 134 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","lvalue", yylineno);}
#line 1585 "parser.c"
    break;

  case 42: /* primary: call  */
#line 135 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","call", yylineno);}
#line 1591 "parser.c"
    break;

  case 43: /* primary: objectdef  */
#line 136 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","objectdef", yylineno);}
#line 1597 "parser.c"
    break;

  case 44: /* primary: PUNC_LPARENTH funcdef PUNC_RPARENTH  */
#line 137 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","PUNC_LPARENTH funcdef PUNC_RPARENTH", yylineno);}
#line 1603 "parser.c"
    break;

  case 45: /* primary: const  */
#line 138 "src/phase2/bison_parser.y"
                                                    {printReduction("primary","const", yylineno);}
#line 1609 "parser.c"
    break;

  case 46: /* lvalue: ID  */
#line 141 "src/phase2/bison_parser.y"
                                                    {printReduction("lvalue","ID", yylineno);}
#line 1615 "parser.c"
    break;

  case 47: /* lvalue: KEYW_LOCAL ID  */
#line 142 "src/phase2/bison_parser.y"
                                                    {printReduction("lvalue","KEYW_LOCAL ID", yylineno);}
#line 1621 "parser.c"
    break;

  case 48: /* lvalue: PUNC_COLON2 ID  */
#line 143 "src/phase2/bison_parser.y"
                                                    {printReduction("lvalue","PUNC_COLON2 ID", yylineno);}
#line 1627 "parser.c"
    break;

  case 49: /* lvalue: member  */
#line 144 "src/phase2/bison_parser.y"
                                                    {printReduction("lvalue","member", yylineno);}
#line 1633 "parser.c"
    break;

  case 50: /* member: lvalue PUNC_DOT ID  */
#line 147 "src/phase2/bison_parser.y"
                                                        {printReduction("member","lvalue PUNC_DOT ID", yylineno);}
#line 1639 "parser.c"
    break;

  case 51: /* member: lvalue PUNC_LBRACKET expr PUNC_RBRACKET  */
#line 148 "src/phase2/bison_parser.y"
                                                        {printReduction("member","lvalue PUNC_LBRACKET expr PUNC_RBRACKET", yylineno);}
#line 1645 "parser.c"
    break;

  case 52: /* member: call PUNC_DOT ID  */
#line 149 "src/phase2/bison_parser.y"
                                                        {printReduction("member","call PUNC_DOT ID", yylineno);}
#line 1651 "parser.c"
    break;

  case 53: /* member: call PUNC_LBRACKET expr PUNC_RBRACKET  */
#line 150 "src/phase2/bison_parser.y"
                                                        {printReduction("member","call PUNC_LBRACKET expr PUNC_RBRACKET", yylineno);}
#line 1657 "parser.c"
    break;

  case 54: /* call: call PUNC_LPARENTH elist PUNC_RPARENTH  */
#line 153 "src/phase2/bison_parser.y"
                                                                                        {printReduction("call","call PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);}
#line 1663 "parser.c"
    break;

  case 55: /* call: lvalue callsuffix  */
#line 154 "src/phase2/bison_parser.y"
                                                                                        {printReduction("call","lvalue callsuffix ID", yylineno);}
#line 1669 "parser.c"
    break;

  case 56: /* call: PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH  */
#line 155 "src/phase2/bison_parser.y"
                                                                                        {printReduction("call","PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH ID", yylineno);}
#line 1675 "parser.c"
    break;

  case 57: /* callsuffix: normcall  */
#line 158 "src/phase2/bison_parser.y"
                                                                    {printReduction("callsuffix","normcall", yylineno);}
#line 1681 "parser.c"
    break;

  case 58: /* callsuffix: methodcall  */
#line 159 "src/phase2/bison_parser.y"
                                                                    {printReduction("callsuffix","methodcall", yylineno);}
#line 1687 "parser.c"
    break;

  case 59: /* normcall: PUNC_LPARENTH elist PUNC_RPARENTH  */
#line 162 "src/phase2/bison_parser.y"
                                                                    {printReduction("normcall","PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);}
#line 1693 "parser.c"
    break;

  case 60: /* methodcall: PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH  */
#line 163 "src/phase2/bison_parser.y"
                                                                    {printReduction("methodcall","PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH", yylineno);}
#line 1699 "parser.c"
    break;

  case 61: /* elist: expr elistrep  */
#line 165 "src/phase2/bison_parser.y"
                                                                    {printReduction("elist","expr elistrep", yylineno);}
#line 1705 "parser.c"
    break;

  case 62: /* elist: %empty  */
#line 166 "src/phase2/bison_parser.y"
                                                                    {printReduction("elist","empty", yylineno);}
#line 1711 "parser.c"
    break;

  case 63: /* elistrep: PUNC_COMMA expr elistrep  */
#line 169 "src/phase2/bison_parser.y"
                                                                    {printReduction("elistrep","PUNC_COMMA expr elistrep", yylineno);}
#line 1717 "parser.c"
    break;

  case 64: /* elistrep: PUNC_COMMA expr  */
#line 170 "src/phase2/bison_parser.y"
                                                                    {printReduction("elistrep","PUNC_COMMA expr", yylineno);}
#line 1723 "parser.c"
    break;

  case 65: /* elistrep: %empty  */
#line 171 "src/phase2/bison_parser.y"
                                                                    {printReduction("elistrep","empty", yylineno);}
#line 1729 "parser.c"
    break;

  case 66: /* objectdef: PUNC_LBRACKET objectin PUNC_RBRACKET  */
#line 174 "src/phase2/bison_parser.y"
                                                                    {printReduction("objectdef","PUNC_LBRACKET objectin PUNC_RBRACKET", yylineno);}
#line 1735 "parser.c"
    break;

  case 67: /* objectin: elist  */
#line 175 "src/phase2/bison_parser.y"
                                                                    {printReduction("objectin","elist", yylineno);}
#line 1741 "parser.c"
    break;

  case 68: /* objectin: indexed  */
#line 176 "src/phase2/bison_parser.y"
                                                                    {printReduction("objectin","indexed", yylineno);}
#line 1747 "parser.c"
    break;

  case 69: /* objectin: %empty  */
#line 177 "src/phase2/bison_parser.y"
                                                                    {printReduction("objectin","empty", yylineno);}
#line 1753 "parser.c"
    break;

  case 70: /* indexed: indexedelem  */
#line 180 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexed","indexedelem", yylineno);}
#line 1759 "parser.c"
    break;

  case 71: /* indexed: indexedelem indexrep  */
#line 181 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexed","indexedelem indexrep", yylineno);}
#line 1765 "parser.c"
    break;

  case 72: /* indexed: %empty  */
#line 182 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexed","empty", yylineno);}
#line 1771 "parser.c"
    break;

  case 73: /* indexrep: PUNC_COMMA indexedelem  */
#line 184 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexrep","PUNC_COMMA indexedelem", yylineno);}
#line 1777 "parser.c"
    break;

  case 74: /* indexedelem: PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE  */
#line 186 "src/phase2/bison_parser.y"
                                                                    {printReduction("indexedelem","PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE", yylineno);}
#line 1783 "parser.c"
    break;

  case 75: /* block: PUNC_LBRACKET statements PUNC_RBRACKET  */
#line 188 "src/phase2/bison_parser.y"
                                                                    {printReduction("block","PUNC_LBRACKET statements PUNC_RBRACKET", yylineno);}
#line 1789 "parser.c"
    break;

  case 76: /* block: %empty  */
#line 189 "src/phase2/bison_parser.y"
                                                                    {printReduction("block","empty", yylineno);}
#line 1795 "parser.c"
    break;

  case 77: /* funcdef: KEYW_FUNC ID PUNC_LPARENTH idlist PUNC_RPARENTH block  */
#line 192 "src/phase2/bison_parser.y"
                                                                    {printReduction("funcdef","KEYW_FUNC ID PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
#line 1801 "parser.c"
    break;

  case 78: /* funcdef: KEYW_FUNC PUNC_LPARENTH idlist PUNC_RPARENTH block  */
#line 193 "src/phase2/bison_parser.y"
                                                                    {printReduction("funcdef","KEYW_FUNC PUNC_LPARENTH idlist PUNC_RPARENTH block", yylineno);}
#line 1807 "parser.c"
    break;

  case 79: /* const: CONST_INT  */
#line 196 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","CONST_INT", yylineno);}
#line 1813 "parser.c"
    break;

  case 80: /* const: CONST_REAL  */
#line 197 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","CONST_REAL", yylineno);}
#line 1819 "parser.c"
    break;

  case 81: /* const: STRING  */
#line 198 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","STRING", yylineno);}
#line 1825 "parser.c"
    break;

  case 82: /* const: KEYW_NIL  */
#line 199 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","KEYW_NIL", yylineno);}
#line 1831 "parser.c"
    break;

  case 83: /* const: KEYW_TRUE  */
#line 200 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","KEYW_TRUE", yylineno);}
#line 1837 "parser.c"
    break;

  case 84: /* const: KEYW_FALSE  */
#line 201 "src/phase2/bison_parser.y"
                                                                    {printReduction("const","KEYW_FALSE", yylineno);}
#line 1843 "parser.c"
    break;

  case 85: /* idlist: ID ids  */
#line 204 "src/phase2/bison_parser.y"
                                                                    {printReduction("idlist","ID ids", yylineno);}
#line 1849 "parser.c"
    break;

  case 86: /* idlist: ID  */
#line 205 "src/phase2/bison_parser.y"
                                                                    {printReduction("idlist","ID", yylineno);}
#line 1855 "parser.c"
    break;

  case 87: /* idlist: %empty  */
#line 206 "src/phase2/bison_parser.y"
                                                                    {printReduction("idlist","empty", yylineno);}
#line 1861 "parser.c"
    break;

  case 88: /* ids: PUNC_COMMA ID ids  */
#line 209 "src/phase2/bison_parser.y"
                                                                    {printReduction("ids","PUNC_COMMA ID ids", yylineno);}
#line 1867 "parser.c"
    break;

  case 89: /* ids: PUNC_COMMA ID  */
#line 210 "src/phase2/bison_parser.y"
                                                                    {printReduction("ids","PUNC_COMMA ID", yylineno);}
#line 1873 "parser.c"
    break;

  case 90: /* ids: %empty  */
#line 211 "src/phase2/bison_parser.y"
                                                                    {printReduction("ids","empty", yylineno);}
#line 1879 "parser.c"
    break;

  case 91: /* ifstmt: KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt  */
#line 214 "src/phase2/bison_parser.y"
                                                                    {printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);}
#line 1885 "parser.c"
    break;

  case 92: /* ifstmt: KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt KEYW_ELSE stmt  */
#line 215 "src/phase2/bison_parser.y"
                                                                                    {printReduction("ifstmt","KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH stmt KEYW_ELSE stmt", yylineno);}
#line 1891 "parser.c"
    break;

  case 93: /* whilestmt: KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt  */
#line 216 "src/phase2/bison_parser.y"
                                                                        {printReduction("whilestmt","KEYW_WHILE PUNC_LPARENTH expr PUNC_RPARENTH stmt", yylineno);}
#line 1897 "parser.c"
    break;

  case 94: /* forstmt: KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt  */
#line 217 "src/phase2/bison_parser.y"
                                                                                                        {printReduction("forstmt","KEYW_FOR PUNC_LPARENTH elist PUNC_SEMIC expr PUNC_SEMIC elist PUNC_RPARENTH stmt", yylineno);}
#line 1903 "parser.c"
    break;

  case 95: /* returnstmt: KEYW_RET PUNC_SEMIC  */
#line 218 "src/phase2/bison_parser.y"
                                        {printReduction("returnstmt","KEYW_RET PUNC_SEMIC", yylineno);}
#line 1909 "parser.c"
    break;

  case 96: /* returnstmt: KEYW_RET expr PUNC_SEMIC  */
#line 219 "src/phase2/bison_parser.y"
                                                {printReduction("returnstmt","KEYW_RET expr PUNC_SEMIC", yylineno);}
#line 1915 "parser.c"
    break;


#line 1919 "parser.c"

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
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

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
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
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
  ++yynerrs;

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

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
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
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
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
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 222 "src/phase2/bison_parser.y"


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
