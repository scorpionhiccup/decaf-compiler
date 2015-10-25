#ifndef VISITOR_H
#include "Visitor.h"
#endif

#ifndef AST_H
#define AST_H
#include <list>

class Visitor;
class Type;
class ASTDeclarations;
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
	Type* type;
	ASTDeclarations* Declarations;
public:
	ASTField_Declaration(Type* type, ASTDeclarations* Declarations){
		this->type = type;
		this->Declarations = Declarations; 
	}
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
};

class ASTBinaryOperatorExpression: public ASTExpression {
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

};
*/

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

class ASTIdentifier: public BaseDeclaration{
	std::string id;
public:
	ASTIdentifier(std::string id){
		this->id=id;
	};
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
Field_Declarations: Field_Declaration SEMI_COLON Field_Declarations |
*/
class ASTField_Declarations: public BaseDeclaration{
	BaseDeclaration *FieldDeclaration_;
	ASTField_Declarations *FieldBaseDeclarations_;
public:
	ASTField_Declarations(BaseDeclaration *BaseDeclaration1, ASTField_Declarations *Field_Declarations1){
		FieldDeclaration_=BaseDeclaration1;
		FieldBaseDeclarations_= Field_Declarations1;
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


/*
Main: Field_Declarations Statements
*/

class ASTMain: public ASTnode{
	std::list<ASTField_Declaration*> *FieldBaseDeclaration_;
public:
	ASTMain(std::list<ASTField_Declaration*> *FieldBaseDeclaration){
		this->FieldBaseDeclaration_=FieldBaseDeclaration;
	}
};


//Boolean
//Binary	
//Unary
//Symbol
//Env

#endif