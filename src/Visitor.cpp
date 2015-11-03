#include <bits/stdc++.h>

#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/PassManager.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Analysis/Verifier.h"
#include "Visitor.h"
#include "AST.h"


using namespace std;
using namespace llvm;

/*static llvm::Module *TheModule = new llvm::Module("main", 
	llvm::getGlobalContext());;
static llvm::LLVMContext &Context = llvm::getGlobalContext();
static llvm::IRBuilder<> Builder(Context);
static std::map<std::string, llvm::AllocaInst * > NamedValues;
static llvm::FunctionPassManager *TheFPM;*/

Visitor::~Visitor(){

}

class GenerateError{
    public:
        static llvm::Value* ErrorMsg(string str) { 
            cout<<"Error: "<<str<<endl;
            return 0;
        }
};

void Visitor::visit(ASTProgram* aSTProgram){
	fprintf(XML_fp, "<program>\n");
	
	ASTMain* aSTMain=aSTProgram->getMain();

	aSTMain->evaluate(this);

	fprintf(XML_fp, "</program>\n");
}


/*llvm::Value* Visitor::CodeGen(ASTProgram* aSTProgram){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	ASTMain* aSTMain=aSTProgram->getMain();
	aSTMain->GenCode();
	return V;
}*/

void Visitor::visit(ASTMain* aSTMain){

	fprintf(XML_fp, "<field_declarations count=\"%lu\">\n", (*aSTMain->FieldDeclarations_).size());

	for (list<ASTField_Declaration*>::reverse_iterator it=aSTMain->FieldDeclarations_->rbegin(); 
		it!=aSTMain->FieldDeclarations_->rend(); ++it){
		(*it)->evaluate(this);
	}

	fprintf(XML_fp, "</field_declarations>\n");

	fprintf(XML_fp, "<statement_declarations count=\"%lu\">\n", (*aSTMain->statements).size());

	for (list<ASTStatement*>::reverse_iterator it=aSTMain->statements->rbegin(); 
		it!=aSTMain->statements->rend(); ++it){
		(*it)->evaluate(this);
	}
	
	fprintf(XML_fp, "</statement_declarations>\n");
}

/*llvm::Value* CodeGen(ASTMain* aSTMain){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	
	for(list<ASTField_Declaration*>::reverse_iterator it=aSTMain->FieldDeclarations_->rbegin(); 
		it!=aSTMain->FieldDeclarations_->rend(); ++it){
		(*it)->GenCode(this);
	}

	for (list<ASTStatement*>::reverse_iterator it=aSTMain->statements->rbegin(); 
		it!=aSTMain->statements->rend(); ++it){
		(*it)->GenCode(this);
	}
	return V;
}*/


void Visitor::visit(ASTField_Declaration* aSTField_Declaration){
	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->evaluate(this);
	}	
}

/*llvm::Value* CodeGen(ASTField_Declaration* aSTField_Declaration){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));

	for (list<ASTDeclarations*>::iterator it=aSTField_Declaration->Declarations->begin(); 
		it!=aSTField_Declaration->Declarations->end(); ++it){
			(*it)->GenCode(this);
	}
	return V;
}*/


void Visitor::visit(ASTDeclarations* aSTDeclarations){
	Def *def=aSTDeclarations->getDef();
	def->evaluate(this);
}

/*llvm::Value* CodeGen(ASTDeclarations* aSTDeclarations){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	Def *def=aSTDeclarations->getDef();
	def->GenCode(this);	
	return V;
}*/

void Visitor::visit(Def* def){
	fprintf(XML_fp, "<def>\n");
}

/*llvm::Value* CodeGen(Def* def){
	return llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
}*/

void Visitor::visit(ASTnode* aSTnode){
	fprintf(XML_fp, "<node>\n");

	aSTnode->evaluate(this);

	fprintf(XML_fp, "</node>\n");
}


/*llvm::Value* Visitor::CodeGen(ASTnode* aSTnode){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	ASTMain* aSTMain=aSTProgram->getMain();
	aSTMain->CodeGen();
	return V;
}*/

void Visitor::visit(ASTLocation* aSTLocation){
	fprintf(XML_fp, "<location>\n");

	fprintf(XML_fp, "</location>\n");
}


void Visitor::visit(ASTIdentifier* aSTIdentifier){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTIdentifier->getId().c_str());
}

/*llvm::Value* CodeGen(ASTIdentifier* aSTIdentifier){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	return V ? V : GenerateError::ErrorV("Unknown variable name");
}*/

void Visitor::visit(ASTArrayIdentifier* aSTArrayIdentifier){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTArrayIdentifier->getId().c_str());
	fprintf(XML_fp, "<position>\n");
	
	std::list<Expression*>* exprs = aSTArrayIdentifier->getExpression();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);
	}

	fprintf(XML_fp, "</position>\n");
}

/*llvm::Value* CodeGen(ASTIdentifier* aSTIdentifier){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	std::list<Expression*>* exprs = aSTArrayIdentifier->getExpression();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	return V ? V : GenerateError::ErrorV("Unknown variable name");
}*/

void Visitor::visit(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	fprintf(XML_fp, "<location id=\"%s\" />\n", aSTArrayFieldDeclaration->getId().c_str());
	fprintf(XML_fp, "<position>\n");
	fprintf(XML_fp, "<integer value=\"%d\" />\n", aSTArrayFieldDeclaration->getExpression());
	fprintf(XML_fp, "</position>\n");
}

/*llvm::Value* CodeGen(ASTArrayFieldDeclaration* aSTArrayFieldDeclaration){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	return V ? V : GenerateError::ErrorV("Unknown variable name");
}*/

void Visitor::visit(CalloutStatement* calloutStatement){
	fprintf(XML_fp, "<callout function=%s>\n", calloutStatement->name.c_str());
	
	for (list<Args *>::iterator it=calloutStatement->Argss->begin(); it!=calloutStatement->Argss->end(); ++it){
		(*it)->evaluate(this);
	}
	
	fprintf(XML_fp, "</callout>\n");
}

/*llvm::Value* CodeGen(CalloutStatement* calloutStatement){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	
	for (list<Args *>::iterator it=calloutStatement->Argss->begin(); it!=calloutStatement->Argss->end(); ++it){
		(*it)->GenCode(this);
	}

	return V;
}*/

void Visitor::visit(AssignmentStatement* assignmentStatement){
	fprintf(XML_fp, "<assignment>\n");

	assignmentStatement->location->evaluate(this);

	for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
		(*it)->evaluate(this);
	}

	fprintf(XML_fp, "</assignment>\n");	
}

/*llvm::Value* CodeGen(AssignmentStatement* assignmentStatement){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	assignmentStatement->location->GenCode(this);

	for (list<ExpressionRight*>::iterator it=assignmentStatement->expressionRight->begin();
		it!=assignmentStatement->expressionRight->end(); ++it){
		(*it)->GenCode(this);
	}
	return V;
}*/

void Visitor::visit(Args* Args){
	fprintf(XML_fp, "<Args>\n");	
	fprintf(XML_fp, "</Args>\n");		
}

/*llvm::Value* CodeGen(Args* args){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	return V;
}*/

void Visitor::visit(RUnaryExpr* rUnaryExpr){
	if (rUnaryExpr->getType()==1)
		fprintf(XML_fp, "<unary_expression type=\"-\"\n");
	else
		fprintf(XML_fp, "<unary_expression type=\"!\"\n");

	std::list<ExpressionRight*> * exprs = rUnaryExpr->getExpressions();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);

	}

	fprintf(XML_fp, "<unary_expression>\n");		
}


/*llvm::Value* CodeGen(RUnaryExpr* rUnaryExpr){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));

	std::list<ExpressionRight*> * exprs = rUnaryExpr->getExpressions();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	return V;	
}*/

void Visitor::visit(RBinaryExpr* rBinaryExpr){
	fprintf(XML_fp, "<binary_expression type=\"%s\" >\n", rBinaryExpr->getType().c_str());

	std::list<ExpressionRight*>* exprs=rBinaryExpr->getLeftExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);

	}

	exprs=rBinaryExpr->getRightExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);

	}	

	fprintf(XML_fp, "</binary_expression>\n");		
}

/*llvm::Value* CodeGen(RBinaryExpr* rBinaryExpr){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));

	std::list<ExpressionRight*>* exprs=rBinaryExpr->getLeftExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);

	}

	exprs=rBinaryExpr->getRightExprs();

	for (list<ExpressionRight*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	return V;
}*/

void Visitor::visit(ExpressionRight* expressionRight){
	fprintf(XML_fp, "<expr>\n");
	//expressionRight->evaluate(this);
	fprintf(XML_fp, "</expr>\n");	
};

/*llvm::Value* CodeGen(ExpressionRight* expressionRight){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));

	return V;	
}*/

void Visitor::visit(Integer* integer){
	fprintf(XML_fp, "<integer value=\"%d\" />\n", integer->getValue());
};

/*llvm::Value* CodeGen(Integer* integer){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));
	
	return V;	
}*/

void Visitor::visit(Bool* bool_obj){
	if (bool_obj->getValue())
		fprintf(XML_fp, "boolean value=\"true\"\n");
	else
		fprintf(XML_fp, "boolean value=\"false\"\n");
}

/*llvm::Value* CodeGen(Bool* bool_obj){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));

	return V;		
}*/


void Visitor::visit(CharLiteral* charLiteral){
	fprintf(XML_fp, "<character value=\'%s\'' />\n", charLiteral->getLiteral().c_str());
};

/*llvm::Value* CodeGen(CharLiteral* charLiteral){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));

	return V;		
}*/


void Visitor::visit(StringLiteral* stringLiteral){
	fprintf(XML_fp, "<string value=%s />\n", stringLiteral->getLiteral().c_str());
};

/*llvm::Value* CodeGen(StringLiteral* stringLiteral){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));

	return V;		
}*/

void Visitor::visit(Expression* expr){
	fprintf(XML_fp, "<expr>\n");
	fprintf(XML_fp, "</expr>\n");
}

/*llvm::Value* CodeGen(Expression* expr){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));

	return V;		
}*/

void Visitor::visit(BinaryExpr* expr){
	fprintf(XML_fp, "<binary_expression type=\"%s\" >\n", expr->getType().c_str());

	std::list<Expression*>* exprs=expr->getLeftExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);
	}

	exprs=expr->getRightExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->evaluate(this);

	}	

	fprintf(XML_fp, "</binary_expression>\n");		
}

/*llvm::Value* CodeGen(BinaryExpr* expr){
	llvm::Value *V = llvm::ConstantInt::get(llvm::getGlobalContext(), llvm::APInt(32,0));

	std::list<Expression*>* exprs=expr->getLeftExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);
	}

	exprs=expr->getRightExprs();

	for (list<Expression*>::reverse_iterator it=exprs->rbegin();
		it!=exprs->rend(); ++it){
		(*it)->GenCode(this);

	}	
	
	return V;		

}*/