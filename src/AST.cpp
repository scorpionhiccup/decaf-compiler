#include <bits/stdc++.h>

#include "AST.h"
#include "Visitor.h"
#include <llvm/ExecutionEngine/GenericValue.h>

using namespace std;
using namespace llvm;

void ASTProgram::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void ASTnode::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void ASTStatement::evaluate(Visitor* visitor){
	visitor->visit(this);
}

std::string ASTProgram::getId(){
	return "";
}

ASTIdentifier::ASTIdentifier(std::string id){
	this->id_=id;		
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
	cout<<"HERE2\n";
	visitor->visit(this);
};

void ASTArrayIdentifier::evaluate(Visitor* visitor){
	cout<<"HERE3\n";
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

string ASTLocation::getId(){
	return "";
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
	cout<<"HERE\n";
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

void ASTMethod_Declaration::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void Declaration::evaluate(Visitor* visitor){
	 visitor->visit(this);
}

void ASTMF_Declaration::evaluate(Visitor * visitor){
	visitor->visit(this);
}

void BooleanType::evaluate(Visitor * visitor){
	visitor->visit(this);
}

void VoidType::evaluate(Visitor * visitor){
	visitor->visit(this);
}

void IntType::evaluate(Visitor * visitor){
	//cout<<"cht\n";
	visitor->visit(this);
}

void ListExpressionRight::evaluate(Visitor * visitor){
	visitor->visit(this);
}

void LangType::evaluate(Visitor * visitor){
	cout<<"Inside LangType\n";
	visitor->visit(this);
}
