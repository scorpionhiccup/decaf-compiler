#include <bits/stdc++.h>

#include "Visitor.h"
#include "AST.h"

using namespace std;

static IRBuilder<> Builder(getGlobalContext());

Visitor::~Visitor(){

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


Value *Visitor::CodeGen(ASTProgram* aSTProgram){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	ASTMain* aSTMain=aSTProgram->getMain();
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

Value *Visitor::CodeGen(ASTMain* aSTMain){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	for(list<ASTField_Declaration*>::reverse_iterator it=aSTMain->FieldDeclarations_->rbegin(); 
		it!=aSTMain->FieldDeclarations_->rend(); ++it){
		(*it)->GenCode(this);
	}

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

Value *Visitor::CodeGen(ASTField_Declaration* aSTField_Declaration){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->GenCode(this);
	}
	return V;
}


void Visitor::visit(ASTDeclarations* aSTDeclarations){
	Def *def=aSTDeclarations->getDef();
	def->evaluate(this);
}

Value *Visitor::CodeGen(ASTDeclarations* aSTDeclarations){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	Def *def=aSTDeclarations->getDef();
	def->GenCode(this);
	return V;
}

void Visitor::visit(Def* def){
	fprintf(XML_fp, "<def>\n");
}

Value *Visitor::CodeGen(Def* def){
	return ConstantInt::get(getGlobalContext(), APInt(32,0));
}

void Visitor::visit(ASTnode* aSTnode){
	fprintf(XML_fp, "<node>\n");

	aSTnode->evaluate(this);

	fprintf(XML_fp, "</node>\n");
}


Value *Visitor::CodeGen(ASTnode* aSTnode){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	aSTnode->GenCode(this);
	return V;
}

void Visitor::visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<location>\n");

	fprintf(XML_fp, "</location>\n");
}

Value *Visitor::CodeGen(ASTLocation* aSTLocation){
	//TODO
}

void Visitor::visit(ASTIdentifier* aSTIdentifier){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTIdentifier->getId().c_str());
}

Value *Visitor::CodeGen(ASTIdentifier* aSTIdentifier){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	return V ? V : GenerateError::ErrorMsg("Unknown variable name");
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

Value *Visitor::CodeGen(ASTArrayIdentifier* aSTArrayIdentifier){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	std::list<Expression*>* exprs = aSTArrayIdentifier->getExpression();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	return V ? V : GenerateError::ErrorMsg("Unknown variable name");
}

void Visitor::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTArrayFieldDeclaration->getId().c_str());
	fprintf(XML_fp, "<position>\n");
	fprintf(XML_fp, "<integer value=\"%d\" />\n", aSTArrayFieldDeclaration->getExpression());
	fprintf(XML_fp, "</position>\n");
}

Value *Visitor::CodeGen(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	return V ? V : GenerateError::ErrorMsg("Unknown variable name");
}

void Visitor::visit(CalloutStatement* calloutStatement){
	fprintf(XML_fp, "<callout function=%s>\n", calloutStatement->name.c_str());
	
	for (list<Args *>::iterator it=calloutStatement->Argss->begin(); it!=calloutStatement->Argss->end(); ++it){
		(*it)->evaluate(this);
	}
	
	fprintf(XML_fp, "</callout>\n");
}

Value *Visitor::CodeGen(CalloutStatement* calloutStatement){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	for (list<Args *>::iterator it=calloutStatement->Argss->begin(); it!=calloutStatement->Argss->end(); ++it){
		(*it)->GenCode(this);
	}

	return V;
}

void Visitor::visit(AssignmentStatement* assignmentStatement){
	fprintf(XML_fp, "<assignment>\n");

	assignmentStatement->location->evaluate(this);

	for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
		(*it)->evaluate(this);
	}

	fprintf(XML_fp, "</assignment>\n");
}

Value *Visitor::CodeGen(AssignmentStatement* assignmentStatement){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	assignmentStatement->location->GenCode(this);

	for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
		(*it)->GenCode(this);
	}
	return V;
}

void Visitor::visit(Args* Args){
	fprintf(XML_fp, "<Args>\n");
	fprintf(XML_fp, "</Args>\n");
}

Value *Visitor::CodeGen(Args* args){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	return V;
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


Value *Visitor::CodeGen(RUnaryExpr* rUnaryExpr){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

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

Value *Visitor::CodeGen(RBinaryExpr* rBinaryExpr){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	std::list<ExpressionRight*>* exprs=rBinaryExpr->getLeftExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);

	}

	exprs=rBinaryExpr->getRightExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	return V;
}

void Visitor::visit(ExpressionRight* expressionRight){
	fprintf(XML_fp, "<expr>\n");
	//expressionRight->evaluate(this);
	fprintf(XML_fp, "</expr>\n");
};

Value *Visitor::CodeGen(ExpressionRight* expressionRight){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	return V;
}

void Visitor::visit(Integer* integer){
	fprintf(XML_fp, "<integer value=\"%d\" />\n", integer->getValue());
};

Value *Visitor::CodeGen(Integer* integer){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));
	
	return V;
}

void Visitor::visit(Bool* bool_obj){
	if (bool_obj->getValue())
		fprintf(XML_fp, "boolean value=\"true\"\n");
	else
		fprintf(XML_fp, "boolean value=\"false\"\n");
}

Value *Visitor::CodeGen(Bool* bool_obj){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	return V;
}


void Visitor::visit(CharLiteral* charLiteral){
	fprintf(XML_fp, "<character value=\'%s\'' />\n", charLiteral->getLiteral().c_str());
};

Value *Visitor::CodeGen(CharLiteral* charLiteral){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	return V;
}


void Visitor::visit(StringLiteral* stringLiteral){
	fprintf(XML_fp, "<string value=%s />\n", stringLiteral->getLiteral().c_str());
};

Value *Visitor::CodeGen(StringLiteral* stringLiteral){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	return V;
}

void Visitor::visit(Expression* expr){
	fprintf(XML_fp, "<expr>\n");
	fprintf(XML_fp, "</expr>\n");
}

Value *Visitor::CodeGen(Expression* expr){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

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

Value *Visitor::CodeGen(BinaryExpr* expr){
	Value *V = ConstantInt::get(getGlobalContext(), APInt(32,0));

	std::list<Expression*>* exprs=expr->getLeftExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	exprs=expr->getRightExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);

	}
	
	return V;
}
