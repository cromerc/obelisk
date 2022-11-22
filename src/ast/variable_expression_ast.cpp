#include "ast/ast.h"
#include "ast/error.h"
#include "ast/variable_expression_ast.h"

llvm::Value *obelisk::VariableExpressionAST::codegen()
{
    llvm::Value *V = NamedValues[name_];
    if (!V)
    {
        return obelisk::LogErrorV("Unknown variable name");
    }
    return V;
}
