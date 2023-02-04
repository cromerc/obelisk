#include "ast/ast.h"
#include "ast/prototype_ast.h"

llvm::Function *obelisk::PrototypeAST::codegen()
{
    std::vector<llvm::Type *> doubles(args_.size(), llvm::Type::getDoubleTy(*TheContext));
    llvm::FunctionType *FT = llvm::FunctionType::get(llvm::Type::getDoubleTy(*TheContext), doubles, false);

    llvm::Function *F = llvm::Function::Create(FT, llvm::Function::ExternalLinkage, name_, obelisk::TheModule.get());

    unsigned idx = 0;
    for (auto &arg : F->args())
    {
        arg.setName(args_[idx++]);
    }

    return F;
}
