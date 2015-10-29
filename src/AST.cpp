#include <bits/stdc++.h>

#include "AST.h"
#include "Visitor.h"

using namespace std;

void ASTProgram::accept(Visitor* visitor){
	visitor->visit(this);
}

void ASTnode::accept(Visitor* visitor){
	visitor->visit(this);
	std::cout<<"Accepted ASTNode\n";
}

void ASTStatement::accept(){
	std::cout<<"Accepted ASTStatement\n";
}

std::string ASTProgram::getId(){
	return id_;
}

ASTIdentifier::ASTIdentifier(std::string id){
	this->id_=id;		
}
	
ASTProgram::ASTProgram(std::string id, ASTMain* aSTMain){
	this->id_=id;
	this->aSTMain=aSTMain;		
}

ASTBlockStatement::ASTBlockStatement(ASTStatement * stmtlist){
	this->stmtlist_ = stmtlist;
}


ASTIntegerLiteralExpression::ASTIntegerLiteralExpression(int value){
	this->value_=value;
}

void ASTIntegerLiteralExpression::setValue(int value){
	this->value_=value;
	
}