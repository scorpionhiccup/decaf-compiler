#include <bits/stdc++.h>

#include "AST.h"
#include "Visitor.h"

using namespace std;

void ASTProgram::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void ASTnode::evaluate(Visitor* visitor){
	//std::cout<<"Accepted ASTNode\n";
	//fflush(stdout);
	visitor->visit(this);
}

void ASTStatement::evaluate(Visitor* visitor){
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

void ASTMain::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void ASTField_Declaration::evaluate(Visitor* visitor){
	visitor->visit(this);
};

void ASTDeclarations::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void ASTIdentifier::evaluate(Visitor* visitor){
	visitor->visit(this);
};

void ASTArrayIdentifier::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void CalloutStatement::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void AssignmentStatement::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void Args::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void ExpressionRight::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

string ASTIdentifier::getId(){
	return this->id_;
};

void ASTExpression::evaluate(Visitor* visitor){
	visitor->visit(this);		
};

void RUnaryExpr::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void RBinaryExpr::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void Integer::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void Bool::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void Expression::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void BinaryExpr::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void Def::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void ASTLocation::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void ASTArrayFieldDeclaration::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void CharLiteral::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void StringLiteral::evaluate(Visitor* visitor){
	visitor->visit(this);	
}