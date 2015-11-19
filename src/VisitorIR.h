#ifndef LLVM_VISITOR
#define LLVM_VISITOR

//#include "AST.h"

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

class CodeGenBlock {
public:
	BasicBlock *block;
	std::map<std::string, Value*> locals;
};


class VisitorIR: public Visitor{
	std::stack<CodeGenBlock *> blocks;
	Function *mainFunction;
public:
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
	void visit(Declaration * declaration);
	void visit(ASTMF_Declaration * aSTMF_Declaration);
	void visit(BinaryExpr* binaryExpr);
	
	Module *module;
	VisitorIR() { 
		module = new Module("main", getGlobalContext()); 
	}

	void visit(IntType* intType){
		intType->type=Type::getInt64Ty(getGlobalContext());
	};
	
	void visit(BooleanType* booleanType){
		booleanType->type=Type::getInt1Ty(getGlobalContext());
	};

	void visit(LangType* langType){
		langType->type=Type::getVoidTy(getGlobalContext());
	};

	void visit(VoidType* voidType){
		voidType->type=Type::getVoidTy(getGlobalContext());
	};

	void visit(CharLiteral* charLiteral){
		charLiteral->type=ConstantDataArray::getString(getGlobalContext(),
			charLiteral->getLiteral(),
			false)->getType();
	};

	void visit(StringLiteral * stringLiteral){
		stringLiteral->type = ConstantDataArray::getString(getGlobalContext(),
			stringLiteral->getLiteral(),
			false)->getType();
	};

	void visit(ListExpressionRight* listExpressionRight){
		listExpressionRight->type = Type::getInt64Ty(getGlobalContext());
	};

	std::map<std::string, Value*>& locals();
	
	BasicBlock *currentBlock();
	
	void pushBlock(BasicBlock *block);

	void popBlock();

	void generateCode(ASTProgram *aSTProgram);

};

#endif