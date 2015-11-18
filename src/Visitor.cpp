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
	
	ASTMain* aSTMain=aSTProgram->getMain();
	aSTMain->evaluate(this);

	fprintf(XML_fp, "</program>\n");
}


Value * Visitor::CodeGen(ASTProgram* aSTProgram){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	ASTMain* aSTMain=aSTProgram->getMain();
	printDebug("Inside ASTProgram");
	aSTMain->GenCode(this);
	
	return V;
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

Value * Visitor::CodeGen(ASTMain* aSTMain){
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


void Visitor::visit(ASTField_Declaration* aSTField_Declaration){
	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->evaluate(this);
	}
}

Value * Visitor::CodeGen(ASTField_Declaration* aSTField_Declaration){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug("Inside ASTField_Declaration");
	LangType * langType=aSTField_Declaration->getType();
	Type * type = langType->GenCode(this);
	
	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->GenCode(this, type);
	}

	return V;
}


void Visitor::visit(ASTDeclarations* aSTDeclarations){
	Def *def=aSTDeclarations->getDef();
	def->evaluate(this);
}

Value * Visitor::CodeGen(ASTDeclarations* aSTDeclarations, Type * type){
	printDebug("Inside ASTDeclarations");
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	Def *def=aSTDeclarations->getDef();
	V=def->GenCode(this, type);
	return V;
}

void Visitor::visit(Def* def){
	fprintf(XML_fp, "<def>\n");
}

void Visitor::visit(ASTnode* aSTnode){
	fprintf(XML_fp, "<node>\n");

	aSTnode->evaluate(this);

	fprintf(XML_fp, "</node>\n");
}


Value * Visitor::CodeGen(ASTnode* aSTnode){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	aSTnode->GenCode(this);

	return V;
}

void Visitor::visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<location>\n");

	fprintf(XML_fp, "</location>\n");
}

Value * Visitor::CodeGen(ASTLocation* aSTLocation){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside ASTLocation");

	return V;
}

void Visitor::visit(ASTIdentifier* aSTIdentifier){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTIdentifier->getId().c_str());
}

Value * Visitor::CodeGen(ASTIdentifier* aSTIdentifier, Type * type){
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

Value * Visitor::CodeGen(ASTArrayIdentifier* aSTArrayIdentifier, Type* type){
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

void Visitor::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<location id=\"%s\" />\n", 
		aSTArrayFieldDeclaration->getId().c_str());
	fprintf(XML_fp, "<position>\n");
	fprintf(XML_fp, "<integer value=\"%d\" />\n", 
		aSTArrayFieldDeclaration->getExpression());
	fprintf(XML_fp, "</position>\n");
}

Value * Visitor::CodeGen(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration, Type * type){
	Value * V;
	
	printDebug("Inside ASTArrayFieldDeclaration");
	V = aSTArrayFieldDeclaration->getIdentifier()->GenCode(this, type);

	return V ? V : GenerateError::ErrorMsg("Unknown variable name");
}

void Visitor::visit(CalloutStatement* calloutStatement){
	fprintf(XML_fp, "<callout function=%s>\n", calloutStatement->name.c_str());
	
	for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		(*it)->evaluate(this);
	}
	
	fprintf(XML_fp, "</callout>\n");
}

Value * Visitor::CodeGen(CalloutStatement* calloutStatement){
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

Value * Visitor::CodeGen(AssignmentStatement* assignmentStatement){
	
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


Value * Visitor::CodeGen(RUnaryExpr* rUnaryExpr){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside RUnaryExpr");

	std::list<ExpressionRight*> * exprs = rUnaryExpr->getExpressions();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	return V;
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

Value * Visitor::CodeGen(RBinaryExpr* rBinaryExpr){

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

void Visitor::visit(ExpressionRight* expressionRight){
	fprintf(XML_fp, "<expr>\n");
	
	expressionRight->evaluate(this);

	fprintf(XML_fp, "</expr>\n");
};

Value * Visitor::CodeGen(ExpressionRight* expressionRight){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	printDebug("Inside ExpressionRight");

	return V;
}

void Visitor::visit(Integer* integer){
	fprintf(XML_fp, "<integer value=\"%d\" />\n", integer->getValue());
};

Value * Visitor::CodeGen(Integer* integer){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	string msg="Inside Integer ";
	msg.append(to_string(integer->getValue()));
	printDebug(msg);

	return V;
}

void Visitor::visit(Bool* bool_obj){
	if (bool_obj->getValue())
		fprintf(XML_fp, "boolean value=\"true\"\n");
	else
		fprintf(XML_fp, "boolean value=\"false\"\n");
}

Value * Visitor::CodeGen(Bool* bool_obj){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside Bool");

	return V;
}


void Visitor::visit(CharLiteral* charLiteral){
	fprintf(XML_fp, "<character value=\'%s\'' />\n", charLiteral->getLiteral().c_str());
};

/*Value * Visitor::CodeGen(CharLiteral* charLiteral){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside CharLiteral");

	return V;
}*/


void Visitor::visit(StringLiteral* stringLiteral){
	fprintf(XML_fp, "<string value=%s />\n", stringLiteral->getLiteral().c_str());
};

/*Value * Visitor::CodeGen(StringLiteral* stringLiteral){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside StringLiteral");

	return V;
}*/

void Visitor::visit(Expression* expr){
	fprintf(XML_fp, "<expr>\n");
	fprintf(XML_fp, "</expr>\n");
}

Value * Visitor::CodeGen(Expression* expr, Type * type){
	Value * V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	printDebug("Inside Expression");

	return V;
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

Value * Visitor::CodeGen(BinaryExpr* expr, Type * type){
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

/*Value * Visitor::CodeGen(ReturnStmt * returnStmt){
	return ReturnInst::Create(getGlobalContext(), this->currentBlock());
}

Value * Visitor::CodeGen(ForStmt * ForStmt){

}

Value * Visitor::CodeGen(Block * block){
	
	list<Method_Declarations *> MethodList=block->MethodList;

	for (list<Expression*>::reverse_iterator it=MethodList->rbegin();
		it!=MethodList->rend(); ++it){
		(*it)->GenCode(this);
	}

	list<Statement_Declarations *> StatementList=block->StatementList;

	for (list<Expression*>::reverse_iterator it=StatementList->rbegin();
		it!=StatementList->rend(); ++it){
		(*it)->GenCode(this);
	}
}

Value * Visitor::CodeGen(IfElseStmt * ifElseStmt){
	Value * condition = ifElseStmt->Expr->codeGen(this);
	if (condition){

		condition = Builder.CreateFCmpONE(condition, 
			ConstantFP::get(getGlobalContext(),APFloat(0.0)), 
			"ifcond");

		Function *TheFunction = Builder.GetInsertBlock()->getParent();

		BasicBlock *IfBB = BasicBlock::Create(getGlobalContext(), "if", 
			TheFunction);
		BasicBlock *ElseBB = BasicBlock::Create(getGlobalContext(), "else");
		BasicBlock *MergeBB = BasicBlock::Create(getGlobalContext(), "ifcont");

		Builder.CreateCondBr(condition, IfBB, ElseBB);
		Builder.SetInsertPoint(IfBB);
		//cout<<"Statement number: "<<bloc1_->stat_->size()<<endl;
		Value *IfV = ifElseStmt->ifBlock->codeGen(context);
		Builder.CreateBr(MergeBB);
		IfBB = Builder.GetInsertBlock();

		TheFunction->getBasicBlockList().push_back(ElseBB);
		Builder.SetInsertPoint(ElseBB);
		Value *ElseV = ifElseStmt->elseBlock->codeGen(context);
		if(!ElseV) return NULL;

		Builder.CreateBr(MergeBB);
		ElseBB = Builder.GetInsertBlock();
		TheFunction->getBasicBlockList().push_back(MergeBB);
		Builder.SetInsertPoint(MergeBB);

		return NULL;
	}
	return condition;
}*/