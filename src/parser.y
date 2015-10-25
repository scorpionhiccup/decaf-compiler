%{
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

void yyerror(const char* s);
void operatorOutput(char op);

int unary=0;
%}


%union {
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
	std::list<ASTField_Declaration *> *_ASTField_Declarations;
	ASTDeclarations * Declarations_;
	//IntType *intType;
	//BooleanType *booleanType;	
	ASTDeclarations * _ASTDeclarations;
	Type *type;
}

%token<number> T_INT
%token<string> IDENTIFIER
%token<string> STRING_LITERAL PROG_ID 
%token<string> CHAR_LITERAL
%token<number> BOOLEAN

%token<string> CALLOUT 
%token TEQUAL  INT TPLUS TMINUS TMUL TDIV NOT MOD RBRACE LBRACE 
%token T_NEWLINE T_QUIT START 
%token TLROUND TRROUND TLSQUARE TRSQUARE 
%token FALSE TRUE  
%token TLESS TGREAT SEMI_COLON TCOMMA NOT_EQUAL

%type<string> Statement
%type<number> Expression InExpression Bool
%type<type> Type
%type<Declarations_> Declarations
//%type<fieldBaseDeclaration> Field_Declarations
%type<_BaseDeclaration> Def
%type<_ASTField_Declaration> Field_Declaration
%type<_ASTField_Declarations> Field_Declarations 

%left TEQUAL
%left TGREAT TLESS
%left TPLUS TMINUS  
%left TMUL TDIV MOD
//%left NOT
%nonassoc NOT
%left TLROUND TRROUND

%start Program 
%%
Program: START PROG_ID LBRACE Main RBRACE {	
		fprintf(bison_fp, "PROGRAM ENCOUNTERED\n");
		ASTProgram *ast_prog = new ASTProgram($2);
		ast_prog->accept(new Visitor());
		//ast_prog->accept();
		std::cout<<"MAIN CLASS ID: "<<ast_prog->getId()<<"\n";
	}

Main: Field_Declarations Statements {
	ASTMain * ast_main = new ASTMain($1);
}

Field_Declarations: Field_Declaration SEMI_COLON Field_Declarations{
	$$=$3;
	$$->push_back($1);
	//$$=new ASTField_Declarations($1, $3);
} | {
	$$=new list<ASTField_Declaration*>();
}


Field_Declaration: Type Declarations {
	$$ = new ASTField_Declaration($1, $2);	
}

Declarations: Def TCOMMA Declarations { 
	$$=new ASTDeclarations($1, $3);}
| Def{
	$$=new ASTDeclarations($1, NULL);
}

Def: IDENTIFIER TLSQUARE InExpression TRSQUARE {
		fprintf(bison_fp, "ID=%s SIZE=%d\n", $1, $3);
		$$=new ASTArrayFieldDeclaration($1, $3);
	} | IDENTIFIER {
		fprintf(bison_fp, "ID=%s\n", yylval.string);
		$$=new ASTIdentifier(yylval.string);
	}

Location: IDENTIFIER TLSQUARE Expression TRSQUARE {
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", $1);
	} | IDENTIFIER {
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", yylval.string);
		//$$=new ASTIdentifier(yylval.string);
	}

InExpression:
    T_INT{
		$$=$1;
	} 

Expression:
	Expression TPLUS Expression {
		operatorOutput('+');
	} | 
	Expression TMINUS Expression {
		operatorOutput('-');
	} | 
	Expression TMUL Expression {
		operatorOutput('*');
	} | 
	Expression TDIV Expression {
		operatorOutput('/');
	} | 
	Expression MOD Expression {
		operatorOutput('%');
	} |
	Def | 
    T_INT{
		fprintf(bison_fp, "INT ENCOUNTERED=%d\n", $1);
	} 

Expression_Right:
	
	NOT  {
		unary=2;
	}  Expression_Right 
	|  TMINUS {
		unary=1;
	}  Expression_Right  
	|  Expression_Right TPLUS Expression_Right {
		operatorOutput('+');
	}
	|   Expression_Right TMINUS Expression_Right {
		operatorOutput('-');
	} | 
		Expression_Right TMUL Expression_Right {
		operatorOutput('*');
	} | 
	    Expression_Right TDIV Expression_Right {
		operatorOutput('/');
	}
	|   Expression_Right MOD Expression_Right {
		operatorOutput('%');
	}
	|   Location 
	|   Bool {
		fprintf(bison_fp, "BOOLEAN ENCOUNTERED=");
		if(unary==2) 
			fprintf(bison_fp, "!");
		unary=0;
		if ($1 == 1)
			fprintf(bison_fp, "true\n");
		else
			fprintf(bison_fp, "false\n");
	} 
	|   T_INT{
		fprintf(bison_fp, "INT ENCOUNTERED=");
		if(unary==1)
			fprintf(bison_fp, "-");
		else if(unary==2) 
			fprintf(bison_fp, "!");
		fprintf(bison_fp, "%d\n",$1);
		unary=0;
	} 

Bool: TRUE {$$=1;}| FALSE{$$=0;}

Statements: Statement SEMI_COLON Statements | 

Statement: Location TEQUAL Expression_Right {
		fprintf(bison_fp, "ASSIGNMENT OPERATION ENCOUNTERED\n");	
	} | CALLOUT TLROUND STRING_LITERAL  {
		fprintf(bison_fp, "CALLOUT TO %s ENCOUNTERED\n", $3);	
	} TCOMMA Callout_Arg TRROUND

Callout_Arg: Arguments | Arguments TCOMMA Callout_Arg

Arguments: Literals | Expression_Right

Type: INT {
		$$=new Type();
		//$$=new IntType();
		fprintf(bison_fp, "INT DECLARATION ENCOUNTERED. ");
	} | BOOLEAN {
		$$=new Type();
		//$$=new BooleanType();
		fprintf(bison_fp, "BOOLEAN DECLARATION ENCOUNTERED. ");
	}
  
Literals: CHAR_LITERAL  {
	fprintf(bison_fp, "CHAR ENCOUNTERED=%s\n", $1);
} | STRING_LITERAL

%%

int main(int argc, char* argv[]) {
	char infile[100] = "stdin";
	char *outfile = (char *)"flex_output.txt";
	char *bison_outfile = (char *)"bison_output.txt";
	char *xml_outfile = (char *)"XML_visitor.txt";
	
	if (argc>=2){
		yyin = fopen( argv[1], "r");
		strcpy(infile, argv[1]);
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

void yyerror( const char *msg) {
	cerr << "Line: " << yylineno << ": " << msg << endl; 
	cerr.flush();
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

