#include <bits/stdc++.h>

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
class ASTField_Declaration;
class ASTMethod_Declaration;
class Declaration;
class Def;

extern FILE* XML_fp;

class ASTnode{
public:
	virtual void evaluate(Visitor* visitor);
	void GenCode(Visitor* visitor);
	Value * to_return;
};

class ASTStatement: public ASTnode{
public:	
	virtual void evaluate(Visitor* visitor);
	virtual void GenCode(Visitor* visitor);
};

class LangType: public ASTnode{
public:
	LangType(){

	}
	virtual void evaluate(Visitor* visitor);
	Type * type;
};

class ASTMF_Declaration: public ASTnode{
public:
	ASTMF_Declaration(){

	}
	virtual void evaluate(Visitor* visitor);
	virtual void GenCode(Visitor* visitor);
};

class ASTProgram: public ASTnode{
private:
	ASTMain* aSTMain;
public:
	list<Declaration*> *Declarations;
	ASTMain* getMain(){
		return aSTMain;
	}
	void evaluate(Visitor* visitor);
	void GenCode(Visitor* visitor);
	ASTProgram(list<Declaration*> *Declarations)
	{
		this->Declarations=Declarations;
	}
	std::string getId();	

};

class ASTExpression: public ASTnode{
	int value_;
public:
	int getValue(){
		return value_;
	}
	void evaluate(Visitor* visitor);
	void GenCode(Visitor* visitor);
};


class ASTParam_Declaration: public ASTnode{
	LangType *LangType1;
	Def *Def1;
public:
	ASTParam_Declaration(LangType *LangType1,Def *Def1){
		this->LangType1=LangType1;
		this->Def1=Def1;
	}

};
/*
	Field_Declaration: Type Declarations
*/
class ASTField_Declaration: public ASTExpression, public ASTMF_Declaration{
public:
	LangType* type;
	list<ASTDeclarations*> * Declarations;
	ASTField_Declaration(LangType* type, list<ASTDeclarations*> * declarations){
		this->type = type;
		this->Declarations=declarations;
	}
	void evaluate(Visitor* visitor);
	void GenCode(Visitor* visitor);
	LangType * getType(){
		return this->type;
	}
};

class Declaration: public ASTnode{
	ASTMF_Declaration * ASTMF_Declaration1;
public:
	Declaration(ASTMF_Declaration* ASTMF_Declaration1){
		this->ASTMF_Declaration1=ASTMF_Declaration1;
	}
	void evaluate(Visitor* visitor);
	ASTMF_Declaration * getDeclaration(){
		return this->ASTMF_Declaration1;
	}
};


class IntType: public LangType{
	//std::string s;
public:
	void evaluate(Visitor* visitor);
	IntType(){
		//this->s=s;
	}
};

class BooleanType: public LangType{
	//std::string s;
public:
	void evaluate(Visitor* visitor);
	BooleanType(){
		//this->s=s;
	}
};

class VoidType: public LangType{
public:
	VoidType(){
		//this->s=s;
	}
	void evaluate(Visitor* visitor);
};

class ASTMethod_Declaration: public ASTMF_Declaration{
	LangType *LangType1;
	string IDENTIFIER;
	list<ASTParam_Declaration*>* ASTParam_Declaration1;	
public:
	ASTMain* Block;
	void evaluate(Visitor* visitor);
	ASTMethod_Declaration(LangType *LangType1, string IDENTIFIER,ASTMain* Block,list<ASTParam_Declaration*>* ASTParam_Declaration1) {
		this->LangType1=LangType1;
		this->IDENTIFIER=IDENTIFIER;
		this->Block=Block;
		this->ASTParam_Declaration1=ASTParam_Declaration1;	
	}
	void GenCode(Visitor * visitor);
	string getIdentifier(){
		return this->IDENTIFIER;
	}
	LangType * getLangType(){
		return this->LangType1;
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
	string getLiteral(){
		return this->str;
	}
	Type * type;
};


class ExpressionRight: public ASTnode{
public:
	ExpressionRight(){

	} 
	virtual void evaluate(Visitor* visitor);
	virtual void GenCode(Visitor* visitor);
};


class ListExpressionRight: public Args{
	list<ExpressionRight *> *expressionRight;
public:
	ListExpressionRight(list<ExpressionRight*> *expressionRight1){
		this->expressionRight=expressionRight1;
	}
	void evaluate(Visitor* visitor);
};


class Expression: public ASTnode{
public:
	Expression(){

	} 
	Type * type;
	virtual void evaluate(Visitor* visitor);
	virtual void GenCode(Visitor* visitor, Type * type);	
};

/*
	Location
*/
class ASTLocation: public ExpressionRight, public ASTStatement{
public:
	virtual void GenCode(Visitor* visitor, Type * type);
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
	virtual void GenCode(Visitor* visitor, Type * type);	
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
	void GenCode(Visitor* visitor, Type * type);
	std::string id_;
	ASTIdentifier(std::string id);
	void evaluate(Visitor* visitor);
	string getId();
};

/*
	Location -> IDENTIFIER TLSQUARE Expression TRSQUARE 
	Def-> IDENTIFIER TLSQUARE InExpression TRSQUARE
*/

class ASTArrayIdentifier: public ASTLocation{
	ASTIdentifier* aSTIdentifier;
	std::list<Expression*>* expression;
public:
	ASTArrayIdentifier(ASTIdentifier* aSTIdentifier, std::list<Expression*>* expression){
		this->aSTIdentifier=aSTIdentifier;
		this->expression=expression;
	}
	Type * getType(){
		return this->aSTIdentifier->type;
	}
	void evaluate(Visitor* visitor);
	void GenCode(Visitor* visitor, Type * type);
	
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
	void GenCode(Visitor* visitor, Type* type);
	ASTArrayFieldDeclaration(std::string id, int size){
		this->aSTIdentifier=new ASTIdentifier(id);
		this->size_=size;
	}
	void evaluate(Visitor* visitor);
	void GenCode(Visitor* visitor);
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
	Type * type;
	void evaluate(Visitor* visitor);
	void GenCode(Visitor* visitor, Type * type);
	Def* getDef(){
		return this->Def_;
	}; 
};

/*
	Callout_Argss: Argss | Argss TCOMMA Callout_Argss 
*/
class CalloutArgs: public ASTnode{
	Args* args;
public:
	CalloutArgs(Args* Args1){
		this->args=Args1;
	}
	Type * type;
};


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
	void GenCode(Visitor* visitor);
};


//CharLiteral is taken as a string
class CharLiteral: public Args {
	string charLiteral;
public:
	CharLiteral(string charLiteral1): Args(charLiteral1) {
		this->charLiteral=charLiteral1;
	}
	void evaluate(Visitor* visitor);
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
	void GenCode(Visitor* visitor);
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
	void GenCode(Visitor* visitor);
	
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
	void GenCode(Visitor* visitor);
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
	void GenCode(Visitor* visitor);
};


class BinaryExpr: public Expression{
	string type2;
	std::list<Expression*> *  expressionL, *expressionR;
public:
	Type * type;
	void evaluate(Visitor* visitor);
	void GenCode(Visitor* visitor, Type* type);
	BinaryExpr(string type1, 
		std::list<Expression*> * expressionL1, 
		std::list<Expression*> * expressionR1) {
		
		this->type2=type1;
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
		return this->type2;
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
	virtual void GenCode(Visitor* visitor);
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
	void GenCode(Visitor* visitor);
};

#endif