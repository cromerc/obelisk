#ifndef OBELISK_AST_CALL_EXPRESSION_AST_H
#define OBELISK_AST_CALL_EXPRESSION_AST_H

#include "ast/expression_ast.h"

#include <memory>
#include <string>
#include <vector>

namespace obelisk
{
    /**
     * @brief The call AST expression node used to call functions.
     *
     */
    class CallExpressionAST : public ExpressionAST
    {
        private:
            /**
             * @brief The function being called.
             *
             */
            std::string callee_;

            /**
             * @brief The arguments passed to the function.
             *
             */
            std::vector<std::unique_ptr<ExpressionAST>> args_;

            /**
             * @brief Get the callee.
             *
             * @return std::string Returns the name of the function being called.
             */
            std::string getCallee();

            /**
             * @brief Set the callee.
             *
             * @param[in] callee The name of the function.
             */
            void setCallee(std::string callee);

            /**
             * @brief Get the arguments being used by the function.
             *
             * @return std::vector<std::unique_ptr<ExpressionAST>> Returns an AST expression containing the args.
             */
            std::vector<std::unique_ptr<ExpressionAST>> getArgs();

            /**
             * @brief Set the arguments to be used by the function.
             *
             * @param[in] args The args to set.
             */
            void setArgs(std::vector<std::unique_ptr<ExpressionAST>> args);

        public:
            /**
             * @brief Construct a new CallExpressionAST object.
             *
             * @param[in] callee The function to call.
             * @param[in] args The args to pass into the function.
             */
            CallExpressionAST(const std::string &callee, std::vector<std::unique_ptr<ExpressionAST>> args) :
                callee_(callee),
                args_(std::move(args))
            {
            }

            /**
             * @brief Generate the calle IR code.
             *
             * @return llvm::Value*
             */
            llvm::Value *codegen() override;
    };
} // namespace obelisk

#endif
