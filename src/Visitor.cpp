#include <bits/stdc++.h>
#include "AST.h"
#include "Visitor.h"

using namespace std;

Visitor::~Visitor(){

}

void Visitor::visit(ASTProgram* aSTProgram){
	//aSTProgram->accept(this);
	fprintf(XML_fp, "<program>\n");
}