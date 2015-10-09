#ifndef __AST_H__
#define __AST_H__

#include <string>
extern FILE* XML_fp;

class ASTnode{
public:
	virtual void visit();
};

class ASTExpression: public ASTnode { 
};

class ASTLocation: public ASTnode{

};

class ASTStatement: public ASTnode{
	virtual void visit();	
};

class ASTProgram: public ASTnode{
private:
	std::string id_;
public:
	void visit();
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
	ASTAssignmentStatement(ASTLocation loc, ASTExpression expr){
		this->loc_ = loc;
		this->expr_ = expr;
	}
};

class ASTMethodCallStatement: public ASTStatement{
	
};
#endif