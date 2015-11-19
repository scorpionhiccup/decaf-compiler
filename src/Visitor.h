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
//#include <llvm/ModuleProvider.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/IR/LLVMContext.h>

using namespace llvm; 

class CodeGenBlock {
public:
	BasicBlock *block;
	std::map<std::string, Value*> locals;
};

class Visitor{
	std::stack<CodeGenBlock *> blocks;
	Function *mainFunction;
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

	Module *module;
	Visitor() { 
		module = new Module("main", getGlobalContext()); 
	}

	Type * CodeGen(Args* args);
	void CodeGen(ASTProgram* aSTProgram);
	void CodeGen(ASTMethod_Declaration* aSTMethod_Declaration);
	void CodeGen(ASTMF_Declaration* aSTMF_Declaration);
	void CodeGen(ASTIdentifier* aSTIdentifier, Type * type);
	void CodeGen(BinaryExpr* expr, Type * type);
	void CodeGen(Expression* expr, Type * type);
	void CodeGen(Bool* bool_obj);
	void CodeGen(Integer* integer);
	void CodeGen(ASTnode* aSTnode);
	void CodeGen(ExpressionRight* expressionRight);
	void CodeGen(RUnaryExpr* rUnaryExpr);
	void CodeGen(RBinaryExpr* rBinaryExpr);
	void CodeGen(ASTMain* aSTMain);
	void CodeGen(AssignmentStatement* assignmentStatement);
	void CodeGen(CalloutStatement* calloutStatement);
	void CodeGen(ASTDeclarations* aSTDeclarations, Type* type);
	void CodeGen(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration, Type * type);
	void CodeGen(ASTLocation* aSTLocation);
	void CodeGen(ASTField_Declaration* aSTField_Declaration);
	void CodeGen(ASTArrayIdentifier* aSTArrayIdentifier, Type * type);
	
	static Type * CodeGen(IntType* intType){
		return Type::getInt64Ty(getGlobalContext());
	};
	
	static Type * CodeGen(BooleanType* booleanType){
		return Type::getInt1Ty(getGlobalContext());
	};

	static Type * CodeGen(LangType* langType){
		return Type::getVoidTy(getGlobalContext());
	};

	static Type * CodeGen(VoidType* voidType){
		return Type::getVoidTy(getGlobalContext());
	};

	static Type * CodeGen(CharLiteral* charLiteral){
		return ConstantDataArray::getString(getGlobalContext(),
			charLiteral->getLiteral(),
			false)->getType();
	};

	static Type * CodeGen(StringLiteral * stringLiteral){
		return ConstantDataArray::getString(getGlobalContext(),
			stringLiteral->getLiteral(),
			false)->getType();
	};

	static Type * CodeGen(ListExpressionRight* listExpressionRight){
		return Type::getInt64Ty(getGlobalContext());
	};

	std::map<std::string, Value*>& locals();
	
	BasicBlock *currentBlock();
	
	void pushBlock(BasicBlock *block);

	void popBlock();

	void generateCode(ASTProgram *aSTProgram);

};

#endif