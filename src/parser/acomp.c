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
#line 1 "src/parser/bison_parser.y"

    /*
    * TODO LIST:
    * return statement only inside functions 
    * fix evaluation (reduce when shift needed)
    * 
    *   BROKEN TESTFILES:
    * p3t_calls.asc                 > OUTPUTING
    * p3t_if_else.asc               > DONE (Removed true evaluation)
    * p3t_flow_control.asc          > DONE (Same as above)
    * p3t_flow_control_error.asc    > DONE
    * p3t_relational.asc            >
    * backpatch0.asc                >
    * backpatch3.asc                >
    * p3t_assignments_objects.asc   >
    * p3t_basic_expr.asc            >
    */

    #include <stdio.h>
    #include <assert.h>
    #include <string.h>
    #include <stdlib.h>

    #include "quads.h"
    #include "utils.h"
    #include "stack.h"
    #include "target_code_generator.h"
    #include "debug_functions.h"

    #define YYERROR_VERBOSE

    SymTable st;
    extern int yylineno;
    extern char * yytext;
    extern FILE * yyin;
    extern uint scope;
    char * current_function;
    extern FILE* file;

    #define REF_NONE   0
    #define REF_LOCAL  1
    #define REF_GLOBAL 2

    int ref_flag;
    int produce_icode = 1;
    int offset;
    int loopcnt;

    Stack offset_stack;
    Stack loopcnt_stack;

    int yylex(void);
    void yyerror(const char *yaccerror);

    extern int prog_var_flag;
    extern struct quad * quads;
    extern unsigned int  total;
    extern unsigned int  currQuad;

    /*** string formatting ***/

    #define F_BOLD "\e[1m"
    #define F_RST  "\e[0m"

#line 136 "src/parser/acomp.c"

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

#include "acomp.h"
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
  YYSYMBOL_STRING = 47,                    /* STRING  */
  YYSYMBOL_UNARY_MINUS = 48,               /* UNARY_MINUS  */
  YYSYMBOL_YYACCEPT = 49,                  /* $accept  */
  YYSYMBOL_program = 50,                   /* program  */
  YYSYMBOL_statements = 51,                /* statements  */
  YYSYMBOL_stmt = 52,                      /* stmt  */
  YYSYMBOL_expr = 53,                      /* expr  */
  YYSYMBOL_54_1 = 54,                      /* $@1  */
  YYSYMBOL_55_2 = 55,                      /* $@2  */
  YYSYMBOL_term = 56,                      /* term  */
  YYSYMBOL_primary = 57,                   /* primary  */
  YYSYMBOL_assignexpr = 58,                /* assignexpr  */
  YYSYMBOL_lvalue = 59,                    /* lvalue  */
  YYSYMBOL_member = 60,                    /* member  */
  YYSYMBOL_call = 61,                      /* call  */
  YYSYMBOL_callsuffix = 62,                /* callsuffix  */
  YYSYMBOL_normcall = 63,                  /* normcall  */
  YYSYMBOL_methodcall = 64,                /* methodcall  */
  YYSYMBOL_elistrep = 65,                  /* elistrep  */
  YYSYMBOL_elist = 66,                     /* elist  */
  YYSYMBOL_objectin = 67,                  /* objectin  */
  YYSYMBOL_objectdef = 68,                 /* objectdef  */
  YYSYMBOL_indexed = 69,                   /* indexed  */
  YYSYMBOL_indexedelem = 70,               /* indexedelem  */
  YYSYMBOL_indexrep = 71,                  /* indexrep  */
  YYSYMBOL_blockprefix = 72,               /* blockprefix  */
  YYSYMBOL_block = 73,                     /* block  */
  YYSYMBOL_funcstart = 74,                 /* funcstart  */
  YYSYMBOL_funcend = 75,                   /* funcend  */
  YYSYMBOL_funcname = 76,                  /* funcname  */
  YYSYMBOL_funcprefix = 77,                /* funcprefix  */
  YYSYMBOL_funcargs = 78,                  /* funcargs  */
  YYSYMBOL_79_3 = 79,                      /* $@3  */
  YYSYMBOL_80_4 = 80,                      /* $@4  */
  YYSYMBOL_funcdef = 81,                   /* funcdef  */
  YYSYMBOL_const = 82,                     /* const  */
  YYSYMBOL_idlist = 83,                    /* idlist  */
  YYSYMBOL_ids = 84,                       /* ids  */
  YYSYMBOL_85_5 = 85,                      /* $@5  */
  YYSYMBOL_ifprefix = 86,                  /* ifprefix  */
  YYSYMBOL_ifstmt = 87,                    /* ifstmt  */
  YYSYMBOL_loopstart = 88,                 /* loopstart  */
  YYSYMBOL_loopend = 89,                   /* loopend  */
  YYSYMBOL_whilestart = 90,                /* whilestart  */
  YYSYMBOL_whilecond = 91,                 /* whilecond  */
  YYSYMBOL_whilestmt = 92,                 /* whilestmt  */
  YYSYMBOL_jumpandsavepos = 93,            /* jumpandsavepos  */
  YYSYMBOL_savepos = 94,                   /* savepos  */
  YYSYMBOL_forprefix = 95,                 /* forprefix  */
  YYSYMBOL_forstmt = 96,                   /* forstmt  */
  YYSYMBOL_returnstmt = 97                 /* returnstmt  */
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
#define YYFINAL  72
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   554

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  49
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  49
/* YYNRULES -- Number of rules.  */
#define YYNRULES  107
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  197

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   303


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
      45,    46,    47,    48
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   187,   187,   194,   201,   207,   215,   219,   223,   227,
     232,   241,   250,   254,   258,   265,   273,   281,   289,   301,
     309,   309,   323,   323,   337,   348,   359,   370,   381,   390,
     400,   404,   423,   429,   437,   470,   499,   533,   558,   591,
     598,   613,   617,   621,   626,   633,   677,   696,   715,   735,
     742,   749,   757,   761,   769,   773,   815,   825,   829,   836,
     845,   855,   863,   869,   878,   884,   902,   918,   925,   933,
     946,   952,   958,   971,   985,   991,   997,  1002,  1009,  1033,
    1040,  1032,  1047,  1062,  1066,  1070,  1074,  1078,  1082,  1089,
    1111,  1116,  1115,  1142,  1148,  1159,  1163,  1171,  1176,  1181,
    1187,  1197,  1208,  1215,  1221,  1235,  1248,  1258
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
  "CONST_REAL", "ID", "STRING", "UNARY_MINUS", "$accept", "program",
  "statements", "stmt", "expr", "$@1", "$@2", "term", "primary",
  "assignexpr", "lvalue", "member", "call", "callsuffix", "normcall",
  "methodcall", "elistrep", "elist", "objectin", "objectdef", "indexed",
  "indexedelem", "indexrep", "blockprefix", "block", "funcstart",
  "funcend", "funcname", "funcprefix", "funcargs", "$@3", "$@4", "funcdef",
  "const", "idlist", "ids", "$@5", "ifprefix", "ifstmt", "loopstart",
  "loopend", "whilestart", "whilecond", "whilestmt", "jumpandsavepos",
  "savepos", "forprefix", "forstmt", "returnstmt", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-140)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  ((Yyn) == YYTABLE_NINF)

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     143,   240,    18,    18,  -140,    91,   186,  -140,   -40,    -8,
    -140,  -140,   -30,   197,    -6,    20,   240,     2,  -140,  -140,
    -140,  -140,  -140,  -140,  -140,    45,  -140,   143,    14,  -140,
    -140,  -140,    35,  -140,    65,  -140,   143,  -140,  -140,  -140,
    -140,   143,  -140,  -140,  -140,  -140,  -140,  -140,  -140,    22,
      13,    65,    13,   240,   284,  -140,    37,  -140,    36,   297,
      43,  -140,   240,    51,  -140,  -140,  -140,   333,  -140,  -140,
    -140,  -140,  -140,  -140,   240,   240,   240,   240,   240,   240,
     240,   240,   240,   240,   240,  -140,  -140,  -140,   240,  -140,
    -140,   240,   240,    39,    42,  -140,  -140,  -140,   240,   240,
      53,    71,    79,    76,    80,   240,    89,   353,   240,  -140,
    -140,    92,  -140,  -140,    93,   389,   240,  -140,    87,    63,
    -140,  -140,  -140,   518,   518,   242,   242,   242,   242,  -140,
    -140,   502,   409,    94,  -140,    97,   427,    98,  -140,  -140,
    -140,    96,  -140,   240,   143,    99,    93,   240,   284,    36,
     240,  -140,  -140,   240,   240,  -140,  -140,   240,  -140,  -140,
      73,  -140,   143,   445,  -140,  -140,   465,  -140,  -140,   100,
     101,   538,   538,   103,   102,  -140,  -140,  -140,  -140,  -140,
     143,  -140,  -140,   240,  -140,    81,  -140,   106,  -140,   482,
    -140,  -140,  -140,  -140,   102,  -140,  -140
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     0,     0,    72,    64,     0,    14,     0,     0,
      99,    97,    77,     0,     0,     0,     0,     0,    87,    88,
      86,    83,    84,    46,    85,     0,     2,     4,     0,    30,
      39,    31,    40,    49,    41,    42,     4,    12,    74,    13,
      44,     0,     6,    97,     7,   102,     8,     9,    33,     0,
      35,     0,    37,     0,    62,    65,     0,    66,    71,     0,
       0,    48,     0,     0,    76,    78,   106,     0,    10,    11,
      34,    47,     1,     3,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     5,    20,    22,     0,    36,
      38,     0,    64,     0,     0,    55,    57,    58,     0,    64,
       0,     0,     0,    95,     0,    64,     0,     0,     0,    63,
      67,     0,    68,    32,    43,     0,    64,   107,    15,    16,
      17,    18,    19,    28,    29,    24,    25,    26,    27,   103,
     103,    45,     0,     0,    50,     0,     0,     0,    52,    73,
      79,     0,   102,     0,     0,     0,     0,     0,    62,    71,
      64,    94,   103,     0,     0,    51,    59,    64,    53,    54,
      90,    75,     0,     0,    98,   102,     0,    61,    70,     0,
       0,    21,    23,     0,    93,    80,    82,    96,   100,   101,
       0,    69,    56,     0,    60,     0,    89,     0,   102,     0,
      91,    81,    98,   104,    93,   105,    92
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -140,  -140,     6,   -39,    -1,  -140,  -140,  -140,  -140,  -140,
       8,  -140,    33,  -140,  -140,  -140,   -18,   -91,  -140,  -140,
    -140,    28,    -9,  -140,     3,  -140,  -140,  -140,  -140,  -140,
    -140,  -140,     1,  -140,  -140,   -51,  -140,  -140,  -140,   104,
     -47,  -140,  -140,  -140,  -139,  -121,  -140,  -140,  -140
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,    25,    26,    27,    28,   129,   130,    29,    30,    31,
      32,    33,    34,    95,    96,    97,   109,    55,    56,    35,
      57,    58,   112,    36,    37,   102,   176,    65,    38,   141,
     160,   187,    39,    40,   175,   186,   194,    41,    42,    63,
     179,    43,   144,    44,   105,   153,    45,    46,    47
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      48,   133,   103,   162,    54,    59,    61,    60,   137,   154,
      50,    52,    67,    62,   145,    70,    64,    68,    74,    75,
      76,    77,    78,    79,    80,   152,   180,    81,    82,    83,
      84,   170,    91,    73,    92,    51,    51,    85,    88,    49,
      93,    94,   101,    69,     8,    72,    89,    90,    71,   192,
     106,    86,   107,    87,    91,    12,    92,   110,    17,   169,
     111,   115,    93,    94,    23,   114,   173,    74,    75,    76,
      77,    78,   116,   118,   119,   120,   121,   122,   123,   124,
     125,   126,   127,   128,    98,   134,    99,   131,   135,   139,
     132,    54,   100,    76,    77,    78,     1,   136,    54,   138,
     140,   143,     2,     3,    54,   164,   142,   148,    53,    53,
       5,   146,     6,     4,   150,    54,   156,     8,   157,   174,
     159,   165,   182,   177,   183,   184,   185,   190,   191,    16,
     167,    17,    18,    19,    20,    21,    22,    23,    24,   149,
     168,   188,   163,   196,   161,   195,   166,   104,     1,    54,
       0,     0,   171,   172,     2,     3,    54,     0,     0,     0,
       4,     0,     5,     0,     6,     0,     7,     0,     0,     8,
       0,     0,     9,     0,    10,    11,    12,    13,    14,    15,
       0,    16,   189,    17,    18,    19,    20,    21,    22,    23,
      24,     1,     0,     0,     0,     0,     0,     2,     3,     0,
       0,     0,     1,     0,     0,     5,     0,     6,     2,     3,
       0,     0,     8,     0,     0,     0,     5,     0,     6,    12,
      66,     0,     0,     8,    16,     0,    17,    18,    19,    20,
      21,    22,    23,    24,     0,    16,     0,    17,    18,    19,
      20,    21,    22,    23,    24,     1,    74,    75,    76,    77,
      78,     2,     3,     0,     0,    -1,    -1,    -1,    -1,     5,
       0,     6,     0,     0,     0,     0,     8,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    16,     0,
      17,    18,    19,    20,    21,    22,    23,    24,    74,    75,
      76,    77,    78,    79,    80,     0,     0,    81,    82,    83,
      84,    74,    75,    76,    77,    78,    79,    80,   108,     0,
      81,    82,    83,    84,     0,     0,     0,     0,     0,   113,
       0,    86,     0,    87,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    86,     0,    87,    74,    75,    76,
      77,    78,    79,    80,     0,     0,    81,    82,    83,    84,
       0,     0,     0,     0,     0,     0,   117,    74,    75,    76,
      77,    78,    79,    80,     0,     0,    81,    82,    83,    84,
      86,     0,    87,     0,     0,     0,     0,     0,   147,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      86,     0,    87,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,     0,     0,     0,     0,
       0,   151,     0,    74,    75,    76,    77,    78,    79,    80,
       0,     0,    81,    82,    83,    84,    86,     0,    87,   155,
       0,    74,    75,    76,    77,    78,    79,    80,     0,     0,
      81,    82,    83,    84,     0,     0,    86,   158,    87,    74,
      75,    76,    77,    78,    79,    80,     0,     0,    81,    82,
      83,    84,     0,     0,    86,     0,    87,   178,     0,    74,
      75,    76,    77,    78,    79,    80,     0,     0,    81,    82,
      83,    84,    86,   181,    87,     0,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,    84,     0,
       0,     0,    86,     0,    87,   193,    74,    75,    76,    77,
      78,    79,    80,     0,     0,    81,    82,    83,    84,    86,
       0,    87,    74,    75,    76,    77,    78,    -1,    -1,     0,
       0,    81,    82,    83,    84,     0,     0,     0,     0,    86,
       0,    87,    74,    75,    76,    77,    78,    79,    80,     0,
       0,    81,    82,    83,    84
};

static const yytype_int16 yycheck[] =
{
       1,    92,    41,   142,     5,     6,    46,     6,    99,   130,
       2,     3,    13,    21,   105,    16,    46,    23,     4,     5,
       6,     7,     8,     9,    10,   116,   165,    13,    14,    15,
      16,   152,    19,    27,    21,     2,     3,    23,     3,    21,
      27,    28,    36,    23,    26,     0,    11,    12,    46,   188,
      49,    37,    53,    39,    19,    33,    21,    20,    40,   150,
      24,    62,    27,    28,    46,    22,   157,     4,     5,     6,
       7,     8,    21,    74,    75,    76,    77,    78,    79,    80,
      81,    82,    83,    84,    19,    46,    21,    88,    46,    18,
      91,    92,    27,     6,     7,     8,     5,    98,    99,    46,
      21,    21,    11,    12,   105,   144,    30,   108,    17,    17,
      19,    22,    21,    17,    21,   116,    22,    26,    21,    46,
      22,    22,    22,   162,    23,    22,    24,    46,    22,    38,
     148,    40,    41,    42,    43,    44,    45,    46,    47,   111,
     149,   180,   143,   194,   141,   192,   147,    43,     5,   150,
      -1,    -1,   153,   154,    11,    12,   157,    -1,    -1,    -1,
      17,    -1,    19,    -1,    21,    -1,    23,    -1,    -1,    26,
      -1,    -1,    29,    -1,    31,    32,    33,    34,    35,    36,
      -1,    38,   183,    40,    41,    42,    43,    44,    45,    46,
      47,     5,    -1,    -1,    -1,    -1,    -1,    11,    12,    -1,
      -1,    -1,     5,    -1,    -1,    19,    -1,    21,    11,    12,
      -1,    -1,    26,    -1,    -1,    -1,    19,    -1,    21,    33,
      23,    -1,    -1,    26,    38,    -1,    40,    41,    42,    43,
      44,    45,    46,    47,    -1,    38,    -1,    40,    41,    42,
      43,    44,    45,    46,    47,     5,     4,     5,     6,     7,
       8,    11,    12,    -1,    -1,    13,    14,    15,    16,    19,
      -1,    21,    -1,    -1,    -1,    -1,    26,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    38,    -1,
      40,    41,    42,    43,    44,    45,    46,    47,     4,     5,
       6,     7,     8,     9,    10,    -1,    -1,    13,    14,    15,
      16,     4,     5,     6,     7,     8,     9,    10,    24,    -1,
      13,    14,    15,    16,    -1,    -1,    -1,    -1,    -1,    22,
      -1,    37,    -1,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    37,    -1,    39,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
      -1,    -1,    -1,    -1,    -1,    -1,    23,     4,     5,     6,
       7,     8,     9,    10,    -1,    -1,    13,    14,    15,    16,
      37,    -1,    39,    -1,    -1,    -1,    -1,    -1,    25,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      37,    -1,    39,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,    15,    16,    -1,    -1,    -1,    -1,
      -1,    22,    -1,     4,     5,     6,     7,     8,     9,    10,
      -1,    -1,    13,    14,    15,    16,    37,    -1,    39,    20,
      -1,     4,     5,     6,     7,     8,     9,    10,    -1,    -1,
      13,    14,    15,    16,    -1,    -1,    37,    20,    39,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    14,
      15,    16,    -1,    -1,    37,    -1,    39,    22,    -1,     4,
       5,     6,     7,     8,     9,    10,    -1,    -1,    13,    14,
      15,    16,    37,    18,    39,    -1,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    14,    15,    16,    -1,
      -1,    -1,    37,    -1,    39,    23,     4,     5,     6,     7,
       8,     9,    10,    -1,    -1,    13,    14,    15,    16,    37,
      -1,    39,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    14,    15,    16,    -1,    -1,    -1,    -1,    37,
      -1,    39,     4,     5,     6,     7,     8,     9,    10,    -1,
      -1,    13,    14,    15,    16
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     5,    11,    12,    17,    19,    21,    23,    26,    29,
      31,    32,    33,    34,    35,    36,    38,    40,    41,    42,
      43,    44,    45,    46,    47,    50,    51,    52,    53,    56,
      57,    58,    59,    60,    61,    68,    72,    73,    77,    81,
      82,    86,    87,    90,    92,    95,    96,    97,    53,    21,
      59,    61,    59,    17,    53,    66,    67,    69,    70,    53,
      81,    46,    21,    88,    46,    76,    23,    53,    23,    23,
      53,    46,     0,    51,     4,     5,     6,     7,     8,     9,
      10,    13,    14,    15,    16,    23,    37,    39,     3,    11,
      12,    19,    21,    27,    28,    62,    63,    64,    19,    21,
      27,    51,    74,    52,    88,    93,    81,    53,    24,    65,
      20,    24,    71,    22,    22,    53,    21,    23,    53,    53,
      53,    53,    53,    53,    53,    53,    53,    53,    53,    54,
      55,    53,    53,    66,    46,    46,    53,    66,    46,    18,
      21,    78,    30,    21,    91,    66,    22,    25,    53,    70,
      21,    22,    66,    94,    94,    20,    22,    21,    20,    22,
      79,    73,    93,    53,    52,    22,    53,    65,    71,    66,
      94,    53,    53,    66,    46,    83,    75,    52,    22,    89,
      93,    18,    22,    23,    22,    24,    84,    80,    52,    53,
      46,    22,    93,    23,    85,    89,    84
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    49,    50,    51,    51,    52,    52,    52,    52,    52,
      52,    52,    52,    52,    52,    53,    53,    53,    53,    53,
      54,    53,    55,    53,    53,    53,    53,    53,    53,    53,
      53,    53,    56,    56,    56,    56,    56,    56,    56,    56,
      57,    57,    57,    57,    57,    58,    59,    59,    59,    59,
      60,    60,    60,    60,    61,    61,    61,    62,    62,    63,
      64,    65,    65,    66,    66,    67,    67,    68,    69,    70,
      71,    71,    72,    73,    74,    75,    76,    76,    77,    79,
      80,    78,    81,    82,    82,    82,    82,    82,    82,    83,
      83,    85,    84,    84,    86,    87,    87,    88,    89,    90,
      91,    92,    93,    94,    95,    96,    97,    97
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     3,     3,     3,     3,     3,
       0,     5,     0,     5,     3,     3,     3,     3,     3,     3,
       1,     1,     3,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     3,     1,     3,     1,     2,     2,     1,
       3,     4,     3,     4,     4,     2,     6,     1,     1,     3,
       5,     3,     0,     2,     0,     1,     1,     3,     2,     5,
       3,     0,     1,     3,     0,     0,     1,     0,     2,     0,
       0,     5,     5,     1,     1,     1,     1,     1,     1,     2,
       0,     0,     4,     0,     4,     2,     5,     0,     0,     1,
       3,     5,     0,     0,     8,     8,     2,     3
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
#line 188 "src/parser/bison_parser.y"
        {
            // add code here
        }
#line 1434 "src/parser/acomp.c"
    break;

  case 3: /* statements: stmt statements  */
#line 195 "src/parser/bison_parser.y"
        {
            (yyval.stmtcont)->breaklist = mergelist((yyvsp[-1].stmtcont)->breaklist, (yyvsp[0].stmtcont)->breaklist);
            (yyval.stmtcont)->contlist = mergelist((yyvsp[-1].stmtcont)->contlist, (yyvsp[0].stmtcont)->contlist);
            (yyval.stmtcont)->retlist = mergelist((yyvsp[-1].stmtcont)->retlist, (yyvsp[0].stmtcont)->retlist);
        }
#line 1444 "src/parser/acomp.c"
    break;

  case 4: /* statements: %empty  */
#line 201 "src/parser/bison_parser.y"
        {
            make_stmt(&(yyval.stmtcont));
        }
#line 1452 "src/parser/acomp.c"
    break;

  case 5: /* stmt: expr PUNC_SEMIC  */
#line 208 "src/parser/bison_parser.y"
        {
            //TODO_PAP emit if boolexpr
            resettemp();
            make_stmt(&(yyval.stmtcont));

            // printExpression($1);
        }
#line 1464 "src/parser/acomp.c"
    break;

  case 6: /* stmt: ifstmt  */
#line 216 "src/parser/bison_parser.y"
        {
            make_stmt(&(yyval.stmtcont));
        }
#line 1472 "src/parser/acomp.c"
    break;

  case 7: /* stmt: whilestmt  */
#line 220 "src/parser/bison_parser.y"
        {
            make_stmt(&(yyval.stmtcont));
        }
#line 1480 "src/parser/acomp.c"
    break;

  case 8: /* stmt: forstmt  */
#line 224 "src/parser/bison_parser.y"
        {
            make_stmt(&(yyval.stmtcont));
        }
#line 1488 "src/parser/acomp.c"
    break;

  case 9: /* stmt: returnstmt  */
#line 228 "src/parser/bison_parser.y"
        {
            make_stmt(&(yyval.stmtcont));
            (yyval.stmtcont)->retlist = newlist((yyvsp[0].intVal));
        }
#line 1497 "src/parser/acomp.c"
    break;

  case 10: /* stmt: KEYW_BREAK PUNC_SEMIC  */
#line 233 "src/parser/bison_parser.y"
        {
            make_stmt(&(yyval.stmtcont));
            emit(jump, NULL, NULL, NULL, 0);
            (yyval.stmtcont)->breaklist = newlist(getNextQuad() - 1);

            if ( !loopcnt )
                print_static_analysis_error(yylineno, F_BOLD "break" F_RST " statement outside of loop\n");
        }
#line 1510 "src/parser/acomp.c"
    break;

  case 11: /* stmt: KEYW_CONT PUNC_SEMIC  */
#line 242 "src/parser/bison_parser.y"
        {
            make_stmt(&(yyval.stmtcont));
            emit(jump, NULL, NULL, NULL, 0);
            (yyval.stmtcont)->contlist = newlist(getNextQuad() - 1);

            if ( !loopcnt )
                print_static_analysis_error(yylineno, F_BOLD "continue" F_RST " statement outside of loop\n");
        }
#line 1523 "src/parser/acomp.c"
    break;

  case 12: /* stmt: block  */
#line 251 "src/parser/bison_parser.y"
        {
            (yyval.stmtcont) = (yyvsp[0].stmtcont);
        }
#line 1531 "src/parser/acomp.c"
    break;

  case 13: /* stmt: funcdef  */
#line 255 "src/parser/bison_parser.y"
        {
            make_stmt(&(yyval.stmtcont));
        }
#line 1539 "src/parser/acomp.c"
    break;

  case 14: /* stmt: PUNC_SEMIC  */
#line 259 "src/parser/bison_parser.y"
        {
            make_stmt(&(yyval.stmtcont));
        }
#line 1547 "src/parser/acomp.c"
    break;

  case 15: /* expr: expr OPER_PLUS expr  */
#line 266 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-2].expression)) || !arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            (yyval.expression) = newexpr(arithexpr_e);
            (yyval.expression)->sym = istempexpr((yyvsp[-2].expression)) ? (yyvsp[-2].expression)->sym : newtemp();
            emit(add,(yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), 0);
        }
#line 1559 "src/parser/acomp.c"
    break;

  case 16: /* expr: expr OPER_MINUS expr  */
#line 274 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-2].expression)) || !arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            (yyval.expression) = newexpr(arithexpr_e);
            (yyval.expression)->sym = istempexpr((yyvsp[-2].expression)) ? (yyvsp[-2].expression)->sym : newtemp();
            emit(sub,(yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), 0);
        }
#line 1571 "src/parser/acomp.c"
    break;

  case 17: /* expr: expr OPER_MUL expr  */
#line 282 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-2].expression)) || !arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            (yyval.expression) = newexpr(arithexpr_e);
            (yyval.expression)->sym = istempexpr((yyvsp[-2].expression)) ? (yyvsp[-2].expression)->sym : newtemp();
            emit(mul,(yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression),0);
        }
#line 1583 "src/parser/acomp.c"
    break;

  case 18: /* expr: expr OPER_DIV expr  */
#line 290 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-2].expression)) || !arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            if((yyvsp[0].expression)->type == constnum_e && (yyvsp[0].expression)->numConst == 0) 
                print_static_analysis_error(yylineno, "Division with 0 is not allowed.\n");
            
            (yyval.expression) = newexpr(arithexpr_e);
            (yyval.expression)->sym = istempexpr((yyvsp[-2].expression)) ? (yyvsp[-2].expression)->sym : newtemp();
            emit(div_o, (yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), 0);
        
        }
#line 1599 "src/parser/acomp.c"
    break;

  case 19: /* expr: expr OPER_MOD expr  */
#line 302 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-2].expression)) || !arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            (yyval.expression) = newexpr(arithexpr_e);
            (yyval.expression)->sym = istempexpr((yyvsp[-2].expression)) ? (yyvsp[-2].expression)->sym : newtemp();
            emit(mod,(yyval.expression), (yyvsp[-2].expression), (yyvsp[0].expression), 0);
        }
#line 1611 "src/parser/acomp.c"
    break;

  case 20: /* $@1: %empty  */
#line 309 "src/parser/bison_parser.y"
                    {if((yyvsp[-1].expression)->type!=boolexpr_e)(yyvsp[-1].expression) = evaluate((yyvsp[-1].expression));}
#line 1617 "src/parser/acomp.c"
    break;

  case 21: /* expr: expr KEYW_AND $@1 savepos expr  */
#line 310 "src/parser/bison_parser.y"
        {
            int additional_quads=0;
            if((yyvsp[0].expression)->type!=boolexpr_e){
                (yyvsp[0].expression) = evaluate((yyvsp[0].expression));
                // additional_quads+=2;
            }


            patch_list((yyvsp[-4].expression)->truelist, (yyvsp[-1].intVal)+additional_quads);
            (yyval.expression) = newexpr(boolexpr_e);
            (yyval.expression)->truelist = (yyvsp[0].expression)->truelist;
            (yyval.expression)->falselist = merge_bool_lists((yyvsp[-4].expression)->falselist, (yyvsp[0].expression)->falselist);
        }
#line 1635 "src/parser/acomp.c"
    break;

  case 22: /* $@2: %empty  */
#line 323 "src/parser/bison_parser.y"
                   {if((yyvsp[-1].expression)->type!=boolexpr_e)(yyvsp[-1].expression) = evaluate((yyvsp[-1].expression));}
#line 1641 "src/parser/acomp.c"
    break;

  case 23: /* expr: expr KEYW_OR $@2 savepos expr  */
#line 324 "src/parser/bison_parser.y"
        {
            int additional_quads=0;
            
            if((yyvsp[0].expression)->type!=boolexpr_e){
                (yyvsp[0].expression) = evaluate((yyvsp[0].expression));
                // additional_quads+=s2;
            }

            patch_list((yyvsp[-4].expression)->falselist, (yyvsp[-1].intVal)+additional_quads);
            (yyval.expression) = newexpr(boolexpr_e);
            (yyval.expression)->truelist = merge_bool_lists((yyvsp[-4].expression)->truelist, (yyvsp[0].expression)->truelist);
            (yyval.expression)->falselist = (yyvsp[0].expression)->falselist;
        }
#line 1659 "src/parser/acomp.c"
    break;

  case 24: /* expr: expr OPER_GRT expr  */
#line 338 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-2].expression)) || !arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            (yyval.expression) = newexpr(boolexpr_e);

            (yyval.expression)->truelist = getNextQuad();
            (yyval.expression)->falselist = getNextQuad() + 1;
            emit(if_greater, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), 0);
            emit(jump, NULL, NULL, NULL, 0);   
        }
#line 1674 "src/parser/acomp.c"
    break;

  case 25: /* expr: expr OPER_GRE expr  */
#line 349 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-2].expression)) || !arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            (yyval.expression) = newexpr(boolexpr_e);

            (yyval.expression)->truelist = getNextQuad();
            (yyval.expression)->falselist = getNextQuad() + 1;
            emit(if_greatereq, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), 0);
            emit(jump, NULL, NULL, NULL, 0);   
        }
#line 1689 "src/parser/acomp.c"
    break;

  case 26: /* expr: expr OPER_LET expr  */
#line 360 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-2].expression)) || !arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            (yyval.expression) = newexpr(boolexpr_e);

            (yyval.expression)->truelist = getNextQuad();
            (yyval.expression)->falselist = getNextQuad() + 1;
            emit(if_less, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
#line 1704 "src/parser/acomp.c"
    break;

  case 27: /* expr: expr OPER_LEE expr  */
#line 371 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-2].expression)) || !arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Both expressions must be arithmetic.\n");
            (yyval.expression) = newexpr(boolexpr_e);

            (yyval.expression)->truelist = getNextQuad();
            (yyval.expression)->falselist = getNextQuad() + 1;
            emit(if_lesseq, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
#line 1719 "src/parser/acomp.c"
    break;

  case 28: /* expr: expr OPER_EQ2 expr  */
#line 382 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr(boolexpr_e);

            (yyval.expression)->truelist = getNextQuad();
            (yyval.expression)->falselist = getNextQuad() + 1;
            emit(if_eq, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), 0);
            emit(jump, NULL, NULL, NULL, 0);
        }
#line 1732 "src/parser/acomp.c"
    break;

  case 29: /* expr: expr OPER_NEQ expr  */
#line 391 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr(boolexpr_e);

            (yyval.expression)->truelist = getNextQuad();
            (yyval.expression)->falselist = getNextQuad() + 1;
            emit(if_noteq, NULL, (yyvsp[-2].expression), (yyvsp[0].expression), 0);
            
            emit(jump, NULL, NULL, NULL, 0);
        }
#line 1746 "src/parser/acomp.c"
    break;

  case 30: /* expr: term  */
#line 401 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[0].expression);
        }
#line 1754 "src/parser/acomp.c"
    break;

  case 31: /* expr: assignexpr  */
#line 405 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[0].expression);
        }
#line 1762 "src/parser/acomp.c"
    break;

  case 32: /* term: PUNC_LPARENTH expr PUNC_RPARENTH  */
#line 424 "src/parser/bison_parser.y"
        {
            //TODO_PAP emit if boolexpr (???)
            // $$ = emit_eval($2);
            (yyval.expression)=(yyvsp[-1].expression);
        }
#line 1772 "src/parser/acomp.c"
    break;

  case 33: /* term: OPER_MINUS expr  */
#line 430 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");
            (yyval.expression) = newexpr(arithexpr_e);
            (yyval.expression)->sym = istempexpr((yyvsp[0].expression))? (yyvsp[0].expression)->sym : newtemp();
            emit(uminus, (yyval.expression), (yyvsp[0].expression), NULL, 0);
        }
#line 1784 "src/parser/acomp.c"
    break;

  case 34: /* term: KEYW_NOT expr  */
#line 438 "src/parser/bison_parser.y"
        {
            // In this approach, if expr is a boolexpr, flip the lists, otherwise tag it and let the other reductions handle it
            // if($2->type == boolexpr_e){
            //     $$ = $2;
                
            //     int temptruelist  = $2->falselist;
            //     int tempfalselist = $2->truelist;
            
            //     $$->truelist    = tempfalselist;
            //     $$->falselist   = temptruelist;
            // }else
            //     $$ = $2;
            //     $$ -> nottag=1;

            // INITIAL APPROACH: we changed it because this way if the stack has expr and not expr, not expr is reduced and emited.
            // This way the second part of the end is evaluated first, wich is wrong

            // if($2->type != boolexpr_e){
            //     $2 = evaluate($2);
            // }   

            if((yyvsp[0].expression)->type!=boolexpr_e){
                (yyvsp[0].expression) = evaluate((yyvsp[0].expression));
            }
            (yyval.expression) = (yyvsp[0].expression);
            
            int temptruelist  = (yyvsp[0].expression)->truelist;
            int tempfalselist = (yyvsp[0].expression)->falselist;
        
            (yyval.expression)->truelist    = tempfalselist;
            (yyval.expression)->falselist   = temptruelist;
        }
#line 1821 "src/parser/acomp.c"
    break;

  case 35: /* term: OPER_PLUS2 lvalue  */
#line 471 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");

            char *name = (yyvsp[0].expression)->strConst;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);


            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "++%s" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "++%s" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                (yyvsp[0].expression)->sym = res;


            if ( (yyvsp[0].expression)->type == tableitem_e ) {

                (yyval.expression) = emit_iftableitem((yyvsp[0].expression));
                emit(add, (yyval.expression), (yyval.expression), newexpr_constnum(1), 0);
                emit(tablesetelem, (yyval.expression), (yyvsp[0].expression), (yyvsp[0].expression)->index, 0);
            }
            else {

                emit(add, (yyvsp[0].expression), newexpr_constnum(1), (yyvsp[0].expression), 0);
                (yyval.expression) = (yyvsp[0].expression);
            }
        }
#line 1854 "src/parser/acomp.c"
    break;

  case 36: /* term: lvalue OPER_PLUS2  */
#line 500 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-1].expression)))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");            
            
            char *name = (yyvsp[-1].expression)->strConst;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);


            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                (yyvsp[-1].expression)->sym = res;


            (yyval.expression) = newexpr(arithexpr_e);
            (yyval.expression)->sym = newtemp();

            if ( (yyvsp[-1].expression)->type == tableitem_e ) {

                struct expr *val = emit_iftableitem((yyvsp[-1].expression));

                emit(assign, (yyval.expression), val, NULL, 0);
                emit(add, val, newexpr_constnum(1), val, 0);
                emit(tablesetelem, val, (yyvsp[-1].expression), (yyvsp[-1].expression)->index, 0);
            }
            else {

                emit(assign, (yyval.expression), (yyvsp[-1].expression), NULL, 0);
                emit(add, (yyvsp[-1].expression), newexpr_constnum(1), (yyvsp[-1].expression), 0);
            }
        }
#line 1892 "src/parser/acomp.c"
    break;

  case 37: /* term: OPER_MINUS2 lvalue  */
#line 534 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[0].expression)))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");
            
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, (yyvsp[0].expression)->sym->name, scope);
            

            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "--%s" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, (yyvsp[0].expression)->sym->name, (yyvsp[0].expression)->sym->name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "--%s" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, (yyvsp[0].expression)->sym->name, (yyvsp[0].expression)->sym->name);
            else
                (yyvsp[0].expression)->sym = res;
            

            if((yyvsp[0].expression)->type==tableitem_e) {
                (yyval.expression) = emit_iftableitem((yyvsp[0].expression));
                emit(sub, (yyval.expression), (yyval.expression), newexpr_constnum(1), 0);
                emit(tablesetelem, (yyval.expression), (yyvsp[0].expression), (yyvsp[0].expression)->index,0);
            }else{
                emit(sub, (yyvsp[0].expression), (yyvsp[0].expression), newexpr_constnum(1), 0);
                (yyval.expression) = (yyvsp[0].expression);
            }
        }
#line 1921 "src/parser/acomp.c"
    break;

  case 38: /* term: lvalue OPER_MINUS2  */
#line 559 "src/parser/bison_parser.y"
        {
            if(!arithexpr_check((yyvsp[-1].expression)))
                print_static_analysis_error(yylineno, "Expression must be arithmetic.\n");

            char *name = (yyvsp[-1].expression)->strConst;
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);
            
            if ( !res )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is undefined\n" F_RST, name, name);
            else if ( res->type == LIBFUNC || res->type == USERFUNC )
                print_static_analysis_error(yylineno, "Operation" F_BOLD "%s++" F_RST " not allowed." F_BOLD "%s is a function\n" F_RST, name, name);
            else
                (yyvsp[-1].expression)->sym = res;


            (yyval.expression) = newexpr(arithexpr_e);
            (yyval.expression)->sym = newtemp();

            if( (yyvsp[-1].expression)->type == tableitem_e ) {

                struct expr *val = emit_iftableitem((yyvsp[-1].expression));

                emit(assign, (yyval.expression), val, NULL, 0);
                emit(sub, val, val, newexpr_constnum(1), 0);
                emit(tablesetelem, val, (yyvsp[-1].expression), (yyvsp[-1].expression)->index, 0);
            }
            else{

                emit(assign,(yyval.expression),(yyvsp[-1].expression),NULL,0);
                emit(sub, (yyvsp[-1].expression), (yyvsp[-1].expression), newexpr_constnum(1),0);
            }
        }
#line 1958 "src/parser/acomp.c"
    break;

  case 39: /* term: primary  */
#line 592 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[0].expression);
        }
#line 1966 "src/parser/acomp.c"
    break;

  case 40: /* primary: lvalue  */
#line 599 "src/parser/bison_parser.y"
        {
            if ( (yyvsp[0].expression)->type == var_e ) {

                if ( ((yyvsp[0].expression)->sym->type == LOCAL || (yyvsp[0].expression)->sym->type == FORMAL) && (yyvsp[0].expression)->sym->scope > scope )
                    print_static_analysis_error(yylineno, "Symbol %s cannot be accessed from scope %d\n", (yyvsp[0].expression)->strConst, scope);
                // else if ( $1->sym->type == USERFUNC || $1->sym->type == LIBFUNC )
                //     print_static_analysis_error(yylineno, "Symbol %s is defined as a function\n", $1->strConst);
                else {

                    (yyval.expression) = (yyvsp[0].expression);
                    (yyval.expression)->sym = (yyvsp[0].expression)->sym;
                }
            }
        }
#line 1985 "src/parser/acomp.c"
    break;

  case 41: /* primary: call  */
#line 614 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[0].expression);
        }
#line 1993 "src/parser/acomp.c"
    break;

  case 42: /* primary: objectdef  */
#line 618 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[0].expression);
        }
#line 2001 "src/parser/acomp.c"
    break;

  case 43: /* primary: PUNC_LPARENTH funcdef PUNC_RPARENTH  */
#line 622 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr(programfunc_e);
            (yyval.expression)->sym = (yyvsp[-1].symbol);
        }
#line 2010 "src/parser/acomp.c"
    break;

  case 44: /* primary: const  */
#line 627 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[0].expression);
        }
#line 2018 "src/parser/acomp.c"
    break;

  case 45: /* assignexpr: lvalue OPER_EQ expr  */
#line 634 "src/parser/bison_parser.y"
        {
            if ( (yyvsp[-2].expression)->type == tableitem_e ) {

                emit(tablesetelem, (yyvsp[0].expression), (yyvsp[-2].expression), (yyvsp[-2].expression)->index, 0);
                (yyval.expression) = emit_iftableitem((yyvsp[-2].expression));
                (yyval.expression)->type = var_e;//It was assignexpr_e but there is no reason for that
            }
            else {

                if((yyvsp[0].expression)->type==boolexpr_e){
                    (yyvsp[0].expression) = emit_eval((yyvsp[0].expression));
                }
                

                // TODO: refactor code - avoid duplication
                
                if ( ref_flag == REF_LOCAL ) {

                    
                    if ( (yyvsp[-2].expression)->sym->scope < scope )
                        print_static_analysis_error(yylineno, "Symbol %s can't be accessed from scope %d\n", (yyvsp[-2].expression)->strConst, scope);
                    else if ( (yyvsp[-2].expression)->sym->type == USERFUNC || (yyvsp[-2].expression)->sym->type == LIBFUNC )
                        print_static_analysis_error(yylineno, "Symbol %s defined as a function\n", (yyvsp[-2].expression)->strConst);
                    else if ( (yyvsp[-2].expression)->sym->type == FORMAL && (yyvsp[-2].expression)->sym->scope != scope )
                        print_static_analysis_error(yylineno, "Symbol %s can't be accessed from scope %d\n", (yyvsp[-2].expression)->strConst, scope);
                }
                else {  //ID
                    if ( ((yyvsp[-2].expression)->sym->type == LOCAL || (yyvsp[-2].expression)->sym->type == FORMAL) && (yyvsp[-2].expression)->sym->scope != scope )
                        print_static_analysis_error(yylineno, "Accessing " F_BOLD "%s" F_RST " from scope %d\n", (yyvsp[-2].expression)->strConst, scope);
                    else if ( (yyvsp[-2].expression)->sym->type == USERFUNC || (yyvsp[-2].expression)->sym->type == LIBFUNC )
                        print_static_analysis_error(yylineno, F_BOLD "%s" F_RST " is defined as a function\n", (yyvsp[-2].expression)->strConst);
                }

                emit(assign, (yyvsp[-2].expression), emit_iftableitem((yyvsp[0].expression)), NULL, 0U);
                (yyval.expression) = newexpr(var_e);//It was assignexpr_e but there is no reason for thatexpr_e
                (yyval.expression)->sym = newtemp();
                emit(assign, (yyval.expression), (yyvsp[-2].expression), NULL, 0U);
                ref_flag = REF_NONE;               
            }
        }
#line 2063 "src/parser/acomp.c"
    break;

  case 46: /* lvalue: ID  */
#line 678 "src/parser/bison_parser.y"
        {
            struct SymbolTableEntry* e = SymTable_lookup_all_scopes(st, (yyvsp[0].strVal), scope); 
            if(!e) {
                e = SymTable_insert(st, (yyvsp[0].strVal), (!prog_var_flag ? GLOBAL : LOCAL), scope, yylineno);
                e->offset = offset++;
            }

            if(e->type==USERFUNC){
                (yyval.expression) = newexpr(programfunc_e);
            }else if(e->type==LIBFUNC){
                (yyval.expression) = newexpr(libraryfunc_e);
            }else{
                (yyval.expression) = newexpr(var_e);
                ref_flag = REF_NONE; 
                (yyval.expression)->strConst = strdup((yyvsp[0].strVal));
            }
            (yyval.expression)->sym = e;
        }
#line 2086 "src/parser/acomp.c"
    break;

  case 47: /* lvalue: KEYW_LOCAL ID  */
#line 697 "src/parser/bison_parser.y"
        {
            struct SymbolTableEntry* e = SymTable_lookup_all_scopes(st, (yyvsp[0].strVal), scope); 
            if(!e) {
                e = SymTable_insert(st, (yyvsp[0].strVal), LOCAL, scope, yylineno);
                e->offset = offset++;
            }
            
            if(e->type==userfunc_a){
                (yyval.expression) = newexpr(programfunc_e);
            }else if(e->type==libfunc_a){
                (yyval.expression) = newexpr(libfunc_a);
            }else{
                (yyval.expression) = newexpr(var_e);
                ref_flag = REF_LOCAL;
                (yyval.expression)->strConst = strdup((yyvsp[0].strVal));
            }
            (yyval.expression)->sym = e;
        }
#line 2109 "src/parser/acomp.c"
    break;

  case 48: /* lvalue: PUNC_COLON2 ID  */
#line 716 "src/parser/bison_parser.y"
        {

            struct SymbolTableEntry* e = SymTable_lookup_all_scopes(st, (yyvsp[0].strVal), scope); 
            if(!e) {
                e = SymTable_insert(st, (yyvsp[0].strVal), GLOBAL, scope, yylineno);
                e->offset = offset++;
            }

            if(e->type==userfunc_a){
                (yyval.expression) = newexpr(programfunc_e);
            }else if(e->type==libfunc_a){
                (yyval.expression) = newexpr(libraryfunc_e);
            }else{
                (yyval.expression) = newexpr(var_e);
                ref_flag = REF_GLOBAL;
                (yyval.expression)->strConst = strdup((yyvsp[0].strVal));
            }
            (yyval.expression)->sym = e;
        }
#line 2133 "src/parser/acomp.c"
    break;

  case 49: /* lvalue: member  */
#line 736 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[0].expression);
        }
#line 2141 "src/parser/acomp.c"
    break;

  case 50: /* member: lvalue PUNC_DOT ID  */
#line 743 "src/parser/bison_parser.y"
        {
            if ( (yyvsp[-2].expression)->type == var_e )
                (yyvsp[-2].expression)->sym = SymTable_lookup_add(st, (yyvsp[-2].expression)->strConst, -1, scope, yylineno);

            (yyval.expression) = member_item((yyvsp[-2].expression), newexpr_conststr((yyvsp[0].strVal)));
        }
#line 2152 "src/parser/acomp.c"
    break;

  case 51: /* member: lvalue PUNC_LBRACKET expr PUNC_RBRACKET  */
#line 750 "src/parser/bison_parser.y"
        {
            if ( (yyvsp[-3].expression)->type == var_e )
                (yyvsp[-3].expression)->sym = SymTable_lookup_add(st, (yyvsp[-3].expression)->strConst, -1, scope, yylineno);
            // else
            //     print_static_analysis_error(yylineno, "%s is not a variable\n", $1->sym->name);
            (yyval.expression) = member_item((yyvsp[-3].expression), (yyvsp[-1].expression));
        }
#line 2164 "src/parser/acomp.c"
    break;

  case 52: /* member: call PUNC_DOT ID  */
#line 758 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[-2].expression);
        }
#line 2172 "src/parser/acomp.c"
    break;

  case 53: /* member: call PUNC_LBRACKET expr PUNC_RBRACKET  */
#line 762 "src/parser/bison_parser.y"
        {
            //TODO_ERRORS check expr type
            (yyval.expression) = (yyvsp[-3].expression);
        }
#line 2181 "src/parser/acomp.c"
    break;

  case 54: /* call: call PUNC_LPARENTH elist PUNC_RPARENTH  */
#line 770 "src/parser/bison_parser.y"
        {
            (yyval.expression) = make_call((yyvsp[-3].expression), (yyvsp[-1].expression));
        }
#line 2189 "src/parser/acomp.c"
    break;

  case 55: /* call: lvalue callsuffix  */
#line 774 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr(nil_e);
            
            // if($1->type!=programfunc_e && $1->type!=libraryfunc_e){
            //     print_static_analysis_error(yylineno, F_BOLD "%s" F_RST " is not a function\n", $1->strConst);
            // }else{   
            
                struct SymbolTableEntry * e;
                if(!istempname((yyvsp[-1].expression)->sym))
                    e = SymTable_lookup_all_scopes(st, (yyvsp[-1].expression)->sym->name, scope);
                else
                    e = (yyvsp[-1].expression)->sym;

                if ( !e )
                    print_static_analysis_error(yylineno, "Symbol %s is not defined\n", (yyvsp[-1].expression)->strConst);
                else if ( e->type == LOCAL && e->scope != scope )
                    print_static_analysis_error(yylineno, "Symbol %s cannot be accessed from scope %d\n", (yyvsp[-1].expression)->strConst,scope);  // TODO: ask the fellas
                // else if ( !istempname(e) && (e->type != USERFUNC && e->type != LIBFUNC) )
                //     print_static_analysis_error(yylineno, F_BOLD "%s" F_RST " is not a function\n", $1->strConst);
                else {

                    (yyvsp[-1].expression)->sym = e;
                    (yyvsp[-1].expression) = emit_iftableitem((yyvsp[-1].expression));

                    if ( (yyvsp[0].functcont)->method ) {

                        struct expr *t = (yyvsp[-1].expression);

                        (yyvsp[-1].expression) = emit_iftableitem(member_item(t, newexpr_conststr((yyvsp[0].functcont)->name)));
                        (yyvsp[0].functcont)->elist->next = t;
                    }


                    (yyval.expression) = make_call((yyvsp[-1].expression), (yyvsp[0].functcont)->elist);
                // }
            }

            if( (yyval.expression)->type == nil_e ) {
                print_static_analysis_error(yylineno, "Function %s is not defined\n", (yyvsp[-1].expression)->strConst);
            }
        }
#line 2235 "src/parser/acomp.c"
    break;

  case 56: /* call: PUNC_LPARENTH funcdef PUNC_RPARENTH PUNC_LPARENTH elist PUNC_RPARENTH  */
#line 816 "src/parser/bison_parser.y"
        {
            struct expr* func = newexpr(programfunc_e);

            func->sym = (yyvsp[-4].symbol);
            (yyval.expression)=make_call(func, (yyvsp[-1].expression));
        }
#line 2246 "src/parser/acomp.c"
    break;

  case 57: /* callsuffix: normcall  */
#line 826 "src/parser/bison_parser.y"
        {
            (yyval.functcont) = (yyvsp[0].functcont);
        }
#line 2254 "src/parser/acomp.c"
    break;

  case 58: /* callsuffix: methodcall  */
#line 830 "src/parser/bison_parser.y"
        {
            (yyval.functcont) = (yyvsp[0].functcont);
        }
#line 2262 "src/parser/acomp.c"
    break;

  case 59: /* normcall: PUNC_LPARENTH elist PUNC_RPARENTH  */
#line 837 "src/parser/bison_parser.y"
        {
            (yyval.functcont) = malloc(sizeof(struct function_contents));
            (yyval.functcont)->elist = (yyvsp[-1].expression);
            (yyval.functcont)->method = 0;
            (yyval.functcont)->name = NULL;
        }
#line 2273 "src/parser/acomp.c"
    break;

  case 60: /* methodcall: PUNC_DOT2 ID PUNC_LPARENTH elist PUNC_RPARENTH  */
#line 846 "src/parser/bison_parser.y"
        {
            (yyval.functcont)=malloc(sizeof(struct function_contents));
            (yyval.functcont)->elist = (yyvsp[-1].expression);
            (yyval.functcont)->method = 1;
            (yyval.functcont)->name = (yyvsp[-3].strVal);
        }
#line 2284 "src/parser/acomp.c"
    break;

  case 61: /* elistrep: PUNC_COMMA expr elistrep  */
#line 856 "src/parser/bison_parser.y"
        {
            //TODO_PAP emit if boolexpr_e
            (yyvsp[-1].expression) = emit_eval((yyvsp[-1].expression));
            (yyval.expression) = (yyvsp[-1].expression);
            (yyval.expression)->next = (yyvsp[0].expression);
        }
#line 2295 "src/parser/acomp.c"
    break;

  case 62: /* elistrep: %empty  */
#line 863 "src/parser/bison_parser.y"
        {
            (yyval.expression) = NULL;
        }
#line 2303 "src/parser/acomp.c"
    break;

  case 63: /* elist: expr elistrep  */
#line 870 "src/parser/bison_parser.y"
        {
            //TODO_PAP emit if boolexpr_e
            if((yyvsp[-1].expression)->type==boolexpr_e)
                (yyvsp[-1].expression) = emit_eval((yyvsp[-1].expression));
            (yyvsp[-1].expression)->next = (yyvsp[0].expression);
            (yyval.expression) = (yyvsp[-1].expression);
        }
#line 2315 "src/parser/acomp.c"
    break;

  case 64: /* elist: %empty  */
#line 878 "src/parser/bison_parser.y"
        {
            (yyval.expression) = NULL;
        }
#line 2323 "src/parser/acomp.c"
    break;

  case 65: /* objectin: elist  */
#line 885 "src/parser/bison_parser.y"
        {
            struct expr * t  = newexpr(newtable_e);
            struct expr * itter = (yyvsp[0].expression);


            if ( (yyvsp[0].expression) )
                t->sym = istempexpr((yyvsp[0].expression)) ? (yyvsp[0].expression)->sym : newtemp();
            else
                t->sym = newtemp();

            emit(tablecreate, t, NULL, NULL, 0);

            for (uint i = 0U; itter; itter = itter->next, ++i)
                emit(tablesetelem, itter, t, newexpr_constnum(i), 0U);

            (yyval.expression) = t;
        }
#line 2345 "src/parser/acomp.c"
    break;

  case 66: /* objectin: indexed  */
#line 903 "src/parser/bison_parser.y"
        { 
            struct expr *t = newexpr(newtable_e);
            struct expr *itter = (yyvsp[0].expression);


            t->sym = newtemp();
            emit(tablecreate, t, NULL, NULL, 0);
            for (int i = 0; itter; itter = itter->next, ++i)
                emit(tablesetelem, itter, t, itter->index, 0);

            (yyval.expression)=t;
        }
#line 2362 "src/parser/acomp.c"
    break;

  case 67: /* objectdef: PUNC_LBRACKET objectin PUNC_RBRACKET  */
#line 919 "src/parser/bison_parser.y"
        { 
            (yyval.expression) = (yyvsp[-1].expression); 
        }
#line 2370 "src/parser/acomp.c"
    break;

  case 68: /* indexed: indexedelem indexrep  */
#line 926 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[-1].expression);
            (yyval.expression)->next = (yyvsp[0].expression);
        }
#line 2379 "src/parser/acomp.c"
    break;

  case 69: /* indexedelem: PUNC_LBRACE expr PUNC_COLON expr PUNC_RBRACE  */
#line 934 "src/parser/bison_parser.y"
        {
            //TODO_PAP emit if expr2 boolexpr_e
            // printExpression($2);
            // printExpression($4);
            (yyvsp[-1].expression) = emit_eval((yyvsp[-1].expression));
            //TODO_ERRORS check expr1 type
            (yyval.expression) = (yyvsp[-1].expression);
            (yyval.expression)->index = (yyvsp[-3].expression);
        }
#line 2393 "src/parser/acomp.c"
    break;

  case 70: /* indexrep: PUNC_COMMA indexedelem indexrep  */
#line 947 "src/parser/bison_parser.y"
        {
            (yyval.expression) = (yyvsp[-1].expression);
            (yyval.expression)->next = (yyvsp[0].expression);
        }
#line 2402 "src/parser/acomp.c"
    break;

  case 71: /* indexrep: %empty  */
#line 952 "src/parser/bison_parser.y"
        {
            (yyval.expression) = NULL;
        }
#line 2410 "src/parser/acomp.c"
    break;

  case 72: /* blockprefix: PUNC_LBRACE  */
#line 959 "src/parser/bison_parser.y"
        {
            ++scope;

            if ( current_function ) {

                Stack_push(offset_stack, offset);
                offset = 0;
            }
        }
#line 2424 "src/parser/acomp.c"
    break;

  case 73: /* block: blockprefix statements PUNC_RBRACE  */
#line 972 "src/parser/bison_parser.y"
        {
            if ( current_function ) {

                SymTable_hide(st, scope);
                Stack_pop(offset_stack, &offset);
            }

            --scope;
            (yyval.stmtcont) = (yyvsp[-1].stmtcont);
        }
#line 2439 "src/parser/acomp.c"
    break;

  case 74: /* funcstart: %empty  */
#line 985 "src/parser/bison_parser.y"
    {
        Stack_push(loopcnt_stack, loopcnt);
        loopcnt = 0;
    }
#line 2448 "src/parser/acomp.c"
    break;

  case 75: /* funcend: %empty  */
#line 991 "src/parser/bison_parser.y"
    {
        Stack_pop(loopcnt_stack, &loopcnt);
    }
#line 2456 "src/parser/acomp.c"
    break;

  case 76: /* funcname: ID  */
#line 998 "src/parser/bison_parser.y"
        {
            (yyval.strVal) = (yyvsp[0].strVal);
        }
#line 2464 "src/parser/acomp.c"
    break;

  case 77: /* funcname: %empty  */
#line 1002 "src/parser/bison_parser.y"
        {
            char *name = getFuncName();
            (yyval.strVal) = strdup(name);
        }
#line 2473 "src/parser/acomp.c"
    break;

  case 78: /* funcprefix: KEYW_FUNC funcname  */
#line 1010 "src/parser/bison_parser.y"
        {
            char *name = (yyvsp[0].strVal);
            current_function = (yyvsp[0].strVal);
            struct SymbolTableEntry *res = SymTable_lookup_all_scopes(st, name, scope);

            if ( res && res->scope >= scope ) {

                print_static_analysis_error(yylineno, "Symbol " F_BOLD "%s" " already exists\n", name);
                (yyval.symbol) = NULL;
            }
            else {

                (yyval.symbol) = SymTable_insert(st, name, USERFUNC, scope, yylineno);

                struct expr* newfunc= newexpr(programfunc_e);
                newfunc->sym = (yyval.symbol);
                emit(funcstart, NULL, newfunc, NULL, 0);
            }
        }
#line 2497 "src/parser/acomp.c"
    break;

  case 79: /* $@3: %empty  */
#line 1033 "src/parser/bison_parser.y"
        {
            ++scope;
            Stack_push(offset_stack, offset);
            offset = 0UL;
            prog_var_flag = 1;
        }
#line 2508 "src/parser/acomp.c"
    break;

  case 80: /* $@4: %empty  */
#line 1040 "src/parser/bison_parser.y"
        {
            --scope;
            Stack_pop(offset_stack, &offset);
        }
#line 2517 "src/parser/acomp.c"
    break;

  case 82: /* funcdef: funcprefix funcstart funcargs block funcend  */
#line 1048 "src/parser/bison_parser.y"
        {
            // if ( ($$ = $1) )
            struct expr* funcending = newexpr(programfunc_e);
            funcending->sym = (yyvsp[-4].symbol);

            patch_list((yyvsp[-1].stmtcont)->retlist,getNextQuad());
            emit(funcend, NULL, funcending, NULL, 0);

            current_function = NULL;
            prog_var_flag = 0;
        }
#line 2533 "src/parser/acomp.c"
    break;

  case 83: /* const: CONST_INT  */
#line 1063 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr_constnum((double)(yylval.intVal));
        }
#line 2541 "src/parser/acomp.c"
    break;

  case 84: /* const: CONST_REAL  */
#line 1067 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr_constnum(yylval.realVal);
        }
#line 2549 "src/parser/acomp.c"
    break;

  case 85: /* const: STRING  */
#line 1071 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr_conststr((yyvsp[0].strVal));
        }
#line 2557 "src/parser/acomp.c"
    break;

  case 86: /* const: KEYW_NIL  */
#line 1075 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr(nil_e);
        }
#line 2565 "src/parser/acomp.c"
    break;

  case 87: /* const: KEYW_TRUE  */
#line 1079 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr_constbool(1);
        }
#line 2573 "src/parser/acomp.c"
    break;

  case 88: /* const: KEYW_FALSE  */
#line 1083 "src/parser/bison_parser.y"
        {
            (yyval.expression) = newexpr_constbool(0);
        }
#line 2581 "src/parser/acomp.c"
    break;

  case 89: /* idlist: ID ids  */
#line 1090 "src/parser/bison_parser.y"
        {
            char * name = (yyvsp[-1].strVal);
            struct SymbolTableEntry * res = SymTable_lookup_scope(st, name, scope);


            if ( !checkIfAllowed(name) )
                print_static_analysis_error(yylineno, "argument \e[1m%s\e[0m of function \e[1m%s\e[0m has the same name as an alpha_library_function\n",\
                            name, current_function);
            else {

                if ( res )
                    print_static_analysis_error(yylineno, "FORMAL variable '%s' has the same name as another FORMAL argument\n", name);
                else {

                    res = SymTable_insert(st, name, FORMAL, scope, yylineno);
                    res->offset = offset++;

                    SymTable_insert_func_arg(st, current_function, name);
                }
            }
        }
#line 2607 "src/parser/acomp.c"
    break;

  case 91: /* $@5: %empty  */
#line 1116 "src/parser/bison_parser.y"
        {
            char *name = (yyvsp[0].strVal);
            struct SymbolTableEntry *res = SymTable_lookup_scope(st, name, scope);


            if ( !checkIfAllowed(name) )
                print_static_analysis_error(yylineno, "argument \e[1m%s\e[0m of function \e[1m%s\e[0m has the same name as an alpha_library_function\n",\
                            name, current_function);
            else {

                if ( res )
                    print_static_analysis_error(yylineno, "Formal variable '%s' has the same name as another formal variable!\n");
                else {

                    res = SymTable_insert(st, name, FORMAL, scope, yylineno);
                    res->offset = offset++;

                    SymTable_insert_func_arg(st, current_function, name);
                }
            }
        }
#line 2633 "src/parser/acomp.c"
    break;

  case 92: /* ids: PUNC_COMMA ID $@5 ids  */
#line 1138 "src/parser/bison_parser.y"
        {
            // add code here
        }
#line 2641 "src/parser/acomp.c"
    break;

  case 93: /* ids: %empty  */
#line 1142 "src/parser/bison_parser.y"
        {
            // add code here
        }
#line 2649 "src/parser/acomp.c"
    break;

  case 94: /* ifprefix: KEYW_IF PUNC_LPARENTH expr PUNC_RPARENTH  */
#line 1149 "src/parser/bison_parser.y"
        {
            //TODO_PAP emit if boolexpr -> evlauate expr
            struct expr* evaluated_expr = emit_eval((yyvsp[-1].expression));
            emit(if_eq, NULL, evaluated_expr, newexpr_constbool(1), currQuad + 2);
            (yyval.intVal) = currQuad;
            emit(jump,NULL,NULL,NULL,0);
        }
#line 2661 "src/parser/acomp.c"
    break;

  case 95: /* ifstmt: ifprefix stmt  */
#line 1160 "src/parser/bison_parser.y"
        {
            patch_label((yyvsp[-1].intVal), currQuad);
        }
#line 2669 "src/parser/acomp.c"
    break;

  case 96: /* ifstmt: ifprefix stmt KEYW_ELSE jumpandsavepos stmt  */
#line 1164 "src/parser/bison_parser.y"
        {
            patch_label((yyvsp[-4].intVal), (yyvsp[-1].intVal)+1);
            patch_label((yyvsp[-1].intVal), currQuad);
        }
#line 2678 "src/parser/acomp.c"
    break;

  case 97: /* loopstart: %empty  */
#line 1171 "src/parser/bison_parser.y"
    {
        ++loopcnt;
    }
#line 2686 "src/parser/acomp.c"
    break;

  case 98: /* loopend: %empty  */
#line 1176 "src/parser/bison_parser.y"
    {
        --loopcnt;
    }
#line 2694 "src/parser/acomp.c"
    break;

  case 99: /* whilestart: KEYW_WHILE  */
#line 1182 "src/parser/bison_parser.y"
        {
            (yyval.intVal) = getNextQuad();
        }
#line 2702 "src/parser/acomp.c"
    break;

  case 100: /* whilecond: PUNC_LPARENTH expr PUNC_RPARENTH  */
#line 1188 "src/parser/bison_parser.y"
        {
            //TODO_PAP emit if boolexpr_e -> evaluate expr
            struct expr* evaluated_expr = emit_eval((yyvsp[-1].expression));
            emit(if_eq, NULL, evaluated_expr, newexpr_constbool(1), getNextQuad() + 2U);
            (yyval.intVal) = getNextQuad();
            emit(jump, NULL, NULL, NULL, 0);
        }
#line 2714 "src/parser/acomp.c"
    break;

  case 101: /* whilestmt: whilestart loopstart whilecond stmt loopend  */
#line 1198 "src/parser/bison_parser.y"
        {
            emit(jump, NULL, NULL, NULL, (yyvsp[-4].intVal));
            patch_label((yyvsp[-2].intVal), getNextQuad());
            
            patch_list((yyvsp[-1].stmtcont)->breaklist, getNextQuad());
            patch_list((yyvsp[-1].stmtcont)->contlist, (yyvsp[-4].intVal));
        }
#line 2726 "src/parser/acomp.c"
    break;

  case 102: /* jumpandsavepos: %empty  */
#line 1208 "src/parser/bison_parser.y"
    {
        (yyval.intVal) = getNextQuad();
        emit(jump, NULL, NULL, NULL, 0);
    }
#line 2735 "src/parser/acomp.c"
    break;

  case 103: /* savepos: %empty  */
#line 1215 "src/parser/bison_parser.y"
    {
        (yyval.intVal) = getNextQuad();
    }
#line 2743 "src/parser/acomp.c"
    break;

  case 104: /* forprefix: KEYW_FOR loopstart PUNC_LPARENTH elist savepos PUNC_SEMIC expr PUNC_SEMIC  */
#line 1222 "src/parser/bison_parser.y"
        {   
            //TODO_PAP emit if boolexpr_e -> evaluate expr
            struct expr* evaluated_expr = emit_eval((yyvsp[-1].expression));
            
            (yyval.forcont) = malloc(sizeof(struct for_contents));
            (yyval.forcont)->test = (yyvsp[-3].intVal);
            (yyval.forcont)->enter = getNextQuad();
            
            emit(if_eq, NULL, evaluated_expr, newexpr_constbool(1), 0);
        }
#line 2758 "src/parser/acomp.c"
    break;

  case 105: /* forstmt: forprefix jumpandsavepos elist PUNC_RPARENTH jumpandsavepos stmt jumpandsavepos loopend  */
#line 1236 "src/parser/bison_parser.y"
        {
            patch_label((yyvsp[-7].forcont)->enter, (yyvsp[-3].intVal) + 1);
            patch_label((yyvsp[-6].intVal), getNextQuad());
            patch_label((yyvsp[-3].intVal), (yyvsp[-7].forcont)->test);
            patch_label((yyvsp[-1].intVal), (yyvsp[-6].intVal) + 1);

            patch_list((yyvsp[-2].stmtcont)->breaklist, getNextQuad());
            patch_list((yyvsp[-2].stmtcont)->contlist, (yyvsp[-6].intVal) + 1);
        }
#line 2772 "src/parser/acomp.c"
    break;

  case 106: /* returnstmt: KEYW_RET PUNC_SEMIC  */
#line 1249 "src/parser/bison_parser.y"
        {
            if ( !prog_var_flag )
                print_static_analysis_error(yylineno, "return statement outside of function\n");

            emit(ret, NULL, NULL, NULL, 0);
            (yyval.intVal) = currQuad;
            emit(jump,NULL,NULL,NULL, 0);

        }
#line 2786 "src/parser/acomp.c"
    break;

  case 107: /* returnstmt: KEYW_RET expr PUNC_SEMIC  */
#line 1259 "src/parser/bison_parser.y"
        {
            (yyvsp[-1].expression) = emit_eval((yyvsp[-1].expression));
            if ( !prog_var_flag )
                print_static_analysis_error(yylineno, "return statement outside of function\n");

            emit(ret, NULL, (yyvsp[-1].expression), NULL, 0);
            (yyval.intVal) = currQuad;
            emit(jump,NULL,NULL,NULL, 0);
        }
#line 2800 "src/parser/acomp.c"
    break;


#line 2804 "src/parser/acomp.c"

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

#line 1270 "src/parser/bison_parser.y"


void yyerror(const char *yaccerror){
    print_static_analysis_error(yylineno, "ERROR: %s\n", yaccerror);
}

int main(int argc, char **argv) {

    int index;
    yydebug = 1;

    if ( argc != 2 ) {

        printf("\e[1;31merror\e[0m: no input file\n");
        return 0;
    }

    if ( !(yyin = fopen(argv[1], "r")) ) {

        perror("fopen()");
        return 1;
    }

    assert( (st = SymTable_create()) );
    assert( (offset_stack = Stack_create()) );
    assert( (loopcnt_stack = Stack_create()) );
    assert( (quads = quadtable_create()) );
    initFile();

    yyparse();

    if( produce_icode )
        print_quads();

    // SymTable_print_all(st);
    /* SymTable_print_scopes(st); */

    /* generate();
    print_readable_instructions();
    dump_binary_file(); */

    fclose(file);
}
