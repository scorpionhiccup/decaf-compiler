#include <bits/stdc++.h>


#ifndef AST_H
#define AST_H

using namespace std;

class Visitor;

class Type;
class ASTDeclarations;
class ASTMain;

extern FILE* XML_fp;

class ASTnode{
public:
	virtual void accept(Visitor* visitor);

};

class ASTStatement: public ASTnode{
public:	
	void accept(Visitor* visitor);
};

class ASTProgram: public ASTnode{
private:
	std::string id_;
	ASTMain* aSTMain;
public:
	ASTMain* getMain(){
		return aSTMain;
	}
	void accept(Visitor* visitor);
	ASTProgram(std::string id, ASTMain* aSTMain);
	std::string getId();

};

class ASTExpression: public ASTnode{
	int value_;
public:
	int getValue(){
		return value_;
	}
	void accept(Visitor* visitor);
};

/*
	Field_Declaration: Type Declarations
*/
class ASTField_Declaration: public ASTExpression{
	Type* type;
public:
	list<ASTDeclarations*> * Declarations;
	ASTField_Declaration(Type* type, list<ASTDeclarations*> * declarations){
		this->type = type;
		this->Declarations=declarations;
	}
	void accept(Visitor* visitor);
};


class Type: public ASTnode{
};

class IntType: public Type{
	//std::string s;
public:
	IntType(){
		//this->s=s;
	}
};

class BooleanType: public Type{
	//std::string s;
public:
	BooleanType(){
		//this->s=s;
	}
};

class BaseDeclaration: public ASTnode{
public:
	BaseDeclaration(){
		
	}
};

class Argument: public ASTnode{
	std::string str;
public:
	Argument(std::string str): ASTnode(){
		this->str=str;
	}
	Argument(){};
	void accept(Visitor* visitor);
};


class ExpressionRight: public ASTnode{
public:
	ExpressionRight(){

	} 
	virtual void accept(Visitor* visitor);
};


class ListExpressionRight: public Argument{
	list<ExpressionRight *> *expressionRight;
public:
	ListExpressionRight(list<ExpressionRight*> *expressionRight1){
		this->expressionRight=expressionRight1;
	}
};


class Expression: public ASTnode{
public:
	Expression(){

	} 
	void accept(Visitor* visitor);	
};

/*
	Location
*/
class ASTLocation: public ExpressionRight{
public:
	ASTLocation(){

	}
	void accept(Visitor* visitor);	
};

/*
	Def: IDENTIFIER TLSQUARE InExpression TRSQUARE | IDENTIFIER
*/
class Def: public Expression{	
public:
	Def() {
		
	}
	void accept(Visitor* visitor);
};

/*
	Location -> IDENTIFIER
	Def -> IDENTIFIER
*/
class ASTIdentifier: public ASTLocation, public Def{
	std::string id_;
public:
	ASTIdentifier(std::string id);
	void accept(Visitor* visitor);
	string getId();
};

/*
	Location -> IDENTIFIER TLSQUARE Expression TRSQUARE 
	Def-> IDENTIFIER TLSQUARE InExpression TRSQUARE
*/
class ASTArrayIdentifier: public ASTLocation{
	ASTIdentifier* aSTIdentifier;
	ASTExpression* aSTExpression;
public:
	ASTArrayIdentifier(ASTIdentifier* aSTIdentifier, ASTExpression* aSTExpression){
		this->aSTIdentifier=aSTIdentifier;
		this->aSTExpression=aSTExpression;
	}
	
	void accept(Visitor* visitor);
	
	string getId(){
		return this->aSTIdentifier->getId();
	};

	ASTExpression* getExpression(){
		return this->aSTExpression;
	};
};

/*
Def: IDENTIFIER TLSQUARE InExpression TRSQUARE
*/
class ASTArrayFieldDeclaration: public Def{
	int size_;
	ASTIdentifier* aSTIdentifier;
public:
	ASTArrayFieldDeclaration(std::string id, int size){
		this->aSTIdentifier=new ASTIdentifier(id);
		this->size_=size;
	}
	void accept(Visitor* visitor);
	string getId(){
		return this->aSTIdentifier->getId();
	};
	int getExpression(){
		return size_;
	}
};

/*
	Declarations: Def TCOMMA Declarations
*/
class ASTDeclarations: public ASTnode{
	Def *Def_;
public:
	ASTDeclarations(Def *Def1) {
		this->Def_=Def1;
	}
	void accept(Visitor* visitor);
	Def* getDef(){
		return this->Def_;
	}; 
};

/*
	Callout_Args: Arguments | Arguments TCOMMA Callout_Args 
*/
class CalloutArg: public ASTnode{
	Argument* argument;
public:
	CalloutArg(Argument* argument1){
		this->argument=argument1;
	}
};


/*
	Statement: CALLOUT TLROUND STRING_LITERAL TCOMMA Callout_Arg TRROUND
*/
class CalloutStatement: public ASTStatement{
public:
	string name;
	list<Argument *> *args;
	CalloutStatement(string name, list<Argument *>* args){
		this->name=name;
		this->args=args;
	}
	void accept(Visitor* visitor);
};


//CharLiteral is taken as a string
class CharLiteral: public Argument {
	string charLiteral;
public:
	CharLiteral(string charLiteral1): Argument(charLiteral1) {
		this->charLiteral=charLiteral1;
	}
	void accept(Visitor* visitor);
	string getLiteral(){
		return this->charLiteral;
	}
};


class StringLiteral: public Argument{
	string stringLiteral;
public:
	StringLiteral(string stringLiteral1): Argument(stringLiteral1) {
		this->stringLiteral=stringLiteral1;
	}
	void accept(Visitor* visitor);
	string getLiteral(){
		return this->stringLiteral;
	}
};

class RUnaryExpr: public ExpressionRight{
	int type;
	std::list<ExpressionRight*> * expressionRight;
public:
	RUnaryExpr(int type1, std::list<ExpressionRight*> * expressionRight1):ExpressionRight() {
		this->type=type1;
		this->expressionRight=expressionRight1;
	}
	list<ExpressionRight*> * getExpressions(){
		return this->expressionRight;
	}
	void accept(Visitor* visitor);
};

class RBinaryExpr: public ExpressionRight{
	char type;
	std::list<ExpressionRight*> *  expressionRightL, *expressionRightR;
public:
	RBinaryExpr(char type1, 
		std::list<ExpressionRight*> * expressionRightL1, 
		std::list<ExpressionRight*> * expressionRightR1) {
		
		this->type=type1;
		this->expressionRightL=expressionRightL1;
		this->expressionRightR=expressionRightR1;
	}
	void accept(Visitor* visitor);
};

class Bool: public ExpressionRight{
	int value;
public:
	Bool(int value1) {
		this->value=value1;
	}
	bool getValue(){
		if (this->value) return true;
		return false;
	}
	void accept(Visitor* visitor);
};

class Integer: public ExpressionRight, public Expression{
	int integer;
public:
	Integer(int integer1){
		this->integer=integer1;
	}
	int getValue(){
		return integer;
	}
	void accept(Visitor* visitor);
};


class BinaryExpr: public Expression{
	char type;
	std::list<Expression*> *  expressionL, *expressionR;
public:
	void accept(Visitor* visitor);
	BinaryExpr(char type1, 
		std::list<Expression*> * expressionL1, 
		std::list<Expression*> * expressionR1) {
		
		this->type=type1;
		this->expressionL=expressionL1;
		this->expressionR=expressionR1;
	}
};


class AssignmentStatement: public ASTStatement{
public:
	ASTLocation* location;
	list<ExpressionRight *> *expressionRight;
	AssignmentStatement(ASTLocation* aSTLocation, 
		list<ExpressionRight *> *expressionRight){
		this->location=aSTLocation;
		this->expressionRight=expressionRight;
	}
	void accept(Visitor* visitor);
};

/*
	Main: Field_Declarations Statements
*/

class ASTMain: public ASTnode{
public:
	std::list<ASTField_Declaration*> *FieldDeclarations_;
	std::list<ASTStatement*> *statements;

	ASTMain(std::list<ASTField_Declaration*> *FieldDeclarations_, std::list<ASTStatement*> *statements){
		this->FieldDeclarations_=FieldDeclarations_;
		this->statements=statements;
	}

	void accept(Visitor* visitor);
};

#endif