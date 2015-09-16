%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;
extern int line_num;

void yyerror(const char* s);
%}

%union {
	int number;
	char character;
}

%token<number> T_INT
%token BOOLEAN CALLOUT INT
%token TEQUAL TPLUS TMINUS TMUL TDIV NOT MOD RBRACE LBRACE 
%token T_NEWLINE T_QUIT START 
%token TLROUND TRROUND TLSQUARE TRSQUARE 
%token FALSE TRUE STRING_LITERAL IDENTIFIER CHAR_LITERAL 
%token TLESS TGREAT SEMI_COLON TCOMMA

%start Program 
%%
Program: START LBRACE Main RBRACE

Main: Field_Declarations Statements | 

Field_Declarations: Field_Declaration SEMI_COLON Field_Declarations | 

Field_Declaration: Type Def

Def: IDENTIFIER | IDENTIFIER TLSQUARE Expression TRSQUARE

Expression: Unary_Op Expression | Expression Op Expression | T_INT | TRUE | FALSE | IDENTIFIER

Statements: Statement SEMI_COLON Statements | 

Statement: Def TEQUAL Expression | CALLOUT TLROUND STRING_LITERAL TCOMMA Callout_Arg TRROUND 

Callout_Arg: Arguments | Arguments TCOMMA Callout_Arg

Arguments: Literals | IDENTIFIER

Op: TPLUS | TMINUS | TMUL | TDIV | MOD | TGREAT | TLESS

Unary_Op: NOT | TMINUS

Type: INT | BOOLEAN 

Literals: CHAR_LITERAL | STRING_LITERAL | T_INT | TRUE | FALSE

%%

main() {
	yyin = stdin;

	do { 
		yyparse();
	} while(!feof(yyin));
}

void yyerror(const char* s) {
	fprintf(stderr, "Line: %d, Parse error: %s\n", line_num, s);
	exit(1);
}
