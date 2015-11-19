/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "parser.y" /* yacc.c:339  */

#include <bits/stdc++.h>

class Visitor;
#include "AST.h"
#include "Visitor.h"
#include "VisitorIR.h"
using namespace std;

extern int yylex(), yylineno;
extern int yyparse();
extern FILE* yyin, *yyout;
FILE *XML_fp, *bison_fp, *LLVM_fp;

void yyerror(const char* s);
void operatorOutput(string op);

enum VERSION{DEBUG, RELEASE};
int version=DEBUG;

int unary=0;

#line 89 "parser.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.tab.h".  */
#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    T_INT = 258,
    STRING_LITERAL = 259,
    IDENTIFIER = 260,
    PROG_ID = 261,
    CHAR_LITERAL = 262,
    BOOLEAN = 263,
    CALLOUT = 264,
    TEQUAL = 265,
    INT = 266,
    TPLUS = 267,
    TMINUS = 268,
    TMUL = 269,
    TDIV = 270,
    NOT = 271,
    MOD = 272,
    RBRACE = 273,
    LBRACE = 274,
    T_NEWLINE = 275,
    T_QUIT = 276,
    START = 277,
    TLE = 278,
    GE = 279,
    AND = 280,
    TEQ = 281,
    OR = 282,
    TLROUND = 283,
    TRROUND = 284,
    TLSQUARE = 285,
    TRSQUARE = 286,
    FALSE = 287,
    TRUE = 288,
    VOID = 289,
    IF = 290,
    ELSE = 291,
    FOR = 292,
    RETURN = 293,
    CONTINUE = 294,
    BREAK = 295,
    TLESS = 296,
    TGREAT = 297,
    SEMI_COLON = 298,
    TCOMMA = 299,
    NOT_EQUAL = 300
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 25 "parser.y" /* yacc.c:355  */

	int number;
	int bval;
	char character;
	char string[100];
	ASTMain *ast_main;
	ASTStatement *_aSTStatement;
	ASTIdentifier *identifier;
	ASTArrayIdentifier *arrayIdentifier;
	ASTField_Declaration *_ASTField_Declaration;
	ASTMethod_Declaration *_ASTMethod_Declaration;
	ASTParam_Declaration *_ASTParam_Declaration;

	Declaration *_Declaration;
	CalloutArgs * _Callout_Args;
	Args* _Argss;
	Def* _Def;

	std::list<Declaration *>*_Declarations;
	std::list<ASTField_Declaration *> *_ASTField_Declarations;

	std::list<ASTParam_Declaration *> *_ASTParam_Declarations;
	std::list<Args*> *_Callout_Argss; 
	std::list<ASTStatement*>* _aSTStatements;
	std::list<ExpressionRight *> *_ExpressionRights;
	std::list<ASTDeclarations *> *Declarations_;
    std::list<Expression *> *_Expressions;
	RUnaryExpr* _RUnaryExpr;
	ExpressionRight* _ExpressionRight;
	RBinaryExpr* _RBinaryExpr;
	BinaryExpr* _BinaryExpr;
	Expression* _Expression;
	
	ASTDeclarations * _ASTDeclarations;
	ASTLocation* _ASTLocation;
	LangType *type;
	std::string *_string;
	ReturnValue *_ReturnValue;

#line 215 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 230 "parser.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   254

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  46
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  146

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   300

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   119,   119,   127,   129,   132,   137,   139,   143,   149,
     154,   158,   164,   169,   173,   178,   182,   187,   191,   194,
     199,   202,   208,   213,   216,   219,   222,   225,   228,   233,
     238,   243,   248,   255,   259,   263,   270,   270,   275,   275,
     282,   284,   286,   288,   290,   292,   295,   298,   301,   304,
     310,   314,   318,   322,   334,   348,   348,   350,   353,   357,
     361,   364,   364,   368,   371,   374,   377,   380,   383,   386,
     390,   392,   395,   398,   403,   406,   408,   412,   416,   420
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_INT", "STRING_LITERAL", "IDENTIFIER",
  "PROG_ID", "CHAR_LITERAL", "BOOLEAN", "CALLOUT", "TEQUAL", "INT",
  "TPLUS", "TMINUS", "TMUL", "TDIV", "NOT", "MOD", "RBRACE", "LBRACE",
  "T_NEWLINE", "T_QUIT", "START", "TLE", "GE", "AND", "TEQ", "OR",
  "TLROUND", "TRROUND", "TLSQUARE", "TRSQUARE", "FALSE", "TRUE", "VOID",
  "IF", "ELSE", "FOR", "RETURN", "CONTINUE", "BREAK", "TLESS", "TGREAT",
  "SEMI_COLON", "TCOMMA", "NOT_EQUAL", "$accept", "Program",
  "Declaration_list", "Declaration", "Method_Declaration", "Block",
  "Field_Declarations", "Field_Declaration", "Declarations",
  "Param_Declarations", "Param_Declaration", "Def", "Location",
  "InExpression", "BinaryExpr", "Expression", "RUnary_Expr", "$@1", "$@2",
  "RBinaryExpr", "Expression_Right", "Bool", "Statements", "Statement",
  "$@3", "Return_Value", "Callout_Argss", "Argss", "Type", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300
};
# endif

#define YYPACT_NINF -95

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-95)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -10,    16,    23,    31,   -95,    13,   -95,   -95,   -95,    76,
     -95,   -95,   -95,    46,   -95,   -95,   -26,   -95,    24,    13,
      64,    65,    42,    29,    65,   -95,    44,    55,   -95,    72,
      13,   -95,   -95,    13,   -95,   -95,    39,    50,    65,    27,
      67,    68,    87,    49,   -95,   -95,   -95,    89,    79,    57,
      13,    49,    61,    98,    56,    93,   -95,   -95,    74,   -95,
     -95,   -95,   -95,   -95,   -95,   -95,   -95,   148,   -95,   -95,
     -95,    56,   -95,    39,   -95,    85,    78,   -95,   -95,   -95,
      94,   -95,   114,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    56,    56,    56,    56,   148,   -95,   -95,    49,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
     -95,    80,    72,     2,    -8,   -95,    -8,    -8,   -95,   -95,
     -95,   231,   231,   164,   194,   164,   -95,    -4,    -4,   -95,
     -95,   -95,   237,   237,   179,   207,   179,    49,    69,    56,
     101,    72,   132,   -95,   -95,   -95
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     1,     0,    78,    77,    79,     0,
       5,     7,     6,     0,     2,     4,    19,    12,    14,    16,
       0,     0,     0,     0,     0,    22,     0,    19,    13,     0,
      16,    17,    18,    11,     8,    15,    58,     0,     0,    21,
       0,     0,     0,    71,    68,    67,    69,     0,     0,     0,
      11,     0,     0,     0,     0,     0,    54,    75,    21,    74,
      38,    36,    56,    55,    52,    50,    51,    76,    53,    66,
      70,     0,     9,    58,    10,     0,    72,    35,    34,    33,
       0,    61,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    59,    57,    60,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      20,     0,     0,     0,    39,    37,    45,    46,    47,    48,
      49,    40,    41,    43,    42,    44,    73,    28,    29,    30,
      31,    32,    23,    24,    26,    25,    27,     0,    63,     0,
       0,     0,     0,    62,    64,    65
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -95,   -95,   -95,   107,   -95,   -29,    73,   -30,   111,   103,
     -95,    77,   -28,   -95,   -95,   133,   -95,   -95,   -95,   -95,
     -53,   -95,    62,   -95,   -95,   -95,   -94,    91,    30
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     9,    10,    11,    46,    36,    12,    17,    22,
      23,    78,    64,    26,    79,    80,    65,    85,    84,    66,
      67,    68,    48,    49,   111,    69,    75,    76,    13
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      34,    82,    19,    37,    20,   126,    88,    89,    47,    90,
     102,   103,     1,   104,    86,    87,    88,    89,    96,    90,
      37,     6,     3,     4,     7,    91,    92,    93,    94,    95,
     113,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   125,   140,    39,    47,   139,     8,    40,    24,
       5,    16,    56,    57,    58,    51,    59,    52,    33,    56,
      24,    58,    60,    38,    77,    61,    27,    25,    21,    60,
      27,    29,    61,    30,    41,    32,    42,    43,    44,    45,
      38,    62,    63,   138,     6,    20,   142,     7,    62,    63,
      18,    33,    55,    50,    14,    53,    54,    72,    18,    71,
      73,    31,    81,    83,    52,   141,   100,   101,   102,   103,
       8,   104,   144,   145,    98,    18,    15,   105,   106,   107,
     108,   109,    99,    74,   137,   110,    86,    87,    88,    89,
     143,    90,    28,    35,    70,    97,     0,    91,    92,    93,
      94,    95,     0,   112,    86,    87,    88,    89,     0,    90,
       0,    33,     0,     0,     0,    91,    92,    93,    94,    95,
      86,    87,    88,    89,     0,    90,     0,     0,     0,     0,
       0,    91,    92,    93,    94,    95,    86,    87,    88,    89,
       0,    90,     0,     0,     0,     0,     0,    91,    92,     0,
      94,   100,   101,   102,   103,     0,   104,     0,     0,     0,
       0,     0,   105,   106,     0,   108,    86,    87,    88,    89,
       0,    90,     0,     0,     0,     0,     0,    91,    92,   100,
     101,   102,   103,     0,   104,     0,     0,     0,     0,     0,
     105,   106,     0,   127,   128,   129,   130,   131,   132,   133,
     134,   135,   136,    86,    87,    88,    89,     0,    90,   100,
     101,   102,   103,     0,   104
};

static const yytype_int16 yycheck[] =
{
      29,    54,    28,    33,    30,    99,    14,    15,    36,    17,
      14,    15,    22,    17,    12,    13,    14,    15,    71,    17,
      50,     8,     6,     0,    11,    23,    24,    25,    26,    27,
      83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
      93,    94,    95,   137,     5,    73,    44,    34,     9,    19,
      19,     5,     3,     4,     5,    28,     7,    30,    19,     3,
      30,     5,    13,    33,     3,    16,     5,     3,    44,    13,
       5,    29,    16,    44,    35,    31,    37,    38,    39,    40,
      50,    32,    33,   112,     8,    30,   139,    11,    32,    33,
      13,    19,     5,    43,    18,    28,    28,    18,    21,    10,
      43,    24,     4,    10,    30,    36,    12,    13,    14,    15,
      34,    17,   141,   142,    29,    38,     9,    23,    24,    25,
      26,    27,    44,    50,    44,    31,    12,    13,    14,    15,
      29,    17,    21,    30,    43,    73,    -1,    23,    24,    25,
      26,    27,    -1,    29,    12,    13,    14,    15,    -1,    17,
      -1,    19,    -1,    -1,    -1,    23,    24,    25,    26,    27,
      12,    13,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,
      -1,    23,    24,    25,    26,    27,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    23,    24,    -1,
      26,    12,    13,    14,    15,    -1,    17,    -1,    -1,    -1,
      -1,    -1,    23,    24,    -1,    26,    12,    13,    14,    15,
      -1,    17,    -1,    -1,    -1,    -1,    -1,    23,    24,    12,
      13,    14,    15,    -1,    17,    -1,    -1,    -1,    -1,    -1,
      23,    24,    -1,   100,   101,   102,   103,   104,   105,   106,
     107,   108,   109,    12,    13,    14,    15,    -1,    17,    12,
      13,    14,    15,    -1,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    22,    47,     6,     0,    19,     8,    11,    34,    48,
      49,    50,    53,    74,    18,    49,     5,    54,    57,    28,
      30,    44,    55,    56,    74,     3,    59,     5,    54,    29,
      44,    57,    31,    19,    51,    55,    52,    53,    74,     5,
       9,    35,    37,    38,    39,    40,    51,    58,    68,    69,
      43,    28,    30,    28,    28,     5,     3,     4,     5,     7,
      13,    16,    32,    33,    58,    62,    65,    66,    67,    71,
      73,    10,    18,    43,    52,    72,    73,     3,    57,    60,
      61,     4,    66,    10,    64,    63,    12,    13,    14,    15,
      17,    23,    24,    25,    26,    27,    66,    68,    29,    44,
      12,    13,    14,    15,    17,    23,    24,    25,    26,    27,
      31,    70,    29,    66,    66,    66,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    72,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    44,    51,    44,
      72,    36,    66,    29,    51,    51
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    46,    47,    47,    48,    48,    49,    49,    50,    51,
      52,    52,    53,    54,    54,    55,    55,    56,    57,    57,
      58,    58,    59,    60,    60,    60,    60,    60,    60,    60,
      60,    60,    60,    61,    61,    61,    63,    62,    64,    62,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      66,    66,    66,    66,    66,    67,    67,    68,    68,    69,
      69,    70,    69,    69,    69,    69,    69,    69,    69,    69,
      71,    71,    72,    72,    73,    73,    73,    74,    74,    74
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     1,     1,     1,     6,     4,
       3,     0,     2,     3,     1,     3,     0,     2,     4,     1,
       4,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     0,     3,     0,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     3,
       4,     0,     7,     5,     7,     7,     2,     1,     1,     1,
       1,     0,     1,     3,     1,     1,     1,     1,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
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
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
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
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
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
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

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
      int yyn = yypact[*yyssp];
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
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
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
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
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
          yyp++;
          yyformat++;
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

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
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
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
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
#line 119 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "PROGRAM ENCOUNTERED\n");
		ASTProgram *ast_prog = new ASTProgram((yyvsp[-1]._Declarations));
		Visitor * visitor=new Visitor();
		ast_prog->evaluate(visitor);
		VisitorIR * visitorIR = new VisitorIR();
		ast_prog->evaluate(visitor);
		//ast_prog->GenCode(visitorIR);
	}
#line 1440 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 129 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Declarations)=(yyvsp[-1]._Declarations);
		(yyval._Declarations)->push_back((yyvsp[0]._Declaration));
	}
#line 1449 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 132 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Declarations)=new list<Declaration*>();
		(yyval._Declarations)->push_back((yyvsp[0]._Declaration));
	}
#line 1458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 137 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Declaration)=new Declaration((yyvsp[0]._ASTField_Declaration));
	}
#line 1466 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 139 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Declaration)=new Declaration((yyvsp[0]._ASTMethod_Declaration));
	}
#line 1474 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 143 "parser.y" /* yacc.c:1646  */
    { 
	cout<<"B3\n";
	(yyval._ASTMethod_Declaration)=new ASTMethod_Declaration((yyvsp[-5].type), (yyvsp[-4].string), (yyvsp[0].ast_main), (yyvsp[-2]._ASTParam_Declarations));
}
#line 1483 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 149 "parser.y" /* yacc.c:1646  */
    {
	ASTMain * ast_main = new ASTMain((yyvsp[-2]._ASTField_Declarations), (yyvsp[-1]._aSTStatements));
	(yyval.ast_main)=ast_main;
}
#line 1492 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 154 "parser.y" /* yacc.c:1646  */
    {
	(yyval._ASTField_Declarations)=(yyvsp[0]._ASTField_Declarations);
	cout<<"C1\n";
	(yyval._ASTField_Declarations)->push_back((yyvsp[-2]._ASTField_Declaration));
}
#line 1502 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 158 "parser.y" /* yacc.c:1646  */
    {
	cout<<"C2\n";
	(yyval._ASTField_Declarations)=new list<ASTField_Declaration*>();
}
#line 1511 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 164 "parser.y" /* yacc.c:1646  */
    {
	cout<<"C\n";
	(yyval._ASTField_Declaration) = new ASTField_Declaration((yyvsp[-1].type), (yyvsp[0].Declarations_));	
}
#line 1520 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 169 "parser.y" /* yacc.c:1646  */
    { 
		(yyval.Declarations_)=(yyvsp[0].Declarations_);
		(yyval.Declarations_)->push_back(new ASTDeclarations((yyvsp[-2]._Def)));
	}
#line 1529 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 173 "parser.y" /* yacc.c:1646  */
    {
		(yyval.Declarations_)=new list<ASTDeclarations*>();
		(yyval.Declarations_)->push_back(new ASTDeclarations((yyvsp[0]._Def)));
	}
#line 1538 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 178 "parser.y" /* yacc.c:1646  */
    {
	(yyval._ASTParam_Declarations)=(yyvsp[0]._ASTParam_Declarations);
	cout<<"C1\n";
	(yyval._ASTParam_Declarations)->push_back((yyvsp[-2]._ASTParam_Declaration));
}
#line 1548 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 182 "parser.y" /* yacc.c:1646  */
    {
	cout<<"C2\n";
	(yyval._ASTParam_Declarations)=new list<ASTParam_Declaration*>();
}
#line 1557 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 187 "parser.y" /* yacc.c:1646  */
    {
	(yyval._ASTParam_Declaration) = new ASTParam_Declaration((yyvsp[-1].type), (yyvsp[0]._Def));	
}
#line 1565 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 191 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "ID=%s SIZE=%d\n", (yyvsp[-3].string), (yyvsp[-1].number));
		(yyval._Def)=new ASTArrayFieldDeclaration((yyvsp[-3].string), (yyvsp[-1].number));
	}
#line 1574 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 194 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "ID=%s\n", yylval.string);
		(yyval._Def)=new ASTIdentifier((yyvsp[0].string));
	}
#line 1583 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 199 "parser.y" /* yacc.c:1646  */
    {
		(yyval._ASTLocation)=new ASTArrayIdentifier(new ASTIdentifier((yyvsp[-3].string)), (yyvsp[-1]._Expressions));
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", (yyvsp[-3].string));
	}
#line 1592 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 202 "parser.y" /* yacc.c:1646  */
    {
		(yyval._ASTLocation)=new ASTIdentifier((yyvsp[0].string));
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", (yyvsp[0].string));
	}
#line 1601 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 208 "parser.y" /* yacc.c:1646  */
    {
		(yyval.number)=(yyvsp[0].number);
	}
#line 1609 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 213 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("<=", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1617 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 216 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("<=", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1625 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 219 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("==", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1633 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 222 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("&&", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1641 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 225 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("||", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1649 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 228 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("+");
		(yyval._BinaryExpr)=new BinaryExpr("+", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));

	}
#line 1659 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 233 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("-");
		(yyval._BinaryExpr)=new BinaryExpr("-", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));

	}
#line 1669 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 238 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("*");
		(yyval._BinaryExpr)=new BinaryExpr("*", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));

	}
#line 1679 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 243 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("/");
		(yyval._BinaryExpr)=new BinaryExpr("/", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));

	}
#line 1689 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 248 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("%");
		(yyval._BinaryExpr)=new BinaryExpr("%", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));
	}
#line 1698 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 255 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Expressions)=new list<Expression *>();
		(yyval._Expressions)->push_back((yyvsp[0]._BinaryExpr));
	}
#line 1707 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 259 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Expressions)=new list<Expression *>();
		(yyval._Expressions)->push_back((yyvsp[0]._Def));	
	}
#line 1716 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 263 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "INT ENCOUNTERED=%d\n", (yyvsp[0].number));
		(yyval._Expressions)=new list<Expression *>();
		(yyval._Expressions)->push_back(new Integer((yyvsp[0].number)));
	}
#line 1726 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 270 "parser.y" /* yacc.c:1646  */
    {
		unary=2;
	}
#line 1734 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 272 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RUnaryExpr)=new RUnaryExpr(2, (yyvsp[0]._ExpressionRights));
	}
#line 1742 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 275 "parser.y" /* yacc.c:1646  */
    {
		unary=1;
	}
#line 1750 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 277 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RUnaryExpr)=new RUnaryExpr(1, (yyvsp[0]._ExpressionRights));
	}
#line 1758 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 282 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr("<=", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1766 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 284 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr(">=", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1774 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 286 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr("==", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1782 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 288 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr("&&", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1790 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 290 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr("||", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1798 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 292 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("+");
		(yyval._RBinaryExpr)=new RBinaryExpr("+", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1807 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 295 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("-");
		(yyval._RBinaryExpr)=new RBinaryExpr("-", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1816 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 298 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("*");
		(yyval._RBinaryExpr)=new RBinaryExpr("*", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1825 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 301 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("/");
		(yyval._RBinaryExpr)=new RBinaryExpr("/", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1834 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 304 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("%");
		(yyval._RBinaryExpr)=new RBinaryExpr("%", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1843 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 310 "parser.y" /* yacc.c:1646  */
    {
		//$$=new list<ExpressionRight *>();
		//$$->push_back($1);
	}
#line 1852 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 314 "parser.y" /* yacc.c:1646  */
    {
		(yyval._ExpressionRights)=new list<ExpressionRight *>();
		(yyval._ExpressionRights)->push_back((yyvsp[0]._RBinaryExpr));
	}
#line 1861 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 318 "parser.y" /* yacc.c:1646  */
    {
		(yyval._ExpressionRights)=new list<ExpressionRight *>();
		(yyval._ExpressionRights)->push_back((yyvsp[0]._ASTLocation));
	}
#line 1870 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 322 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "BOOLEAN ENCOUNTERED=");
		if(unary==2) 
			fprintf(bison_fp, "!");
		unary=0;
		if ((yyvsp[0].number) == 1)
			fprintf(bison_fp, "true\n");
		else
			fprintf(bison_fp, "false\n");
		(yyval._ExpressionRights)=new list<ExpressionRight *>();
		(yyval._ExpressionRights)->push_back(new Integer((yyvsp[0].number)));
	}
#line 1887 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 334 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "INT ENCOUNTERED=");
		if(unary==1)
			fprintf(bison_fp, "-");
		else if(unary==2) 
			fprintf(bison_fp, "!");
		fprintf(bison_fp, "%d\n",(yyvsp[0].number));
		unary=0;

		(yyval._ExpressionRights)=new list<ExpressionRight *>();
		(yyval._ExpressionRights)->push_back(new Integer((yyvsp[0].number)));

	}
#line 1905 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 348 "parser.y" /* yacc.c:1646  */
    {(yyval.number)=1;}
#line 1911 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 348 "parser.y" /* yacc.c:1646  */
    {(yyval.number)=0;}
#line 1917 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 350 "parser.y" /* yacc.c:1646  */
    {
	(yyval._aSTStatements)=(yyvsp[0]._aSTStatements);
	(yyval._aSTStatements)->push_back((yyvsp[-2]._aSTStatement));	
}
#line 1926 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 353 "parser.y" /* yacc.c:1646  */
    {
	(yyval._aSTStatements)=new list<ASTStatement*>();
}
#line 1934 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 357 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "ASSIGNMENT OPERATION ENCOUNTERED\n");
		(yyval._aSTStatement)=new AssignmentStatement((yyvsp[-2]._ASTLocation), (yyvsp[0]._ExpressionRights));
	}
#line 1943 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 361 "parser.y" /* yacc.c:1646  */
    {
	  	(yyval._aSTStatement)=new MethodCallStatement((yyvsp[-3].string),(yyvsp[-1]._Callout_Argss));
	  }
#line 1951 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 364 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "CALLOUT TO %s ENCOUNTERED\n", (yyvsp[0].string));	
	}
#line 1959 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 366 "parser.y" /* yacc.c:1646  */
    {
		(yyval._aSTStatement)=new CalloutStatement((yyvsp[-4].string), (yyvsp[-1]._Callout_Argss));
	}
#line 1967 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 368 "parser.y" /* yacc.c:1646  */
    {
		(yyval._aSTStatement)=new ASTIF((yyvsp[-2]._ExpressionRights),(yyvsp[0].ast_main));
	}
#line 1975 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 371 "parser.y" /* yacc.c:1646  */
    {
	  	(yyval._aSTStatement)=new ASTIFELSE((yyvsp[-4]._ExpressionRights),(yyvsp[-2].ast_main),(yyvsp[0].ast_main));
	  }
#line 1983 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 374 "parser.y" /* yacc.c:1646  */
    {
      	(yyval._aSTStatement)=new ASTFor((yyvsp[-5].string),(yyvsp[-3]._ExpressionRights),(yyvsp[-1]._ExpressionRights),(yyvsp[0].ast_main));
      }
#line 1991 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 377 "parser.y" /* yacc.c:1646  */
    {
      	(yyval._aSTStatement)= new ASTReturn((yyvsp[0]._ReturnValue));
      }
#line 1999 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 380 "parser.y" /* yacc.c:1646  */
    {
      	(yyval._aSTStatement)=new ASTBreak();
      }
#line 2007 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 383 "parser.y" /* yacc.c:1646  */
    {
      	(yyval._aSTStatement)=new ASTContinue();
      }
#line 2015 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 386 "parser.y" /* yacc.c:1646  */
    {
      	(yyval._aSTStatement)=(yyvsp[0].ast_main);
      }
#line 2023 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 390 "parser.y" /* yacc.c:1646  */
    {
	(yyval._ReturnValue)=(yyvsp[0]._Argss);
}
#line 2031 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 392 "parser.y" /* yacc.c:1646  */
    {
	(yyval._ReturnValue)=new NoReturn();
}
#line 2039 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 395 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Callout_Argss)=new list<Args*>();
		(yyval._Callout_Argss)->push_back((yyvsp[0]._Argss));
	}
#line 2048 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 398 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Callout_Argss)=(yyvsp[0]._Callout_Argss);
		(yyval._Callout_Argss)->push_back((yyvsp[-2]._Argss));
	}
#line 2057 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 403 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "CHAR ENCOUNTERED=%s\n", (yyvsp[0].string));
		(yyval._Argss)=new CharLiteral((yyvsp[0].string));
	}
#line 2066 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 406 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Argss)=new StringLiteral((yyvsp[0].string));
	}
#line 2074 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 408 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Argss)=new ListExpressionRight((yyvsp[0]._ExpressionRights));
	}
#line 2082 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 412 "parser.y" /* yacc.c:1646  */
    {
		//$$=new Type();
		(yyval.type)=new IntType();
		fprintf(bison_fp, "INT DECLARATION ENCOUNTERED. ");
	}
#line 2092 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 416 "parser.y" /* yacc.c:1646  */
    {
		//$$=new Type();
		(yyval.type)=new BooleanType();
		fprintf(bison_fp, "BOOLEAN DECLARATION ENCOUNTERED. ");
	}
#line 2102 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 420 "parser.y" /* yacc.c:1646  */
    {
		(yyval.type)=new VoidType();
	}
#line 2110 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 2114 "parser.tab.c" /* yacc.c:1646  */
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

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

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
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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
                  yystos[*yyssp], yyvsp);
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
#line 424 "parser.y" /* yacc.c:1906  */


int main(int Argsc, char* Argsv[]) {
	char infile[100] = "stdin";
	const char *outfile = "flex_output.txt";		
	const char *bison_outfile = "bison_output.txt";
	const char *xml_outfile = "XML_visitor.txt";
	const char *llvm_outfile = "llvm_debug.txt";
	
	if (Argsc>=2){
		yyin = fopen( Argsv[1], "r");
		strcpy(infile, Argsv[1]);
	}else{
		yyin = stdin;
	}

	yyout = fopen(outfile, "w");
	bison_fp = fopen(bison_outfile, "w");	
	XML_fp = fopen(xml_outfile, "w");
	LLVM_fp = fopen(llvm_outfile, "w");

	if(!yyin){
		printf("Error in opening '%s' for reading!", infile);
		exit(0);
	}

	if(!yyout){
		printf("Error in opening '%s' for writing!", outfile);
		exit(0);
	}

	if(!bison_fp){
		printf("Error in opening '%s' for writing!", bison_outfile);
		exit(0);
	}	

	if(!XML_fp){
		printf("Error in opening '%s' for writing!", xml_outfile);
		exit(0);
	}	

	if (!LLVM_fp){
		printf("Error in opening '%s' for writing!", llvm_outfile);
		exit(0);
	}

	clock_t start, end;
	if (version == DEBUG){
		start = clock();		
	}
	
	do { 
		yyparse();
	} while(!feof(yyin));
	
	if (version == DEBUG){
		end = clock();
		printf("Elapsed Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);
	}

	fprintf(stdout, "Success\n");
	
	fclose(bison_fp);
	fclose(yyout);
	
}

void yyerror( const char *msg) {
	cerr << "Line: " << yylineno << ": " << msg << endl; 
	cerr.flush();
	exit(1);
}

void operatorOutput(string op) {
	switch(op.at(0)){
		case '/': 
				fprintf(bison_fp, "DIVISION ENCOUNTERED\n");
				break;
		case '*': 
				fprintf(bison_fp, "MULTIPLICATION ENCOUNTERED\n");
				break;
		case '%': 
				fprintf(bison_fp, "MOD ENCOUNTERED\n");
				break;
		case '+': 
				fprintf(bison_fp, "ADDITION ENCOUNTERED\n");
				break;
		case '-': 
				fprintf(bison_fp, "SUBTRACTION ENCOUNTERED\n");
				break;
		case '>': 
				fprintf(bison_fp, "GREATER THAN ENCOUNTERED\n");
				break;
		case '<': 
				fprintf(bison_fp, "LESS THAN ENCOUNTERED\n");
				break;
		default:
				fprintf(bison_fp, "OPERATOR ENCOUNTERED\n");
				break;		
	}
}

