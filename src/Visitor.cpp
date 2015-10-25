#include <bits/stdc++.h>
#include "Visitor.h"
#include "AST.h"

using namespace std;

Visitor::~Visitor(){

}

void Visitor::visit(ASTProgram* aSTProgram){
	//aSTProgram->accept(this);
	fprintf(XML_fp, "<program>\n");
}

void Visitor::visit(ASTnode* aSTnode){
	//aSTProgram->accept(this);
	fprintf(XML_fp, "<program>\n");
}
