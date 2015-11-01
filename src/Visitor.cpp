#include <bits/stdc++.h>
#include "Visitor.h"
#include "AST.h"

using namespace std;

Visitor::~Visitor(){

}

void Visitor::visit(ASTProgram* aSTProgram){
	//aSTProgram->accept(this);
	fprintf(XML_fp, "<program>\n");
	aSTProgram->aSTMain->accept(this);

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

/*
	fprintf(XML_fp, "<node>\n");
	fprintf(XML_fp, "</node>\n");	
*/
}


void Visitor::visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<location>\n");

	fprintf(XML_fp, "<location>\n");
}

void Visitor::visit(BaseDeclaration* baseDeclaration){
	fprintf(XML_fp, "<BaseDeclaration>\n");
}

void Visitor::visit(ASTIdentifier* aSTIdentifier){
	fprintf(XML_fp, "<ASTIdentifier>\n");
}


void Visitor::visit(ASTArrayIdentifier* aSTArrayIdentifier){
	fprintf(XML_fp, "<ASTArrayIdentifier>\n");
}

void Visitor::visit(BaseFieldDeclaration* baseFieldDeclaration){
	fprintf(XML_fp, "<BaseFieldDeclaration>\n");
}

void Visitor::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<program>\n");
}

void Visitor::visit(Def* def){
	fprintf(XML_fp, "<program>\n");
}

void Visitor::visit(ASTDeclarations* aSTDeclarations){
	fprintf(XML_fp, "<node>\n");

	fprintf(XML_fp, "</node>\n");	
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
	fprintf(XML_fp, "<assignment>n");

	assignmentStatement->location->accept(this);

	for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
		(*it)->accept(this);
	}

	fprintf(XML_fp, "</assignment>n");	
}


void Visitor::visit(ASTMain* aSTMain){
	fprintf(XML_fp, "<field_declarations count=\"%lu\">\n", (*aSTMain->FieldBaseDeclaration_).size());

	for (list<ASTField_Declaration*>::iterator it=aSTMain->FieldBaseDeclaration_->begin(); 
		it!=aSTMain->FieldBaseDeclaration_->end(); ++it){

		(*it)->accept(this);
	}
	fprintf(XML_fp, "<field_declarations>\n");

	fprintf(XML_fp, "<statement_declarations count=\"%lu\">\n", (*aSTMain->statements).size());

	for (list<ASTStatement*>::iterator it=aSTMain->statements->begin(); 
		it!=aSTMain->statements->end(); ++it){
		(*it)->accept(this);
	}

	fprintf(XML_fp, "<statement_declarations>\n");

}
