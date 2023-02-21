#ifndef OBELISK_AST_EXPRESSION_AST_H
#define OBELISK_AST_EXPRESSION_AST_H

#include <llvm/IR/Constants.h>

namespace obelisk
{
    /**
     * @brief A generic AST expression which other expression will inherit from.
     *
     */
    class ExpressionAST
    {
        public:
            /**
             * @brief Destroy the ExpressionAST object.
             *
             */
            virtual ~ExpressionAST() = default;

            /**
             * @brief Generate LLVM IR code based on the AST expression.
             *
             * @return llvm::Value* Returns the LLVM code value from the expression.
             */
            virtual llvm::Value *codegen() = 0;
    };
} // namespace obelisk

#endif
