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

Value * ASTStatement::GenCode(Visitor* visitor){
	visitor->CodeGen(this);
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

Value* ASTIdentifier::GenCode(Visitor* visitor, Type *type){
	return visitor->CodeGen(this, type);
};

void ASTArrayIdentifier::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

Value* ASTArrayIdentifier::GenCode(Visitor* visitor, Type *type){
	visitor->CodeGen(this, type);	
};

void CalloutStatement::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

Value * CalloutStatement::GenCode(Visitor* visitor){
	return visitor->CodeGen(this);	
};

void AssignmentStatement::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

Value * AssignmentStatement::GenCode(Visitor* visitor){
	return visitor->CodeGen(this);	
};

void Args::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void Args::GenCode(Visitor* visitor){
	visitor->CodeGen(this);	
};

void ExpressionRight::evaluate(Visitor* visitor){
	visitor->visit(this);	
};

void ExpressionRight::GenCode(Visitor* visitor){
	visitor->CodeGen(this);	
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
	visitor->visit(this);
}

void RBinaryExpr::evaluate(Visitor* visitor){
	visitor->CodeGen(this);
}

void Integer::GenCode(Visitor* visitor){
	visitor->visit(this);	
}

void Integer::evaluate(Visitor* visitor){
	visitor->CodeGen(this);	
}

void Bool::GenCode(Visitor* visitor){
	visitor->visit(this);	
}

void Bool::evaluate(Visitor* visitor){
	visitor->CodeGen(this);	
}

void Expression::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

Value * Expression::GenCode(Visitor* visitor, Type * type){
	visitor->CodeGen(this, type);	
}

void BinaryExpr::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

Value * BinaryExpr::GenCode(Visitor* visitor, Type * type){
	visitor->CodeGen(this, type);	
}

void Def::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

Value *Def::GenCode(Visitor* visitor, Type * type){
	return visitor->CodeGen(this, type);	
}

void ASTLocation::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

Value * ASTLocation::GenCode(Visitor* visitor){
	return visitor->CodeGen(this);	
}

void ASTArrayFieldDeclaration::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

Value *  ASTArrayFieldDeclaration::GenCode(Visitor* visitor, Type * type){
	return visitor->CodeGen(this, type);
}

void CharLiteral::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void CharLiteral::GenCode(Visitor* visitor){
	visitor->CodeGen(this);	
}

void StringLiteral::evaluate(Visitor* visitor){
	visitor->visit(this);	
}

void StringLiteral::GenCode(Visitor* visitor){
	visitor->CodeGen(this);	
}

Type * IntType::GenCode(Visitor* visitor){
	return visitor->CodeGen(this);
}

Type * BooleanType::GenCode(Visitor* visitor){
	return visitor->CodeGen(this);
}

Type * LangType::GenCode(Visitor* visitor){
	return visitor->CodeGen(this);
}