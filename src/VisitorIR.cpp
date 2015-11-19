#include <bits/stdc++.h>

#include "Visitor.h"
#include "AST.h"
#include "VisitorIR.h"

static IRBuilder<> Builder(getGlobalContext());
static bool in_field=true, is_debug=true, is_error=false;

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
	FunctionType *ftype = FunctionType::get(Type::getVoidTy(getGlobalContext()), argTypes, false);
	mainFunction = Function::Create(ftype, GlobalValue::InternalLinkage, "Class Program", this->module);
	BasicBlock *bblock = BasicBlock::Create(getGlobalContext(), "entry", mainFunction, 0);

	printDebug2("Inside Main Block");

	pushBlock(bblock);
	aSTProgram->evaluate(this);
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

void VisitorIR::visit(ASTProgram* aSTProgram){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug2("Inside ASTProgram ");	
	
	for (list<Declaration*>::reverse_iterator it=aSTProgram->Declarations->rbegin();
		it!=aSTProgram->Declarations->rend(); ++it){
		(*it)->evaluate(this);
	}

	aSTProgram->to_return=V;
	
}

void VisitorIR::visit(Args* args){

	string msg="Inside Args ";
	msg.append(args->getLiteral());

	printDebug2(msg);
	
	args->type=ConstantDataArray::getString(getGlobalContext(),
			"args", false)->getType();
		
}

void VisitorIR::visit(ASTMethod_Declaration* aSTMethod_Declaration){
	Value * V;

	//TODO: Add Callout Arguements from AST Class.
	printDebug2("Inside ASTMethod_Declaration");

	aSTMethod_Declaration->Block->evaluate(this);

	vector<Type*> argTypes;
	
	/*for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		Type * type = static_cast<Type *>((*it)->evaluate(this));
		argTypes.push_back(type);
	}*/

	LangType* langType = aSTMethod_Declaration->getLangType();
	langType->evaluate(this);
	Type * type = langType->type;
	
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
			static_cast<Type *>((*it)->evaluate(this)), 
			(*it)->getLiteral(), 
			this->currentBlock());
	    this->locals()[(*it)->getLiteral()] = alloc;

		//(*it)->evaluate(this);
	}*/
	
	this->popBlock();
	
	aSTMethod_Declaration->to_return=function;

};
	
void VisitorIR::visit(ASTMF_Declaration * aSTMF_Declaration){
	printDebug2("Inside ASTMF_Declaration");

	aSTMF_Declaration->to_return=ConstantInt::get(getGlobalContext(), APInt(32,0));
}

void VisitorIR::visit(ASTIdentifier* aSTIdentifier){
	
	string msg="Inside ASTIdentifier ";
	msg.append(aSTIdentifier->getId());
	printDebug2(msg);
	
	if (in_field){
		AllocaInst *alloc = new AllocaInst(aSTIdentifier->type, aSTIdentifier->getId(), this->currentBlock());
    	aSTIdentifier->Def::to_return=this->locals()[aSTIdentifier->getId()]=alloc;
    	return;
	}

	string msg="Inside ASTIdentifier ";
	msg.append(aSTIdentifier->getId());
	printDebug2(msg);
	
	if (this->locals().find(aSTIdentifier->getId()) == this->locals().end()){
		is_error=true;
		aSTIdentifier->Def::to_return=GenerateError::ErrorMsg("Unknown variable name");
	}
	aSTIdentifier->Def::to_return=new LoadInst(this->locals()[aSTIdentifier->getId()], "", false, this->currentBlock());
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
}

void VisitorIR::visit(Expression* expr){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug2("Inside Expression");

	expr->to_return=V;
}

void VisitorIR::visit(Bool* bool_obj){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug2("Inside Bool");

	bool_obj->to_return=V;
}

void VisitorIR::visit(Integer* integer){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	string msg="Inside Integer ";
	msg.append(to_string(integer->getValue()));
	printDebug2(msg);

	integer->ExpressionRight::to_return=V;
}

void VisitorIR::visit(ASTnode* aSTnode){
	printDebug2("Inside ASTnode");

	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	//aSTnode->evaluate(this);
	aSTnode->to_return=V;
}

void VisitorIR::visit(ExpressionRight* expressionRight){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug2("Inside ExpressionRight");

	expressionRight->to_return=V;
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
		rBinaryExpr->to_return = CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_EQ, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, "<=")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULE, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, ">=")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGE, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, ">")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_ULT, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, "<")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_UGT, lhs, rhs, "", this->currentBlock());
	} else if (!strcmp(type, "!=")){
		rBinaryExpr->to_return =  CmpInst::Create(Instruction::ICmp, ICmpInst::ICMP_NE, lhs, rhs, "", this->currentBlock());
	}

	Value * V=NULL;

	if (lhs && rhs){
		V=BinaryOperator::Create(instr, lhs, rhs, "", this->currentBlock());
	}
	
	rBinaryExpr->to_return = V;
}

void VisitorIR::visit(ASTMain* aSTMain){

	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug2("Inside ASTMain");
	
	for(list<ASTField_Declaration*>::reverse_iterator it=aSTMain->FieldDeclarations_->rbegin(); 
		it!=aSTMain->FieldDeclarations_->rend(); ++it){
		(*it)->evaluate(this);
	}

	//in_field=false;

	printDebug2("Inside ASTStatements");

	for (list<ASTStatement*>::reverse_iterator it=aSTMain->statements->rbegin(); 
		it!=aSTMain->statements->rend(); ++it){
		(*it)->evaluate(this);
	}

	aSTMain->to_return=V;
}

void VisitorIR::visit(AssignmentStatement* assignmentStatement){
	

	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	ASTLocation * location = assignmentStatement->getLocation();
	
	string id=location->getId();
	
	location->evaluate(this);

	printDebug2("Inside AssignmentStatement");
	
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
		if (V!=NULL){
			V=new StoreInst(V, this->locals()[id], this->currentBlock());
		}
		
	}

	/*for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
	}*/

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
}

void VisitorIR::visit(ASTDeclarations* aSTDeclarations){
	printDebug2("Inside ASTDeclarations");
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	Def *def=aSTDeclarations->getDef();
	def->type=aSTDeclarations->type;
	def->evaluate(this);

	aSTDeclarations->to_return = aSTDeclarations->to_return?aSTDeclarations->to_return:V;
}

void VisitorIR::visit(ASTLocation* aSTLocation){
	printDebug2("Inside ASTLocation");

	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));	

	aSTLocation->ExpressionRight::to_return=V;
}


void VisitorIR::visit(ASTArrayIdentifier* aSTArrayIdentifier){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	std::list<Expression*>* exprs = aSTArrayIdentifier->getExpression();

	printDebug2("Inside ASTArrayIdentifier");
	AllocaInst *alloc = new AllocaInst(aSTArrayIdentifier->getType(), 
		aSTArrayIdentifier->getId(), this->currentBlock());
	V=this->locals()[aSTArrayIdentifier->getId()]=alloc;
	
	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);
		V=(*it)->to_return;
	}

	aSTArrayIdentifier->ASTLocation::ExpressionRight::to_return = V ? V : GenerateError::ErrorMsg("Unknown variable name");
}

void VisitorIR::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	Value * V;
	
	printDebug2("Inside ASTArrayFieldDeclaration");
	ASTIdentifier * aSTIdentifier=aSTArrayFieldDeclaration->getIdentifier();
	aSTIdentifier->type=aSTArrayFieldDeclaration->type;

	aSTIdentifier->evaluate(this);

	aSTArrayFieldDeclaration->to_return= aSTIdentifier->Def::to_return ? aSTIdentifier->Def::to_return : GenerateError::ErrorMsg("Unknown variable name");
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

void VisitorIR::visit(ASTField_Declaration* aSTField_Declaration){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	LangType *langType=aSTField_Declaration->getType();
	printDebug2("Inside ASTField_Declaration");
	langType->evaluate(this);
	aSTField_Declaration->type=langType;

	aSTField_Declaration->ASTExpression::to_return=V;
}

void VisitorIR::visit(Def* def){

}

void VisitorIR::visit(Declaration* declaration){
	printDebug2("Inside Declaration");
	ASTMF_Declaration * dec = declaration->getDeclaration();
	dec->evaluate(this);
	declaration->to_return=dec->to_return;
}
