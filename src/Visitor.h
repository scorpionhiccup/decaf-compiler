#ifndef VISITOR_H
#define VISITOR_H

#include "AST.h"
#include "codegen.h"

class Visitor{
public:
	virtual ~Visitor();

	void visit(Args* args);
	void visit(ASTProgram* aSTProgram);
	void visit(ASTLocation* aSTLocation);
	void visit(ASTIdentifier* aSTIdentifier);
	void visit(ASTField_Declaration* aSTField_Declaration);
	void visit(ASTArrayIdentifier* aSTArrayIdentifier);
	void visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration);
	void visit(Def* def);
	void visit(ASTDeclarations* aSTDeclarations);
	void visit(CalloutStatement* calloutStatement);
	void visit(AssignmentStatement* assignmentStatement);
	void visit(ASTMain* aSTMain);
	void visit(RBinaryExpr* rBinaryExpr);
	void visit(RUnaryExpr* rUnaryExpr);
	void visit(ExpressionRight* expressionRight);
	void visit(ASTnode* aSTnode);
	void visit(Integer* integer);
	void visit(Bool* bool_obj);
	void visit(Expression* expr);
	void visit(BinaryExpr* expr);
	void visit(CharLiteral* charLiteral);
	void visit(StringLiteral* stringLiteral);

	CodeGenContext * codeGenContext;

	void CodeGen(Args* args);
	void CodeGen(ASTProgram* aSTProgram);
	void CodeGen(StringLiteral* stringLiteral);
	void CodeGen(CharLiteral* charLiteral);
	void CodeGen(BinaryExpr* expr);
	void CodeGen(Expression* expr);
	void CodeGen(Bool* bool_obj);
	void CodeGen(Integer* integer);
	void CodeGen(ASTnode* aSTnode);
	void CodeGen(ExpressionRight* expressionRight);
	void CodeGen(RUnaryExpr* rUnaryExpr);
	void CodeGen(RBinaryExpr* rBinaryExpr);
	void CodeGen(ASTMain* aSTMain);
	void CodeGen(AssignmentStatement* assignmentStatement);
	void CodeGen(CalloutStatement* calloutStatement);
	void CodeGen(ASTDeclarations* aSTDeclarations);
	void CodeGen(Def* def);
	void CodeGen(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration);
	void CodeGen(ASTLocation* aSTLocation);
	void CodeGen(ASTIdentifier* aSTIdentifier);
	void CodeGen(ASTField_Declaration* aSTField_Declaration);
	void CodeGen(ASTArrayIdentifier* aSTArrayIdentifier);
	
};

#endif