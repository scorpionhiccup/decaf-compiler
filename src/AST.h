#ifndef AST_H
#define AST_H

#include <bits/stdc++.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/IR/IRBuilder.h>
//#include <llvm/ModuleProvider.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>

using namespace std;
using namespace llvm;


class Visitor;

class LangType;
class ASTDeclarations;
class ASTMain;

extern FILE* XML_fp;

class ASTnode{
public:
	virtual void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);

};

class ASTStatement: public ASTnode{
public:	
	virtual void evaluate(Visitor* visitor);
	virtual Value * GenCode(Visitor* visitor);
};

class ASTProgram: public ASTnode{
private:
	std::string id_;
	ASTMain* aSTMain;
public:
	ASTMain* getMain(){
		return aSTMain;
	}
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);
	ASTProgram(std::string id, ASTMain* aSTMain);
	std::string getId();

};

class ASTExpression: public ASTnode{
	int value_;
public:
	int getValue(){
		return value_;
	}
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);
};

/*
	Field_Declaration: Type Declarations
*/
class ASTField_Declaration: public ASTExpression{
	LangType * type;
public:
	list<ASTDeclarations*> * Declarations;
	ASTField_Declaration(LangType* type, list<ASTDeclarations*> * declarations){
		this->type = type;
		this->Declarations=declarations;
	}
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);
	LangType * getType(){
		return this->type;
	}
};


class LangType: public ASTnode{
public:
	virtual Type* GenCode(Visitor* visitor);	
};

class IntType: public LangType{
	//std::string s;
public:
	Type* GenCode(Visitor* visitor);
	IntType(){
		//this->s=s;
	}
};

class BooleanType: public LangType{
	//std::string s;
public:
	Type* GenCode(Visitor* visitor);
	BooleanType(){
		//this->s=s;
	}
};

class Args: public ASTnode{
	std::string str;
public:
	Args(std::string str): ASTnode(){
		this->str=str;
	}
	Args(){};
	void evaluate(Visitor* visitor);
	Type * GenCode(Visitor* visitor);
	string getLiteral(){
		return this->str;
	}
};


class ExpressionRight: public ASTnode{
public:
	ExpressionRight(){

	} 
	virtual void evaluate(Visitor* visitor);
	virtual Value * GenCode(Visitor* visitor);
};


class ListExpressionRight: public Args{
	list<ExpressionRight *> *expressionRight;
public:
	ListExpressionRight(list<ExpressionRight*> *expressionRight1){
		this->expressionRight=expressionRight1;
	}
	Type * GenCode(Visitor* visitor);
};


class Expression: public ASTnode{
public:
	Expression(){

	} 
	virtual void evaluate(Visitor* visitor);
	virtual Value* GenCode(Visitor* visitor, Type * type);	
};

/*
	Location
*/
class ASTLocation: public ExpressionRight, public ASTStatement{
public:
	virtual Value * GenCode(Visitor* visitor, Type * type);
	ASTLocation(){

	}
	virtual void evaluate(Visitor* visitor);
	virtual string getId();
};

/*
	Def: IDENTIFIER TLSQUARE InExpression TRSQUARE | IDENTIFIER
*/
class Def: public Expression{
public:
	virtual Value* GenCode(Visitor* visitor, Type * type);	
	Def() {
		
	}
	virtual void evaluate(Visitor* visitor);
};

/*
	Location -> IDENTIFIER
	Def -> IDENTIFIER
*/
class ASTIdentifier: public ASTLocation, public Def{
public:
	Value* GenCode(Visitor* visitor, Type * type);
	std::string id_;
	ASTIdentifier(std::string id);
	void evaluate(Visitor* visitor);
	string getId();
};

/*
	Location -> IDENTIFIER TLSQUARE Expression TRSQUARE 
*/

class ASTArrayIdentifier: public ASTLocation{
	ASTIdentifier* aSTIdentifier;
	std::list<Expression*>* expression;
public:
	ASTArrayIdentifier(ASTIdentifier* aSTIdentifier, std::list<Expression*>* expression){
		this->aSTIdentifier=aSTIdentifier;
		this->expression=expression;
	}
	
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor, Type * type);
	
	string getId(){
		return this->aSTIdentifier->getId();
	};

	std::list<Expression*>* getExpression(){
		return this->expression;
	};
};

/*
	Def: IDENTIFIER TLSQUARE InExpression TRSQUARE
*/
class ASTArrayFieldDeclaration: public Def{
	int size_;
	ASTIdentifier* aSTIdentifier;
public:
	Value* GenCode(Visitor* visitor, Type* type);
	ASTArrayFieldDeclaration(std::string id, int size){
		this->aSTIdentifier=new ASTIdentifier(id);
		this->size_=size;
	}
	void evaluate(Visitor* visitor);
	string getId(){
		return this->aSTIdentifier->getId();
	};

	int getExpression(){
		return size_;
	}

	ASTIdentifier* getIdentifier(){
		return aSTIdentifier;
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
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor, Type * type);
	Def* getDef(){
		return this->Def_;
	}; 
};

/*
	Callout_Argss: Argss | Argss TCOMMA Callout_Argss 
*/


/*
	Statement: CALLOUT TLROUND STRING_LITERAL TCOMMA Callout_Args TRROUND
*/
class CalloutStatement: public ASTStatement{
public:
	string name;
	list<Args *> *Argss;
	CalloutStatement(string name, list<Args *>* Argss){
		this->name=name;
		this->Argss=Argss;
	}
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);
};


//CharLiteral is taken as a string
class CharLiteral: public Args {
	string charLiteral;
public:
	CharLiteral(string charLiteral1): Args(charLiteral1) {
		this->charLiteral=charLiteral1;
	}
	void evaluate(Visitor* visitor);
	Type * GenCode(Visitor* visitor);
	string getLiteral(){
		return this->charLiteral;
	}
};


class StringLiteral: public Args{
	string stringLiteral;
public:
	StringLiteral(string stringLiteral1): Args(stringLiteral1) {
		this->stringLiteral=stringLiteral1;
	}
	void evaluate(Visitor* visitor);
	Type * GenCode(Visitor* visitor);
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
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);
	int getType(){
		return this->type;
	}
};

class RBinaryExpr: public ExpressionRight{
	string type;
	std::list<ExpressionRight*> *  expressionRightL, *expressionRightR;
public:
	RBinaryExpr(string type1, 
		std::list<ExpressionRight*> * expressionRightL1, 
		std::list<ExpressionRight*> * expressionRightR1) {
		
		this->type=type1;
		this->expressionRightL=expressionRightL1;
		this->expressionRightR=expressionRightR1;
	}
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);
	
	list<ExpressionRight*>* getLeftExprs(){
		return this->expressionRightL;
	}
	
	list<ExpressionRight*>* getRightExprs(){
		return this->expressionRightR;
	}

	string getType(){
		return this->type;
	}
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
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);
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
	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);
};


class BinaryExpr: public Expression{
	string type;
	std::list<Expression*> *  expressionL, *expressionR;
public:
	void evaluate(Visitor* visitor);
	Value* GenCode(Visitor* visitor, Type* type);
	BinaryExpr(string type1, 
		std::list<Expression*> * expressionL1, 
		std::list<Expression*> * expressionR1) {
		
		this->type=type1;
		this->expressionL=expressionL1;
		this->expressionR=expressionR1;
	}
	list<Expression*>* getLeftExprs(){
		return this->expressionL;
	}
	list<Expression*>* getRightExprs(){
		return this->expressionR;
	}
	string getType(){
		return this->type;
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
	void evaluate(Visitor* visitor);
	Value* GenCode(Visitor* visitor);
	ASTLocation * getLocation(){
		return this->location;
	}
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

	void evaluate(Visitor* visitor);
	Value * GenCode(Visitor* visitor);
};

#endif