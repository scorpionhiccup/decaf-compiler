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
	virtual void visit(Declaration * declaration);
	virtual void visit(ASTMF_Declaration * aSTMF_Declaration);
	virtual void visit(BinaryExpr* binaryExpr);
	virtual void visit(ASTParam_Declaration * aSTParam_Declaration);
	
	Module *module;
	VisitorIR() { 
		module = new Module("main", getGlobalContext()); 
	}

	virtual void visit(IntType* intType){
		intType->type=Type::getInt64Ty(getGlobalContext());
		cout<<"caasfht\n";
		return;
	};
	
	virtual void visit(BooleanType* booleanType){
		cout<<"Inside BooleanType\n";
		booleanType->type=Type::getInt1Ty(getGlobalContext());
	};

	virtual void visit(LangType* langType){
		cout<<"Inside LangType\n";
		langType->type=Type::getVoidTy(getGlobalContext());
	};

	virtual void visit(VoidType* voidType){
		cout<<"Inside VoidType\n";
		voidType->type=Type::getVoidTy(getGlobalContext());
	};

	virtual void visit(CharLiteral* charLiteral){
		charLiteral->type=ConstantDataArray::getString(getGlobalContext(),
			charLiteral->getLiteral(),
			false)->getType();
	};

	virtual void visit(StringLiteral * stringLiteral){
		stringLiteral->type = ConstantDataArray::getString(getGlobalContext(),
			stringLiteral->getLiteral(),
			false)->getType();
	};

	virtual void visit(ListExpressionRight* listExpressionRight){
		listExpressionRight->type = Type::getInt64Ty(getGlobalContext());
	};

	std::map<std::string, Value*>& locals();
	
	BasicBlock *currentBlock();
	
	void pushBlock(BasicBlock *block);

	void popBlock();

	void generateCode(ASTProgram *aSTProgram);

};

#endif