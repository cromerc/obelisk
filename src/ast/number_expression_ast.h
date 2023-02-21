#ifndef OBELISK_AST_NUMBER_EXPRESSION_AST_H
#define OBELISK_AST_NUMBER_EXPRESSION_AST_H

#include "ast/expression_ast.h"

namespace obelisk
{
    /**
     * @brief A number expression AST node.
     *
     */
    class NumberExpressionAST : public ExpressionAST
    {
        private:
            /**
             * @brief The number.
             *
             */
            double number_;

            /**
             * @brief Get the number.
             *
             * @return double Returns the number.
             */
            double getNumber();

            /**
             * @brief Set the number.
             *
             * @param[in] number The number.
             */
            void setNumber(double number);

        public:
            /**
             * @brief Construct a new NumberExpressionAST object.
             *
             * @param[in] number The number.
             */
            NumberExpressionAST(double number) :
                number_(number)
            {
            }

            /**
             * @brief Generate LLVM IR code for the number.
             *
             * @return llvm::Value* Returns the genrated IR code.
             */
            llvm::Value *codegen() override;
    };
} // namespace obelisk

#endif
