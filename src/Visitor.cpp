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

void Visitor::visit(ASTField_Declaration* aSTField_Declaration){
	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->evaluate(this);
	}	
}

void Visitor::visit(ASTMethod_Declaration* aSTMethod_Declaration){	
	aSTMethod_Declaration->Block->evaluate(this);
}

/*void Visitor::CodeGen(ASTMethod_Declaration* aSTMethod_Declaration){
	Value * V;

	printDebug("Inside ASTMethod_Declaration");
	vector<Type*> argTypes;
	
	for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		Type * type = static_cast<Type *>((*it)->GenCode(this));
		argTypes.push_back(type);
	}

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
	
	aSTMethod_Declaration->to_return=function;
}*/

void Visitor::visit(ASTDeclarations* aSTDeclarations){
	Def *def=aSTDeclarations->getDef();
	def->evaluate(this);
}

void Visitor::visit(Def* def){
	fprintf(XML_fp, "<def>\n");
}

void Visitor::visit(ASTnode* aSTnode){
	fprintf(XML_fp, "<node>\n");

	aSTnode->evaluate(this);

	fprintf(XML_fp, "</node>\n");
}

void Visitor::visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<location>\n");

	fprintf(XML_fp, "</location>\n");
}

void Visitor::visit(ASTIdentifier* aSTIdentifier){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTIdentifier->getId().c_str());
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

void Visitor::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<location id=\"%s\" />\n", 
		aSTArrayFieldDeclaration->getId().c_str());
	fprintf(XML_fp, "<position>\n");
	fprintf(XML_fp, "<integer value=\"%d\" />\n", 
		aSTArrayFieldDeclaration->getExpression());
	fprintf(XML_fp, "</position>\n");
}

void Visitor::visit(CalloutStatement* calloutStatement){
	fprintf(XML_fp, "<callout function=%s>\n", calloutStatement->name.c_str());
	
	for (list<Args *>::reverse_iterator it=calloutStatement->Argss->rbegin(); 
		it!=calloutStatement->Argss->rend(); ++it){
		(*it)->evaluate(this);
	}
	
	fprintf(XML_fp, "</callout>\n");
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

void Visitor::visit(Args* Args){
	fprintf(XML_fp, "<Args>\n");
	fprintf(XML_fp, "</Args>\n");
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

void Visitor::visit(ExpressionRight* expressionRight){
	fprintf(XML_fp, "<expr>\n");
	
	expressionRight->evaluate(this);

	fprintf(XML_fp, "</expr>\n");
};

void Visitor::visit(Integer* integer){
	fprintf(XML_fp, "<integer value=\"%d\" />\n", integer->getValue());
};

void Visitor::visit(Bool* bool_obj){
	if (bool_obj->getValue())
		fprintf(XML_fp, "boolean value=\"true\"\n");
	else
		fprintf(XML_fp, "boolean value=\"false\"\n");
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

void Visitor::visit(Declaration * declaration){
	printDebug("Inside Declaration");
}
