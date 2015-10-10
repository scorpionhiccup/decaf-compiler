#include <bits/stdc++.h>
#include "Visitor.h"

using namespace std;

Visitor::~Visitor(){

}

void Visitor::visit(ASTProgram aSTProgram){
	//aSTProgram.accept(this);
	std::cout<<"Accepted aSTProgram again\n";
}