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

	virtual void visit(Args* args);
	virtual void visit(ASTProgram* aSTProgram);
	virtual void visit(ASTLocation* aSTLocation);
	virtual void visit(ASTIdentifier* aSTIdentifier);
	virtual void visit(ASTMethod_Declaration* aSTMethod_Declaration);	
	virtual void visit(ASTField_Declaration* aSTField_Declaration);
	virtual void visit(ASTArrayIdentifier* aSTArrayIdentifier);
	virtual void visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration);
	virtual void visit(Def* def);
	virtual void visit(ASTDeclarations* aSTDeclarations);
	virtual void visit(CalloutStatement* calloutStatement);
	virtual void visit(AssignmentStatement* assignmentStatement);
	virtual void visit(ASTMain* aSTMain);
	virtual void visit(RBinaryExpr* rBinaryExpr);
	virtual void visit(RUnaryExpr* rUnaryExpr);
	virtual void visit(ExpressionRight* expressionRight);
	virtual void visit(ASTnode* aSTnode);
	virtual void visit(Integer* integer);
	virtual void visit(Bool* bool_obj);
	virtual void visit(Expression* expr);
	virtual void visit(BinaryExpr* expr);
	virtual void visit(Declaration * declaration);
	virtual void visit(ASTParam_Declaration * aSTParam_Declaration);
	virtual void visit(MethodCallStatement * methodCallStatement);
	virtual void visit(ASTIF * aSTIF);
	virtual void visit(ASTIFELSE * aSTIFELSE);
	virtual void visit(ASTFor * aSTFor);
	virtual void visit(ASTReturn * aSTReturn);
	virtual void visit(ReturnValue * returnValue);	
	virtual void visit(ASTBreak * aSTBreak);
	virtual void visit(ASTContinue * aSTContinue);
	virtual void visit(LangType * langType);
	virtual void visit(IntType* intType);
	virtual void visit(BooleanType* booleanType);
	virtual void visit(VoidType* voidType);
	virtual void visit(CharLiteral* charLiteral);
	virtual void visit(StringLiteral * stringLiteral);


	Visitor() { 
	}

};

#endif