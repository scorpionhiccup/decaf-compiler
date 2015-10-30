#include <bits/stdc++.h>
#include "Visitor.h"
#include "AST.h"

using namespace std;

Visitor::~Visitor(){

}

void Visitor::visit(ASTProgram* aSTProgram){
	//aSTProgram->accept(this);
	fprintf(XML_fp, "<program1>\n");
	aSTProgram->aSTMain->accept(this);
	fprintf(XML_fp, "</program1>\n");
}

void Visitor::visit(ASTnode* aSTnode){
	//aSTProgram->accept(this);
	fprintf(XML_fp, "<program>\n");
}

void Visitor::visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<ASTLocation>\n");
}

void Visitor::visit(BaseDeclaration* baseDeclaration){
	fprintf(XML_fp, "<BaseDeclaration>\n");}
void Visitor::visit(ASTIdentifier* aSTIdentifier){
	fprintf(XML_fp, "<ASTIdentifier>\n");}
void Visitor::visit(ASTArrayIdentifier* aSTArrayIdentifier){
	fprintf(XML_fp, "<ASTArrayIdentifier>\n");}
void Visitor::visit(BaseFieldDeclaration* baseFieldDeclaration){
	fprintf(XML_fp, "<BaseFieldDeclaration>\n");}
void Visitor::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<program>\n");}
void Visitor::visit(Def* def){fprintf(XML_fp, "<program>\n");}
void Visitor::visit(ASTDeclarations* aSTDeclarations){fprintf(XML_fp, "<program>\n");}
void Visitor::visit(CalloutStatement* calloutStatement){fprintf(XML_fp, "<program>\n");}
void Visitor::visit(AssignmentStatement* assignmentStatement){fprintf(XML_fp, "<program>\n");}
void Visitor::visit(ASTMain* aSTMain){
	fprintf(XML_fp, "<main>\n");	
	
	for (list<ASTField_Declaration*>::iterator it=aSTMain->FieldBaseDeclaration_->begin(); it!=aSTMain->FieldBaseDeclaration_->end(); ++it){
		aSTMain->accept(this);
	}

	fprintf(XML_fp, "</main>\n");
}
