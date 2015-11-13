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

	/*
	llvm::Value* CodeGen(Args* args);
	llvm::Value* CodeGen(ASTProgram* aSTProgram);
	llvm::Value* CodeGen(StringLiteral* stringLiteral);
	llvm::Value* CodeGen(CharLiteral* charLiteral);
	llvm::Value* CodeGen(BinaryExpr* expr);
	llvm::Value* CodeGen(Expression* expr);
	llvm::Value* CodeGen(Bool* bool_obj);
	llvm::Value* CodeGen(Integer* integer);
	llvm::Value* CodeGen(ASTnode* aSTnode);
	llvm::Value* CodeGen(ExpressionRight* expressionRight);
	llvm::Value* CodeGen(RUnaryExpr* rUnaryExpr);
	llvm::Value* CodeGen(RBinaryExpr* rBinaryExpr);
	llvm::Value* CodeGen(ASTMain* aSTMain);
	llvm::Value* CodeGen(AssignmentStatement* assignmentStatement);
	llvm::Value* CodeGen(CalloutStatement* calloutStatement);
	llvm::Value* CodeGen(ASTDeclarations* aSTDeclarations);
	llvm::Value* CodeGen(Def* def);
	llvm::Value* CodeGen(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration);
	llvm::Value* CodeGen(ASTLocation* aSTLocation);
	llvm::Value* CodeGen(ASTIdentifier* aSTIdentifier);
	llvm::Value* CodeGen(ASTField_Declaration* aSTField_Declaration);
	llvm::Value* CodeGen(ASTArrayIdentifier* aSTArrayIdentifier);*/
	
};

#endif