#ifndef VISITOR_H
#define VISITOR_H

#include "AST.h"

#include <stack>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/PassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LLVMContext.h>

using namespace llvm; 

class Visitor{
public:
	virtual ~Visitor();

	void visit(Args* args);
	void visit(ASTProgram* aSTProgram);
	void visit(ASTLocation* aSTLocation);
	void visit(ASTIdentifier* aSTIdentifier);
	void visit(ASTMethod_Declaration* aSTMethod_Declaration);	
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
	void visit(Declaration * declaration);
	void visit(ASTParam_Declaration * aSTParam_Declaration);
	void visit(MethodCallStatement * methodCallStatement);
	void visit(ASTIF * aSTIF);
	void visit(ASTIFELSE * aSTIFELSE);
	void visit(ASTFor * aSTFor);
	void visit(ASTReturn * aSTReturn);
	void visit(ReturnValue * returnValue);	
	void visit(ASTBreak * aSTBreak);
	void visit(ASTContinue * aSTContinue);
	
	Visitor() { 
	}


};

#endif