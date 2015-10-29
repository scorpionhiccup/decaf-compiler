#ifndef VISITOR_H
#define VISITOR_H

#include "AST.h"
	
class Visitor{
public:
	virtual ~Visitor();

	void visit(ASTProgram* aSTProgram);
	void visit(ASTnode* aSTnode);
	void visit(ASTLocation* aSTLocation);
	void visit(BaseDeclaration* baseDeclaration);
	void visit(ASTLocation* aSTLocation);
	void visit(ASTIdentifier* aSTIdentifier);
	void visit(ASTArrayIdentifier* aSTArrayIdentifier);
	void visit(BaseFieldDeclaration* baseFieldDeclaration);
	void visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration);
	void visit(Def* def);
	void visit(ASTDeclarations* aSTDeclarations);
	void visit(CalloutStatement* calloutStatement);
	void visit(AssignmentStatement* assignmentStatement);
	void visit(ASTMain* aSTMain);	
};

#endif