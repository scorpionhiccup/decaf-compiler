#ifndef VISITOR_H
#define VISITOR_H

#include "AST.h"

class Visitor{
public:
	virtual ~Visitor();
	void visit(ASTProgram* aSTProgram);
	void visit(ASTnode* aSTnode);
};

#endif