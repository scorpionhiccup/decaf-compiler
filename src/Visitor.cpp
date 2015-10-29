#include <bits/stdc++.h>
#include "Visitor.h"
#include "AST.h"

using namespace std;

Visitor::~Visitor(){

}

void Visitor::visit(ASTProgram* aSTProgram){
	//aSTProgram->accept(this);
	fprintf(XML_fp, "<program1>\n");
	aSTProgram->ASTMain->accept(this);
	fprintf(XML_fp, "</program1>\n");
}

void Visitor::visit(ASTnode* aSTnode){
	//aSTProgram->accept(this);
	fprintf(XML_fp, "<program>\n");
}

void visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<location>\n");
}

void visit(BaseDeclaration* baseDeclaration){
	fprintf(XML_fp, "<BaseDeclaration>\n");}
void visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<ASTLocation>\n");}
void visit(ASTIdentifier* aSTIdentifier){
	fprintf(XML_fp, "<ASTIdentifier>\n");}
void visit(ASTArrayIdentifier* aSTArrayIdentifier){
	fprintf(XML_fp, "<ASTArrayIdentifier>\n");}
void visit(BaseFieldDeclaration* baseFieldDeclaration){
	fprintf(XML_fp, "<BaseFieldDeclaration>\n");}
void visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<program>\n");}
void visit(Def* def){fprintf(XML_fp, "<program>\n");}
void visit(ASTDeclarations* aSTDeclarations){fprintf(XML_fp, "<program>\n");}
void visit(CalloutStatement* calloutStatement){fprintf(XML_fp, "<program>\n");}
void visit(AssignmentStatement* assignmentStatement){fprintf(XML_fp, "<program>\n");}
void visit(ASTMain* aSTMain){
	fprintf(XML_fp, "<main>\n");	
	for (list<ASTField_Declaration*>::iterator it=aSTProgram->FieldBaseDeclaration_; it!=aSTProgram->FieldBaseDeclaration_.begin(); ++it){
		aSTMain->accept()
	}

	fprintf(XML_fp, "</main>\n");
}
