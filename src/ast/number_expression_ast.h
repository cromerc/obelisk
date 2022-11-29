#ifndef OBELISK_AST_NUMBER_EXPRESSION_AST_H
#define OBELISK_AST_NUMBER_EXPRESSION_AST_H

#include "ast/expression_ast.h"

namespace obelisk
{
    class NumberExpressionAST : public ExpressionAST
    {
        private:
            double number_;

            double getNumber();
            void setNumber(double number);

        public:
            NumberExpressionAST(double number) :
                number_(number)
            {
            }

            llvm::Value *codegen() override;
    };
} // namespace obelisk

#endif
