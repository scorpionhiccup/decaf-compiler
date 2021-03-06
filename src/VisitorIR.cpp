#include <bits/stdc++.h>

#include "Visitor.h"
#include "AST.h"
#include "VisitorIR.h"
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/PassManager.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/ADT/ArrayRef.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/IR/DataLayout.h>

#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/CallingConv.h>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Assembly/PrintModulePass.h>

#include <llvm/ExecutionEngine/GenericValue.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/ADT/STLExtras.h>



static IRBuilder<> Builder(getGlobalContext());
bool is_debug=true, is_error=false;

extern int version;

static void printLevel(int depth){
	for(int i=0;i<depth-1;i++){
		cout<<'\t';
	}
}

void printDebug2(string str){
	if (version==0){
		cout<<str<<"\n";
	}
}

class GenerateError{
public:
	static Value* ErrorMsg(string str) { 
		cout<<"Error: "<<str<<endl;
		return 0;
	}
};

void VisitorIR::generateCode(ASTProgram *aSTProgram){
	fflush(stdout);
	vector<Type*> argTypes;
	FunctionType *ftype = FunctionType::get(
		Type::getVoidTy(getGlobalContext()), argTypes, false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "Class Program", this->module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);

	printDebug2("Inside Main Block");

	pushBlock(bblock);
	aSTProgram->evaluate(this);
	popBlock();

	//printDebug2("Outside Main Block");

	if (!is_error){
		PassManager pm;
		pm.add(createPrintModulePass(&outs()));
		pm.run(*module);
	}else{
		cout<<"Failure\n";
		exit(1);
	}
	
}

void VisitorIR::visit(ASTProgram* aSTProgram){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug2("Inside ASTProgram ");	
	
	for (list<ASTDeclaration*>::iterator it=aSTProgram->ASTDeclarations->begin();
		it!=aSTProgram->ASTDeclarations->end(); ++it){
		(*it)->evaluate(this);
	}


	//printDebug2("Outside ASTProgram");
	aSTProgram->to_return=V;
	
}

void VisitorIR::visit(Args* args){

	string msg="Inside Args ";
	msg.append(args->getLiteral());

	printDebug2(msg);
	
	args->type=ConstantDataArray::getString(getGlobalContext(),
			"args", false)->getType();

	args->to_return=ConstantInt::get(getGlobalContext(), APInt(32,0));

	//printDebug2("Outside Args");
		
}

void VisitorIR::visit(ASTMethod_Declaration* aSTMethod_Declaration){
	Value * V;

	//TODO: Add Callout Arguements from AST Class.
	printDebug2("Inside ASTMethod_Declaration");

	vector<Type*> argTypes;

	for (list<ASTParam_Declaration *>::reverse_iterator it=aSTMethod_Declaration->ASTParam_Declaration1->rbegin(); 
		it!=aSTMethod_Declaration->ASTParam_Declaration1->rend(); ++it){
		(*it)->evaluate(this, false);
		/*Type * type = (*it)->type;
		argTypes.push_back(type);*/
	}

	LangType * langType = aSTMethod_Declaration->getLangType();
	
	printDebug2("<--------------------------------------------------------------------");
	
	langType->evaluate(this);

	printDebug2("-------------------------------------------------------------------->");	
	
	Type * type = langType->type;
	
	FunctionType *ftype = FunctionType::get(
		type, argTypes, false);

	Function *function = Function::Create(ftype, 
		GlobalValue::InternalLinkage,
		aSTMethod_Declaration->getIdentifier(),
		this->module);
	
	BasicBlock *bblock = BasicBlock::Create(
		getGlobalContext(), "entry", function, 0);
	
	/*
		BasicBlock *bblock = BasicBlock::Create(
			getGlobalContext(), aSTMethod_Declaration->IDENTIFIER, function, 0);
	*/

	Builder.SetInsertPoint(bblock);
	this->pushBlock(bblock);

	printDebug2("--------------------------------------------------------------------");
	//Block * block =

	aSTMethod_Declaration->Block->evaluate(this);
	
	for (list<ASTParam_Declaration *>::reverse_iterator it=aSTMethod_Declaration->ASTParam_Declaration1->rbegin(); 
		it!=aSTMethod_Declaration->ASTParam_Declaration1->rend(); ++it){
		(*it)->evaluate(this, true);
	}


	/*for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		
		AllocaInst *alloc = new AllocaInst(
			static_cast<Type *>((*it)->evaluate(this)), 
			(*it)->getLiteral(), 
			this->currentBlock());
		this->locals()[(*it)->getLiteral()] = alloc;

		//(*it)->evaluate(this);
	}*/

	printDebug2("--------------------------------------------------------------------");
	
	this->popBlock();
	
	aSTMethod_Declaration->to_return=function;

	//printDebug2("Outside ASTMethod_Declaration");

};
	
void VisitorIR::visit(ASTMF_Declaration * aSTMF_Declaration){
	printDebug2("Inside ASTMF_Declaration");

	aSTMF_Declaration->to_return=ConstantInt::get(getGlobalContext(), APInt(32,0));

	//printDebug2("Outside ASTMF_Declaration");

}

void VisitorIR::visit(ASTIdentifier* aSTIdentifier){
	string msg="Inside ASTIdentifier ";
	msg.append(aSTIdentifier->getId());
	printDebug2(msg);
	
	string id=aSTIdentifier->getId();

	if (this->getCurrentCodeGenBlock()->in_field){
		if (this->locals().find(id) != this->locals().end()){
			is_error=true;
			aSTIdentifier->Def::to_return=GenerateError::ErrorMsg("Same Variable with name " + aSTIdentifier->getId() + "declared more than twice");
			return;
		}

		AllocaInst *alloc = new AllocaInst(
			aSTIdentifier->type, id, this->currentBlock());
		aSTIdentifier->Def::to_return=this->locals()[id]=alloc;
		return;
	}

	if (this->locals().find(id) == this->locals().end()){
		is_error=true;
		aSTIdentifier->Def::to_return=GenerateError::ErrorMsg("Unknown variable name " + aSTIdentifier->getId());
		return;
	}

	aSTIdentifier->Def::to_return=new LoadInst(this->locals()[id], "", false, this->currentBlock());

	//printDebug2("Outside ASTIdentifier");

}


void VisitorIR::visit(ASTArrayIdentifier* aSTArrayIdentifier){
	Value * V;
	std::list<Expression*>* exprs = aSTArrayIdentifier->getExpression();

	printDebug2("Inside ASTArrayIdentifier");

	string id=aSTArrayIdentifier->getId();

	ASTIdentifier * aSTIdentifier = aSTArrayIdentifier->getIdentifier();

	aSTIdentifier->evaluate(this);

	AllocaInst *alloc = new AllocaInst(
		Type::getInt64Ty(getGlobalContext()),
		id, this->currentBlock());

	V=this->locals()[id]=alloc;
	
	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);
		(*it)->to_return;
	}

	aSTIdentifier->Def::to_return = 
		V ? V : GenerateError::ErrorMsg("Unknown variable name " + aSTIdentifier->getId());

	//printDebug2("Outside ASTArrayIdentifier");

}

void VisitorIR::visit(BinaryExpr* expr){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug2("Inside BinaryExpr");

	std::list<Expression*>* exprs=expr->getLeftExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->type=expr->type;
		(*it)->evaluate(this);
	}

	exprs=expr->getRightExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){

		(*it)->type=expr->type;
		(*it)->evaluate(this);
	}

	expr->to_return=V;

	//printDebug2("Outside BinaryExpr");

}

void VisitorIR::visit(Expression * expr){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug2("Inside Expression");

	expr->evaluate(this);

	//expr->to_return=V;

	//printDebug2("Outside Expression");

}

void VisitorIR::visit(Bool* bool_obj){
	Value * V = ConstantInt::get(
		getGlobalContext(), APInt(32, bool_obj->getValue()));
	
	printDebug2("Inside Bool");

	bool_obj->ExpressionRight::to_return=V;

	//printDebug2("Outside Bool");

}

void VisitorIR::visit(Integer* integer){
	int value = integer->getValue();

	Value * V = ConstantInt::get(
		getGlobalContext(), APInt(32, value));
	
	string msg="Inside Integer ";
	msg.append(to_string(value));
	printDebug2(msg);

	integer->ExpressionRight::to_return=V;

	//printDebug2("Outside Args");

}

void VisitorIR::visit(ASTnode* aSTnode){
	printDebug2("Inside ASTnode");

	Value * V = ConstantInt::get(
		getGlobalContext(), APInt(32,0));

	//aSTnode->evaluate(this);
	aSTnode->to_return=V;

	//printDebug2("Outside ASTnode");

}

void VisitorIR::visit(ExpressionRight* expressionRight){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug2("Inside ExpressionRight");

	expressionRight->evaluate(this);

	//expressionRight->to_return=V;

	//printDebug2("Outside ExpressionRight");

}

void VisitorIR::visit(RUnaryExpr* rUnaryExpr){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug2("Inside RUnaryExpr");

	std::list<ExpressionRight*> * exprs = rUnaryExpr->getExpressions();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);
	}

	rUnaryExpr->to_return=V;

	//printDebug2("Outside RUnaryExpr");

}


void VisitorIR::visit(RBinaryExpr* rBinaryExpr){

	printDebug2("Inside RBinaryExpr");
	Instruction::BinaryOps instr;

	Value * lhs=NULL, * rhs=NULL, *temp;

	std::list<ExpressionRight*>* exprs=rBinaryExpr->getLeftExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);
		temp=(*it)->to_return;
		if (temp){
			lhs=temp;
		}
	}

	exprs=rBinaryExpr->getRightExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);
		temp=(*it)->to_return;
		if (temp){
			rhs=temp;
		}
	}

	const char * type=rBinaryExpr->getType().c_str();

	if (!strcmp(type, "+")){
		instr=Instruction::Add;
	}else if (!strcmp(type, "-")){
		instr=Instruction::Sub;	
	}else if (!strcmp(type, "*")){
		instr=Instruction::Mul;	
	}else if (!strcmp(type, "/")){
		instr=Instruction::SDiv;	
	}else if (!strcmp(type, "%")){
		instr=Instruction::SRem;	
	} else if (!strcmp(type, "&&")){
		instr=Instruction::And;	
	} else if (!strcmp(type, "||")){
		instr=Instruction::Or;	
	} else if (!strcmp(type, "==")){
		rBinaryExpr->to_return = CmpInst::Create(Instruction::ICmp, 
			ICmpInst::ICMP_EQ, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, "<=")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, 
			ICmpInst::ICMP_ULE, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, ">=")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, 
			ICmpInst::ICMP_UGE, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, ">")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, 
			ICmpInst::ICMP_ULT, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, "<")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, 
			ICmpInst::ICMP_UGT, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, "!=")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, 
			ICmpInst::ICMP_NE, lhs, rhs, "", this->currentBlock());
	}

	Value * V=NULL;

	if (lhs && rhs){
		V=BinaryOperator::Create(instr, lhs, rhs, "", this->currentBlock());
	}
	
	rBinaryExpr->to_return = V;

	//printDebug2("Outside RBinaryExpr");

}

void VisitorIR::visit(ASTMain* aSTMain){

	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug2("Inside ASTMain");
	
	printDebug2("Inside FieldDeclarations");

	for(list<ASTField_Declaration*>::reverse_iterator it=aSTMain->FieldDeclarations_->rbegin(); 
		it!=aSTMain->FieldDeclarations_->rend(); ++it){
		(*it)->evaluate(this);
		V=(*it)->ASTExpression::to_return;
	}

	this->getCurrentCodeGenBlock()->in_field=false;

	//printDebug2("Outside FieldDeclarations");

	printDebug2("Inside ASTStatements");

	for (list<ASTStatement*>::reverse_iterator it=aSTMain->statements->rbegin(); 
		it!=aSTMain->statements->rend(); ++it){
		(*it)->evaluate(this);
		V=(*it)->to_return;

	}

	//printDebug2("Outside ASTStatements");

	//printDebug2("Outside ASTMain");

	aSTMain->to_return=V;
}

void VisitorIR::visit(AssignmentStatement* assignmentStatement){
	
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug2("Inside AssignmentStatement");

	ASTLocation * location = assignmentStatement->getLocation();
	string id=location->getId();

	if (this->locals().find(id) == this->locals().end()){
		string error_str="Undeclared Variable in assignment statement: ";
		cerr<<error_str<<id<<"\n";
		is_error=1;
		assignmentStatement->to_return=NULL;
		return;
	}

	if (assignmentStatement->expressionRight->size()){
		ExpressionRight * expr = assignmentStatement->expressionRight->back();

		expr->evaluate(this);
		V=expr->to_return;
		
		if (V){
			V=new StoreInst(V, this->locals()[id], this->currentBlock());
			//location->type=expr->type;
			location->evaluate(this);
		}	
	}

	/*for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
	}*/

	//printDebug2("Outside AssignmentStatement");

	assignmentStatement->to_return=V;
}

void VisitorIR::visit(CalloutStatement* calloutStatement){
	printDebug2("Inside CalloutStatement");
	
	Value * V;

	vector<Type*> argTypes;
	LangType* langType;

	for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		(*it)->evaluate(this);
		argTypes.push_back((*it)->type);
	}

	FunctionType *ftype = FunctionType::get(
		Type::getInt64Ty(getGlobalContext()), 
		argTypes, false);

	Function *function = Function::Create(ftype, 
		GlobalValue::InternalLinkage,
		calloutStatement->name.c_str(),
		this->module);
	
	BasicBlock *bblock = BasicBlock::Create(
		getGlobalContext(), "entry", function, 0);
	Builder.SetInsertPoint(bblock);
	this->pushBlock(bblock);

	for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		(*it)->evaluate(this);
		AllocaInst *alloc = new AllocaInst(
			(*it)->type, 
			(*it)->getLiteral(), 
			this->currentBlock());
		this->locals()[(*it)->getLiteral()] = alloc;

		//(*it)->evaluate(this);
	}
	
	this->popBlock();
	
	calloutStatement->to_return=function;

	//printDebug2("Outside CalloutStatement");

}

void VisitorIR::visit(ASTDeclarations* aSTDeclarations){
	printDebug2("Inside ASTDeclarations");
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	Def *def=aSTDeclarations->getDef();
	def->type=aSTDeclarations->type;
	def->evaluate(this);

	aSTDeclarations->to_return = aSTDeclarations->to_return?aSTDeclarations->to_return:V;

	//printDebug2("Outside ASTDeclarations");

}

void VisitorIR::visit(ASTLocation* aSTLocation){
	printDebug2("Inside ASTLocation");

	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));	

	aSTLocation->ExpressionRight::to_return=V;
	//printDebug2("Outside ASTLocation");

}

void VisitorIR::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	Value * V;
	
	printDebug2("Inside ASTArrayFieldDeclaration");
	ASTIdentifier * aSTIdentifier=aSTArrayFieldDeclaration->getIdentifier();
	aSTIdentifier->type=aSTArrayFieldDeclaration->type;

	aSTIdentifier->evaluate(this);

	aSTArrayFieldDeclaration->to_return = aSTIdentifier->Def::to_return ? 
		aSTIdentifier->Def::to_return : GenerateError::ErrorMsg("Unknown variable name " + aSTIdentifier->getId());

	//printDebug2("Outside aSTArrayFieldDeclaration");

}

BasicBlock * VisitorIR::currentBlock() { 
	return blocks.top()->block; 
}

void VisitorIR::pushBlock(BasicBlock *block) { 
	blocks.push(new CodeGenBlock()); 
	blocks.top()->block = block;
}

CodeGenBlock * VisitorIR::getCurrentCodeGenBlock(){
	return blocks.top();
};

void VisitorIR::popBlock() { 
	CodeGenBlock *top = blocks.top(); 
	blocks.pop(); 
	delete top; 
}

std::map<std::string, Value*>& VisitorIR::locals() { 
	return blocks.top()->locals;
}

void VisitorIR::visit(ASTField_Declaration* aSTField_Declaration){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	LangType *langType=aSTField_Declaration->getType();
	printDebug2("Inside ASTField_Declaration");

	langType->evaluate(this);

	aSTField_Declaration->type=langType;

	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){

		(*it)->type=langType->type;
		(*it)->evaluate(this);
		if ((*it)->to_return){
			V=(*it)->to_return;
		}
	}	
	
	aSTField_Declaration->ASTExpression::to_return=V;

	//printDebug2("Outside ASTField_Declaration");

}

void VisitorIR::visit(Def* def){
	printDebug2("Inside Def");
	def->evaluate(this);
}

void VisitorIR::visit(ASTDeclaration* declaration){
	printDebug2("Inside ASTDeclaration");
	ASTMF_Declaration * dec = declaration->getDeclaration();
	dec->evaluate(this);
	declaration->to_return=dec->to_return;
	//printDebug2("Outside ASTDeclaration");

}

void VisitorIR::visit(ASTParam_Declaration * aSTParam_Declaration, bool go_into){
	printDebug2("Inside ASTParam_Declaration");

	LangType * langType = aSTParam_Declaration->getType();

	langType->evaluate(this);

	if (go_into){
		bool temp=this->getCurrentCodeGenBlock()->in_field;
		this->getCurrentCodeGenBlock()->in_field=true;

		aSTParam_Declaration->Def1->type = langType->type;
		aSTParam_Declaration->Def1->evaluate(this);
		this->getCurrentCodeGenBlock()->in_field=temp;
	}
	
	aSTParam_Declaration->type = langType->type;

	//aSTParam_Declaration->type=dynamic_cast<Type *>(langType->to_return);
	printDebug2("Outside ASTParam_Declaration");

}

void VisitorIR::visit(ASTFor * aSTFor){
	printDebug2("Inside ASTForjebngjksdb");

	Value * InitExpr;

	for (list<ExpressionRight*>::reverse_iterator it=aSTFor->ExpressionRight1->rbegin();
		it!=aSTFor->ExpressionRight1->rend(); ++it){
		(*it)->evaluate(this);
		InitExpr = (*it)->to_return;
	}

	Function *TheFunction = Builder.GetInsertBlock()->getParent();

	BasicBlock *PreheaderBB = Builder.GetInsertBlock();

	BasicBlock *LoopBB = BasicBlock::Create(getGlobalContext(), 
		"loop", TheFunction);

	Builder.CreateBr(LoopBB);

    Builder.SetInsertPoint(LoopBB);


    Value * EndExpr;

	for (list<ExpressionRight*>::reverse_iterator it=aSTFor->ExpressionRight2->rbegin();
		it!=aSTFor->ExpressionRight2->rend(); ++it){
		(*it)->evaluate(this);
		EndExpr = (*it)->to_return;
	}

	/*EndExpr = Builder.CreateFCmpONE(EndExpr, 
			ConstantFP::get(getGlobalContext(), APFloat(0.0)),
			"loop-condition");*/

    /*llvm::AllocaInst *Alloca = Builder2.CreateAlloca(
    	llvm::Type::getInt32Ty(llvm::getGlobalContext()), 
    	0, aSTFor->IDENTIFIER);

    Builder.CreateStore(InitExpr, Alloca);

    BasicBlock *PreheaderBB = Builder.GetInsertBlock();
    BasicBlock *LoopBB = BasicBlock::Create(getGlobalContext(), 
    	"loop", TheFunction);

    PHINode *Variable = Builder.CreatePHI(
    	Type::getInt32Ty(getGlobalContext()), 
    	2, aSTFor->IDENTIFIER);

    Variable->addIncoming(InitExpr, PreheaderBB);*/

       
	printDebug2("Outside ASTFor");
}

void VisitorIR::visit(ASTStatement * aSTStatement){
	printDebug2("Inside ASTStatement");	
}