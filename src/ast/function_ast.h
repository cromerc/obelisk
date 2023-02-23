#ifndef OBELISK_AST_FUNCTION_AST_H
#define OBELISK_AST_FUNCTION_AST_H

#include "ast/expression_ast.h"
#include "ast/prototype_ast.h"

#include <memory>

namespace obelisk
{
    /**
     * @brief A Funcion AST node.
     *
     */
    class FunctionAST
    {
        private:
            /**
             * @brief The prototype of the function.
             *
             */
            std::unique_ptr<PrototypeAST> prototype_;

            /**
             * @brief The body of the function.
             *
             */
            std::unique_ptr<ExpressionAST> body_;

            /**
             * @brief Get the prototype.
             *
             * @return std::unique_ptr<PrototypeAST> Returns the prototype AST.
             */
            std::unique_ptr<PrototypeAST> getPrototype();

            /**
             * @brief Set the prototype.
             *
             * @param[in] prototype Set the prototype.
             */
            void setPrototype(std::unique_ptr<PrototypeAST> prototype);

        public:
            /**
             * @brief Construct a new FunctionAST object.
             *
             * @param[in] prototype The prototype of the function.
             * @param[in] body The body of the function.
             */
            FunctionAST(std::unique_ptr<PrototypeAST> prototype,
                std::unique_ptr<ExpressionAST> body) :
                prototype_(std::move(prototype)),
                body_(std::move(body))
            {
            }

            /**
             * @brief Generate LLVM IR code.
             *
             * @return llvm::Function* Returns the LLVM IR function code.
             */
            llvm::Function *codegen();
    };
} // namespace obelisk

#endif
