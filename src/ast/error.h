#ifndef OBELISK_AST_ERROR_H
#define OBELISK_AST_ERROR_H

#include "ast/expression_ast.h"

#include <memory>

namespace obelisk
{
    std::unique_ptr<ExpressionAST> LogError(const char *Str);
    llvm::Value *LogErrorV(const char *Str);
} // namespace obelisk

#endif
