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
    IDENTIFIER = 259,
    STRING_LITERAL = 260,
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
    TLROUND = 278,
    TRROUND = 279,
    TLSQUARE = 280,
    TRSQUARE = 281,
    FALSE = 282,
    TRUE = 283,
    TLESS = 284,
    TGREAT = 285,
    SEMI_COLON = 286,
    TCOMMA = 287,
    NOT_EQUAL = 288
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
	BaseDeclaration * _BaseDeclaration;
	ASTIdentifier *identifier;
	ASTField_Declaration *_ASTField_Declaration;
	//ASTField_Declarations *fieldBaseDeclaration;
	Def *Def_;
	//Field_Declaration *Field_Declaration_;
	//Field_Declarations *Field_Declarations_;
	list<ASTField_Declaration *> *_ASTField_Declarations;
	ASTDeclarations * Declarations_;
	//IntType *intType;
	//BooleanType *booleanType;	
	ASTDeclarations * _ASTDeclarations;
	Type *type;

#line 109 "parser.tab.h" /* yacc.c:1909  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
