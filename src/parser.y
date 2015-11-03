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

map<string,string> tcheck;
string type;

void yyerror(const char* s);
void operatorOutput(string op);

int unary=0;
%}


%union {
	int number;
	int bval;
	char character;
	char string[100];
	ASTMain *ast_main;
	ASTStatement *_aSTStatement;
	ASTIdentifier *identifier;
	ASTArrayIdentifier *arrayIdentifier;
	ASTField_Declaration *_ASTField_Declaration;
	CalloutArgs * _Callout_Args;
	Args* _Argss;
	Def* _Def;
	std::list<ASTField_Declaration *> *_ASTField_Declarations;
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
	Type *type;
	std::string *_string;
}

%token<number> T_INT
%token<string> STRING_LITERAL IDENTIFIER PROG_ID 
%token<string> CHAR_LITERAL
%token<number> BOOLEAN

%token<string> CALLOUT 
%token TEQUAL INT TPLUS TMINUS TMUL TDIV NOT MOD RBRACE LBRACE 
%token T_NEWLINE T_QUIT START LE GE AND EQ OR 
%token TLROUND TRROUND TLSQUARE TRSQUARE 
%token FALSE TRUE  
%token TLESS TGREAT SEMI_COLON TCOMMA NOT_EQUAL

//%type<number> Expression 
%type<number>InExpression Bool
%type<type> Type
%type<Declarations_> Declarations
//%type<fieldBaseDeclaration> Field_Declarations
//%type<_BaseDeclaration> Def
%type<_Def> Def
%type<_ASTField_Declaration> Field_Declaration
%type<_ASTField_Declarations> Field_Declarations 
%type<_ASTLocation> Location
%type<_Callout_Argss> Callout_Argss
%type<_Argss> Argss
%type<_ExpressionRights> Expression_Right
%type<_Expressions> Expression

%type<_aSTStatement> Statement
%type<_aSTStatements> Statements
%type<ast_main> Main
%type<_RUnaryExpr> RUnary_Expr
%type<_RBinaryExpr> RBinaryExpr
%type<_BinaryExpr> BinaryExpr

//%type<_string> STRING_LITERAL

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
		ASTProgram *ast_prog = new ASTProgram($2, $4);
		ast_prog->evaluate(new Visitor());
		std::cout<<"MAIN CLASS ID: "<<ast_prog->getId()<<"\n";
	}

Main: Field_Declarations Statements {
	ASTMain * ast_main = new ASTMain($1, $2);
	$$=ast_main;
}

Field_Declarations: Field_Declaration SEMI_COLON Field_Declarations{
	$$=$3;
	$$->push_back($1);
} | {
	$$=new list<ASTField_Declaration*>();
}


Field_Declaration: Type Declarations {
	$$ = new ASTField_Declaration($1, $2);	
}

Declarations: Def TCOMMA Declarations { 
		$$=$3;
		$$->push_back(new ASTDeclarations($1));
	}
	| Def{
		$$=new list<ASTDeclarations*>();
		$$->push_back(new ASTDeclarations($1));
	}

Def: IDENTIFIER TLSQUARE InExpression TRSQUARE {
		fprintf(bison_fp, "ID=%s SIZE=%d\n", $1, $3);
		tcheck[yylval.string]=type+"array";
		$$=new ASTArrayFieldDeclaration($1, $3);
	} | IDENTIFIER {
		fprintf(bison_fp, "ID=%s\n", yylval.string);
		tcheck[yylval.string]=type;
		$$=new ASTIdentifier($1);
	}

Location: IDENTIFIER {if(tcheck.count(yylval.string)==0) {
			cout<<"Variable "<<yylval.string<<"  not declared\n";
			exit(0);
		}
		if(tcheck[yylval.string]!="intarray"&&tcheck[yylval.string]!="booleanarray") {
			cout<<"Variable "<<yylval.string<<" is not an array\n";
			exit(0);
		}
		}TLSQUARE Expression TRSQUARE {
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", $1);
		$$=new ASTArrayIdentifier(new ASTIdentifier($1), $4);
		
		//TEMPORARY:
		//$$=new ASTIdentifier($1);
	} | IDENTIFIER {
		$$=new ASTIdentifier($1);
		fprintf(bison_fp, "LOCATION ENCOUNTERED=%s\n", $1);
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

InExpression:
    T_INT{
		$$=$1;
	} 

BinaryExpr:
	Expression LE Expression{
		$$=new BinaryExpr("<=", $1, $3);	
	} |
	Expression GE Expression{
		$$=new BinaryExpr("<=", $1, $3);	
	} |
	Expression EQ Expression{
		$$=new BinaryExpr("==", $1, $3);	
	} |
	Expression AND Expression{
		$$=new BinaryExpr("&&", $1, $3);	
	} |
	Expression OR Expression{
		$$=new BinaryExpr("||", $1, $3);	
	} |
	Expression TPLUS Expression {
		operatorOutput("+");
		$$=new BinaryExpr("+", $1, $3);

	} | 
	Expression TMINUS Expression {
		operatorOutput("-");
		$$=new BinaryExpr("-", $1, $3);

	} | 
	Expression TMUL Expression {
		operatorOutput("*");
		$$=new BinaryExpr("*", $1, $3);

	} | 
	Expression TDIV Expression {
		operatorOutput("/");
		$$=new BinaryExpr("/", $1, $3);

	} | 
	Expression MOD Expression {
		operatorOutput("%");
		$$=new BinaryExpr("%", $1, $3);
	}


Expression:
	BinaryExpr {
		$$=new list<Expression *>();
		$$->push_back($1);
	} |
	Def {
		$$=new list<Expression *>();
		$$->push_back($1);	
	} | 
	T_INT{
		fprintf(bison_fp, "INT ENCOUNTERED=%d\n", $1);
		$$=new list<Expression *>();
		$$->push_back(new Integer($1));
	} 

RUnary_Expr:
	NOT  {
		unary=2;
	}  Expression_Right {
		$$=new RUnaryExpr(2, $3);
	}
	|  TMINUS {
		unary=1;
	}  Expression_Right {
		$$=new RUnaryExpr(1, $3);
	}	

RBinaryExpr:
	Expression_Right LE Expression_Right{
		$$=new RBinaryExpr("<=", $1, $3);	
	} | Expression_Right GE Expression_Right{
		$$=new RBinaryExpr(">=", $1, $3);	
	} | Expression_Right EQ Expression_Right{
		$$=new RBinaryExpr("==", $1, $3);	
	} | Expression_Right AND Expression_Right{
		$$=new RBinaryExpr("&&", $1, $3);	
	} | Expression_Right OR Expression_Right{
		$$=new RBinaryExpr("||", $1, $3);	
	} | Expression_Right TPLUS Expression_Right {
		operatorOutput("+");
		$$=new RBinaryExpr("+", $1, $3);
	} | Expression_Right TMINUS Expression_Right {
		operatorOutput("-");
		$$=new RBinaryExpr("-", $1, $3);
	} | Expression_Right TMUL Expression_Right {
		operatorOutput("*");
		$$=new RBinaryExpr("*", $1, $3);
	} | Expression_Right TDIV Expression_Right {
		operatorOutput("/");
		$$=new RBinaryExpr("/", $1, $3);
	} | Expression_Right MOD Expression_Right {
		operatorOutput("%");
		$$=new RBinaryExpr("%", $1, $3);
	}

Expression_Right:
	RUnary_Expr {
		//$$=new list<ExpressionRight *>();
		//$$->push_back($1);
	}
	|   RBinaryExpr {
		$$=new list<ExpressionRight *>();
		$$->push_back($1);
	}
	|   Location {
		$$=new list<ExpressionRight *>();
		$$->push_back($1);
	}
	|   Bool {
		fprintf(bison_fp, "BOOLEAN ENCOUNTERED=");
		if(unary==2) 
			fprintf(bison_fp, "!");
		unary=0;
		if ($1 == 1)
			fprintf(bison_fp, "true\n");
		else
			fprintf(bison_fp, "false\n");
		$$=new list<ExpressionRight *>();
		$$->push_back(new Integer($1));
	} 
	|   T_INT{
		fprintf(bison_fp, "INT ENCOUNTERED=");
		if(unary==1)
			fprintf(bison_fp, "-");
		else if(unary==2) 
			fprintf(bison_fp, "!");
		fprintf(bison_fp, "%d\n",$1);
		unary=0;

		$$=new list<ExpressionRight *>();
		$$->push_back(new Integer($1));

	} 

Bool: TRUE {$$=1;}| FALSE{$$=0;}

Statements: Statement SEMI_COLON Statements{
	$$=$3;
	$$->push_back($1);	
} | {
	$$=new list<ASTStatement*>();
}

Statement: Location TEQUAL Expression_Right {
		fprintf(bison_fp, "ASSIGNMENT OPERATION ENCOUNTERED\n");
		$$=new AssignmentStatement($1, $3);
	} | CALLOUT TLROUND STRING_LITERAL  {
		fprintf(bison_fp, "CALLOUT TO %s ENCOUNTERED\n", $3);	
	} TCOMMA Callout_Argss TRROUND {
		$$=new CalloutStatement($3, $6);
	}

Callout_Argss: Argss{
		$$=new list<Args*>();
	} | Argss TCOMMA Callout_Argss {
		$$=$3;
		$$->push_back($1);
	}

Argss: CHAR_LITERAL  {
		fprintf(bison_fp, "CHAR ENCOUNTERED=%s\n", $1);
		$$=new CharLiteral($1);
	} | STRING_LITERAL{
		$$=new StringLiteral($1);
	} | Expression_Right {
		$$=new ListExpressionRight($1);
	}

Type: INT {
		//$$=new Type();
		$$=new IntType();
		fprintf(bison_fp, "INT DECLARATION ENCOUNTERED. ");
		type="int";
	} | BOOLEAN {
		//$$=new Type();
		$$=new BooleanType();
		fprintf(bison_fp, "BOOLEAN DECLARATION ENCOUNTERED. ");
		type="boolean";
	}
  
%%

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

	//clock_t start, end;
	//start = clock();
	
	do { 
		yyparse();
	} while(!feof(yyin));
	
	//end = clock();
	//printf("Elapsed Time: %f\n", (double)(end - start) / CLOCKS_PER_SEC);

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

