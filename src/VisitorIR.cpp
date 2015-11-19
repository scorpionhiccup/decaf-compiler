#include <bits/stdc++.h>

#include "Visitor.h"
#include "AST.h"
#include "VisitorIR.h"

static IRBuilder<> Builder(getGlobalContext());
static bool in_field=true, is_debug=true, is_error=false;

class GenerateError{
public:
	static Value* ErrorMsg(string str) { 
		cout<<"Error: "<<str<<endl;
		return 0;
	}
};

void VisitorIR::generateCode(ASTProgram *aSTProgram){
	vector<Type*> argTypes;
	FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), argTypes, false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "Class Program", this->module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);

	printDebug("Inside Main Block");

	pushBlock(bblock);
	aSTProgram->GenCode(this);
	popBlock();

	if (!is_error){
		PassManager pm;
		pm.add(createPrintModulePass(&outs()));
		pm.run(*module);
	}else{
		cout<<"Failure\n";
		exit(1);
	}
	
}

void VisitorIR::CodeGen(ASTProgram* aSTProgram){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	ASTMain* aSTMain=aSTProgram->getMain();
	printDebug("Inside ASTProgram");
	aSTMain->GenCode(this);
	
	aSTProgram->to_return=V;
}

Type * VisitorIR::CodeGen(Args* args){
	string msg="Inside Args ";
	msg.append(args->getLiteral());

	printDebug(msg);
	
	return ConstantDataArray::getString(getGlobalContext(),
			"args", false)->getType();
		
}

void VisitorIR::CodeGen(ASTMethod_Declaration* aSTMethod_Declaration){
	Value * V;

	//TODO: Add Callout Arguements from AST Class.

	printDebug("Inside ASTMethod_Declaration");
	vector<Type*> argTypes;
	
	/*for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		Type * type = static_cast<Type *>((*it)->GenCode(this));
		argTypes.push_back(type);
	}*/

	LangType* langType = aSTMethod_Declaration->getLangType();
	Type * type = static_cast<Type *>(langType->GenCode(this));
	
	FunctionType *ftype = FunctionType::get(
		type, 
		argTypes, false);

	Function *function = Function::Create(ftype, 
		GlobalValue::InternalLinkage,
		aSTMethod_Declaration->getIdentifier(),
		this->module);
	
	BasicBlock *bblock = BasicBlock::Create(
		getGlobalContext(), "entry", function, 0);
	
	Builder.SetInsertPoint(bblock);
	this->pushBlock(bblock);

	/*for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		
		AllocaInst *alloc = new AllocaInst(
			static_cast<Type *>((*it)->GenCode(this)), 
			(*it)->getLiteral(), 
			this->currentBlock());
	    this->locals()[(*it)->getLiteral()] = alloc;

		//(*it)->GenCode(this);
	}*/
	
	this->popBlock();
	
	return function;

};
	
void VisitorIR::CodeGen(ASTMF_Declaration * aSTMF_Declaration){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	return V;
}

void VisitorIR::CodeGen(ASTIdentifier* aSTIdentifier, Type * type){
	if (in_field){
		Value *v;
		AllocaInst *alloc = new AllocaInst(type, aSTIdentifier->getId(), this->currentBlock());
		v=this->locals()[aSTIdentifier->getId()]=alloc;
    	return v;
	}

	string msg="Inside ASTIdentifier ";
	msg.append(aSTIdentifier->getId());
	printDebug(msg);
	
	if (this->locals().find(aSTIdentifier->getId()) == this->locals().end()){
		is_error=true;
		return GenerateError::ErrorMsg("Unknown variable name");
	}
	
	return new LoadInst(this->locals()[aSTIdentifier->getId()], "", false, this->currentBlock());
}

void VisitorIR::CodeGen(BinaryExpr* expr, Type * type){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside BinaryExpr");

	std::list<Expression*>* exprs=expr->getLeftExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this, type);
	}

	exprs=expr->getRightExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this, type);

	}
	
	return V;
}

void VisitorIR::CodeGen(Expression* expr, Type * type){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside Expression");

	return V;
}

void VisitorIR::CodeGen(Bool* bool_obj){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside Bool");

	return V;
}

void VisitorIR::CodeGen(Integer* integer){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	string msg="Inside Integer ";
	msg.append(to_string(integer->getValue()));
	printDebug(msg);

	return V;
}

void VisitorIR::CodeGen(ASTnode* aSTnode){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	aSTnode->GenCode(this);

	return V;
}

void VisitorIR::CodeGen(ExpressionRight* expressionRight){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug("Inside ExpressionRight");

	return V;
}

void VisitorIR::CodeGen(RUnaryExpr* rUnaryExpr){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside RUnaryExpr");

	std::list<ExpressionRight*> * exprs = rUnaryExpr->getExpressions();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	return V;
}


void VisitorIR::CodeGen(RBinaryExpr* rBinaryExpr){

	printDebug("Inside RBinaryExpr");
	Instruction::BinaryOps instr;

	Value * lhs=NULL, * rhs=NULL, *temp;

	std::list<ExpressionRight*>* exprs=rBinaryExpr->getLeftExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		temp=(*it)->GenCode(this);
		if (temp){
			lhs=temp;
		}
	}

	exprs=rBinaryExpr->getRightExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		temp=(*it)->GenCode(this);
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
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, "<=")){
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULE, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, ">=")){
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGE, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, ">")){
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULT, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, "<")){
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGT, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, "!=")){
		return CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_NE, lhs, rhs, "", this->currentBlock());
	}

	Value * V=NULL;

	if (lhs && rhs){
		V=BinaryOperator::Create(instr, lhs, rhs, "", this->currentBlock());
	}
	
	return V;

}

void VisitorIR::CodeGen(ASTMain* aSTMain){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug("Inside ASTMain");
	
	for(list<ASTField_Declaration*>::reverse_iterator it=aSTMain->FieldDeclarations_->rbegin(); 
		it!=aSTMain->FieldDeclarations_->rend(); ++it){
		(*it)->GenCode(this);
	}

	in_field=false;

	printDebug("Inside ASTStatements");

	for (list<ASTStatement*>::reverse_iterator it=aSTMain->statements->rbegin(); 
		it!=aSTMain->statements->rend(); ++it){
		(*it)->GenCode(this);
	}
	return V;
}

void VisitorIR::CodeGen(AssignmentStatement* assignmentStatement){
	
	printDebug("Inside AssignmentStatement");

	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	ASTLocation * location = assignmentStatement->getLocation();
	string id=location->getId();
	V=location->GenCode(this, NULL);

	if (this->locals().find(id) == this->locals().end()){
		string error_str="Undeclared Variable in assignment statement: ";
		cerr<<error_str<<id<<"\n";
		is_error=1;
		return NULL;
	}


	for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
		V=(*it)->GenCode(this);
		if (V!=NULL){
			V=new StoreInst(V, this->locals()[id], this->currentBlock());
		}
	}

	return V;
}

void VisitorIR::CodeGen(CalloutStatement* calloutStatement){
	printDebug("Inside CalloutStatement");
	
	Value * V;

	vector<Type*> argTypes;
	
	for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		Type * type = static_cast<Type *>((*it)->GenCode(this));
		argTypes.push_back(type);
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
		
		AllocaInst *alloc = new AllocaInst(
			static_cast<Type *>((*it)->GenCode(this)), 
			(*it)->getLiteral(), 
			this->currentBlock());
	    this->locals()[(*it)->getLiteral()] = alloc;

		//(*it)->GenCode(this);
	}
	
	this->popBlock();
	
	return function;
}

void VisitorIR::CodeGen(ASTDeclarations* aSTDeclarations, Type * type){
	printDebug("Inside ASTDeclarations");
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	Def *def=aSTDeclarations->getDef();
	V=def->GenCode(this, type);
	return V;
}

void VisitorIR::CodeGen(ASTLocation* aSTLocation){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside ASTLocation");

	return V;
}


void VisitorIR::CodeGen(ASTArrayIdentifier* aSTArrayIdentifier, Type* type){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	std::list<Expression*>* exprs = aSTArrayIdentifier->getExpression();

	printDebug("Inside ASTArrayIdentifier");
	AllocaInst *alloc = new AllocaInst(type, 
		aSTArrayIdentifier->getId(), this->currentBlock());
	V=this->locals()[aSTArrayIdentifier->getId()]=alloc;
	
	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		V=(*it)->GenCode(this, type);
	}

	return V ? V : GenerateError::ErrorMsg("Unknown variable name");
}

void VisitorIR::CodeGen(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration, Type * type){
	Value * V;
	
	printDebug("Inside ASTArrayFieldDeclaration");
	V = aSTArrayFieldDeclaration->getIdentifier()->GenCode(this, type);

	return V ? V : GenerateError::ErrorMsg("Unknown variable name");
}

BasicBlock * VisitorIR::currentBlock() { 
	return blocks.top()->block; 
}

void VisitorIR::pushBlock(BasicBlock *block) { 
	blocks.push(new CodeGenBlock()); blocks.top()->block = block;
}

void VisitorIR::popBlock() { 
	CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; 
}


std::map<std::string, Value*>& VisitorIR::locals() { 
	return blocks.top()->locals;
}

Value *VisitorIR::CodeGen(ASTField_Declaration* aSTField_Declaration){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug("Inside ASTField_Declaration");
	LangType * langType=aSTField_Declaration->getType();
	Type * type = langType->GenCode(this);
	
	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->GenCode(this, type);
	}

	return V;
}
