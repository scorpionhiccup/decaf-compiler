#include <bits/stdc++.h>
#include "Visitor.h"
#include "AST.h"

using namespace std;

Visitor::~Visitor(){

}

void Visitor::visit(ASTProgram* aSTProgram){
	fprintf(XML_fp, "<program>\n");
	
	ASTMain* aSTMain=aSTProgram->getMain();

	aSTMain->accept(this);

	fprintf(XML_fp, "</program>\n");
}

void Visitor::visit(ASTnode* aSTnode){
	fprintf(XML_fp, "<node>\n");

	aSTnode->accept(this);

	fprintf(XML_fp, "</node>\n");
}

void Visitor::visit(ASTField_Declaration* aSTField_Declaration){
	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->accept(this);
	}	
}


void Visitor::visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<location>\n");

	fprintf(XML_fp, "</location>\n");
}

void Visitor::visit(BaseDeclaration* baseDeclaration){
	fprintf(XML_fp, "<BaseDeclaration>\n");
}

void Visitor::visit(ASTIdentifier* aSTIdentifier){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTIdentifier->getId().c_str());
}


void Visitor::visit(ASTArrayIdentifier* aSTArrayIdentifier){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTArrayIdentifier->getId().c_str());
	fprintf(XML_fp, "<position>\n");
	aSTArrayIdentifier->getExpression()->accept(this);
	fprintf(XML_fp, "</position>\n");
}

void Visitor::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTArrayFieldDeclaration->getId().c_str());
	fprintf(XML_fp, "<position>\n");
	fprintf(XML_fp, "<integer value=\"%d\" />\n", aSTArrayFieldDeclaration->getExpression());
	fprintf(XML_fp, "</position>\n");
}

void Visitor::visit(Def* def){
	//fprintf(XML_fp, "<def>\n");
}

void Visitor::visit(ASTDeclarations* aSTDeclarations){
	Def *def=aSTDeclarations->getDef();
	def->accept(this);
}

void Visitor::visit(CalloutStatement* calloutStatement){
	fprintf(XML_fp, "<callout function=\"%s\">\n", calloutStatement->name.c_str());
	

	for (list<Argument *>::iterator it=calloutStatement->args->begin(); 
		it!=calloutStatement->args->end(); ++it){
		(*it)->accept(this);
	}
	
	fprintf(XML_fp, "</callout>\n");
}

void Visitor::visit(AssignmentStatement* assignmentStatement){
	fprintf(XML_fp, "<assignment>\n");

	assignmentStatement->location->accept(this);

	for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
		(*it)->accept(this);
	}

	fprintf(XML_fp, "</assignment>\n");	
}


void Visitor::visit(ASTMain* aSTMain){

	fprintf(XML_fp, "<field_declarations count=\"%lu\">\n", (*aSTMain->FieldDeclarations_).size());

	for (list<ASTField_Declaration*>::reverse_iterator it=aSTMain->FieldDeclarations_->rbegin(); 
		it!=aSTMain->FieldDeclarations_->rend(); ++it){
		(*it)->accept(this);
	}

	fprintf(XML_fp, "</field_declarations>\n");

	fprintf(XML_fp, "<statement_declarations count=\"%lu\">\n", (*aSTMain->statements).size());

	for (list<ASTStatement*>::reverse_iterator it=aSTMain->statements->rbegin(); 
		it!=aSTMain->statements->rend(); ++it){
		(*it)->accept(this);
	}
	
	fprintf(XML_fp, "</statement_declarations>\n");
}


void Visitor::visit(Argument* argument){
	fprintf(XML_fp, "<argument>\n");	
	fprintf(XML_fp, "</argument>\n");		
}

void Visitor::visit(RUnaryExpr* rUnaryExpr){
	fprintf(XML_fp, "<unary_expression type=\"x\"\n");

	std::list<ExpressionRight*> * exprs = rUnaryExpr->getExpressions();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->accept(this);

	}
	fprintf(XML_fp, "<unary_expression>\n");		
}

void Visitor::visit(RBinaryExpr* rBinaryExpr){
	fprintf(XML_fp, "<binary_expression type=\"x\"\n");

	fprintf(XML_fp, "<binary_expression>\n");		
}

void Visitor::visit(ExpressionRight* expressionRight){
	fprintf(XML_fp, "<expr>\n");
	//expressionRight->accept(this);
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
	fprintf(XML_fp, "<expr2>\n");
	fprintf(XML_fp, "</expr>\n");
}

void Visitor::visit(BinaryExpr* expr){
	fprintf(XML_fp, "<expr2>\n");
	fprintf(XML_fp, "</expr>\n");	
}