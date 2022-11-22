#include "ast/ast.h"
#include "ast/number_expression_ast.h"

llvm::Value *obelisk::NumberExpressionAST::codegen()
{
    return llvm::ConstantFP::get(*TheContext, llvm::APFloat(number_));
}
