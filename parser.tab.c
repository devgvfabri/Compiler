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
#line 1 "parser.y"

#define YYPARSER

#include <stdio.h>
#include "util.h"
#include "global.h"
#include "symtab.h"
#include "semantico.h"
#include "geradordequadrupla.h"
void yyerror(char *);
#define YYDEBUG 1    //Para exibir na tela os passos da análise sintática quando o parser é executado
extern "C"
{
  int yylex(void);
  void abrirArq();

}
#define YYSTYPE TreeNode *
int numline = 1;
static char * savedNameFun;
static char * savedNameVar;
static char * savedNameAtiv;
static int savedLineNo;
static TreeNode* savedTree;
static int location = 0;
static char *currentFunctionName = "global";
ErroSintatico *listaErrosSintaticos = NULL;  // Ponteiro global para a lista de erros
extern Quadrupla *listaCodInt; // Ponteiro global para a lista de codInt


#line 102 "parser.tab.c"

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

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUM = 3,                        /* NUM  */
  YYSYMBOL_ID = 4,                         /* ID  */
  YYSYMBOL_ELSE = 5,                       /* ELSE  */
  YYSYMBOL_WHILE = 6,                      /* WHILE  */
  YYSYMBOL_IF = 7,                         /* IF  */
  YYSYMBOL_RETURN = 8,                     /* RETURN  */
  YYSYMBOL_VOID = 9,                       /* VOID  */
  YYSYMBOL_INT = 10,                       /* INT  */
  YYSYMBOL_SOM = 11,                       /* SOM  */
  YYSYMBOL_SUB = 12,                       /* SUB  */
  YYSYMBOL_MUL = 13,                       /* MUL  */
  YYSYMBOL_DIV = 14,                       /* DIV  */
  YYSYMBOL_MAI = 15,                       /* MAI  */
  YYSYMBOL_MEN = 16,                       /* MEN  */
  YYSYMBOL_MIG = 17,                       /* MIG  */
  YYSYMBOL_MEI = 18,                       /* MEI  */
  YYSYMBOL_IGU = 19,                       /* IGU  */
  YYSYMBOL_DIF = 20,                       /* DIF  */
  YYSYMBOL_ATR = 21,                       /* ATR  */
  YYSYMBOL_PEV = 22,                       /* PEV  */
  YYSYMBOL_VIR = 23,                       /* VIR  */
  YYSYMBOL_APA = 24,                       /* APA  */
  YYSYMBOL_FPA = 25,                       /* FPA  */
  YYSYMBOL_ACO = 26,                       /* ACO  */
  YYSYMBOL_FCO = 27,                       /* FCO  */
  YYSYMBOL_ACH = 28,                       /* ACH  */
  YYSYMBOL_FCH = 29,                       /* FCH  */
  YYSYMBOL_ERRO = 30,                      /* ERRO  */
  YYSYMBOL_FIM = 31,                       /* FIM  */
  YYSYMBOL_FIMLIN = 32,                    /* FIMLIN  */
  YYSYMBOL_ERROR = 33,                     /* ERROR  */
  YYSYMBOL_OUTRO = 34,                     /* OUTRO  */
  YYSYMBOL_YYACCEPT = 35,                  /* $accept  */
  YYSYMBOL_programa = 36,                  /* programa  */
  YYSYMBOL_declaracoes = 37,               /* declaracoes  */
  YYSYMBOL_declaracaoLista = 38,           /* declaracaoLista  */
  YYSYMBOL_declaracao = 39,                /* declaracao  */
  YYSYMBOL_varDeclaracao = 40,             /* varDeclaracao  */
  YYSYMBOL_41_1 = 41,                      /* $@1  */
  YYSYMBOL_funDeclaracao = 42,             /* funDeclaracao  */
  YYSYMBOL_43_2 = 43,                      /* $@2  */
  YYSYMBOL_params = 44,                    /* params  */
  YYSYMBOL_paramLista = 45,                /* paramLista  */
  YYSYMBOL_tipoEspecificador = 46,         /* tipoEspecificador  */
  YYSYMBOL_param = 47,                     /* param  */
  YYSYMBOL_48_3 = 48,                      /* $@3  */
  YYSYMBOL_compostoDecl = 49,              /* compostoDecl  */
  YYSYMBOL_localDeclaracoes = 50,          /* localDeclaracoes  */
  YYSYMBOL_statementLista = 51,            /* statementLista  */
  YYSYMBOL_statement = 52,                 /* statement  */
  YYSYMBOL_expressaoDecl = 53,             /* expressaoDecl  */
  YYSYMBOL_selecaoDecl = 54,               /* selecaoDecl  */
  YYSYMBOL_iteracaoDecl = 55,              /* iteracaoDecl  */
  YYSYMBOL_retornoDecl = 56,               /* retornoDecl  */
  YYSYMBOL_expressao = 57,                 /* expressao  */
  YYSYMBOL_var = 58,                       /* var  */
  YYSYMBOL_59_4 = 59,                      /* $@4  */
  YYSYMBOL_simplesExpressao = 60,          /* simplesExpressao  */
  YYSYMBOL_relacional = 61,                /* relacional  */
  YYSYMBOL_somaExpressao = 62,             /* somaExpressao  */
  YYSYMBOL_soma = 63,                      /* soma  */
  YYSYMBOL_termo = 64,                     /* termo  */
  YYSYMBOL_mult = 65,                      /* mult  */
  YYSYMBOL_fator = 66,                     /* fator  */
  YYSYMBOL_ativacao = 67,                  /* ativacao  */
  YYSYMBOL_idAtiv = 68,                    /* idAtiv  */
  YYSYMBOL_args = 69,                      /* args  */
  YYSYMBOL_argLista = 70                   /* argLista  */
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
typedef yytype_int8 yy_state_t;

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
#define YYFINAL  10
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   112

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  35
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  36
/* YYNRULES -- Number of rules.  */
#define YYNRULES  74
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  118

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   289


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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    40,    40,    45,    48,    59,    62,    63,    66,    82,
      80,   104,   114,   113,   137,   144,   147,   155,   166,   167,
     174,   179,   186,   197,   196,   209,   216,   229,   230,   243,
     244,   257,   258,   259,   260,   261,   262,   269,   270,   274,
     279,   287,   294,   300,   310,   318,   322,   329,   329,   341,
     347,   350,   355,   360,   365,   370,   375,   382,   388,   390,
     395,   402,   409,   412,   417,   424,   425,   426,   427,   434,
     444,   453,   454,   457,   468
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
  "\"end of file\"", "error", "\"invalid token\"", "NUM", "ID", "ELSE",
  "WHILE", "IF", "RETURN", "VOID", "INT", "SOM", "SUB", "MUL", "DIV",
  "MAI", "MEN", "MIG", "MEI", "IGU", "DIF", "ATR", "PEV", "VIR", "APA",
  "FPA", "ACO", "FCO", "ACH", "FCH", "ERRO", "FIM", "FIMLIN", "ERROR",
  "OUTRO", "$accept", "programa", "declaracoes", "declaracaoLista",
  "declaracao", "varDeclaracao", "$@1", "funDeclaracao", "$@2", "params",
  "paramLista", "tipoEspecificador", "param", "$@3", "compostoDecl",
  "localDeclaracoes", "statementLista", "statement", "expressaoDecl",
  "selecaoDecl", "iteracaoDecl", "retornoDecl", "expressao", "var", "$@4",
  "simplesExpressao", "relacional", "somaExpressao", "soma", "termo",
  "mult", "fator", "ativacao", "idAtiv", "args", "argLista", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-74)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-71)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int8 yypact[] =
{
      46,   -74,   -74,     5,   -74,    46,   -74,   -74,   -74,    23,
     -74,   -74,   -18,    15,   -74,   -74,   -74,   -15,    -2,    26,
      70,    19,     8,    39,     0,    56,   -74,    59,    40,    46,
      46,    54,    62,   -74,   -74,   -74,   -74,   -74,   -74,    63,
      46,    64,   -74,    58,     6,   -74,    68,    72,    73,   -74,
      52,    60,    61,    14,   -74,    28,   -74,   -74,   -74,   -74,
     -74,   -74,   -74,    74,    76,   -74,    55,    37,   -74,   -74,
      69,   -74,    66,    28,    28,   -74,    77,    75,   -74,    28,
     -74,   -74,   -74,   -74,   -74,   -74,   -74,   -74,    28,    28,
     -74,   -74,    28,    28,    28,    78,    79,   -74,   -74,   -74,
     -74,    71,    37,   -74,   -74,    80,    83,    81,    41,    41,
     -74,    28,   -74,   -74,    93,   -74,    41,   -74
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,    21,    20,     0,     2,     3,     5,     6,     7,     0,
       1,     4,     0,     9,    11,    14,     8,     0,     0,     0,
       0,     0,    21,     0,     0,     0,    18,     0,     0,     0,
       0,     0,    22,    10,    27,    13,    19,    17,    25,     0,
      29,     0,    28,     0,     0,    24,     0,     9,     0,    68,
      46,     0,     0,     0,    38,     0,    26,    32,    30,    31,
      33,    34,    35,     0,    66,    45,    50,    58,    62,    67,
       0,    36,     0,     0,     0,    42,     0,     0,    37,     0,
      59,    60,    53,    52,    54,    51,    55,    56,     0,     0,
      63,    64,     0,    71,     0,     0,     0,    43,    65,    44,
      66,    49,    57,    61,    74,     0,    72,     0,     0,     0,
      69,     0,    48,    41,    39,    73,     0,    40
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -74,   -74,   -74,   -74,    96,    67,   -74,   -74,   -74,   -74,
     -74,     3,    57,   -74,    82,   -74,   -74,   -55,   -74,   -74,
     -74,   -74,   -53,   -73,   -74,   -74,   -74,    21,   -74,    13,
     -74,    20,   -74,   -74,   -74,   -74
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     3,     4,     5,     6,     7,    17,     8,    18,    23,
      24,    25,    26,    39,    57,    40,    44,    58,    59,    60,
      61,    62,    63,    64,    72,    65,    88,    66,    89,    67,
      92,    68,    69,    70,   105,   106
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      76,    29,    77,     9,    14,    10,    15,    48,     9,    49,
      50,    19,    51,    52,    53,   100,   100,    49,    50,   100,
      95,    96,    20,    30,    12,   -15,    99,    13,    54,    21,
      55,    49,    50,   -16,    34,    56,    75,    16,    55,   -12,
     104,   107,    48,    43,    49,    50,    27,    51,    52,    53,
      90,    91,    55,   113,   114,     1,     2,    31,   115,    46,
      32,   117,    47,    54,    28,    55,    80,    81,    34,    34,
      82,    83,    84,    85,    86,    87,   -70,    38,   -47,    22,
       2,    33,    80,    81,    73,    74,    36,    37,   -23,    41,
      14,    45,    94,    93,    16,    71,    78,    79,   116,    97,
      98,    11,   102,   108,   109,   110,   111,    42,   112,   101,
      35,     0,   103
};

static const yytype_int8 yycheck[] =
{
      53,     1,    55,     0,    22,     0,    24,     1,     5,     3,
       4,    26,     6,     7,     8,    88,    89,     3,     4,    92,
      73,    74,    24,    23,     1,    25,    79,     4,    22,     3,
      24,     3,     4,    25,    28,    29,    22,    22,    24,    24,
      93,    94,     1,    40,     3,     4,    27,     6,     7,     8,
      13,    14,    24,   108,   109,     9,    10,     1,   111,     1,
       4,   116,     4,    22,    25,    24,    11,    12,    28,    28,
      15,    16,    17,    18,    19,    20,    24,    23,    26,     9,
      10,    22,    11,    12,    24,    24,    29,    30,    26,    26,
      22,    27,    26,    24,    22,    22,    22,    21,     5,    22,
      25,     5,    89,    25,    25,    25,    23,    40,    27,    88,
      28,    -1,    92
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     9,    10,    36,    37,    38,    39,    40,    42,    46,
       0,    39,     1,     4,    22,    24,    22,    41,    43,    26,
      24,     3,     9,    44,    45,    46,    47,    27,    25,     1,
      23,     1,     4,    22,    28,    49,    47,    47,    23,    48,
      50,    26,    40,    46,    51,    27,     1,     4,     1,     3,
       4,     6,     7,     8,    22,    24,    29,    49,    52,    53,
      54,    55,    56,    57,    58,    60,    62,    64,    66,    67,
      68,    22,    59,    24,    24,    22,    57,    57,    22,    21,
      11,    12,    15,    16,    17,    18,    19,    20,    61,    63,
      13,    14,    65,    24,    26,    57,    57,    22,    25,    57,
      58,    62,    64,    66,    57,    69,    70,    57,    25,    25,
      25,    23,    27,    52,    52,    57,     5,    52
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    35,    36,    37,    38,    38,    39,    39,    40,    41,
      40,    40,    43,    42,    42,    44,    44,    45,    45,    45,
      46,    46,    47,    48,    47,    47,    49,    50,    50,    51,
      51,    52,    52,    52,    52,    52,    52,    53,    53,    54,
      54,    55,    56,    56,    57,    57,    58,    59,    58,    60,
      60,    61,    61,    61,    61,    61,    61,    62,    62,    63,
      63,    64,    64,    65,    65,    66,    66,    66,    66,    67,
      68,    69,    69,    70,    70
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     1,     1,     3,     0,
       7,     3,     0,     7,     3,     1,     1,     3,     1,     3,
       1,     1,     2,     0,     5,     3,     4,     0,     2,     0,
       2,     1,     1,     1,     1,     1,     2,     2,     1,     5,
       7,     5,     2,     3,     3,     1,     1,     0,     5,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     1,
       1,     3,     1,     1,     1,     3,     1,     1,     1,     4,
       1,     0,     1,     3,     1
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
  switch (yykind)
    {
    case YYSYMBOL_NUM: /* NUM  */
#line 36 "parser.y"
         { fprintf (yyoutput, "’%d’", (*yyvaluep)); }
#line 859 "parser.tab.c"
        break;

      default:
        break;
    }
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
  case 2: /* programa: declaracoes  */
#line 40 "parser.y"
                         { printf("Programa finalizado com sucesso\n"); 
				savedTree = yyvsp[0];
				YYACCEPT; }
#line 1251 "parser.tab.c"
    break;

  case 3: /* declaracoes: declaracaoLista  */
#line 45 "parser.y"
                               { yyval = yyvsp[0]; }
#line 1257 "parser.tab.c"
    break;

  case 4: /* declaracaoLista: declaracaoLista declaracao  */
#line 49 "parser.y"
                        {	
			    TreeNode * t = yyvsp[-1];
			    if (t != NULL) {
				while (t->sibling != NULL) t = t->sibling;
				t->sibling = yyvsp[0];
				yyval = yyvsp[-1];
			    } else {
				yyval = yyvsp[0];
			    }
			}
#line 1272 "parser.tab.c"
    break;

  case 5: /* declaracaoLista: declaracao  */
#line 59 "parser.y"
                                     { yyval = yyvsp[0]; }
#line 1278 "parser.tab.c"
    break;

  case 6: /* declaracao: varDeclaracao  */
#line 62 "parser.y"
                                      { yyval = yyvsp[0];}
#line 1284 "parser.tab.c"
    break;

  case 7: /* declaracao: funDeclaracao  */
#line 63 "parser.y"
                                        { yyval = yyvsp[0];}
#line 1290 "parser.tab.c"
    break;

  case 8: /* varDeclaracao: tipoEspecificador ID PEV  */
#line 67 "parser.y"
                        { 
					yyval = newExpNode(TypeK);
               				yyval->type = yyvsp[-2]->type;
					TreeNode *id = newExpNode(IdK);
					id->attr.name = copyString(tokenString);
                			yyval->attr.name = id->attr.name;
                			yyval->child[0] = id;
                			id->nodekind = StmtK;
                			id->kind.stmt = VarK;
                			id->type = yyvsp[-2]->type;
					id->escopo = copyString(currentFunctionName);
                			st_insert(location++, id->attr.name, currentFunctionName , "var",yyvsp[-2]->type, numline, 1);
    			}
#line 1308 "parser.tab.c"
    break;

  case 9: /* $@1: %empty  */
#line 82 "parser.y"
                        {
			savedNameVar = copyString(tokenString);
			}
#line 1316 "parser.tab.c"
    break;

  case 10: /* varDeclaracao: tipoEspecificador ID $@1 ACO NUM FCO PEV  */
#line 86 "parser.y"
                        { 
				yyval = newExpNode(TypeK);
                yyval->type = yyvsp[-6]->type;
				TreeNode *id = newExpNode(IdK);
				id->attr.name = copyString(savedNameVar);
				yyval->attr.name = yyvsp[-6]->attr.name;
				yyval->child[0] = id;
				id->nodekind = ExpK;
				id->kind.exp = VetK;
				id->type = yyvsp[-6]->type;
				id->child[0] = newExpNode(ConstK);
				id->child[0]->attr.val = atoi(tokenString);
				id->child[0]->type = Integer;
				id->child[0]->numline = numline;
				id->attr.vetor = 1;
				id->escopo = copyString(currentFunctionName);
				st_insert(location++, id->attr.name, currentFunctionName, "var", yyvsp[-6]->type, numline, 1);
    			}
#line 1339 "parser.tab.c"
    break;

  case 11: /* varDeclaracao: tipoEspecificador error PEV  */
#line 105 "parser.y"
                        {
				yyerrok;
				yyval = NULL;
			}
#line 1348 "parser.tab.c"
    break;

  case 12: /* $@2: %empty  */
#line 114 "parser.y"
                        {
				savedNameFun = copyString(tokenString);
				savedLineNo = numline;
				currentFunctionName = savedNameFun;
				setCurrentFunction(copyString(tokenString));
			}
#line 1359 "parser.tab.c"
    break;

  case 13: /* funDeclaracao: tipoEspecificador ID $@2 APA params FPA compostoDecl  */
#line 121 "parser.y"
                        { 
				yyval = newExpNode(TypeK);
                		yyval->type = yyvsp[-6]->type;
				TreeNode *id = newExpNode(IdK);
				id->attr.name = copyString(savedNameFun);
				yyval->attr.name = id->attr.name;
				yyval->child[0] = id;
				id->child[0] = yyvsp[-2];
				id->child[1] = yyvsp[0];
				id->nodekind = StmtK;
				id->kind.stmt = FunK;
				id->type = yyvsp[-6]->type;
				id->escopo = copyString("global");
				st_insert(location++, id->attr.name, "global","funcao", yyvsp[-6]->type, savedLineNo, 1);
				currentFunctionName = "global";
			}
#line 1380 "parser.tab.c"
    break;

  case 14: /* funDeclaracao: tipoEspecificador error APA  */
#line 138 "parser.y"
                        {
				yyerrok;
				yyval = NULL;
			}
#line 1389 "parser.tab.c"
    break;

  case 15: /* params: paramLista  */
#line 144 "parser.y"
                                   {yyval = yyvsp[0];
				}
#line 1396 "parser.tab.c"
    break;

  case 16: /* params: VOID  */
#line 148 "parser.y"
                        {	
				yyval = newExpNode(TypeK);
				yyval->type = Void;
				yyval->child[0] = NULL;
			}
#line 1406 "parser.tab.c"
    break;

  case 17: /* paramLista: paramLista VIR param  */
#line 156 "parser.y"
                        {	
			    TreeNode * t = yyvsp[-2];
			    if (t != NULL) {
				while (t->sibling != NULL) t = t->sibling;
				t->sibling = yyvsp[0];
				yyval = yyvsp[-2];
			    } else {
				yyval = yyvsp[0];
			    }
			}
#line 1421 "parser.tab.c"
    break;

  case 18: /* paramLista: param  */
#line 166 "parser.y"
                                {yyval = yyvsp[0];}
#line 1427 "parser.tab.c"
    break;

  case 19: /* paramLista: paramLista error param  */
#line 168 "parser.y"
                        {
				yyerrok;
				yyval = NULL;
			}
#line 1436 "parser.tab.c"
    break;

  case 20: /* tipoEspecificador: INT  */
#line 175 "parser.y"
                        {	
				yyval = newExpNode(TypeK);
				yyval->type = Integer;
			}
#line 1445 "parser.tab.c"
    break;

  case 21: /* tipoEspecificador: VOID  */
#line 180 "parser.y"
                        {	
				yyval = newExpNode(TypeK);
				yyval->type = Void;
			}
#line 1454 "parser.tab.c"
    break;

  case 22: /* param: tipoEspecificador ID  */
#line 187 "parser.y"
                        { 
				TreeNode *paramNode = newStmtNode(ParamK);
				paramNode->attr.name = copyString(tokenString); // Nome do parâmetro
				yyval->child[0] = paramNode;
				paramNode->type = yyvsp[-1]->type; // Tipo do parâmetro
				paramNode->escopo = copyString(currentFunctionName); // Escopo do parâmetro
				st_insert(location++, paramNode->attr.name, currentFunctionName, "param", yyvsp[-1]->type, numline, 1);
				yyval = yyvsp[-1];
    			}
#line 1468 "parser.tab.c"
    break;

  case 23: /* $@3: %empty  */
#line 197 "parser.y"
                        {
				savedNameVar = copyString(tokenString);
			}
#line 1476 "parser.tab.c"
    break;

  case 24: /* param: tipoEspecificador ID $@3 ACO FCO  */
#line 200 "parser.y"
                        { 
				TreeNode *paramNode = newStmtNode(ParamK);
				paramNode->attr.name = copyString(savedNameVar); // Nome do parâmetro
				yyval->child[0] = paramNode;
				paramNode->type = IntegerVetorK; // Tipo do parâmetro (vetor)
				paramNode->escopo = copyString(currentFunctionName); // Escopo do parâmetro
				st_insert(location++, paramNode->attr.name, currentFunctionName, "param", IntegerVetorK, numline, 1);
				yyval = yyvsp[-4];
    			}
#line 1490 "parser.tab.c"
    break;

  case 25: /* param: tipoEspecificador error VIR  */
#line 210 "parser.y"
                        {
    				yyerrok;
    				yyval = NULL;
    			}
#line 1499 "parser.tab.c"
    break;

  case 26: /* compostoDecl: ACH localDeclaracoes statementLista FCH  */
#line 217 "parser.y"
                        {
				TreeNode* t = yyvsp[-2];
				if(t != NULL){
				  while(t->sibling != NULL)
				  t = t->sibling;
				  t->sibling = yyvsp[-1];
				  yyval = yyvsp[-2];
				} 
				else yyval = yyvsp[-1];
             		 }
#line 1514 "parser.tab.c"
    break;

  case 27: /* localDeclaracoes: %empty  */
#line 229 "parser.y"
                                  { yyval = NULL; }
#line 1520 "parser.tab.c"
    break;

  case 28: /* localDeclaracoes: localDeclaracoes varDeclaracao  */
#line 231 "parser.y"
                        {
				TreeNode *t = yyvsp[-1];
				if (t != NULL) {
				    while (t->sibling != NULL) t = t->sibling;
				    t->sibling = yyvsp[0];
				    yyval = yyvsp[-1];
				} else {
				    yyval = yyvsp[0];
				}
			 }
#line 1535 "parser.tab.c"
    break;

  case 29: /* statementLista: %empty  */
#line 243 "parser.y"
                                  { yyval = NULL; }
#line 1541 "parser.tab.c"
    break;

  case 30: /* statementLista: statementLista statement  */
#line 245 "parser.y"
                        {
				TreeNode *t = yyvsp[-1];
				if (t != NULL) {
				    while (t->sibling != NULL) t = t->sibling;
				    t->sibling = yyvsp[0];
				    yyval = yyvsp[-1];
				} else {
				    yyval = yyvsp[0];
				}
			    }
#line 1556 "parser.tab.c"
    break;

  case 31: /* statement: expressaoDecl  */
#line 257 "parser.y"
                                       {yyval = yyvsp[0];}
#line 1562 "parser.tab.c"
    break;

  case 32: /* statement: compostoDecl  */
#line 258 "parser.y"
                                       {yyval = yyvsp[0];}
#line 1568 "parser.tab.c"
    break;

  case 33: /* statement: selecaoDecl  */
#line 259 "parser.y"
                                       {yyval = yyvsp[0];}
#line 1574 "parser.tab.c"
    break;

  case 34: /* statement: iteracaoDecl  */
#line 260 "parser.y"
                                       {yyval = yyvsp[0];}
#line 1580 "parser.tab.c"
    break;

  case 35: /* statement: retornoDecl  */
#line 261 "parser.y"
                                       {yyval = yyvsp[0];}
#line 1586 "parser.tab.c"
    break;

  case 36: /* statement: error PEV  */
#line 263 "parser.y"
                        {
				yyerrok;
				yyval = NULL;
			}
#line 1595 "parser.tab.c"
    break;

  case 37: /* expressaoDecl: expressao PEV  */
#line 269 "parser.y"
                                      {yyval = yyvsp[-1];}
#line 1601 "parser.tab.c"
    break;

  case 39: /* selecaoDecl: IF APA expressao FPA statement  */
#line 275 "parser.y"
                        {  yyval = newStmtNode(IfK);
	                   yyval->child[0] = yyvsp[-2];
	                   yyval->child[1] = yyvsp[0];
	                 }
#line 1610 "parser.tab.c"
    break;

  case 40: /* selecaoDecl: IF APA expressao FPA statement ELSE statement  */
#line 280 "parser.y"
                        {  yyval = newStmtNode(IfK);
	                   yyval->child[0] = yyvsp[-4];
	                   yyval->child[1] = yyvsp[-2];
	                   yyval->child[2] = yyvsp[0];
	                 }
#line 1620 "parser.tab.c"
    break;

  case 41: /* iteracaoDecl: WHILE APA expressao FPA statement  */
#line 288 "parser.y"
                        {  yyval = newStmtNode(WhileK);
	                   yyval->child[0] = yyvsp[-2];
	                   yyval->child[1] = yyvsp[0];
	                 }
#line 1629 "parser.tab.c"
    break;

  case 42: /* retornoDecl: RETURN PEV  */
#line 295 "parser.y"
                        {
				yyval = newStmtNode(returnK);
				yyval->escopo = currentFunctionName;
				yyval->type = Void;
			}
#line 1639 "parser.tab.c"
    break;

  case 43: /* retornoDecl: RETURN expressao PEV  */
#line 301 "parser.y"
                        {  
				yyval = newStmtNode(returnK);
	                   	yyval->child[0] = yyvsp[-1];
				yyval->type = Integer;
				yyval->child[0]->type = Integer;
				yyval->escopo = currentFunctionName;
	                }
#line 1651 "parser.tab.c"
    break;

  case 44: /* expressao: var ATR expressao  */
#line 311 "parser.y"
                        { 
				yyval = newStmtNode(AtrK);
				yyval->attr.name = yyvsp[-2]->attr.name;
				yyval->attr.op = ATR;
				yyval->child[0] = yyvsp[-2];
				yyval->child[1] = yyvsp[0];
			}
#line 1663 "parser.tab.c"
    break;

  case 45: /* expressao: simplesExpressao  */
#line 318 "parser.y"
                                           {yyval = yyvsp[0];}
#line 1669 "parser.tab.c"
    break;

  case 46: /* var: ID  */
#line 323 "parser.y"
                        {
				yyval = newExpNode(IdK);
				yyval->attr.name = copyString(tokenString);
				yyval->type = Integer;
				st_insert(location++, tokenString, currentFunctionName, "var", NULL, numline, 0);
			}
#line 1680 "parser.tab.c"
    break;

  case 47: /* $@4: %empty  */
#line 329 "parser.y"
                             {	savedNameVar = copyString(tokenString); }
#line 1686 "parser.tab.c"
    break;

  case 48: /* var: ID $@4 ACO expressao FCO  */
#line 331 "parser.y"
                        {
				yyval = newExpNode(IdK);
				yyval->attr.name = copyString(savedNameVar);
				yyval->child[0] = yyvsp[-1];
				yyval->kind.exp = VetK;
				yyval->type = Integer;
				st_insert(location++, savedNameVar, currentFunctionName, "var", NULL, numline, 0);
			}
#line 1699 "parser.tab.c"
    break;

  case 49: /* simplesExpressao: somaExpressao relacional somaExpressao  */
#line 342 "parser.y"
                        {
				yyval = yyvsp[-1];
				yyval->child[0] = yyvsp[-2];
				yyval->child[1] = yyvsp[0];
			}
#line 1709 "parser.tab.c"
    break;

  case 50: /* simplesExpressao: somaExpressao  */
#line 347 "parser.y"
                                        {yyval = yyvsp[0];}
#line 1715 "parser.tab.c"
    break;

  case 51: /* relacional: MEI  */
#line 351 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = MEI;
			}
#line 1724 "parser.tab.c"
    break;

  case 52: /* relacional: MEN  */
#line 356 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = MEN;
			}
#line 1733 "parser.tab.c"
    break;

  case 53: /* relacional: MAI  */
#line 361 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = MAI;
			}
#line 1742 "parser.tab.c"
    break;

  case 54: /* relacional: MIG  */
#line 366 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = MIG;
			}
#line 1751 "parser.tab.c"
    break;

  case 55: /* relacional: IGU  */
#line 371 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = IGU;
			}
#line 1760 "parser.tab.c"
    break;

  case 56: /* relacional: DIF  */
#line 376 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = DIF;
			}
#line 1769 "parser.tab.c"
    break;

  case 57: /* somaExpressao: somaExpressao soma termo  */
#line 383 "parser.y"
                        {
				yyval = yyvsp[-1];
				yyval->child[0] = yyvsp[-2];
				yyval->child[1] = yyvsp[0];
			}
#line 1779 "parser.tab.c"
    break;

  case 58: /* somaExpressao: termo  */
#line 388 "parser.y"
                                {yyval = yyvsp[0];}
#line 1785 "parser.tab.c"
    break;

  case 59: /* soma: SOM  */
#line 391 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = SOM;
			}
#line 1794 "parser.tab.c"
    break;

  case 60: /* soma: SUB  */
#line 396 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = SUB;
			}
#line 1803 "parser.tab.c"
    break;

  case 61: /* termo: termo mult fator  */
#line 403 "parser.y"
                        {
				yyval = yyvsp[-1];
				yyval->child[0] = yyvsp[-2];
				yyval->child[1] = yyvsp[0];	
			}
#line 1813 "parser.tab.c"
    break;

  case 62: /* termo: fator  */
#line 409 "parser.y"
                                {yyval = yyvsp[0];}
#line 1819 "parser.tab.c"
    break;

  case 63: /* mult: MUL  */
#line 413 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = MUL;
			}
#line 1828 "parser.tab.c"
    break;

  case 64: /* mult: DIV  */
#line 418 "parser.y"
                        { 
				yyval = newExpNode(OpK);
				yyval->attr.op = DIV;
			}
#line 1837 "parser.tab.c"
    break;

  case 65: /* fator: APA expressao FPA  */
#line 424 "parser.y"
                                          {yyval = yyvsp[-1];}
#line 1843 "parser.tab.c"
    break;

  case 66: /* fator: var  */
#line 425 "parser.y"
                               {yyval = yyvsp[0];}
#line 1849 "parser.tab.c"
    break;

  case 67: /* fator: ativacao  */
#line 426 "parser.y"
                                   {yyval = yyvsp[0];}
#line 1855 "parser.tab.c"
    break;

  case 68: /* fator: NUM  */
#line 428 "parser.y"
                        {
				yyval = newExpNode(ConstK);
				yyval->attr.val = atoi(tokenString);
  			}
#line 1864 "parser.tab.c"
    break;

  case 69: /* ativacao: idAtiv APA args FPA  */
#line 435 "parser.y"
                        {
				yyval = yyvsp[-3];
				yyval->child[0] = yyvsp[-1];
				yyval->nodekind = StmtK;
				yyval->kind.stmt = CallK;
				yyval->numline = numline;
				yyval->attr.name = yyvsp[-3]->attr.name;
			}
#line 1877 "parser.tab.c"
    break;

  case 70: /* idAtiv: ID  */
#line 445 "parser.y"
                        {
				yyval = newExpNode(IdK);
				yyval->attr.name = copyString(tokenString);
				yyval->numline = numline;
				if(strcmp("output", tokenString) != 0 && strcmp("input", tokenString) && strcmp("main", tokenString) )
				st_insert(location++, tokenString, currentFunctionName, "funcao", NULL, numline, 0);
			}
#line 1889 "parser.tab.c"
    break;

  case 71: /* args: %empty  */
#line 453 "parser.y"
                                  { yyval = NULL; }
#line 1895 "parser.tab.c"
    break;

  case 72: /* args: argLista  */
#line 454 "parser.y"
                                   {yyval = yyvsp[0];}
#line 1901 "parser.tab.c"
    break;

  case 73: /* argLista: argLista VIR expressao  */
#line 458 "parser.y"
                        {	
			    TreeNode * t = yyvsp[-2];
			    if (t != NULL) {
				while (t->sibling != NULL) t = t->sibling;
				t->sibling = yyvsp[0];
				yyval = yyvsp[-2];
			    } else {
				yyval = yyvsp[0];
			    }
			}
#line 1916 "parser.tab.c"
    break;

  case 74: /* argLista: expressao  */
#line 468 "parser.y"
                                    {yyval = yyvsp[0];}
#line 1922 "parser.tab.c"
    break;


#line 1926 "parser.tab.c"

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

#line 472 "parser.y"



void imprimirErrosSintaticos() 
{
	ErroSintatico *atual = listaErrosSintaticos;
	while (atual) 
	{
		printf("%s", atual->mensagem);
		atual = atual->prox;
	}
}

int main()
{
  extern int yydebug;
  yydebug = 1;
  printf("\nParser em execução...\n");
  abrirArq();
  
  yyparse(); 
  if (savedTree != NULL) {
      printTreeArq(savedTree);  
  } else {
      printf("\nErro ao construir a árvore sintática.\n");
  }
  imprimirErros();
  imprimirErrosSintaticos();
  imprimirErrosLexicos();
  semanticCheck(savedTree);
  printSymTab();
  generateCode(savedTree);
  imprimirQuadruplas();
  return 0;

}

void yyerror(char * msg)
{
  extern char* yytext;
  extern int yychar;
    ErroSintatico *novoErroSintatico = (ErroSintatico *)malloc(sizeof(ErroSintatico));
	snprintf(novoErroSintatico->mensagem, sizeof(novoErroSintatico->mensagem), 
             "ERRO SINTÁTICO: %s LINHA: %d\n", yytext, numline);

    novoErroSintatico->prox = listaErrosSintaticos;  // Adicionar ao início da lista
    listaErrosSintaticos = novoErroSintatico;
  printf("\n\n\n\tERRO SINTÁTICO: %s, Token: ", msg);
  printToken(yychar, yytext);
  printf(" LINHA: %d\n\n\n", numline);

  
}

