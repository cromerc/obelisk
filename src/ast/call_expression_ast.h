#ifndef OBELISK_AST_CALL_EXPRESSION_AST_H
#define OBELISK_AST_CALL_EXPRESSION_AST_H

#include "ast/expression_ast.h"

#include <memory>
#include <string>
#include <vector>

namespace obelisk
{
    class CallExpressionAST : public ExpressionAST
    {
        private:
            std::string callee_;
            std::vector<std::unique_ptr<ExpressionAST>> args_;

            std::string getCallee();
            void setCallee(std::string callee);

            std::vector<std::unique_ptr<ExpressionAST>> getArgs();
            void setArgs(std::vector<std::unique_ptr<ExpressionAST>> args);

        public:
            CallExpressionAST(const std::string &callee, std::vector<std::unique_ptr<ExpressionAST>> args) :
                callee_(callee),
                args_(std::move(args))
            {
            }

            llvm::Value *codegen() override;
    };
} // namespace obelisk

#endif
