#include <bits/stdc++.h>
#include "AST.h"
using namespace std;

void ASTProgram::visit(){
	fprintf(XML_fp, "<program>\n");
}

void ASTnode::visit(){
	std::cout<<"Visited ASTNode\n";
}

void ASTStatement::visit(){
	std::cout<<"Visited ASTStatement\n";
}

std::string ASTProgram::getId(){
	return id_;
}

ASTProgram::ASTProgram(std::string id){
	this->id_=id;
}
	
ASTBlockStatement::ASTBlockStatement(ASTStatement * stmtlist){
	this->stmtlist_ = stmtlist;
}
