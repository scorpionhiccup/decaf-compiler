#include <bits/stdc++.h>

#include "Visitor.h"
#include "AST.h"

using namespace std;

static IRBuilder<> Builder(getGlobalContext());
static bool in_field=true, is_debug=true, is_error=false;

extern FILE* LLVM_fp;
extern int version;

Visitor::~Visitor(){

}

static void printLevel(int depth){
    for(int i=0;i<depth-1;i++){
        cout<<'\t';
   	}
}

void printDebug(string str){
	if (version==0){
		cout<<str<<"\n";
		fprintf( LLVM_fp, "%s\n", str.c_str());
	}
}

class GenerateError{
public:
	static Value* ErrorMsg(string str) { 
		cout<<"Error: "<<str<<endl;
		return 0;
	}
};

void Visitor::visit(ASTProgram* aSTProgram){
	fprintf(XML_fp, "<program>\n");
	fprintf(XML_fp, "<declarations count=\"%lu\">\n", (aSTProgram->Declarations)->size());

	for (list<Declaration*>::reverse_iterator it=aSTProgram->Declarations->rbegin(); 
		it!=aSTProgram->Declarations->rend(); ++it){
		(*it)->evaluate(this);
	}

	fprintf(XML_fp, "</field_declarations>\n");

	fprintf(XML_fp, "</program>\n");
}


void Visitor::CodeGen(ASTProgram* aSTProgram){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	ASTMain* aSTMain=aSTProgram->getMain();
	printDebug("Inside ASTProgram");
	aSTMain->GenCode(this);
	
	aSTMain->to_return=V;
}

void Visitor::visit(ASTMain* aSTMain){

	fprintf(XML_fp, "<field_declarations count=\"%lu\">\n", (*aSTMain->FieldDeclarations_).size());

	for (list<ASTField_Declaration*>::reverse_iterator it=aSTMain->FieldDeclarations_->rbegin(); 
		it!=aSTMain->FieldDeclarations_->rend(); ++it){
		(*it)->evaluate(this);
	}

	fprintf(XML_fp, "</field_declarations>\n");

	fprintf(XML_fp, "<statement_declarations count=\"%lu\">\n", (*aSTMain->statements).size());

	for (list<ASTStatement*>::reverse_iterator it=aSTMain->statements->rbegin(); 
		it!=aSTMain->statements->rend(); ++it){
		(*it)->evaluate(this);
	}
	
	fprintf(XML_fp, "</statement_declarations>\n");
}

void Visitor::CodeGen(ASTMain* aSTMain){
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

	aSTMain->to_return=V;
}


void Visitor::visit(ASTField_Declaration* aSTField_Declaration){
	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->evaluate(this);
	}	
}

void Visitor::visit(ASTMethod_Declaration* aSTMethod_Declaration){	
	aSTMethod_Declaration->Block->evaluate(this);
}

void Visitor::CodeGen(ASTMethod_Declaration* aSTMethod_Declaration){
	Value * V;

	printDebug("Inside ASTMethod_Declaration");
	vector<Type*> argTypes;
	
	/*for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		Type * type = static_cast<Type *>((*it)->GenCode(this));
		argTypes.push_back(type);
	}*/

	LangType* langType = aSTMethod_Declaration->getLangType();
	langType->GenCode(this);
	Type * type=langType->type;
	
	FunctionType *ftype = FunctionType::get(
		type, argTypes, false);

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
	
	aSTMethod_Declaration->to_return=function;
}


void Visitor::CodeGen(ASTField_Declaration* aSTField_Declaration){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug("Inside ASTField_Declaration");
	LangType * langType=aSTField_Declaration->getType();
	langType->GenCode(this);
	Type * type = langType->type;

	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->GenCode(this, type);

	}

	//CHECK

	aSTField_Declaration->ASTExpression::to_return=V;
}


void Visitor::visit(ASTDeclarations* aSTDeclarations){
	Def *def=aSTDeclarations->getDef();
	def->evaluate(this);
}

void Visitor::CodeGen(ASTDeclarations* aSTDeclarations, Type * type){
	printDebug("Inside ASTDeclarations");
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	Def *def=aSTDeclarations->getDef();
	def->GenCode(this, type);

	aSTDeclarations->to_return = aSTDeclarations->to_return?aSTDeclarations->to_return:V;
}

void Visitor::visit(Def* def){
	fprintf(XML_fp, "<def>\n");
}

void Visitor::visit(ASTnode* aSTnode){
	fprintf(XML_fp, "<node>\n");

	aSTnode->evaluate(this);

	fprintf(XML_fp, "</node>\n");
}


void Visitor::CodeGen(ASTnode* aSTnode){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	aSTnode->GenCode(this);

	aSTnode->to_return=V;
}

void Visitor::visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<location>\n");

	fprintf(XML_fp, "</location>\n");
}

void Visitor::CodeGen(ASTLocation* aSTLocation){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside ASTLocation");

	aSTLocation->ExpressionRight::to_return=V;
}

void Visitor::visit(ASTIdentifier* aSTIdentifier){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTIdentifier->getId().c_str());
}

void Visitor::CodeGen(ASTIdentifier* aSTIdentifier, Type * type){
	if (in_field){
		Value *v;
		AllocaInst *alloc = new AllocaInst(type, aSTIdentifier->getId(), this->currentBlock());
		v=this->locals()[aSTIdentifier->getId()]=alloc;
    	aSTIdentifier->Def::to_return=v;
	}

	string msg="Inside ASTIdentifier ";
	msg.append(aSTIdentifier->getId());
	printDebug(msg);
	
	if (this->locals().find(aSTIdentifier->getId()) == this->locals().end()){
		is_error=true;
		aSTIdentifier->Def::to_return=GenerateError::ErrorMsg("Unknown variable name");
	}
	
	aSTIdentifier->Def::to_return=new LoadInst(this->locals()[aSTIdentifier->getId()], "", false, this->currentBlock());
}

void Visitor::visit(ASTArrayIdentifier* aSTArrayIdentifier){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTArrayIdentifier->getId().c_str());
	fprintf(XML_fp, "<position>\n");

	std::list<Expression*>* exprs = aSTArrayIdentifier->getExpression();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);
	}

	fprintf(XML_fp, "</position>\n");
}

void Visitor::CodeGen(ASTArrayIdentifier* aSTArrayIdentifier, Type* type){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	std::list<Expression*>* exprs = aSTArrayIdentifier->getExpression();

	printDebug("Inside ASTArrayIdentifier");
	AllocaInst *alloc = new AllocaInst(type, 
		aSTArrayIdentifier->getId(), this->currentBlock());
	V=this->locals()[aSTArrayIdentifier->getId()]=alloc;
	
	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this, type);
		V=(*it)->to_return;
	}

	//aSTArrayIdentifier->to_return = V ? V : GenerateError::ErrorMsg("Unknown variable name");
	aSTArrayIdentifier->ASTLocation::ExpressionRight::to_return = V ? V : GenerateError::ErrorMsg("Unknown variable name");
}

void Visitor::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<location id=\"%s\" />\n", 
		aSTArrayFieldDeclaration->getId().c_str());
	fprintf(XML_fp, "<position>\n");
	fprintf(XML_fp, "<integer value=\"%d\" />\n", 
		aSTArrayFieldDeclaration->getExpression());
	fprintf(XML_fp, "</position>\n");
}

void Visitor::CodeGen(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration, Type * type){
	Value * V;
	
	printDebug("Inside ASTArrayFieldDeclaration");
	
	ASTIdentifier * aSTIdentifier=aSTArrayFieldDeclaration->getIdentifier();
	aSTIdentifier->GenCode(this, type);

	if(aSTIdentifier->Def::to_return){
		aSTArrayFieldDeclaration->to_return=aSTIdentifier->Def::to_return;
	}else{
		aSTIdentifier->Def::to_return = GenerateError::ErrorMsg("Unknown variable name");
	}

}

void Visitor::visit(CalloutStatement* calloutStatement){
	fprintf(XML_fp, "<callout function=%s>\n", calloutStatement->name.c_str());
	
	for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		(*it)->evaluate(this);
	}
	
	fprintf(XML_fp, "</callout>\n");
}

void Visitor::CodeGen(CalloutStatement* calloutStatement){
	printDebug("Inside CalloutStatement");
	
	Value * V;

	vector<Type*> argTypes;
	LangType* langType;

	for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		(*it)->GenCode(this);
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
		(*it)->GenCode(this);
		AllocaInst *alloc = new AllocaInst(
			(*it)->type, 
			(*it)->getLiteral(), 
			this->currentBlock());
	    this->locals()[(*it)->getLiteral()] = alloc;

		//(*it)->GenCode(this);
	}
	
	this->popBlock();
	
	calloutStatement->to_return=function;
}

void Visitor::visit(AssignmentStatement* assignmentStatement){
	fprintf(XML_fp, "<assignment>\n");

	ASTLocation * location = assignmentStatement->getLocation();
	location->evaluate(this);

	for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
		(*it)->evaluate(this);
	}

	fprintf(XML_fp, "</assignment>\n");
}

void Visitor::CodeGen(AssignmentStatement* assignmentStatement){
	
	printDebug("Inside AssignmentStatement");

	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	ASTLocation * location = assignmentStatement->getLocation();
	string id=location->getId();
	location->GenCode(this, NULL);
	
	if (this->locals().find(id) == this->locals().end()){
		string error_str="Undeclared Variable in assignment statement: ";
		cerr<<error_str<<id<<"\n";
		is_error=1;
		assignmentStatement->to_return=NULL;
		return;
	}

	for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
		(*it)->GenCode(this);
		V=(*it)->to_return;
		if (V!=NULL){
			V=new StoreInst(V, this->locals()[id], this->currentBlock());
		}
	}

	assignmentStatement->to_return=V;
}

void Visitor::visit(Args* Args){
	fprintf(XML_fp, "<Args>\n");
	fprintf(XML_fp, "</Args>\n");
}

Type * Visitor::CodeGen(Args* args){
	
	string msg="Inside Args ";
	msg.append(args->getLiteral());

	printDebug(msg);
	
	return ConstantDataArray::getString(getGlobalContext(),
			"args",
			false)->getType();
		
}

void Visitor::visit(RUnaryExpr* rUnaryExpr){

	if (rUnaryExpr->getType()==1)
		fprintf(XML_fp, "<unary_expression type=\"-\"\n");
	else
		fprintf(XML_fp, "<unary_expression type=\"!\"\n");

	std::list<ExpressionRight*> * exprs = rUnaryExpr->getExpressions();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);

	}

	fprintf(XML_fp, "<unary_expression>\n");
}


void Visitor::CodeGen(RUnaryExpr* rUnaryExpr){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside RUnaryExpr");

	std::list<ExpressionRight*> * exprs = rUnaryExpr->getExpressions();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	//TODO: RUnaryExpr

	rUnaryExpr->to_return=V;
}

void Visitor::visit(RBinaryExpr* rBinaryExpr){
	fprintf(XML_fp, "<binary_expression type=\"%s\" >\n", rBinaryExpr->getType().c_str());

	std::list<ExpressionRight*>* exprs=rBinaryExpr->getLeftExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);

	}

	exprs=rBinaryExpr->getRightExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);

	}	

	fprintf(XML_fp, "</binary_expression>\n");
}

void Visitor::CodeGen(RBinaryExpr* rBinaryExpr){

	printDebug("Inside RBinaryExpr");
	Instruction::BinaryOps instr;

	Value * lhs=NULL, * rhs=NULL, *temp;

	std::list<ExpressionRight*>* exprs=rBinaryExpr->getLeftExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
		temp=(*it)->to_return;
		if (temp){
			lhs=temp;
		}
	}

	exprs=rBinaryExpr->getRightExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
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

void Visitor::visit(ExpressionRight* expressionRight){
	fprintf(XML_fp, "<expr>\n");
	
	expressionRight->evaluate(this);

	fprintf(XML_fp, "</expr>\n");
};

void Visitor::CodeGen(ExpressionRight* expressionRight){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug("Inside ExpressionRight");

	expressionRight->to_return=V;
}

void Visitor::visit(Integer* integer){
	fprintf(XML_fp, "<integer value=\"%d\" />\n", integer->getValue());
};

void Visitor::CodeGen(Integer* integer){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	string msg="Inside Integer ";
	msg.append(to_string(integer->getValue()));
	printDebug(msg);

	integer->ExpressionRight::to_return=V;
}

void Visitor::visit(Bool* bool_obj){
	if (bool_obj->getValue())
		fprintf(XML_fp, "boolean value=\"true\"\n");
	else
		fprintf(XML_fp, "boolean value=\"false\"\n");
}

void Visitor::CodeGen(Bool* bool_obj){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside Bool");

	bool_obj->to_return=V;
}


void Visitor::visit(CharLiteral* charLiteral){
	fprintf(XML_fp, "<character value=\'%s\'' />\n", charLiteral->getLiteral().c_str());
};

void Visitor::visit(StringLiteral* stringLiteral){
	fprintf(XML_fp, "<string value=%s />\n", stringLiteral->getLiteral().c_str());
};

void Visitor::visit(Expression* expr){
	fprintf(XML_fp, "<expr>\n");
	fprintf(XML_fp, "</expr>\n");
}

void Visitor::CodeGen(Expression* expr, Type * type){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside Expression");

	expr->to_return=V;
}

void Visitor::visit(BinaryExpr* expr){
	fprintf(XML_fp, "<binary_expression type=\"%s\" >\n", expr->getType().c_str());

	std::list<Expression*>* exprs=expr->getLeftExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);
	}

	exprs=expr->getRightExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);

	}	

	fprintf(XML_fp, "</binary_expression>\n");
}

void Visitor::CodeGen(BinaryExpr* expr, Type * type){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside BinaryExpr");

	std::list<Expression*>* exprs=expr->getLeftExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this, type);
		if ((*it)->to_return){
			V=(*it)->to_return;
		}
	}

	exprs=expr->getRightExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this, type);
		if ((*it)->to_return){
			V=(*it)->to_return;
		}
	}
	
	//TODO ADD OPERATIONS

	expr->to_return=V;
}

std::map<std::string, Value*>& Visitor::locals() { 
	return blocks.top()->locals;
}

BasicBlock * Visitor::currentBlock() { 
	return blocks.top()->block; 
}

void Visitor::pushBlock(BasicBlock *block) { 
	blocks.push(new CodeGenBlock()); blocks.top()->block = block;
}

void Visitor::popBlock() { 
	CodeGenBlock *top = blocks.top(); blocks.pop(); delete top; 
}

void Visitor::generateCode(ASTProgram *aSTProgram){
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

void Visitor::visit(Declaration * declaration){
	printDebug("Inside Declaration");
}

void Visitor::CodeGen(ASTMF_Declaration * aSTMF_Declaration){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	aSTMF_Declaration->to_return=V;
}