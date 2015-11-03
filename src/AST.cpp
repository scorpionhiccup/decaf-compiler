#include <bits/stdc++.h>

#include "AST.h"
#include "Visitor.h"

using namespace std;

void ASTProgram::accept(Visitor* visitor){
	visitor->visit(this);
}

void ASTnode::accept(Visitor* visitor){
	//std::cout<<"Accepted ASTNode\n";
	//fflush(stdout);
	visitor->visit(this);
}

void ASTStatement::accept(Visitor* visitor){
	visitor->visit(this);
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

void ASTMain::accept(Visitor* visitor){
	visitor->visit(this);
}

void ASTField_Declaration::accept(Visitor* visitor){
	visitor->visit(this);
};

void ASTDeclarations::accept(Visitor* visitor){
	visitor->visit(this);	
};

void ASTIdentifier::accept(Visitor* visitor){
	visitor->visit(this);
};

void ASTArrayIdentifier::accept(Visitor* visitor){
	visitor->visit(this);	
};

void CalloutStatement::accept(Visitor* visitor){
	visitor->visit(this);	
};

void AssignmentStatement::accept(Visitor* visitor){
	visitor->visit(this);	
};

void Argument::accept(Visitor* visitor){
	visitor->visit(this);	
};

void ExpressionRight::accept(Visitor* visitor){
	visitor->visit(this);	
};

string ASTIdentifier::getId(){
	return this->id_;
};

void ASTExpression::accept(Visitor* visitor){
	visitor->visit(this);		
};

void RUnaryExpr::accept(Visitor* visitor){
	visitor->visit(this);
}

void RBinaryExpr::accept(Visitor* visitor){
	visitor->visit(this);
}

void Integer::accept(Visitor* visitor){
	visitor->visit(this);	
}

void Bool::accept(Visitor* visitor){
	visitor->visit(this);	
}

void Expression::accept(Visitor* visitor){
	visitor->visit(this);	
}

void BinaryExpr::accept(Visitor* visitor){
	visitor->visit(this);	
}

void Def::accept(Visitor* visitor){
	visitor->visit(this);	
}

void ASTLocation::accept(Visitor* visitor){
	visitor->visit(this);	
}

void ASTArrayFieldDeclaration::accept(Visitor* visitor){
	visitor->visit(this);	
}