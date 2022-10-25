#ifndef OBELISK_AST_VARIABLE_EXPRESSION_AST_H
#define OBELISK_AST_VARIABLE_EXPRESSION_AST_H

#include "ast/expression_ast.h"

#include <string>

namespace obelisk
{
    class VariableExpressionAST : public ExpressionAST
    {
        private:
            std::string name_;
            std::string getName();
            void setName(const std::string name);

        public:
            VariableExpressionAST(const std::string &name) :
                name_(name)
            {
            }
    };
} //namespace obelisk

#endif
