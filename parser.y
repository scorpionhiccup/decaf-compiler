%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
	int ival;
	float fval;
}

%token<ival> T_INT
%token BOOLEAN CALLOUT
%token TPLUS TMINUS TMUL TDIV RBRACE LBRACE 
%token T_NEWLINE T_QUIT START TLSQUARE TRSQUARE 
%token FALSE TRUE STRING_LITERAL

%start program 
%%
program: T_NEWLINE | START statements

statements: T_NEWLINE | line
//| expression line
line: T_NEWLINE | 

%%

main() {
	yyin = stdin;

	do { 
		yyparse();
	} while(!feof(yyin));
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
