#ifndef OBELISK_AST_VARIABLE_EXPRESSION_AST_H
#define OBELISK_AST_VARIABLE_EXPRESSION_AST_H

#include "ast/expression_ast.h"

#include <string>

namespace obelisk
{
    /**
     * @brief The variable expression AST node.
     *
     */
    class VariableExpressionAST : public ExpressionAST
    {
        private:
            /**
             * @brief The name of the variable.
             *
             */
            std::string name_;

            /**
             * @brief Get the name of the variable.
             *
             * @return std::string Returns the name of the variable.
             */
            std::string getName();

            /**
             * @brief Set the name of the variable.
             *
             * @param[in] name The name of the variable.
             */
            void setName(const std::string name);

        public:
            /**
             * @brief Construct a new VariableExpressionAST object.
             *
             * @param[in] name The name of the variable.
             */
            VariableExpressionAST(const std::string &name) :
                name_(name)
            {
            }

            /**
             * @brief Generate the variable LLVM IR code.
             *
             * @return llvm::Value* Returns the generated IR code.
             */
            llvm::Value *codegen() override;
    };
} // namespace obelisk

#endif
