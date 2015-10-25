#include <list>

#ifndef VISITOR_H
#define VISITOR_H

class ASTProgram;
class Visitor
{
public:
	virtual ~Visitor();
	void visit(ASTProgram* aSTProgram);
};

#endif