%{

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin, *yyout;
extern int line_num;
FILE* bison_fp;
void yyerror(const char* s);

int a;
char stack[200];
int stackv[200];
int i=0;
char op;
int opv;
%}

%union {
	int number;
	int bval;
	char character;
	char string[100];
}


%token<number> T_INT
%token<string> IDENTIFIER
%token BOOLEAN CALLOUT INT
%token TEQUAL TPLUS TMINUS TMUL TDIV NOT MOD RBRACE LBRACE 
%token T_NEWLINE T_QUIT START 
%token TLROUND TRROUND TLSQUARE TRSQUARE 
%token FALSE TRUE STRING_LITERAL CHAR_LITERAL 
%token TLESS TGREAT SEMI_COLON TCOMMA

%type<string> Statement
%type<number> Expression
%type<character> Op



%start Program 
%%
Program: START LBRACE Main RBRACE {	
	fprintf(bison_fp, "PROGRAM ENCOUNTERED\n");
	}

Main: Field_Declarations Statements | 

Field_Declarations: Field_Declaration SEMI_COLON Field_Declarations | 

Field_Declaration: Type Def

Def: IDENTIFIER TLSQUARE InExpression TRSQUARE {
		fprintf(bison_fp, "ID=%s SIZE=%d\n", $1, a);
	} | IDENTIFIER {
		fprintf(bison_fp, "ID=%s\n", yylval.string);
	}
Location: IDENTIFIER TLSQUARE Expression TRSQUARE {
		fprintf(bison_fp, "i= %d\n", i);
		while(i--) {
			fprintf(bison_fp, "%c\n", stack[i]);
		}
		i=0;
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", $1);
	} | IDENTIFIER {
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", yylval.string);
	}

InExpression:
	Def |  
    T_INT{
		a=$1;
	
	} 
	| TRUE | FALSE | 
	Unary_Op InExpression 
	| InExpression Op InExpression 


Expression:
	Def |  
    T_INT{
		fprintf(bison_fp, "INT ENCOUNTERD=%d\n", $1);
	} 
	| TRUE | FALSE | 
	Unary_Op Expression 
	| Expression Op Expression {

	fprintf(bison_fp, "operator= %c ***\n", op);

	if( i>0 && opv>=stackv[i-1] ) {
	fprintf(bison_fp, "%c\n", stack[i-1]);
	i--;
	}
	stackv[i]=opv;
	stack[i++]=op;
	}
	

Statements: Statement SEMI_COLON Statements | 

Statement: Location TEQUAL Expression {
		fprintf(bison_fp, "ASSIGNMENT OPERATION ENCOUNTERED\n");
		fprintf(bison_fp, "i= %d\n", i);
		while(i--) {
			fprintf(bison_fp, "%c\n", stack[i]);
		}
		i=0;
	}
	| CALLOUT TLROUND STRING_LITERAL TCOMMA Callout_Arg TRROUND {
		fprintf(bison_fp, "CALLOUT TO %s ENCOUNTERED\n", "");	
	}

Callout_Arg: Arguments | Arguments TCOMMA Callout_Arg

Arguments: Literals | IDENTIFIER

Op: 
	 TDIV {
		op='/';
		opv=2;
	} | 
	TMUL {
		op='*';
		opv=2;
	} |
	MOD {
		op='%';
		opv=2;
	} | TPLUS {
		op='+';
		opv=1;
	} | TMINUS  {
		op='-';
		opv=1;
	} | TGREAT {op='>';opv=0;} | TLESS {op='<';opv=0;}

Unary_Op: NOT | TMINUS

Type: INT {fprintf(bison_fp, "INT DECLARATION ENCOUNTERED. ");}
	| BOOLEAN {fprintf(bison_fp, "BOOLEAN DECLARATION ENCOUNTERED. ");}

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
