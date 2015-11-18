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
using namespace std;

extern int yylex(), yylineno;
extern int yyparse();
extern FILE* yyin, *yyout;
FILE *XML_fp;
FILE* bison_fp;

map<string,string> tcheck;
string type;

void yyerror(const char* s);
void operatorOutput(string op);

enum VERSION{DEBUG, RELEASE};
VERSION version=DEBUG;

int unary=0;

#line 92 "parser.tab.c" /* yacc.c:339  */

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
    TLESS = 290,
    TGREAT = 291,
    SEMI_COLON = 292,
    TCOMMA = 293,
    NOT_EQUAL = 294
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 28 "parser.y" /* yacc.c:355  */

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
	Declaration *_Declaration;
	CalloutArgs * _Callout_Args;
	Args* _Argss;
	Def* _Def;
	std::list<ASTField_Declaration *> *_ASTField_Declarations;
	std::list<Declaration *>*_Declarations;

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
	//IntType *intType;
	//BooleanType *booleanType;	
	ASTDeclarations * _ASTDeclarations;
	ASTLocation* _ASTLocation;
	LangType *type;
	std::string *_string;

#line 208 "parser.tab.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 223 "parser.tab.c" /* yacc.c:358  */

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
#define YYLAST   161

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  40
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  27
/* YYNRULES -- Number of rules.  */
#define YYNRULES  67
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  117

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   294

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
      35,    36,    37,    38,    39
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   114,   114,   119,   121,   125,   130,   132,   138,   144,
     149,   153,   159,   164,   168,   173,   177,   183,   183,   197,
     214,   219,   222,   225,   228,   231,   234,   239,   244,   249,
     254,   261,   265,   269,   276,   276,   281,   281,   288,   290,
     292,   294,   296,   298,   301,   304,   307,   310,   316,   320,
     324,   328,   340,   354,   354,   356,   359,   363,   366,   366,
     372,   374,   379,   382,   384,   388,   393,   398
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
  "TLESS", "TGREAT", "SEMI_COLON", "TCOMMA", "NOT_EQUAL", "$accept",
  "Program", "Declaration_list", "Declaration", "Method_Declaration",
  "Block", "Field_Declarations", "Field_Declaration", "Declarations",
  "Def", "Location", "$@1", "InExpression", "BinaryExpr", "Expression",
  "RUnary_Expr", "$@2", "$@3", "RBinaryExpr", "Expression_Right", "Bool",
  "Statements", "Statement", "$@4", "Callout_Argss", "Argss", "Type", YY_NULLPTR
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
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294
};
# endif

#define YYPACT_NINF -42

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-42)))

#define YYTABLE_NINF -18

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -20,    14,    44,    31,   -42,     5,   -42,   -42,   -42,     3,
     -42,   -42,   -42,    55,   -42,   -42,   -27,   -42,    24,    34,
      61,    67,    57,   -42,    47,    58,   -42,     5,   -42,   -42,
      52,    66,    67,    62,    69,    84,    88,    68,     5,    77,
     104,    33,   -42,    52,   -42,     7,   -42,   -42,   -42,   -42,
     -42,   -42,   -42,   -42,   -42,    56,   -42,   -42,   -42,   -42,
     -42,    28,    71,    33,    33,    33,    33,    33,    33,    33,
      33,    33,    33,    33,    33,     7,     7,     7,     7,     7,
       7,     7,     7,     7,     7,   -42,     2,    60,   -42,    60,
      60,   -42,   -42,   -42,   138,   138,    72,   102,    72,    76,
      76,   -42,   -42,   -42,   144,   144,    87,   115,    87,   -42,
     -42,    56,    83,    80,   -42,     2,   -42
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     0,     0,     1,     0,    66,    65,    67,     0,
       5,     7,     6,     0,     2,     4,    16,    12,    14,     0,
       0,     0,     0,    20,     0,    16,    13,    11,     8,    15,
      56,     0,     0,    19,     0,     0,     0,     0,    11,     0,
       0,     0,     9,    56,    10,     0,    58,    52,    36,    34,
      54,    53,    50,    48,    49,    57,    51,    55,    33,    32,
      31,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    18,     0,    37,    35,    43,
      44,    45,    46,    47,    38,    39,    41,    40,    42,    26,
      27,    28,    29,    30,    21,    22,    24,    23,    25,    63,
      62,    64,     0,    60,    59,     0,    61
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -42,   111,   -42,   -42,    85,   -19,   100,    35,
     -26,   -42,   -42,   -42,    65,   -42,   -42,   -42,   -42,   -41,
     -42,    79,   -42,   -42,     9,   -42,    20
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     9,    10,    11,    28,    30,    12,    17,    59,
      52,    39,    24,    60,    61,    53,    64,    63,    54,   111,
      56,    36,    37,    62,   112,   113,    13
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      55,    19,     1,    20,    35,    47,   109,    33,    31,   110,
      58,     6,    25,     6,     7,    48,     7,    35,    49,    31,
       3,    14,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    50,    51,    47,     8,    33,     8,
      75,    76,    77,    78,     4,    79,    48,    32,    18,    49,
       5,    80,    81,    82,    83,    84,    18,    33,    32,    85,
      16,    34,    21,    22,    23,    50,    51,    18,    65,    66,
      67,    68,    25,    69,    67,    68,    27,    69,    29,    70,
      71,    72,    73,    74,    65,    66,    67,    68,    20,    69,
      77,    78,   -17,    79,    41,    70,    71,    40,    73,    75,
      76,    77,    78,    38,    79,    43,    42,    45,    46,    86,
      80,    81,   114,    83,    65,    66,    67,    68,   115,    69,
      15,    26,    57,    44,   116,    70,    71,    75,    76,    77,
      78,     0,    79,     0,     0,     0,     0,     0,    80,    81,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
      65,    66,    67,    68,     0,    69,    75,    76,    77,    78,
       0,    79
};

static const yytype_int8 yycheck[] =
{
      41,    28,    22,    30,    30,     3,     4,     5,    27,     7,
       3,     8,     5,     8,    11,    13,    11,    43,    16,    38,
       6,    18,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    32,    33,     3,    34,     5,    34,
      12,    13,    14,    15,     0,    17,    13,    27,    13,    16,
      19,    23,    24,    25,    26,    27,    21,     5,    38,    31,
       5,     9,    38,    29,     3,    32,    33,    32,    12,    13,
      14,    15,     5,    17,    14,    15,    19,    17,    31,    23,
      24,    25,    26,    27,    12,    13,    14,    15,    30,    17,
      14,    15,    30,    17,    10,    23,    24,    28,    26,    12,
      13,    14,    15,    37,    17,    37,    18,    30,     4,    38,
      23,    24,    29,    26,    12,    13,    14,    15,    38,    17,
       9,    21,    43,    38,   115,    23,    24,    12,    13,    14,
      15,    -1,    17,    -1,    -1,    -1,    -1,    -1,    23,    24,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      12,    13,    14,    15,    -1,    17,    12,    13,    14,    15,
      -1,    17
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    22,    41,     6,     0,    19,     8,    11,    34,    42,
      43,    44,    47,    66,    18,    43,     5,    48,    49,    28,
      30,    38,    29,     3,    52,     5,    48,    19,    45,    31,
      46,    47,    66,     5,     9,    50,    61,    62,    37,    51,
      28,    10,    18,    37,    46,    30,     4,     3,    13,    16,
      32,    33,    50,    55,    58,    59,    60,    61,     3,    49,
      53,    54,    63,    57,    56,    12,    13,    14,    15,    17,
      23,    24,    25,    26,    27,    12,    13,    14,    15,    17,
      23,    24,    25,    26,    27,    31,    38,    59,    59,    59,
      59,    59,    59,    59,    59,    59,    59,    59,    59,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,     4,
       7,    59,    64,    65,    29,    38,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    40,    41,    41,    42,    42,    43,    43,    44,    45,
      46,    46,    47,    48,    48,    49,    49,    51,    50,    50,
      52,    53,    53,    53,    53,    53,    53,    53,    53,    53,
      53,    54,    54,    54,    56,    55,    57,    55,    58,    58,
      58,    58,    58,    58,    58,    58,    58,    58,    59,    59,
      59,    59,    59,    60,    60,    61,    61,    62,    63,    62,
      64,    64,    65,    65,    65,    66,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     5,     0,     2,     1,     1,     1,     5,     4,
       3,     0,     2,     3,     1,     4,     1,     0,     5,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     1,     1,     1,     0,     3,     0,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     3,     0,     3,     0,     7,
       1,     3,     1,     1,     1,     1,     1,     1
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
#line 114 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "PROGRAM ENCOUNTERED\n");
		ASTProgram *ast_prog = new ASTProgram((yyvsp[-1]._Declarations));
		ast_prog->evaluate(new Visitor());
		std::cout<<"MAIN CLASS ID: "<<ast_prog->getId()<<"\n";
	}
#line 1396 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 121 "parser.y" /* yacc.c:1646  */
    {
	(yyval._Declarations)=(yyvsp[-1]._Declarations);
	(yyval._Declarations)->push_back((yyvsp[0]._Declaration));
}
#line 1405 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 125 "parser.y" /* yacc.c:1646  */
    {
	(yyval._Declarations)=new list<Declaration*>();
	(yyval._Declarations)->push_back((yyvsp[0]._Declaration));
}
#line 1414 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 130 "parser.y" /* yacc.c:1646  */
    {
	(yyval._Declaration)=new Declaration((yyvsp[0]._ASTField_Declaration));
}
#line 1422 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 132 "parser.y" /* yacc.c:1646  */
    {
	(yyval._Declaration)=new Declaration((yyvsp[0]._ASTMethod_Declaration));
}
#line 1430 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 138 "parser.y" /* yacc.c:1646  */
    { 
	cout<<"B3\n";
	(yyval._ASTMethod_Declaration)=new ASTMethod_Declaration((yyvsp[-4].type), (yyvsp[-3].string), (yyvsp[0].ast_main));
}
#line 1439 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 144 "parser.y" /* yacc.c:1646  */
    {
	ASTMain * ast_main = new ASTMain((yyvsp[-2]._ASTField_Declarations), (yyvsp[-1]._aSTStatements));
	(yyval.ast_main)=ast_main;
}
#line 1448 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 149 "parser.y" /* yacc.c:1646  */
    {
	(yyval._ASTField_Declarations)=(yyvsp[0]._ASTField_Declarations);
	cout<<"C1\n";
	(yyval._ASTField_Declarations)->push_back((yyvsp[-2]._ASTField_Declaration));
}
#line 1458 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 153 "parser.y" /* yacc.c:1646  */
    {
	cout<<"C2\n";
	(yyval._ASTField_Declarations)=new list<ASTField_Declaration*>();
}
#line 1467 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 159 "parser.y" /* yacc.c:1646  */
    {
	cout<<"C\n";
	(yyval._ASTField_Declaration) = new ASTField_Declaration((yyvsp[-1].type), (yyvsp[0].Declarations_));	
}
#line 1476 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 164 "parser.y" /* yacc.c:1646  */
    { 
		(yyval.Declarations_)=(yyvsp[0].Declarations_);
		(yyval.Declarations_)->push_back(new ASTDeclarations((yyvsp[-2]._Def)));
	}
#line 1485 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 168 "parser.y" /* yacc.c:1646  */
    {
		(yyval.Declarations_)=new list<ASTDeclarations*>();
		(yyval.Declarations_)->push_back(new ASTDeclarations((yyvsp[0]._Def)));
	}
#line 1494 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 173 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "ID=%s SIZE=%d\n", (yyvsp[-3].string), (yyvsp[-1].number));
		tcheck[yylval.string]=type+"array";
		(yyval._Def)=new ASTArrayFieldDeclaration((yyvsp[-3].string), (yyvsp[-1].number));
	}
#line 1504 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 177 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "ID=%s\n", yylval.string);
		tcheck[yylval.string]=type;
		(yyval._Def)=new ASTIdentifier((yyvsp[0].string));
	}
#line 1514 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 183 "parser.y" /* yacc.c:1646  */
    {if(tcheck.count(yylval.string)==0) {
			cout<<"Variable "<<yylval.string<<"  not declared\n";
			exit(0);
		}
		if(tcheck[yylval.string]!="intarray"&&tcheck[yylval.string]!="booleanarray") {
			cout<<"Variable "<<yylval.string<<" is not an array\n";
			exit(0);
		}
		}
#line 1528 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 191 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", (yyvsp[-4].string));
		(yyval._ASTLocation)=new ASTArrayIdentifier(new ASTIdentifier((yyvsp[-4].string)), (yyvsp[-1]._Expressions));
		
		//TEMPORARY:
		//$$=new ASTIdentifier($1);
	}
#line 1540 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 197 "parser.y" /* yacc.c:1646  */
    {
		(yyval._ASTLocation)=new ASTIdentifier((yyvsp[0].string));
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", (yyvsp[0].string));
		if(tcheck.count(yylval.string)==0) {
			cout<<"Variable "<<yylval.string<<" not declared\n";
			exit(0);
		}
		cout<<tcheck[yylval.string]<<endl;
		
		if(tcheck[yylval.string]!="int"&& tcheck[yylval.string]!="boolean") {
			cout<<"Variable "<<yylval.string<<" is an array\n";
			exit(0);
		}
		//$$=new ASTIdentifier(yylval.string);
	}
#line 1560 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 214 "parser.y" /* yacc.c:1646  */
    {
		(yyval.number)=(yyvsp[0].number);
	}
#line 1568 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 219 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("<=", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1576 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 222 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("<=", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1584 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 225 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("==", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1592 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 228 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("&&", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1600 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 231 "parser.y" /* yacc.c:1646  */
    {
		(yyval._BinaryExpr)=new BinaryExpr("||", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));	
	}
#line 1608 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 234 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("+");
		(yyval._BinaryExpr)=new BinaryExpr("+", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));

	}
#line 1618 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 239 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("-");
		(yyval._BinaryExpr)=new BinaryExpr("-", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));

	}
#line 1628 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 244 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("*");
		(yyval._BinaryExpr)=new BinaryExpr("*", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));

	}
#line 1638 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 249 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("/");
		(yyval._BinaryExpr)=new BinaryExpr("/", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));

	}
#line 1648 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 254 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("%");
		(yyval._BinaryExpr)=new BinaryExpr("%", (yyvsp[-2]._Expressions), (yyvsp[0]._Expressions));
	}
#line 1657 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 261 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Expressions)=new list<Expression *>();
		(yyval._Expressions)->push_back((yyvsp[0]._BinaryExpr));
	}
#line 1666 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 265 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Expressions)=new list<Expression *>();
		(yyval._Expressions)->push_back((yyvsp[0]._Def));	
	}
#line 1675 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 269 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "INT ENCOUNTERED=%d\n", (yyvsp[0].number));
		(yyval._Expressions)=new list<Expression *>();
		(yyval._Expressions)->push_back(new Integer((yyvsp[0].number)));
	}
#line 1685 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 276 "parser.y" /* yacc.c:1646  */
    {
		unary=2;
	}
#line 1693 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 278 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RUnaryExpr)=new RUnaryExpr(2, (yyvsp[0]._ExpressionRights));
	}
#line 1701 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 281 "parser.y" /* yacc.c:1646  */
    {
		unary=1;
	}
#line 1709 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 283 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RUnaryExpr)=new RUnaryExpr(1, (yyvsp[0]._ExpressionRights));
	}
#line 1717 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 288 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr("<=", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1725 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 290 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr(">=", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1733 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 292 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr("==", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1741 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 294 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr("&&", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1749 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 296 "parser.y" /* yacc.c:1646  */
    {
		(yyval._RBinaryExpr)=new RBinaryExpr("||", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));	
	}
#line 1757 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 298 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("+");
		(yyval._RBinaryExpr)=new RBinaryExpr("+", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1766 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 301 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("-");
		(yyval._RBinaryExpr)=new RBinaryExpr("-", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1775 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 304 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("*");
		(yyval._RBinaryExpr)=new RBinaryExpr("*", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1784 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 307 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("/");
		(yyval._RBinaryExpr)=new RBinaryExpr("/", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1793 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 310 "parser.y" /* yacc.c:1646  */
    {
		operatorOutput("%");
		(yyval._RBinaryExpr)=new RBinaryExpr("%", (yyvsp[-2]._ExpressionRights), (yyvsp[0]._ExpressionRights));
	}
#line 1802 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 316 "parser.y" /* yacc.c:1646  */
    {
		//$$=new list<ExpressionRight *>();
		//$$->push_back($1);
	}
#line 1811 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 320 "parser.y" /* yacc.c:1646  */
    {
		(yyval._ExpressionRights)=new list<ExpressionRight *>();
		(yyval._ExpressionRights)->push_back((yyvsp[0]._RBinaryExpr));
	}
#line 1820 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 324 "parser.y" /* yacc.c:1646  */
    {
		(yyval._ExpressionRights)=new list<ExpressionRight *>();
		(yyval._ExpressionRights)->push_back((yyvsp[0]._ASTLocation));
	}
#line 1829 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 328 "parser.y" /* yacc.c:1646  */
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
#line 1846 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 340 "parser.y" /* yacc.c:1646  */
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
#line 1864 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 354 "parser.y" /* yacc.c:1646  */
    {(yyval.number)=1;}
#line 1870 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 354 "parser.y" /* yacc.c:1646  */
    {(yyval.number)=0;}
#line 1876 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 356 "parser.y" /* yacc.c:1646  */
    {
	(yyval._aSTStatements)=(yyvsp[0]._aSTStatements);
	(yyval._aSTStatements)->push_back((yyvsp[-2]._aSTStatement));	
}
#line 1885 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 359 "parser.y" /* yacc.c:1646  */
    {
	(yyval._aSTStatements)=new list<ASTStatement*>();
}
#line 1893 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 363 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "ASSIGNMENT OPERATION ENCOUNTERED\n");
		(yyval._aSTStatement)=new AssignmentStatement((yyvsp[-2]._ASTLocation), (yyvsp[0]._ExpressionRights));
	}
#line 1902 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 366 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "CALLOUT TO %s ENCOUNTERED\n", (yyvsp[0].string));	
	}
#line 1910 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 368 "parser.y" /* yacc.c:1646  */
    {
		(yyval._aSTStatement)=new CalloutStatement((yyvsp[-4].string), (yyvsp[-1]._Callout_Argss));
	}
#line 1918 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 372 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Callout_Argss)=new list<Args*>();
	}
#line 1926 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 374 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Callout_Argss)=(yyvsp[0]._Callout_Argss);
		(yyval._Callout_Argss)->push_back((yyvsp[-2]._Argss));
	}
#line 1935 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 379 "parser.y" /* yacc.c:1646  */
    {
		fprintf(bison_fp, "CHAR ENCOUNTERED=%s\n", (yyvsp[0].string));
		(yyval._Argss)=new CharLiteral((yyvsp[0].string));
	}
#line 1944 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 382 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Argss)=new StringLiteral((yyvsp[0].string));
	}
#line 1952 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 384 "parser.y" /* yacc.c:1646  */
    {
		(yyval._Argss)=new ListExpressionRight((yyvsp[0]._ExpressionRights));
	}
#line 1960 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 388 "parser.y" /* yacc.c:1646  */
    {
		//$$=new Type();
		(yyval.type)=new IntType();
		fprintf(bison_fp, "INT DECLARATION ENCOUNTERED. ");
		type="int";
	}
#line 1971 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 393 "parser.y" /* yacc.c:1646  */
    {
		//$$=new Type();
		(yyval.type)=new BooleanType();
		fprintf(bison_fp, "BOOLEAN DECLARATION ENCOUNTERED. ");
		type="boolean";
	}
#line 1982 "parser.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 398 "parser.y" /* yacc.c:1646  */
    {
		(yyval.type)=new VoidType();
	}
#line 1990 "parser.tab.c" /* yacc.c:1646  */
    break;


#line 1994 "parser.tab.c" /* yacc.c:1646  */
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
#line 402 "parser.y" /* yacc.c:1906  */


int main(int Argsc, char* Argsv[]) {
	char infile[100] = "stdin";
	const char *outfile = "flex_output.txt";		
	const char *bison_outfile = "bison_output.txt";
	const char *xml_outfile = "XML_visitor.txt";

	if (Argsc>=2){
		yyin = fopen( Argsv[1], "r");
		strcpy(infile, Argsv[1]);
	}else{
		yyin = stdin;
	}

	yyout = fopen(outfile, "w");
	bison_fp = fopen(bison_outfile, "w");	
	XML_fp = fopen(xml_outfile, "w");

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

