#include <bits/stdc++.h>
#include "AST.h"
using namespace std;

/*void ASTProgram::accept(Visitor* visitor){
	fprintf(XML_fp, "<program>\n");
}*/

void ASTnode::accept(){
	std::cout<<"Accepted ASTNode\n";
}

void ASTStatement::accept(){
	std::cout<<"Accepted ASTStatement\n";
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

ASTAssignmentStatement::ASTAssignmentStatement(ASTLocation loc, ASTExpression expr){
	this->loc_ = loc;
	this->expr_ = expr;	
}

ASTIntegerLiteralExpression::ASTIntegerLiteralExpression(int value){
	this->value_=value;
}

void ASTIntegerLiteralExpression::setValue(int value){
	this->value_=value;
}