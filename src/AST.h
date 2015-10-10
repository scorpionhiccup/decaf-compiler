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

class ASTExpression: public ASTnode { 
};

class ASTLocation: public ASTnode{

};

class ASTStatement: public ASTnode{
	virtual void accept();	
};

class ASTProgram: public ASTnode{
private:
	std::string id_;
public:
	void accept(Visitor* visitor);
	ASTProgram(std::string id);
	std::string getId();
};

class ASTBlockStatement: public ASTStatement{
	ASTStatement* stmtlist_;
public:
	ASTBlockStatement(ASTStatement *stmtlist);
};

class ASTAssignmentStatement: public ASTStatement{
	ASTLocation loc_;
	ASTExpression expr_;
public:
	ASTAssignmentStatement(ASTLocation loc, ASTExpression expr);
};

class ASTMethodCallStatement: public ASTStatement{
	
};

class ASTIntegerLiteralExpression: public ASTExpression{
	int value_;
public:
	ASTIntegerLiteralExpression(int value);
	void setValue(int value);
};

//Float
//Boolean
//Binary	
//Unary
//Symbol
//Env


#endif