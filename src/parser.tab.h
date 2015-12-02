/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
    TAD = 260,
    IDENTIFIER = 261,
    PROG_ID = 262,
    CHAR_LITERAL = 263,
    BOOLEAN = 264,
    CALLOUT = 265,
    TEQUAL = 266,
    INT = 267,
    TPLUS = 268,
    TMINUS = 269,
    TMUL = 270,
    TDIV = 271,
    NOT = 272,
    MOD = 273,
    RBRACE = 274,
    LBRACE = 275,
    T_NEWLINE = 276,
    T_QUIT = 277,
    START = 278,
    TLE = 279,
    GE = 280,
    AND = 281,
    TEQ = 282,
    OR = 283,
    TLROUND = 284,
    TRROUND = 285,
    TLSQUARE = 286,
    TRSQUARE = 287,
    FALSE = 288,
    TRUE = 289,
    VOID = 290,
    IF = 291,
    ELSE = 292,
    FOR = 293,
    RETURN = 294,
    CONTINUE = 295,
    BREAK = 296,
    TLESS = 297,
    TGREAT = 298,
    SEMI_COLON = 299,
    TCOMMA = 300,
    NOT_EQUAL = 301
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 27 "parser.y" /* yacc.c:1909  */

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

	ASTDeclaration *_Declaration;
	CalloutArgs * _Callout_Args;
	Args* _Argss;
	Def* _Def;

	std::list<ASTDeclaration *>*_Declarations;
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

#line 141 "parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
