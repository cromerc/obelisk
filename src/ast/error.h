#ifndef OBELISK_AST_ERROR_H
#define OBELISK_AST_ERROR_H

#include "ast/expression_ast.h"

#include <memory>

namespace obelisk
{
    /**
     * @brief Log an AST expression error.
     *
     * @param[in] str The error message.
     * @return std::unique_ptr<ExpressionAST> Returns the AST expression that caused the error.
     */
    std::unique_ptr<ExpressionAST> LogError(const char *str);

    /**
     * @brief Log an AST value error.
     *
     * @param[in] str The error message.
     * @return llvm::Value* Returns the AST value that caused the error.
     */
    llvm::Value *LogErrorV(const char *str);
} // namespace obelisk

#endif
