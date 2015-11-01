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
	virtual void accept();
};

class ASTProgram: public ASTnode{
private:
	std::string id_;
public:
	ASTMain* aSTMain;
	virtual void accept(Visitor* visitor);
	ASTProgram(std::string id, ASTMain* aSTMain);
	std::string getId();

};

class ASTExpression: public ASTnode{
	int value_;
public:
	int getValue(){
		return value_;
	}
};

class ASTField_Declaration: public ASTExpression{
	Type* type;
	ASTDeclarations* Declarations;
public:
	ASTField_Declaration(Type* type, ASTDeclarations* Declarations){
		this->type = type;
		this->Declarations = Declarations; 
	}
};

/*class ASTCallout: public ASTnode{
	std::string id_;
	CalloutArg[] CalloutArgs;
public:
	ASTCallout(std::string id, CalloutArg[] CalloutArgs){
		this->id=id_;
		this->CalloutArgs=CalloutArgs;
	};
};*/

/*class ASTBinaryOperatorExpression: public ASTExpression {
	ASTExpression *right_, *left_;
	std::string operator_;
public:
	ASTBinaryOperatorExpression(ASTExpression *left, ASTExpression *right, std::string operator_){
		this->left_ = left;
		this->right_ = right;
		this->operator_ = operator_;
	}

	ASTExpression left(){
		return left_;
	};

	ASTExpression right(){
		return right_;
	};

};

class ASTUnaryOperatorExpression: public ASTExpression {
	ASTExpression *expr_;
	std::string operator_;
public:
	ASTUnaryOperatorExpression(ASTExpression *expr, std::string operator_){
		this->expr_ = expr;
		this->operator_ = operator_;
	}

	ASTExpression expr(){
		return expr_;
	};

};*/

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
};


class ExpressionRight: public ASTnode{
public:
	ExpressionRight(){

	} 
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
};


class ListExpression: public Argument{
	list<Expression *> *expression;
public:
	ListExpression(list<Expression*> *expression1){
		this->expression=expression1;
	}
};

/*
	Location
*/
class ASTLocation: public ExpressionRight{
public:
	ASTLocation(){

	}
};

/*
	Location -> IDENTIFIER
	Def -> IDENTIFIER
*/
class ASTIdentifier: public ASTLocation, public BaseDeclaration{
	std::string id_;
public:
	ASTIdentifier(std::string id){};
};

/*
	Location -> IDENTIFIER TLSQUARE Expression TRSQUARE 
	Def-> IDENTIFIER TLSQUARE InExpression TRSQUARE
*/
class ASTArrayIdentifier: public ASTLocation, public BaseDeclaration{
	ASTIdentifier* aSTIdentifier;
	ASTExpression* aSTExpression;
public:
	ASTArrayIdentifier(ASTIdentifier* aSTIdentifier, ASTExpression* aSTExpression){
		this->aSTIdentifier=aSTIdentifier;
		this->aSTExpression=aSTExpression;
	}
};

/*
	Field_Declaration: Type Declarations
*/
class BaseFieldDeclaration: public ASTnode{
	Type *type_;
	BaseDeclaration *FieldDeclaration_;
public:
	BaseFieldDeclaration(Type *type_, BaseDeclaration *FieldDeclaration_){
		this->type_=type_;
		this->FieldDeclaration_=FieldDeclaration_;
	}

};



/*
Def: IDENTIFIER TLSQUARE InExpression TRSQUARE
*/
class ASTArrayFieldDeclaration: public BaseDeclaration,public Def{
	int size_;
	ASTIdentifier* id_;
public:
	ASTArrayFieldDeclaration(std::string id, int size){
		this->id_=new ASTIdentifier(id);
		this->size_=size;
	}
};

/*
	Def: IDENTIFIER TLSQUARE InExpression TRSQUARE | IDENTIFIER
*/
class Def: public ASTnode, public Expression{	
public:
	Def() {
		
	}
};

/*
	Declarations: Def TCOMMA Declarations
*/
class ASTDeclarations: public ASTnode{
	BaseDeclaration *Def_;
	ASTDeclarations *Declarations_;
public:
	ASTDeclarations(BaseDeclaration *Def1, ASTDeclarations *Declarations1) {
		this->Def_=Def1;
		this->Declarations_=Declarations1;
	}
};


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
	char *name;
	list<Argument *> *args;
public:
	CalloutStatement(char *name, list<Argument *>* args){
		this->name=name;
		this->args=args;
	}
};


//CharLiteral is taken as a string
class CharLiteral: public Argument {
	string charLiteral;
public:
	CharLiteral(string charLiteral1): Argument(charLiteral1) {
		this->charLiteral=charLiteral1;
	}
};


class StringLiteral: public Argument{
	string stringLiteral;
public:
	StringLiteral(string stringLiteral1): Argument(stringLiteral1) {
		this->stringLiteral=stringLiteral1;
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
};

class Bool: public ExpressionRight{
	int value;
	Bool(int value1) {
		this->value=value1;
	}
};

class Integer: public ExpressionRight{
	int integer;
public:
	Integer(int integer1){
		this->integer=integer1;
	}
};

class BinaryExpr: public Expression{
	char type;
	std::list<Expression*> *  expressionL, *expressionR;
public:
	RBinaryExpr(char type1, 
		std::list<Expression*> * expressionL1, 
		std::list<Expression*> * expressionR1) {
		
		this->type=type1;
		this->expressionL=expressionL1;
		this->expressionR=expressionR1;
	}
};


class Literal: public ASTnode{

};


class AssignmentStatement: public ASTStatement{
	ASTLocation* location;
	list<ExpressionRight *> *expressionRight;
public:
	AssignmentStatement(ASTLocation* aSTLocation, 
		list<ExpressionRight *> *expressionRight){
		this->location=aSTLocation;
		this->expressionRight=expressionRight;
	}
};

/*
Main: Field_Declarations Statements
*/

class ASTMain: public ASTnode{
public:
	std::list<ASTField_Declaration*> *FieldBaseDeclaration_;
	std::list<ASTStatement*> *statements;
	ASTMain(std::list<ASTField_Declaration*> *FieldBaseDeclaration, std::list<ASTStatement*> *statements){
		this->FieldBaseDeclaration_=FieldBaseDeclaration;
		this->statements=statements;
	}

	void accept(Visitor* visitor){};
};

//Boolean
//Binary	
//Unary
//Symbol
//Env

#endif