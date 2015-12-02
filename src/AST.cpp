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

string ASTLocation::getId(){
	return "";
};

string ASTIdentifier::getId(){
	return this->id_;
};

void ASTExpression::evaluate(Visitor* visitor){
	visitor->visit(this);		
};

void ASTParam_Declaration::evaluate(Visitor* visitor, bool go_into){
	cout<<"Inside ASTParam_Declaration\n";	
	visitor->visit(this, go_into);		
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
	cout<<"Inside Def\n";
	visitor->visit(this);	
}

void ASTLocation::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void ASTArrayFieldDeclaration::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void CharLiteral::evaluate(Visitor* visitor){
	cout<<"Inside CharLiteral\n";
	fflush(stdout);

	visitor->visit(this);	
}

void StringLiteral::evaluate(Visitor* visitor){
	cout<<"Inside StringLiteral\n";
	fflush(stdout);
	visitor->visit(this);	
}

void ASTMethod_Declaration::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void ASTDeclaration::evaluate(Visitor* visitor){
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
	visitor->visit(this);
}

void ListExpressionRight::evaluate(Visitor * visitor){
	visitor->visit(this);
}

void LangType::evaluate(Visitor * visitor){
	visitor->visit(this);
}

void ASTFor::evaluate(Visitor * visitor){
	visitor->visit(this);
}