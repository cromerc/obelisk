#ifndef OBELISK_AST_EXPRESSION_AST_H
#define OBELISK_AST_EXPRESSION_AST_H

#include <llvm/IR/Constants.h>

namespace obelisk
{
    class ExpressionAST
    {
        public:
            virtual ~ExpressionAST()       = default;
            virtual llvm::Value *codegen() = 0;
    };
} // namespace obelisk

#endif
