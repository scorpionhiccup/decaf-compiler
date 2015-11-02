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
	//aSTArrayIdentifier->getExpression()->accept(this);
	fprintf(XML_fp, "</position>\n");
}

void Visitor::visit(BaseFieldDeclaration* baseFieldDeclaration){
	fprintf(XML_fp, "<BaseFieldDeclaration>\n");
}

void Visitor::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<program>\n");
}

void Visitor::visit(Def* def){
	fprintf(XML_fp, "<def>\n");
}

void Visitor::visit(ASTDeclarations* aSTDeclarations){
	//Def *def=aSTDeclarations->getDef();
	//def->accept(this);
}

void Visitor::visit(CalloutStatement* calloutStatement){
	fprintf(XML_fp, "<callout function=\"%s\">\n", calloutStatement->name);

	
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
	//cout<<"HERE3\n";

	fprintf(XML_fp, "<field_declarations count=\"%lu\">\n", (*aSTMain->FieldBaseDeclaration_).size());

	for (list<ASTField_Declaration*>::reverse_iterator it=aSTMain->FieldBaseDeclaration_->rbegin(); 
		it!=aSTMain->FieldBaseDeclaration_->rend(); ++it){
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

void Visitor::visit(ExpressionRight* expressionRight){
	fprintf(XML_fp, "<expr>\n");
	fprintf(XML_fp, "</expr>\n");	
};