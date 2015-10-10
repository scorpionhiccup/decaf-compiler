#include "AST.h"

#if !defined(VISITOR_H)
#define VISITOR_H 1

class Visitor
{
public:
	virtual ~Visitor();
	void visit(ASTProgram aSTProgram);
};

#endif