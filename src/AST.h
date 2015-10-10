#include <string>

#ifndef VISITOR_H
#include "Visitor.h"
#endif

#ifndef AST_H
#define AST_H
class Visitor;
extern FILE* XML_fp;

class ASTnode{
public:
	virtual void accept();
};

class ASTStatement: public ASTnode{
	virtual void accept();
};

class ASTProgram: public ASTnode{
private:
	std::string id_;
public:
	virtual void accept(Visitor* visitor);
	ASTProgram(std::string id);
	std::string getId();
};

class ASTBlockStatement: public ASTStatement{
	ASTStatement* stmtlist_;
public:
	ASTBlockStatement(ASTStatement *stmtlist);
};

class ASTExpression: public ASTnode{
	int value_;
public:
	int getValue(){
		return value_;
	}
};

/*class ASTAssignmentStatement: public ASTStatement{
	ASTLocation loc_;
	ASTExpression expr_;
public:
	ASTAssignmentStatement(ASTLocation loc, ASTExpression expr);
};*/

class ASTMethodCallStatement: public ASTStatement{
	
};

class ASTIntegerLiteralExpression: public ASTExpression{
	int value_;
public:
	ASTIntegerLiteralExpression(int value);
	void setValue(int value);
};

class ASTField_Declaration: public ASTExpression{
public:
		
};


class ASTIdentifier: public ASTnode{
	std::string id;
public:
	ASTIdentifier(std::string id){
		this->id=id;
	};
};

/*class CalloutArg: public ASTnode{
	std::string id;
	CalloutArg(std::string id){
		this->id=id;
	}
};

class ASTCallout: public ASTStatement{
	std::string id_;
	CalloutArg[] CalloutArgs;
public:
	ASTCallout(std::string id, CalloutArg[] CalloutArgs){
		this->id=id_;
		this->CalloutArgs=CalloutArgs;
	};
};*/

class ASTBinaryOperatorExpression: public ASTExpression {
	ASTExpression right_, left_;
	std::string operator_;
public:
	ASTBinaryOperatorExpression(ASTExpression left, ASTExpression right, std::string operator_){
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
	ASTExpression expr_;
	std::string operator_;
public:
	ASTUnaryOperatorExpression(ASTExpression expr, std::string operator_){
		this->expr_ = expr;
		this->operator_ = operator_;
	}

	ASTExpression expr(){
		return expr_;
	};

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

/*
Field_Declaration: Type Declarations
*/
class BaseFieldDeclaration: public ASTnode{
		Type type_;
		BaseDeclaration FieldDeclaration_;
	public:
		BaseFieldDeclaration(Type type_, BaseDeclaration FieldDeclaration_){
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
Field_Declarations: Field_Declaration SEMI_COLON Field_Declarations |
*/
class ASTField_Declarations: public BaseDeclaration{
	BaseDeclaration FieldDeclaration_;
	ASTField_Declarations FieldBaseDeclarations;
public:
	ASTField_Declarations(BaseDeclaration FieldBaseDeclaration,	ASTField_Declarations FieldBaseDeclarations){
		this->BaseDeclaration=FieldBaseDeclaration;
		this->FieldDeclarations = FieldBaseDeclarations;
	}
};
/*
Declarations: Def TCOMMA Declarations
*/
class Declarations: public ASTnode{
	Def Def_;
	Declarations Declarations_;
public:
	Declarations(Def Def_,Declarations Declarations_) {
		this->Def_=Def_;
		this->Declarations_=Declarations_;
	}
};
/*
Def: IDENTIFIER TLSQUARE InExpression TRSQUARE | IDENTIFIER
*/
class Def: public ASTnode{
	union def_value{
		struct value{
			ASTIdentifier Identifier_;
			int InEpression_;
		};
		ASTIdentifier Indentifier_;
	};
public:
	Def(Identifier Identifier_obj) {
		this->def_value=Identifier_obj;
	}
	Def(Identifier Identifier_obj, int InEpression){
		this->def_value.value.Identifier_=Identifier_obj;
		this->def_value.value.InEpression_=InEpression;
	}

};

/*
Main: Field_Declarations Statements
*/

class ASTMain: public ASTnode{
	ASTField_Declarations FieldBaseDeclaration_;
public:
	ASTMain(ASTField_Declarations FieldBaseDeclaration){
		this->FieldBaseDeclaration_=FieldBaseDeclaration;
	}
};


//Boolean
//Binary	
//Unary
//Symbol
//Env

#endif