%{

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin, *yyout;
extern int line_num;
FILE* bison_fp;
void yyerror(const char* s);
%}

%union {
	int number;
	char character;
	char string[100];
}

%token<number> T_INT
%token BOOLEAN CALLOUT INT
%token TEQUAL TPLUS TMINUS TMUL TDIV NOT MOD RBRACE LBRACE 
%token T_NEWLINE T_QUIT START 
%token TLROUND TRROUND TLSQUARE TRSQUARE 
%token FALSE TRUE STRING_LITERAL IDENTIFIER CHAR_LITERAL 
%token TLESS TGREAT SEMI_COLON TCOMMA

%type<string> IDENTIFIER 
%type<string> Statement

%start Program 
%%
Program: START LBRACE Main RBRACE {	
	fprintf(bison_fp, "PROGRAM ENCOUNTERED\n");
	}

Main: Field_Declarations Statements | 

Field_Declarations: Field_Declaration SEMI_COLON Field_Declarations | 

Field_Declaration: Type Def

Def: IDENTIFIER {
		fprintf(bison_fp, "ID=%s\n", $1);
	}
	| IDENTIFIER TLSQUARE Expression TRSQUARE

Expression: Unary_Op Expression 
	| Expression Op Expression 
	| T_INT{
		fprintf(bison_fp, "INT ENCOUNTERD=%d\n", $1);
	} 
	| TRUE | FALSE | IDENTIFIER

Statements: Statement SEMI_COLON Statements | 

Statement: Def TEQUAL Expression {
		fprintf(bison_fp, "ASSIGNMENT OPERATION ENCOUNTERED\n");
	}
	| CALLOUT TLROUND STRING_LITERAL TCOMMA Callout_Arg TRROUND {
		fprintf(bison_fp, "CALLOUT TO %s ENCOUNTERED\n", "");	
	}

Callout_Arg: Arguments | Arguments TCOMMA Callout_Arg

Arguments: Literals | IDENTIFIER

Op: TPLUS {
		fprintf(bison_fp ,"ADDITION ENCOUNTERED\n");
	} | TMINUS  {
		fprintf(bison_fp ,"SUBTRACTION ENCOUNTERED\n");
	} | TMUL {
		fprintf(bison_fp ,"MULTIPLICATION ENCOUNTERED\n");
	} | TDIV {
		fprintf(bison_fp ,"DIVISION ENCOUNTERED\n");
	} | MOD {
		fprintf(bison_fp ,"MODULUS ENCOUNTERED\n");
	} | TGREAT | TLESS

Unary_Op: NOT | TMINUS

Type: INT {fprintf(bison_fp, "INT DECLARATION ENCOUNTERED.\n");}
	| BOOLEAN {fprintf(bison_fp, "BOOLEAN DECLARATION ENCOUNTERED.\n");}

Literals: CHAR_LITERAL 
	| STRING_LITERAL 
	| T_INT {fprintf(bison_fp, "%i\n", $1);} 
	| TRUE | FALSE

%%

int main(int argc, char* argv[]) {
	yyin = stdin;
	char *outfile = "flex_output.txt";
	char *bison_outfile = "bison_output.txt";
	yyout = fopen(outfile, "w");
	bison_fp = fopen(bison_outfile, "w");

	if(!yyout){
		printf("Error in opening '%s' for writing!", outfile);
		exit(0);
	}

	if(!bison_fp){
		printf("Error in opening '%s' for writing!", bison_outfile);
		exit(0);
	}	

	clock_t start, end;
	start = clock();
	
	do { 
		yyparse();
	} while(!feof(yyin));
	
	end = clock();
	printf("Elapsed Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	fprintf(stderr, "Success\n");
	
	fclose(bison_fp);
	fclose(yyout);
}

void yyerror(const char* s) {
	//fprintf(stderr, "Syntax Error\n");
	fprintf(stderr, "Line: %d, Parse error: %s\n", line_num, s);
	exit(1);
}
