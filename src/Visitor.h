#ifndef VISITOR_H
#define VISITOR_H

#include <list>

class ASTProgram;
class ASTnode;
class Visitor{
public:
	virtual ~Visitor();
	void visit(ASTProgram* aSTProgram);
	void visit(ASTnode* aSTnode);
};

#endif