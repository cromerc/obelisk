#include "ast/error.h"

std::unique_ptr<obelisk::ExpressionAST> obelisk::LogError(const char *Str)
{
    fprintf(stderr, "Error: %s\n", Str);
    return nullptr;
}

llvm::Value *obelisk::LogErrorV(const char *Str)
{
    LogError(Str);
    return nullptr;
}
