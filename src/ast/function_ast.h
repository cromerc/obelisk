#ifndef OBELISK_AST_FUNCTION_AST_H
#define OBELISK_AST_FUNCTION_AST_H

#include "ast/expression_ast.h"
#include "ast/prototype_ast.h"

#include <memory>

namespace obelisk
{
    class FunctionAST
    {
        private:
            std::unique_ptr<PrototypeAST> prototype_;
            std::unique_ptr<ExpressionAST> body_;

            std::unique_ptr<PrototypeAST> getPrototype();
            void setPrototype(std::unique_ptr<PrototypeAST> prototype);

        public:
            FunctionAST(std::unique_ptr<PrototypeAST> prototype, std::unique_ptr<ExpressionAST> body) :
                prototype_(std::move(prototype)),
                body_(std::move(body))
            {
            }

            llvm::Function *codegen();
    };
} // namespace obelisk

#endif
