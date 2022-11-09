#ifndef OBELISK_PARSER_H
#define OBELISK_PARSER_H

#include "ast/expression_ast.h"
#include "ast/function_ast.h"
#include "ast/prototype_ast.h"
#include "lexer.h"

#include <memory>

namespace obelisk
{
    class Parser
    {
        private:
            obelisk::Lexer* lexer_;
            int currentToken_;

            void setCurrentToken(int currentToken);

            std::unique_ptr<obelisk::ExpressionAST> logError(const char* str);
            std::unique_ptr<obelisk::PrototypeAST> logErrorPrototype(
                const char* str);

            std::unique_ptr<obelisk::ExpressionAST> parseExpression();
            std::unique_ptr<obelisk::ExpressionAST> parseNumberExpression();
            std::unique_ptr<obelisk::ExpressionAST>
                parseParenthesisExpression();
            std::unique_ptr<obelisk::ExpressionAST> parseIdentifierExpression();
            std::unique_ptr<obelisk::ExpressionAST> parsePrimary();
            std::unique_ptr<obelisk::PrototypeAST> parsePrototype();
            std::unique_ptr<obelisk::FunctionAST> parseDefinition();
            std::unique_ptr<obelisk::FunctionAST> parseTopLevelExpression();
            std::unique_ptr<obelisk::PrototypeAST> parseExtern();
            std::unique_ptr<obelisk::ExpressionAST> parseAction();
            std::unique_ptr<obelisk::ExpressionAST> parseRule();
            std::unique_ptr<obelisk::ExpressionAST> parseFact();

        public:
            Parser();
            Parser(obelisk::Lexer* lexer);
            ~Parser();

            obelisk::Lexer* getLexer();

            int getCurrentToken();

            int getNextToken();

            void handleDefinition();
            void handleExtern();
            void handleTopLevelExpression();
            void handleAction();
            void handleRule();
            void handleFact();
    };
} // namespace obelisk

#endif
