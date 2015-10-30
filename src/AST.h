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

/*
	Location
*/
class ASTLocation: public ASTnode{
};

/*
	Location -> IDENTIFIER
*/
class ASTIdentifier: public ASTLocation, public BaseDeclaration{
	std::string id_;
public:
	ASTIdentifier(std::string id);
};

/*
	Location -> IDENTIFIER TLSQUARE Expression TRSQUARE 
*/
class ASTArrayIdentifier: public ASTLocation{
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
class ASTArrayFieldDeclaration: public BaseDeclaration{
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
class Def: public ASTnode{
	struct value{
			ASTIdentifier *Identifier_;
			int InEpression_;
		};
	union def_value{
		struct  value *v1;
		ASTIdentifier *Identifier;
	}*dv1;
public:
	Def(ASTIdentifier *Identifier_obj) {
		dv1->Identifier=Identifier_obj;
	}
	Def(ASTIdentifier Identifier_obj, int InEpression){
		dv1->v1->Identifier_=&Identifier_obj;
		dv1->v1->InEpression_=InEpression;
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


class Argument: public ASTnode{
	std::string str;
public:
	Argument(std::string str){
		this->str=str;
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
	std::string name;
	list<CalloutArg *> callout_args;
public:
	CalloutStatement(string name, list<CalloutArg *> callout_args){
		this->name=name;
		this->callout_args=callout_args;
	}
};

/*
	Statement: Location TEQUAL Expression_Right
*/
class AssignmentStatement: public ASTStatement{
	ASTLocation *locations;
public:
	AssignmentStatement(ASTLocation *locations){
		this->locations=locations;
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
};

//Boolean
//Binary	
//Unary
//Symbol
//Env

#endif