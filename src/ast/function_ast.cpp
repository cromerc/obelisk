#include "ast/ast.h"
#include "ast/function_ast.h"

#include <llvm/IR/Verifier.h>

llvm::Function *obelisk::FunctionAST::codegen()
{
    llvm::Function *theFunction = TheModule->getFunction(prototype_->getName());

    if (!theFunction)
    {
        theFunction = prototype_->codegen();
    }

    if (!theFunction)
    {
        return nullptr;
    }

    llvm::BasicBlock *bB = llvm::BasicBlock::Create(*TheContext, "entry", theFunction);
    Builder->SetInsertPoint(bB);

    NamedValues.clear();
    for (auto &arg : theFunction->args())
    {
        NamedValues[std::string(arg.getName())] = &arg;
    }

    if (llvm::Value *retVal = body_->codegen())
    {
        Builder->CreateRet(retVal);
        llvm::verifyFunction(*theFunction);
        return theFunction;
    }

    theFunction->eraseFromParent();
    return nullptr;
}
