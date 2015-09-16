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
void operatorOutput(char op);

char stack[200];
int stackv[200];
int i=0;
char op;
int opv;
int unary;
%}

%union {
	int number;
	int bval;
	char character;
	char string[100];
}


%token<number> T_INT
%token<string> IDENTIFIER
%token<string> STRING_LITERAL PROG_ID

%token BOOLEAN CALLOUT INT
%token TEQUAL TPLUS TMINUS TMUL TDIV NOT MOD RBRACE LBRACE 
%token T_NEWLINE T_QUIT START 
%token TLROUND TRROUND TLSQUARE TRSQUARE 
%token FALSE TRUE CHAR_LITERAL 
%token TLESS TGREAT SEMI_COLON TCOMMA

%type<string> Statement
%type<number> InExpression
%type<character> Op

%start Program 
%%
Program: START PROG_ID LBRACE Main RBRACE {	
	fprintf(bison_fp, "PROGRAM ENCOUNTERED\n");
	}

Main: Field_Declarations Statements | 

Field_Declarations: Field_Declaration SEMI_COLON Field_Declarations | 

Field_Declaration: Type Def

Def: IDENTIFIER TLSQUARE InExpression TRSQUARE {
		fprintf(bison_fp, "ID=%s SIZE=%d\n", $1, $3);
	} | IDENTIFIER {
		fprintf(bison_fp, "ID=%s\n", yylval.string);
	}
Location: IDENTIFIER TLSQUARE Expression TRSQUARE {
		while(i--) {
			operatorOutput(stack[i]);
		}
		i=0;
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", $1);
	} | IDENTIFIER {
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", yylval.string);
	}

InExpression:
    T_INT{
		$$=$1;
	} 

Expression:
	Def |  
    T_INT{
		fprintf(bison_fp, "INT ENCOUNTERD=%d\n", $1);
	} 
	| TRUE | FALSE | Unary_Op Expression 
	| Expression Operator Expression 

Expression_Right:
	Location |  
    T_INT{
		fprintf(bison_fp, "INT ENCOUNTERD=");
		if(unary==1)
			fprintf(bison_fp, "-");
		else if(unary==2) 
			fprintf(bison_fp, "!");
		fprintf(bison_fp, "%d\n",$1);
		unary=0;
	} 
	| Unary_Op Expression_Right 
	| Expression_Right Operator Expression_Right 

Statements: Statement SEMI_COLON Statements | 

Statement: Location TEQUAL {unary=0; } Expression_Right {
		while(i--) {
			operatorOutput(stack[i]);
		}
		i=0;
		fprintf(bison_fp, "ASSIGNMENT OPERATION ENCOUNTERED\n");	
	}
	| CALLOUT TLROUND STRING_LITERAL TCOMMA Callout_Arg TRROUND {
		fprintf(bison_fp, "CALLOUT TO %s ENCOUNTERED\n", $3);	
	}

Callout_Arg: Arguments | Arguments TCOMMA Callout_Arg

Arguments: Literals | Expression_Right

Operator: Op {
	if( i>0 && opv<=stackv[i-1] ) {
		operatorOutput(stack[i-1]);
		i--;
	}
	stackv[i]=opv;
	stack[i++]=op;
}

Op: 
	NOT {
		op='!';
		opv=3;
	} | TDIV {
		op='/';
		opv=2;
	} | TMUL {
		op='*';
		opv=2;
	} | MOD {
		op='%';
		opv=2;
	} | TPLUS {
		op='+';
		opv=1;
	} | TMINUS  {
		op='-';
		opv=1;
	} | TGREAT {
		op='>';
		opv=0;
	} | TLESS {
		op='<';
		opv=0;
	}

Unary_Op: NOT {
		unary=2;
	} | TMINUS{
		unary=1;
	} 

Type: INT {
		fprintf(bison_fp, "INT DECLARATION ENCOUNTERED. ");
	} | BOOLEAN {
		fprintf(bison_fp, "BOOLEAN DECLARATION ENCOUNTERED. ");
	}

Literals: CHAR_LITERAL 
	| STRING_LITERAL 
	| TRUE | FALSE

%%

int main(int argc, char* argv[]) {
	char infile[100] = "stdin";
	char *outfile = "flex_output.txt";
	char *bison_outfile = "bison_output.txt";

	if (argc>=2){
		yyin = fopen( argv[1], "r");
		strcpy(infile, argv[1]);
	}else{
		yyin = stdin;
	}

	yyout = fopen(outfile, "w");
	bison_fp = fopen(bison_outfile, "w");

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

	clock_t start, end;
	start = clock();
	
	do { 
		yyparse();
	} while(!feof(yyin));
	
	end = clock();
	printf("Elapsed Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

	fprintf(stdout, "Success\n");
	
	fclose(bison_fp);
	fclose(yyout);
}

void yyerror(const char* s) {
	fprintf(stdout, "Syntax Error\n");
	fprintf(stderr, "Line: %d, Parse error: %s\n", line_num, s);
	exit(1);
}

void operatorOutput(char op) {
	switch(op){
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
