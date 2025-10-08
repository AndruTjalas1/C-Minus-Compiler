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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "symtab.h"
#include "error.h"

extern int yylex();
extern FILE* yyin;
extern int yylineno;
extern char* yytext;

ASTNode* root = NULL;

void yyerror(const char* s);
int* extractInitValues(ASTNode* initList, int* count);

#line 90 "parser.tab.c"

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
  YYSYMBOL_IDENTIFIER = 3,                 /* IDENTIFIER  */
  YYSYMBOL_TYPE = 4,                       /* TYPE  */
  YYSYMBOL_NUMBER = 5,                     /* NUMBER  */
  YYSYMBOL_CHAR_LITERAL = 6,               /* CHAR_LITERAL  */
  YYSYMBOL_STRING_LITERAL = 7,             /* STRING_LITERAL  */
  YYSYMBOL_SEMICOLON = 8,                  /* SEMICOLON  */
  YYSYMBOL_EQ = 9,                         /* EQ  */
  YYSYMBOL_PLUS = 10,                      /* PLUS  */
  YYSYMBOL_MINUS = 11,                     /* MINUS  */
  YYSYMBOL_MULTIPLY = 12,                  /* MULTIPLY  */
  YYSYMBOL_DIVIDE = 13,                    /* DIVIDE  */
  YYSYMBOL_MODULO = 14,                    /* MODULO  */
  YYSYMBOL_PLUSEQ = 15,                    /* PLUSEQ  */
  YYSYMBOL_MINUSEQ = 16,                   /* MINUSEQ  */
  YYSYMBOL_MULTEQ = 17,                    /* MULTEQ  */
  YYSYMBOL_DIVEQ = 18,                     /* DIVEQ  */
  YYSYMBOL_MODEQ = 19,                     /* MODEQ  */
  YYSYMBOL_PLUSPLUS = 20,                  /* PLUSPLUS  */
  YYSYMBOL_MINUSMINUS = 21,                /* MINUSMINUS  */
  YYSYMBOL_LBRACKET = 22,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 23,                  /* RBRACKET  */
  YYSYMBOL_LBRACE = 24,                    /* LBRACE  */
  YYSYMBOL_RBRACE = 25,                    /* RBRACE  */
  YYSYMBOL_COMMA = 26,                     /* COMMA  */
  YYSYMBOL_KEYWORD = 27,                   /* KEYWORD  */
  YYSYMBOL_LPAREN = 28,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 29,                    /* RPAREN  */
  YYSYMBOL_IF = 30,                        /* IF  */
  YYSYMBOL_ELSEIF = 31,                    /* ELSEIF  */
  YYSYMBOL_ELSE = 32,                      /* ELSE  */
  YYSYMBOL_FOR = 33,                       /* FOR  */
  YYSYMBOL_WHILE = 34,                     /* WHILE  */
  YYSYMBOL_DO = 35,                        /* DO  */
  YYSYMBOL_FUNCTION = 36,                  /* FUNCTION  */
  YYSYMBOL_RETURN = 37,                    /* RETURN  */
  YYSYMBOL_EQEQ = 38,                      /* EQEQ  */
  YYSYMBOL_NEQ = 39,                       /* NEQ  */
  YYSYMBOL_LT = 40,                        /* LT  */
  YYSYMBOL_LE = 41,                        /* LE  */
  YYSYMBOL_GT = 42,                        /* GT  */
  YYSYMBOL_GE = 43,                        /* GE  */
  YYSYMBOL_AND = 44,                       /* AND  */
  YYSYMBOL_OR = 45,                        /* OR  */
  YYSYMBOL_NOT = 46,                       /* NOT  */
  YYSYMBOL_XOR = 47,                       /* XOR  */
  YYSYMBOL_TRUE = 48,                      /* TRUE  */
  YYSYMBOL_FALSE = 49,                     /* FALSE  */
  YYSYMBOL_50_ = 50,                       /* '('  */
  YYSYMBOL_51_ = 51,                       /* ')'  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_program = 53,                   /* program  */
  YYSYMBOL_stmt = 54,                      /* stmt  */
  YYSYMBOL_declaration = 55,               /* declaration  */
  YYSYMBOL_assignment = 56,                /* assignment  */
  YYSYMBOL_print_stmt = 57,                /* print_stmt  */
  YYSYMBOL_array_access = 58,              /* array_access  */
  YYSYMBOL_init_list = 59,                 /* init_list  */
  YYSYMBOL_if_stmt = 60,                   /* if_stmt  */
  YYSYMBOL_elseif_list = 61,               /* elseif_list  */
  YYSYMBOL_stmt_list = 62,                 /* stmt_list  */
  YYSYMBOL_stmt_block = 63,                /* stmt_block  */
  YYSYMBOL_condition = 64,                 /* condition  */
  YYSYMBOL_for_stmt = 65,                  /* for_stmt  */
  YYSYMBOL_loop_init = 66,                 /* loop_init  */
  YYSYMBOL_loop_update = 67,               /* loop_update  */
  YYSYMBOL_while_stmt = 68,                /* while_stmt  */
  YYSYMBOL_do_while_stmt = 69,             /* do_while_stmt  */
  YYSYMBOL_function_def = 70,              /* function_def  */
  YYSYMBOL_71_1 = 71,                      /* $@1  */
  YYSYMBOL_72_2 = 72,                      /* $@2  */
  YYSYMBOL_param_list = 73,                /* param_list  */
  YYSYMBOL_param = 74,                     /* param  */
  YYSYMBOL_function_call = 75,             /* function_call  */
  YYSYMBOL_arg_list = 76,                  /* arg_list  */
  YYSYMBOL_return_stmt = 77,               /* return_stmt  */
  YYSYMBOL_expression = 78                 /* expression  */
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
#define YYFINAL  2
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   459

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  96
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  227

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   304


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
      50,    51,     2,     2,     2,     2,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    63,    63,    64,    65,    69,    70,    71,    72,    73,
      74,    75,    76,    77,    81,    92,   103,   112,   119,   126,
     135,   149,   158,   169,   180,   191,   202,   213,   225,   237,
     249,   261,   269,   277,   285,   296,   297,   301,   306,   311,
     316,   324,   328,   335,   336,   340,   341,   345,   346,   347,
     348,   349,   350,   351,   352,   353,   354,   355,   359,   367,
     374,   384,   388,   396,   407,   418,   429,   440,   444,   452,
     461,   460,   486,   485,   501,   502,   506,   513,   520,   530,
     531,   535,   539,   546,   547,   548,   549,   550,   551,   558,
     559,   560,   561,   562,   563,   564,   565
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
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFIER", "TYPE",
  "NUMBER", "CHAR_LITERAL", "STRING_LITERAL", "SEMICOLON", "EQ", "PLUS",
  "MINUS", "MULTIPLY", "DIVIDE", "MODULO", "PLUSEQ", "MINUSEQ", "MULTEQ",
  "DIVEQ", "MODEQ", "PLUSPLUS", "MINUSMINUS", "LBRACKET", "RBRACKET",
  "LBRACE", "RBRACE", "COMMA", "KEYWORD", "LPAREN", "RPAREN", "IF",
  "ELSEIF", "ELSE", "FOR", "WHILE", "DO", "FUNCTION", "RETURN", "EQEQ",
  "NEQ", "LT", "LE", "GT", "GE", "AND", "OR", "NOT", "XOR", "TRUE",
  "FALSE", "'('", "')'", "$accept", "program", "stmt", "declaration",
  "assignment", "print_stmt", "array_access", "init_list", "if_stmt",
  "elseif_list", "stmt_list", "stmt_block", "condition", "for_stmt",
  "loop_init", "loop_update", "while_stmt", "do_while_stmt",
  "function_def", "$@1", "$@2", "param_list", "param", "function_call",
  "arg_list", "return_stmt", "expression", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-182)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -182,   227,  -182,   369,     5,    24,    26,    32,    42,    54,
      68,   246,    84,    25,  -182,  -182,  -182,  -182,   102,  -182,
    -182,  -182,  -182,  -182,    92,  -182,    96,    96,    96,    96,
      96,    96,   110,   141,    96,   114,    -4,   145,   157,    96,
       9,    40,     9,   322,  -182,   133,   132,    18,  -182,  -182,
    -182,  -182,  -182,  -182,    96,  -182,  -182,   350,    96,  -182,
     390,   398,   405,   412,   419,   426,  -182,  -182,   356,  -182,
      27,   445,  -182,   131,   156,  -182,  -182,    95,     9,     9,
       7,   334,   161,   171,   168,   140,  -182,   265,   149,   150,
      10,  -182,    96,    96,    96,    96,    96,   433,  -182,  -182,
    -182,  -182,  -182,  -182,   166,    96,  -182,   182,   440,   172,
     183,   153,  -182,   246,     9,     9,     9,    96,    96,    96,
      96,    96,    96,    96,   185,     9,   246,  -182,  -182,     9,
      -3,  -182,   127,   127,  -182,  -182,  -182,  -182,    96,   445,
    -182,  -182,    70,  -182,  -182,    91,  -182,    43,   155,   445,
     445,   445,   445,   445,   445,   445,    96,    -6,  -182,   188,
     198,  -182,    87,  -182,   382,  -182,   178,   204,   186,   246,
     116,   445,    14,   211,  -182,   197,   221,  -182,  -182,    96,
     203,     9,  -182,   201,   246,    60,   231,   234,   209,  -182,
     322,  -182,   217,   101,   445,   143,   195,     9,  -182,    96,
    -182,  -182,  -182,  -182,   246,   284,   322,   243,    96,  -182,
     228,   246,   199,   445,  -182,  -182,   303,  -182,   445,    96,
    -182,   246,  -182,   147,  -182,   245,  -182
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,     0,     1,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     2,     5,     6,     7,     0,     8,
       9,    10,    11,     3,     0,    13,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    61,     0,     0,    46,     0,     0,    88,    83,    84,
      85,    82,    86,    87,     0,    90,    89,     0,     0,    12,
       0,     0,     0,     0,     0,     0,    27,    28,     0,    78,
       0,    79,    14,     0,     0,    29,    30,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    43,     0,     0,     0,
       0,    81,     0,     0,     0,     0,     0,     0,    21,    22,
      23,    24,    25,    26,    33,     0,    77,    85,     0,     0,
       0,     0,    56,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    44,     0,
       0,    91,    92,    93,    94,    95,    96,    31,     0,    80,
      20,    15,     0,    32,    57,    37,    53,    54,    55,    47,
      48,    49,    50,    51,    52,    59,     0,     0,    68,     0,
       0,    72,     0,    74,     0,    17,     0,     0,     0,     0,
      39,    60,    67,     0,    76,     0,     0,    70,    34,     0,
       0,     0,    38,     0,     0,     0,     0,     0,     0,    69,
       0,    75,     0,     0,    35,     0,     0,     0,    40,     0,
      63,    64,    65,    66,     0,     0,     0,     0,     0,    18,
       0,     0,     0,    62,    58,    73,     0,    16,    36,     0,
      41,     0,    71,     0,    42,     0,    19
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -182,  -182,     6,  -182,  -182,  -182,    -1,    36,  -182,  -182,
    -181,  -107,   -31,  -182,  -182,  -182,  -182,  -182,  -182,  -182,
    -182,  -182,    82,     2,  -182,  -182,    37
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,    44,    15,    16,    17,    55,   193,    19,   170,
      87,    45,    80,    20,    84,   188,    21,    22,    23,   192,
     175,   162,   163,    56,    70,    25,    81
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      18,   160,   172,    24,    72,    73,   145,    14,    36,   205,
      18,    85,    47,    24,    48,    49,    50,   185,    74,   158,
      92,    93,    94,    95,    96,   216,   161,    37,    47,    38,
      48,    49,    50,    51,   186,   187,   113,    78,   114,   115,
      34,   116,    18,    82,    83,    24,    35,   111,   112,    86,
      57,   114,   115,   105,   116,    79,   106,    52,    53,    54,
      39,   131,   182,    60,    61,    62,    63,    64,    65,   199,
      40,    68,    71,    52,    53,    54,    77,   198,   165,   166,
     200,   201,    41,   146,   147,   148,    18,   114,    46,    24,
     116,    90,   167,   128,   157,    97,    42,   214,   159,    47,
      59,    48,    49,    50,   220,    92,    93,    94,    95,    96,
     108,    58,    18,   176,   224,    24,   177,    47,    66,    48,
      49,    50,   168,   169,   110,    18,   207,   208,    24,   132,
     133,   134,   135,   136,    47,    89,    48,    49,   107,    94,
      95,    96,   139,    69,    52,    53,    54,   183,   184,    67,
     196,   209,   210,    75,   149,   150,   151,   152,   153,   154,
     155,   109,    52,    53,    54,    76,   212,    88,    18,   126,
     123,    24,   225,   208,   124,   164,   125,   129,   130,    52,
      53,    54,   144,    18,   114,   115,    24,   116,   138,    18,
     140,   143,    24,   171,   156,   142,    86,   114,   115,   114,
     116,   174,   179,    18,    18,    18,    24,    24,    24,   180,
      18,   128,    86,    24,   181,    18,   194,   173,    24,   189,
      18,   190,   128,    24,   211,   160,   195,     2,   221,   197,
       3,     4,   114,   115,   202,   116,   213,   203,   204,   114,
     115,   206,   116,   114,   115,   218,   116,     5,     6,     3,
       4,   217,   219,   226,     7,   223,   194,     8,   191,     0,
       9,    10,    11,    12,    13,     0,     5,     6,     3,     4,
      43,     0,     0,     7,     0,     0,     8,     0,     0,     9,
      10,    11,     0,    13,     0,     5,     6,     3,     4,     0,
     127,     0,     7,     0,     0,     8,     0,     0,     9,    10,
      11,     0,    13,     0,     5,     6,     3,     4,     0,   215,
       0,     7,     0,     0,     8,     0,     0,     9,    10,    11,
       0,    13,     0,     5,     6,     3,     4,     0,   222,     0,
       7,     0,     0,     8,     0,     0,     9,    10,    11,     0,
      13,     0,     5,     6,    92,    93,    94,    95,    96,     7,
       0,     0,     8,     0,     0,     9,    10,    11,    91,    13,
      92,    93,    94,    95,    96,     0,    92,    93,    94,    95,
      96,     0,   117,   118,   119,   120,   121,   122,    26,   104,
       0,     0,     0,     0,    27,    28,    29,    30,    31,    32,
      33,    34,    92,    93,    94,    95,    96,    35,    98,     0,
      92,    93,    94,    95,    96,   178,    99,     0,    92,    93,
      94,    95,    96,   100,     0,    92,    93,    94,    95,    96,
     101,     0,    92,    93,    94,    95,    96,   102,     0,    92,
      93,    94,    95,    96,   103,     0,    92,    93,    94,    95,
      96,   137,     0,    92,    93,    94,    95,    96,   141,     0,
      92,    93,    94,    95,    96,    92,    93,    94,    95,    96
};

static const yytype_int16 yycheck[] =
{
       1,     4,     8,     1,     8,     9,   113,     1,     3,   190,
      11,    42,     3,    11,     5,     6,     7,     3,    22,   126,
      10,    11,    12,    13,    14,   206,    29,     3,     3,     3,
       5,     6,     7,     8,    20,    21,    29,    28,    44,    45,
      22,    47,    43,     3,     4,    43,    28,    78,    79,    43,
      13,    44,    45,    26,    47,    46,    29,    48,    49,    50,
      28,    51,   169,    26,    27,    28,    29,    30,    31,     9,
      28,    34,    35,    48,    49,    50,    39,   184,     8,     9,
      20,    21,    28,   114,   115,   116,    87,    44,     4,    87,
      47,    54,    22,    87,   125,    58,    28,   204,   129,     3,
       8,     5,     6,     7,   211,    10,    11,    12,    13,    14,
      73,     9,   113,    26,   221,   113,    29,     3,     8,     5,
       6,     7,    31,    32,    29,   126,    25,    26,   126,    92,
      93,    94,    95,    96,     3,     3,     5,     6,     7,    12,
      13,    14,   105,    29,    48,    49,    50,    31,    32,     8,
     181,     8,     9,     8,   117,   118,   119,   120,   121,   122,
     123,     5,    48,    49,    50,     8,   197,    34,   169,    29,
       9,   169,    25,    26,     3,   138,     8,    28,    28,    48,
      49,    50,    29,   184,    44,    45,   184,    47,    22,   190,
       8,     8,   190,   156,     9,    23,   190,    44,    45,    44,
      47,     3,    24,   204,   205,   206,   204,   205,   206,     5,
     211,   205,   206,   211,    28,   216,   179,    29,   216,     8,
     221,    24,   216,   221,    29,     4,    23,     0,    29,    28,
       3,     4,    44,    45,     3,    47,   199,     3,    29,    44,
      45,    24,    47,    44,    45,   208,    47,    20,    21,     3,
       4,     8,    24,     8,    27,   219,   219,    30,   176,    -1,
      33,    34,    35,    36,    37,    -1,    20,    21,     3,     4,
      24,    -1,    -1,    27,    -1,    -1,    30,    -1,    -1,    33,
      34,    35,    -1,    37,    -1,    20,    21,     3,     4,    -1,
      25,    -1,    27,    -1,    -1,    30,    -1,    -1,    33,    34,
      35,    -1,    37,    -1,    20,    21,     3,     4,    -1,    25,
      -1,    27,    -1,    -1,    30,    -1,    -1,    33,    34,    35,
      -1,    37,    -1,    20,    21,     3,     4,    -1,    25,    -1,
      27,    -1,    -1,    30,    -1,    -1,    33,    34,    35,    -1,
      37,    -1,    20,    21,    10,    11,    12,    13,    14,    27,
      -1,    -1,    30,    -1,    -1,    33,    34,    35,     8,    37,
      10,    11,    12,    13,    14,    -1,    10,    11,    12,    13,
      14,    -1,    38,    39,    40,    41,    42,    43,     9,    23,
      -1,    -1,    -1,    -1,    15,    16,    17,    18,    19,    20,
      21,    22,    10,    11,    12,    13,    14,    28,     8,    -1,
      10,    11,    12,    13,    14,    23,     8,    -1,    10,    11,
      12,    13,    14,     8,    -1,    10,    11,    12,    13,    14,
       8,    -1,    10,    11,    12,    13,    14,     8,    -1,    10,
      11,    12,    13,    14,     8,    -1,    10,    11,    12,    13,
      14,     8,    -1,    10,    11,    12,    13,    14,     8,    -1,
      10,    11,    12,    13,    14,    10,    11,    12,    13,    14
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    53,     0,     3,     4,    20,    21,    27,    30,    33,
      34,    35,    36,    37,    54,    55,    56,    57,    58,    60,
      65,    68,    69,    70,    75,    77,     9,    15,    16,    17,
      18,    19,    20,    21,    22,    28,     3,     3,     3,    28,
      28,    28,    28,    24,    54,    63,     4,     3,     5,     6,
       7,     8,    48,    49,    50,    58,    75,    78,     9,     8,
      78,    78,    78,    78,    78,    78,     8,     8,    78,    29,
      76,    78,     8,     9,    22,     8,     8,    78,    28,    46,
      64,    78,     3,     4,    66,    64,    54,    62,    34,     3,
      78,     8,    10,    11,    12,    13,    14,    78,     8,     8,
       8,     8,     8,     8,    23,    26,    29,     7,    78,     5,
      29,    64,    64,    29,    44,    45,    47,    38,    39,    40,
      41,    42,    43,     9,     3,     8,    29,    25,    54,    28,
      28,    51,    78,    78,    78,    78,    78,     8,    22,    78,
       8,     8,    23,     8,    29,    63,    64,    64,    64,    78,
      78,    78,    78,    78,    78,    78,     9,    64,    63,    64,
       4,    29,    73,    74,    78,     8,     9,    22,    31,    32,
      61,    78,     8,    29,     3,    72,    26,    29,    23,    24,
       5,    28,    63,    31,    32,     3,    20,    21,    67,     8,
      24,    74,    71,    59,    78,    23,    64,    28,    63,     9,
      20,    21,     3,     3,    29,    62,    24,    25,    26,     8,
       9,    29,    64,    78,    63,    25,    62,     8,    78,    24,
      63,    29,    25,    59,    63,    25,     8
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    57,    58,    58,    59,    59,    60,    60,    60,
      60,    61,    61,    62,    62,    63,    63,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    65,    66,
      66,    66,    67,    67,    67,    67,    67,    67,    68,    69,
      71,    70,    72,    70,    73,    73,    74,    75,    75,    76,
      76,    77,    77,    78,    78,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    78,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     2,     2,     0,     1,     1,     1,     1,     1,
       1,     1,     2,     1,     3,     5,    10,     6,     9,    13,
       5,     4,     4,     4,     4,     4,     4,     3,     3,     3,
       3,     4,     5,     4,     7,     1,     3,     5,     7,     6,
       8,     5,     6,     1,     2,     3,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     3,     9,     3,
       4,     0,     3,     2,     2,     2,     2,     0,     5,     7,
       0,    10,     0,     9,     1,     3,     2,     4,     3,     1,
       3,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3
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
  case 2: /* program: program stmt  */
#line 63 "parser.y"
                            { root = createStmtList(root, (yyvsp[0].node)); (yyval.node) = root; }
#line 1344 "parser.tab.c"
    break;

  case 3: /* program: program function_def  */
#line 64 "parser.y"
                            { root = createStmtList(root, (yyvsp[0].node)); (yyval.node) = root; }
#line 1350 "parser.tab.c"
    break;

  case 4: /* program: %empty  */
#line 65 "parser.y"
                            { (yyval.node) = NULL; }
#line 1356 "parser.tab.c"
    break;

  case 12: /* stmt: function_call SEMICOLON  */
#line 76 "parser.y"
                              { (yyval.node) = (yyvsp[-1].node); }
#line 1362 "parser.tab.c"
    break;

  case 14: /* declaration: TYPE IDENTIFIER SEMICOLON  */
#line 82 "parser.y"
        { 
          (yyval.node) = createDecl((yyvsp[-1].str));
          char varType;
          if (strcmp((yyvsp[-2].str), "char") == 0) varType = 'c';
          else if (strcmp((yyvsp[-2].str), "string") == 0) varType = 's';
          else if (strcmp((yyvsp[-2].str), "bool") == 0) varType = 'b';
          else varType = 'i';
          addVar((yyvsp[-1].str), 1, 0, varType);
          // printf("Variable declaration: %s\n", $2); 
        }
#line 1377 "parser.tab.c"
    break;

  case 15: /* declaration: TYPE IDENTIFIER EQ expression SEMICOLON  */
#line 93 "parser.y"
        { 
          (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node));
          char varType;
          if (strcmp((yyvsp[-4].str), "char") == 0) varType = 'c';
          else if (strcmp((yyvsp[-4].str), "string") == 0) varType = 's';
          else if (strcmp((yyvsp[-4].str), "bool") == 0) varType = 'b';
          else varType = 'i';
          addVar((yyvsp[-3].str), 1, (yyvsp[-1].node)->value, varType);
          // printf("Initialized variable: %s\n", $2);
        }
#line 1392 "parser.tab.c"
    break;

  case 16: /* declaration: TYPE IDENTIFIER LBRACKET NUMBER RBRACKET EQ LBRACE init_list RBRACE SEMICOLON  */
#line 104 "parser.y"
        { 
          int initCount;
          int* initValues = extractInitValues((yyvsp[-2].node), &initCount);
          (yyval.node) = createArrayDeclInit((yyvsp[-8].str), (yyvsp[-6].num), (yyvsp[-2].node));
          char varType = (strcmp((yyvsp[-9].str), "char") == 0) ? 'c' : 'i';
          addArrayWithInit((yyvsp[-8].str), (yyvsp[-6].num), varType, initValues, initCount);
          // printf("Initialized array declaration: %s[%d] with %d values\n", $2, $4, initCount);
        }
#line 1405 "parser.tab.c"
    break;

  case 17: /* declaration: TYPE IDENTIFIER LBRACKET NUMBER RBRACKET SEMICOLON  */
#line 113 "parser.y"
        { 
          (yyval.node) = createArrayDecl((yyvsp[-4].str), (yyvsp[-2].num));
          char varType = (strcmp((yyvsp[-5].str), "char") == 0) ? 'c' : 'i';
          addArray((yyvsp[-4].str), (yyvsp[-2].num), varType);
          // printf("Array declaration: %s[%d]\n", $2, $4);
        }
#line 1416 "parser.tab.c"
    break;

  case 18: /* declaration: TYPE IDENTIFIER LBRACKET NUMBER RBRACKET LBRACKET NUMBER RBRACKET SEMICOLON  */
#line 120 "parser.y"
        { 
          (yyval.node) = create2DArrayDecl((yyvsp[-7].str), (yyvsp[-5].num), (yyvsp[-2].num));
          char varType = (strcmp((yyvsp[-8].str), "char") == 0) ? 'c' : 'i';
          add2DArray((yyvsp[-7].str), (yyvsp[-5].num), (yyvsp[-2].num), varType);
          // printf("2D Array declaration: %s[%d][%d]\n", $2, $4, $7);
        }
#line 1427 "parser.tab.c"
    break;

  case 19: /* declaration: TYPE IDENTIFIER LBRACKET NUMBER RBRACKET LBRACKET NUMBER RBRACKET EQ LBRACE init_list RBRACE SEMICOLON  */
#line 127 "parser.y"
        { 
          int initCount;
          int* initValues = extractInitValues((yyvsp[-2].node), &initCount);
          (yyval.node) = create2DArrayDeclInit((yyvsp[-11].str), (yyvsp[-9].num), (yyvsp[-6].num), (yyvsp[-2].node));
          char varType = (strcmp((yyvsp[-12].str), "char") == 0) ? 'c' : 'i';
          add2DArrayWithInit((yyvsp[-11].str), (yyvsp[-9].num), (yyvsp[-6].num), varType, initValues, initCount);
          // printf("Initialized 2D array declaration: %s[%d][%d] with %d values\n", $2, $4, $7, initCount);
        }
#line 1440 "parser.tab.c"
    break;

  case 20: /* declaration: TYPE IDENTIFIER EQ STRING_LITERAL SEMICOLON  */
#line 136 "parser.y"
        {
            if (strcmp((yyvsp[-4].str), "string") == 0) {
                (yyval.node) = createStringDecl((yyvsp[-3].str), (yyvsp[-1].str));
                addStringVar((yyvsp[-3].str), (yyvsp[-1].str));
                // printf("String declaration: %s = \"%s\"\n", $2, $4);
            } else {
                fprintf(stderr, "Error: string literals must use 'string' type\n");
                exit(1);
            }
        }
#line 1455 "parser.tab.c"
    break;

  case 21: /* assignment: IDENTIFIER EQ expression SEMICOLON  */
#line 150 "parser.y"
        { 
          if (!isVarDeclared((yyvsp[-3].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-3].str));
              exit(1);
          }
          (yyval.node) = createAssign((yyvsp[-3].str), (yyvsp[-1].node)); 
          // printf("Assignment: %s\n", $1);
        }
#line 1468 "parser.tab.c"
    break;

  case 22: /* assignment: IDENTIFIER PLUSEQ expression SEMICOLON  */
#line 159 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-3].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-3].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-3].str));
          ASTNode* add = createBinOp('+', var, (yyvsp[-1].node));
          (yyval.node) = createAssign((yyvsp[-3].str), add);
          // printf("Compound assignment: %s += \n", $1);
        }
#line 1483 "parser.tab.c"
    break;

  case 23: /* assignment: IDENTIFIER MINUSEQ expression SEMICOLON  */
#line 170 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-3].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-3].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-3].str));
          ASTNode* sub = createBinOp('-', var, (yyvsp[-1].node));
          (yyval.node) = createAssign((yyvsp[-3].str), sub);
          // printf("Compound assignment: %s -= \n", $1);
        }
#line 1498 "parser.tab.c"
    break;

  case 24: /* assignment: IDENTIFIER MULTEQ expression SEMICOLON  */
#line 181 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-3].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-3].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-3].str));
          ASTNode* mul = createBinOp('*', var, (yyvsp[-1].node));
          (yyval.node) = createAssign((yyvsp[-3].str), mul);
          // printf("Compound assignment: %s *= \n", $1);
        }
#line 1513 "parser.tab.c"
    break;

  case 25: /* assignment: IDENTIFIER DIVEQ expression SEMICOLON  */
#line 192 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-3].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-3].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-3].str));
          ASTNode* div = createBinOp('/', var, (yyvsp[-1].node));
          (yyval.node) = createAssign((yyvsp[-3].str), div);
          // printf("Compound assignment: %s /= \n", $1);
        }
#line 1528 "parser.tab.c"
    break;

  case 26: /* assignment: IDENTIFIER MODEQ expression SEMICOLON  */
#line 203 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-3].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-3].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-3].str));
          ASTNode* mod = createBinOp('%', var, (yyvsp[-1].node));
          (yyval.node) = createAssign((yyvsp[-3].str), mod);
          // printf("Compound assignment: %s %%= \n", $1);
        }
#line 1543 "parser.tab.c"
    break;

  case 27: /* assignment: IDENTIFIER PLUSPLUS SEMICOLON  */
#line 214 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-2].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-2].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-2].str));
          ASTNode* one = createNum(1);
          ASTNode* add = createBinOp('+', var, one);
          (yyval.node) = createAssign((yyvsp[-2].str), add);
          // printf("Post-increment: %s++\n", $1);
        }
#line 1559 "parser.tab.c"
    break;

  case 28: /* assignment: IDENTIFIER MINUSMINUS SEMICOLON  */
#line 226 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-2].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-2].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-2].str));
          ASTNode* one = createNum(1);
          ASTNode* sub = createBinOp('-', var, one);
          (yyval.node) = createAssign((yyvsp[-2].str), sub);
          // printf("Post-decrement: %s--\n", $1);
        }
#line 1575 "parser.tab.c"
    break;

  case 29: /* assignment: PLUSPLUS IDENTIFIER SEMICOLON  */
#line 238 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-1].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-1].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-1].str));
          ASTNode* one = createNum(1);
          ASTNode* add = createBinOp('+', var, one);
          (yyval.node) = createAssign((yyvsp[-1].str), add);
          // printf("Pre-increment: ++%s\n", $2);
        }
#line 1591 "parser.tab.c"
    break;

  case 30: /* assignment: MINUSMINUS IDENTIFIER SEMICOLON  */
#line 250 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-1].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-1].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-1].str));
          ASTNode* one = createNum(1);
          ASTNode* sub = createBinOp('-', var, one);
          (yyval.node) = createAssign((yyvsp[-1].str), sub);
          // printf("Pre-decrement: --%s\n", $2);
        }
#line 1607 "parser.tab.c"
    break;

  case 31: /* assignment: array_access EQ expression SEMICOLON  */
#line 262 "parser.y"
        {
          (yyval.node) = createArrayAssign((yyvsp[-3].node), (yyvsp[-1].node));
          // printf("Array assignment\n");
        }
#line 1616 "parser.tab.c"
    break;

  case 32: /* print_stmt: KEYWORD LPAREN expression RPAREN SEMICOLON  */
#line 270 "parser.y"
        {
           (yyval.node) = createPrint((yyvsp[-2].node));
            // printf("Print statement created\n");
        }
#line 1625 "parser.tab.c"
    break;

  case 33: /* array_access: IDENTIFIER LBRACKET expression RBRACKET  */
#line 278 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-3].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-3].str));
              exit(1);
          }
          (yyval.node) = createArrayAccess((yyvsp[-3].str), (yyvsp[-1].node));
        }
#line 1637 "parser.tab.c"
    break;

  case 34: /* array_access: IDENTIFIER LBRACKET expression RBRACKET LBRACKET expression RBRACKET  */
#line 286 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-6].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-6].str));
              exit(1);
          }
          (yyval.node) = create2DArrayAccess((yyvsp[-6].str), (yyvsp[-4].node), (yyvsp[-1].node));
        }
#line 1649 "parser.tab.c"
    break;

  case 35: /* init_list: expression  */
#line 296 "parser.y"
                       { (yyval.node) = (yyvsp[0].node); }
#line 1655 "parser.tab.c"
    break;

  case 36: /* init_list: init_list COMMA expression  */
#line 297 "parser.y"
                                 { (yyval.node) = createInitList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 1661 "parser.tab.c"
    break;

  case 37: /* if_stmt: IF LPAREN condition RPAREN stmt_block  */
#line 302 "parser.y"
        {
          (yyval.node) = createIf((yyvsp[-2].node), (yyvsp[0].node), NULL, NULL);
          // printf("If statement created\n");
        }
#line 1670 "parser.tab.c"
    break;

  case 38: /* if_stmt: IF LPAREN condition RPAREN stmt_block ELSE stmt_block  */
#line 307 "parser.y"
        {
          (yyval.node) = createIf((yyvsp[-4].node), (yyvsp[-2].node), NULL, (yyvsp[0].node));
          // printf("If-else statement created\n");
        }
#line 1679 "parser.tab.c"
    break;

  case 39: /* if_stmt: IF LPAREN condition RPAREN stmt_block elseif_list  */
#line 312 "parser.y"
        {
          (yyval.node) = createIf((yyvsp[-3].node), (yyvsp[-1].node), (yyvsp[0].node), NULL);
          // printf("If-elseif statement created\n");
        }
#line 1688 "parser.tab.c"
    break;

  case 40: /* if_stmt: IF LPAREN condition RPAREN stmt_block elseif_list ELSE stmt_block  */
#line 317 "parser.y"
        {
          (yyval.node) = createIf((yyvsp[-5].node), (yyvsp[-3].node), (yyvsp[-2].node), (yyvsp[0].node));
          // printf("If-elseif-else statement created\n");
        }
#line 1697 "parser.tab.c"
    break;

  case 41: /* elseif_list: ELSEIF LPAREN condition RPAREN stmt_block  */
#line 325 "parser.y"
        {
          (yyval.node) = createElseIf((yyvsp[-2].node), (yyvsp[0].node));
        }
#line 1705 "parser.tab.c"
    break;

  case 42: /* elseif_list: elseif_list ELSEIF LPAREN condition RPAREN stmt_block  */
#line 329 "parser.y"
        {
          (yyval.node) = createElseIfList((yyvsp[-5].node), (yyvsp[-2].node), (yyvsp[0].node));
        }
#line 1713 "parser.tab.c"
    break;

  case 43: /* stmt_list: stmt  */
#line 335 "parser.y"
            { (yyval.node) = (yyvsp[0].node); }
#line 1719 "parser.tab.c"
    break;

  case 44: /* stmt_list: stmt_list stmt  */
#line 336 "parser.y"
                     { (yyval.node) = createStmtList((yyvsp[-1].node), (yyvsp[0].node)); }
#line 1725 "parser.tab.c"
    break;

  case 45: /* stmt_block: LBRACE stmt_list RBRACE  */
#line 340 "parser.y"
                               { (yyval.node) = (yyvsp[-1].node); }
#line 1731 "parser.tab.c"
    break;

  case 46: /* stmt_block: stmt  */
#line 341 "parser.y"
                               { (yyval.node) = (yyvsp[0].node); }
#line 1737 "parser.tab.c"
    break;

  case 47: /* condition: expression EQEQ expression  */
#line 345 "parser.y"
                                 { (yyval.node) = createCondition("==", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1743 "parser.tab.c"
    break;

  case 48: /* condition: expression NEQ expression  */
#line 346 "parser.y"
                                 { (yyval.node) = createCondition("!=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1749 "parser.tab.c"
    break;

  case 49: /* condition: expression LT expression  */
#line 347 "parser.y"
                                 { (yyval.node) = createCondition("<", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1755 "parser.tab.c"
    break;

  case 50: /* condition: expression LE expression  */
#line 348 "parser.y"
                                 { (yyval.node) = createCondition("<=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1761 "parser.tab.c"
    break;

  case 51: /* condition: expression GT expression  */
#line 349 "parser.y"
                                 { (yyval.node) = createCondition(">", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1767 "parser.tab.c"
    break;

  case 52: /* condition: expression GE expression  */
#line 350 "parser.y"
                                 { (yyval.node) = createCondition(">=", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1773 "parser.tab.c"
    break;

  case 53: /* condition: condition AND condition  */
#line 351 "parser.y"
                                 { (yyval.node) = createCondition("&&", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1779 "parser.tab.c"
    break;

  case 54: /* condition: condition OR condition  */
#line 352 "parser.y"
                                 { (yyval.node) = createCondition("||", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1785 "parser.tab.c"
    break;

  case 55: /* condition: condition XOR condition  */
#line 353 "parser.y"
                                 { (yyval.node) = createCondition("xor", (yyvsp[-2].node), (yyvsp[0].node)); }
#line 1791 "parser.tab.c"
    break;

  case 56: /* condition: NOT condition  */
#line 354 "parser.y"
                                 { (yyval.node) = createCondition("!", (yyvsp[0].node), NULL); }
#line 1797 "parser.tab.c"
    break;

  case 57: /* condition: LPAREN condition RPAREN  */
#line 355 "parser.y"
                                 { (yyval.node) = (yyvsp[-1].node); }
#line 1803 "parser.tab.c"
    break;

  case 58: /* for_stmt: FOR LPAREN loop_init SEMICOLON condition SEMICOLON loop_update RPAREN stmt_block  */
#line 360 "parser.y"
        {
          (yyval.node) = createFor((yyvsp[-6].node), (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));
          // printf("For loop created\n");
        }
#line 1812 "parser.tab.c"
    break;

  case 59: /* loop_init: IDENTIFIER EQ expression  */
#line 367 "parser.y"
                               { 
          if (!isVarDeclared((yyvsp[-2].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[-2].str));
              exit(1);
          }
          (yyval.node) = createAssign((yyvsp[-2].str), (yyvsp[0].node));
      }
#line 1824 "parser.tab.c"
    break;

  case 60: /* loop_init: TYPE IDENTIFIER EQ expression  */
#line 374 "parser.y"
                                    {
          (yyval.node) = createAssign((yyvsp[-2].str), (yyvsp[0].node));
          char varType;
          if (strcmp((yyvsp[-3].str), "char") == 0) varType = 'c';
          else if (strcmp((yyvsp[-3].str), "string") == 0) varType = 's';
          else if (strcmp((yyvsp[-3].str), "bool") == 0) varType = 'b';
          else varType = 'i';
          addVar((yyvsp[-2].str), 1, (yyvsp[0].node)->value, varType);
          // printf("Loop variable declaration: %s\n", $2);
      }
#line 1839 "parser.tab.c"
    break;

  case 61: /* loop_init: %empty  */
#line 384 "parser.y"
                  { (yyval.node) = NULL; }
#line 1845 "parser.tab.c"
    break;

  case 62: /* loop_update: IDENTIFIER EQ expression  */
#line 389 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-2].str))) {
              fprintf(stderr, "Error: variable '%s' not declared\n", (yyvsp[-2].str));
              exit(1);
          }
          (yyval.node) = createAssign((yyvsp[-2].str), (yyvsp[0].node));
        }
#line 1857 "parser.tab.c"
    break;

  case 63: /* loop_update: IDENTIFIER PLUSPLUS  */
#line 397 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-1].str))) {
              fprintf(stderr, "Error: variable '%s' not declared\n", (yyvsp[-1].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-1].str));
          ASTNode* one = createNum(1);
          ASTNode* add = createBinOp('+', var, one);
          (yyval.node) = createAssign((yyvsp[-1].str), add);
        }
#line 1872 "parser.tab.c"
    break;

  case 64: /* loop_update: IDENTIFIER MINUSMINUS  */
#line 408 "parser.y"
        {
          if (!isVarDeclared((yyvsp[-1].str))) {
              fprintf(stderr, "Error: variable '%s' not declared\n", (yyvsp[-1].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[-1].str));
          ASTNode* one = createNum(1);
          ASTNode* sub = createBinOp('-', var, one);
          (yyval.node) = createAssign((yyvsp[-1].str), sub);
        }
#line 1887 "parser.tab.c"
    break;

  case 65: /* loop_update: PLUSPLUS IDENTIFIER  */
#line 419 "parser.y"
        {
          if (!isVarDeclared((yyvsp[0].str))) {
              fprintf(stderr, "Error: variable '%s' not declared\n", (yyvsp[0].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[0].str));
          ASTNode* one = createNum(1);
          ASTNode* add = createBinOp('+', var, one);
          (yyval.node) = createAssign((yyvsp[0].str), add);
        }
#line 1902 "parser.tab.c"
    break;

  case 66: /* loop_update: MINUSMINUS IDENTIFIER  */
#line 430 "parser.y"
        {
          if (!isVarDeclared((yyvsp[0].str))) {
              fprintf(stderr, "Error: variable '%s' not declared\n", (yyvsp[0].str));
              exit(1);
          }
          ASTNode* var = createVar((yyvsp[0].str));
          ASTNode* one = createNum(1);
          ASTNode* sub = createBinOp('-', var, one);
          (yyval.node) = createAssign((yyvsp[0].str), sub);
        }
#line 1917 "parser.tab.c"
    break;

  case 67: /* loop_update: %empty  */
#line 440 "parser.y"
                  { (yyval.node) = NULL; }
#line 1923 "parser.tab.c"
    break;

  case 68: /* while_stmt: WHILE LPAREN condition RPAREN stmt_block  */
#line 445 "parser.y"
        {
          (yyval.node) = createWhile((yyvsp[-2].node), (yyvsp[0].node));
          // printf("While loop created\n");
        }
#line 1932 "parser.tab.c"
    break;

  case 69: /* do_while_stmt: DO stmt_block WHILE LPAREN condition RPAREN SEMICOLON  */
#line 453 "parser.y"
        {
          (yyval.node) = createDoWhile((yyvsp[-2].node), (yyvsp[-5].node));
          // printf("Do-while loop created\n");
        }
#line 1941 "parser.tab.c"
    break;

  case 70: /* $@1: %empty  */
#line 461 "parser.y"
        {
          // Mid-rule action: Add function and parameters BEFORE parsing body
          if (!addFunction((yyvsp[-3].str), (yyvsp[-4].str), (yyvsp[-1].node))) {
              fprintf(stderr, "Failed to add function '%s'\n", (yyvsp[-3].str));
              exit(1);
          }
          
          // Add parameters as local variables before parsing function body
          ASTNode* param = (yyvsp[-1].node);
          while (param) {
              char varType;
              if (strcmp(param->returnType, "char") == 0) varType = 'c';
              else if (strcmp(param->returnType, "string") == 0) varType = 's';
              else if (strcmp(param->returnType, "bool") == 0) varType = 'b';
              else varType = 'i';
              addVar(param->name, 1, 0, varType);
              param = param->next;
          }
        }
#line 1965 "parser.tab.c"
    break;

  case 71: /* function_def: FUNCTION TYPE IDENTIFIER LPAREN param_list RPAREN $@1 LBRACE stmt_list RBRACE  */
#line 481 "parser.y"
        {
          (yyval.node) = createFunctionDecl((yyvsp[-8].str), (yyvsp[-7].str), (yyvsp[-5].node), (yyvsp[-1].node));
          // printf("Function declaration: %s\n", $3);
        }
#line 1974 "parser.tab.c"
    break;

  case 72: /* $@2: %empty  */
#line 486 "parser.y"
        {
          // Mid-rule action for function with no parameters
          if (!addFunction((yyvsp[-2].str), (yyvsp[-3].str), NULL)) {
              fprintf(stderr, "Failed to add function '%s'\n", (yyvsp[-2].str));
              exit(1);
          }
        }
#line 1986 "parser.tab.c"
    break;

  case 73: /* function_def: FUNCTION TYPE IDENTIFIER LPAREN RPAREN $@2 LBRACE stmt_list RBRACE  */
#line 494 "parser.y"
        {
          (yyval.node) = createFunctionDecl((yyvsp[-7].str), (yyvsp[-6].str), NULL, (yyvsp[-1].node));
          // printf("Function declaration: %s (no params)\n", $3);
        }
#line 1995 "parser.tab.c"
    break;

  case 74: /* param_list: param  */
#line 501 "parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 2001 "parser.tab.c"
    break;

  case 75: /* param_list: param_list COMMA param  */
#line 502 "parser.y"
                                 { (yyval.node) = createParamList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2007 "parser.tab.c"
    break;

  case 76: /* param: TYPE IDENTIFIER  */
#line 507 "parser.y"
        {
          (yyval.node) = createParam((yyvsp[-1].str), (yyvsp[0].str));
        }
#line 2015 "parser.tab.c"
    break;

  case 77: /* function_call: IDENTIFIER LPAREN arg_list RPAREN  */
#line 514 "parser.y"
        {
          if (!validateFunctionCall((yyvsp[-3].str), (yyvsp[-1].node))) {
              exit(1);
          }
          (yyval.node) = createFunctionCall((yyvsp[-3].str), (yyvsp[-1].node));
        }
#line 2026 "parser.tab.c"
    break;

  case 78: /* function_call: IDENTIFIER LPAREN RPAREN  */
#line 521 "parser.y"
        {
          if (!validateFunctionCall((yyvsp[-2].str), NULL)) {
              exit(1);
          }
          (yyval.node) = createFunctionCall((yyvsp[-2].str), NULL);
        }
#line 2037 "parser.tab.c"
    break;

  case 79: /* arg_list: expression  */
#line 530 "parser.y"
                                 { (yyval.node) = (yyvsp[0].node); }
#line 2043 "parser.tab.c"
    break;

  case 80: /* arg_list: arg_list COMMA expression  */
#line 531 "parser.y"
                                 { (yyval.node) = createArgList((yyvsp[-2].node), (yyvsp[0].node)); }
#line 2049 "parser.tab.c"
    break;

  case 81: /* return_stmt: RETURN expression SEMICOLON  */
#line 536 "parser.y"
        {
          (yyval.node) = createReturn((yyvsp[-1].node));
        }
#line 2057 "parser.tab.c"
    break;

  case 82: /* return_stmt: RETURN SEMICOLON  */
#line 540 "parser.y"
        {
          (yyval.node) = createReturn(NULL);
        }
#line 2065 "parser.tab.c"
    break;

  case 83: /* expression: NUMBER  */
#line 546 "parser.y"
                         { (yyval.node) = createNum((yyvsp[0].num)); }
#line 2071 "parser.tab.c"
    break;

  case 84: /* expression: CHAR_LITERAL  */
#line 547 "parser.y"
                         { (yyval.node) = createChar((yyvsp[0].character)); }
#line 2077 "parser.tab.c"
    break;

  case 85: /* expression: STRING_LITERAL  */
#line 548 "parser.y"
                         { (yyval.node) = createStringLiteral((yyvsp[0].str)); }
#line 2083 "parser.tab.c"
    break;

  case 86: /* expression: TRUE  */
#line 549 "parser.y"
                         { (yyval.node) = createBool(1); }
#line 2089 "parser.tab.c"
    break;

  case 87: /* expression: FALSE  */
#line 550 "parser.y"
                         { (yyval.node) = createBool(0); }
#line 2095 "parser.tab.c"
    break;

  case 88: /* expression: IDENTIFIER  */
#line 551 "parser.y"
                         { 
          if (!isVarDeclared((yyvsp[0].str)) && !isFunctionDeclared((yyvsp[0].str))) {
              errorUndeclaredVariable(yylineno, (yyvsp[0].str));
              exit(1);
          }
          (yyval.node) = createVar((yyvsp[0].str)); 
      }
#line 2107 "parser.tab.c"
    break;

  case 89: /* expression: function_call  */
#line 558 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2113 "parser.tab.c"
    break;

  case 90: /* expression: array_access  */
#line 559 "parser.y"
                         { (yyval.node) = (yyvsp[0].node); }
#line 2119 "parser.tab.c"
    break;

  case 91: /* expression: '(' expression ')'  */
#line 560 "parser.y"
                         { (yyval.node) = (yyvsp[-1].node); }
#line 2125 "parser.tab.c"
    break;

  case 92: /* expression: expression PLUS expression  */
#line 561 "parser.y"
                                     { (yyval.node) = createBinOp('+', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2131 "parser.tab.c"
    break;

  case 93: /* expression: expression MINUS expression  */
#line 562 "parser.y"
                                     { (yyval.node) = createBinOp('-', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2137 "parser.tab.c"
    break;

  case 94: /* expression: expression MULTIPLY expression  */
#line 563 "parser.y"
                                     { (yyval.node) = createBinOp('*', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2143 "parser.tab.c"
    break;

  case 95: /* expression: expression DIVIDE expression  */
#line 564 "parser.y"
                                     { (yyval.node) = createBinOp('/', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2149 "parser.tab.c"
    break;

  case 96: /* expression: expression MODULO expression  */
#line 565 "parser.y"
                                     { (yyval.node) = createBinOp('%', (yyvsp[-2].node), (yyvsp[0].node)); }
#line 2155 "parser.tab.c"
    break;


#line 2159 "parser.tab.c"

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

#line 568 "parser.y"


void yyerror(const char* s) {
    // Try to provide more context about the error
    if (strstr(s, "syntax error")) {
        if (yytext && strlen(yytext) > 0) {
            reportError(yylineno, yytext, ERROR_SYNTAX, 
                       "Unexpected token or syntax error");
        } else {
            reportError(yylineno, "", ERROR_SYNTAX, 
                       "Syntax error in source code");
        }
    } else {
        reportError(yylineno, yytext ? yytext : "", ERROR_SYNTAX, s);
    }
}

int* extractInitValues(ASTNode* initList, int* count) {
    if (!initList) {
        *count = 0;
        return NULL;
    }
    
    *count = 0;
    ASTNode* cur = initList;
    while (cur) {
        (*count)++;
        cur = cur->next;
    }
    
    int* values = malloc((*count) * sizeof(int));
    cur = initList;
    int i = 0;
    while (cur && i < *count) {
        if (strcmp(cur->type, "num") == 0 || strcmp(cur->type, "char") == 0) {
            values[i] = cur->value;
        } else {
            values[i] = 0;
        }
        cur = cur->next;
        i++;
    }
    
    return values;
}
