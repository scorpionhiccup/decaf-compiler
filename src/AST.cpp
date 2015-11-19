#include <bits/stdc++.h>

#include "AST.h"
#include "Visitor.h"
#include <llvm/ExecutionEngine/GenericValue.h>

using namespace std;
using namespace llvm;

void ASTProgram::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void ASTProgram::GenCode(Visitor* visitor){
	visitor->CodeGen(this);
}

void ASTnode::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void ASTnode::GenCode(Visitor* visitor){
	visitor->CodeGen(this);
}

void ASTStatement::evaluate(Visitor* visitor){
	visitor->visit(this);
	std::cout<<"Accepted ASTStatement\n";
}

void ASTStatement::GenCode(Visitor* visitor){
	visitor->CodeGen(this);
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

void ASTMain::GenCode(Visitor* visitor){
	visitor->CodeGen(this);
}

void ASTField_Declaration::evaluate(Visitor* visitor){
	visitor->visit(this);
};


void ASTField_Declaration::GenCode(Visitor* visitor){
	visitor->CodeGen(this);
};

void ASTDeclarations::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void ASTDeclarations::GenCode(Visitor* visitor, Type * type){
	visitor->CodeGen(this, type);	
};

void ASTIdentifier::evaluate(Visitor* visitor){
	visitor->visit(this);
};

void ASTIdentifier::GenCode(Visitor* visitor, Type *type){
	visitor->CodeGen(this, type);
};

void ASTArrayIdentifier::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void ASTArrayIdentifier::GenCode(Visitor* visitor, Type *type){
	visitor->CodeGen(this, type);	
};

void CalloutStatement::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void CalloutStatement::GenCode(Visitor* visitor){
	visitor->CodeGen(this);	
};

void AssignmentStatement::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void AssignmentStatement::GenCode(Visitor* visitor){
	visitor->CodeGen(this);	
};

void Args::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void ExpressionRight::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void ExpressionRight::GenCode(Visitor* visitor){
	visitor->CodeGen(this);	
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

void ASTExpression::GenCode(Visitor* visitor){
	visitor->CodeGen(this);		
};

void RUnaryExpr::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void RUnaryExpr::GenCode(Visitor* visitor){
	visitor->CodeGen(this);
}

void RBinaryExpr::GenCode(Visitor* visitor){
	visitor->CodeGen(this);
}

void RBinaryExpr::evaluate(Visitor* visitor){
	visitor->visit(this);
}

void Integer::GenCode(Visitor* visitor){
	visitor->CodeGen(this);	
}

void Integer::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void Bool::GenCode(Visitor* visitor){
	visitor->CodeGen(this);	
}

void Bool::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void Expression::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void Expression::GenCode(Visitor* visitor, Type * type){
	visitor->CodeGen(this, type);	
}

void BinaryExpr::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void BinaryExpr::GenCode(Visitor* visitor, Type * type){
	visitor->CodeGen(this, type);	
}

void Def::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void Def::GenCode(Visitor* visitor, Type * type){
	visitor->CodeGen(this, type);	
}

void ASTLocation::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void ASTLocation::GenCode(Visitor* visitor, Type * type){
	visitor->CodeGen(this);	
}

void ASTArrayFieldDeclaration::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void ASTArrayFieldDeclaration::GenCode(Visitor* visitor, Type * type){
	visitor->CodeGen(this, type);
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

void ASTMethod_Declaration::GenCode(Visitor * visitor){
	visitor->CodeGen(this);
}

void Declaration::evaluate(Visitor* visitor){
	 visitor->visit(this);
}

void ASTMF_Declaration::evaluate(Visitor * visitor){
	visitor->visit(this);
}

void ASTMF_Declaration::GenCode(Visitor * visitor){
	visitor->CodeGen(this);
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