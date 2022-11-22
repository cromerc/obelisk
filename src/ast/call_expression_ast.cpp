#include "ast/ast.h"
#include "ast/call_expression_ast.h"
#include "ast/error.h"

llvm::Value *obelisk::CallExpressionAST::codegen()
{
    // Look up the name in the global module table.
    llvm::Function *calleeF = TheModule->getFunction(callee_);
    if (!calleeF)
    {
        return LogErrorV("Unknown function referenced");
    }

    // If argument mismatch error.
    if (calleeF->arg_size() != args_.size())
    {
        return LogErrorV("Incorrect # arguments passed");
    }

    std::vector<llvm::Value *> argsV;
    for (unsigned i = 0, e = args_.size(); i != e; ++i)
    {
        argsV.push_back(args_[i]->codegen());
        if (!argsV.back())
        {
            return nullptr;
        }
    }

    return Builder->CreateCall(calleeF, argsV, "calltmp");
}
