#ifndef OBELISK_PARSER_H
#define OBELISK_PARSER_H

#include "ast/expression_ast.h"
#include "ast/function_ast.h"
#include "ast/prototype_ast.h"
#include "knowledge_base.h"
#include "lexer.h"
#include "models/fact.h"

#include <memory>

namespace obelisk
{
    class Parser
    {
        private:
            std::shared_ptr<obelisk::Lexer> lexer_;
            int currentToken_ = 0;

            void setCurrentToken(int currentToken);

            std::unique_ptr<obelisk::ExpressionAST> logError(const char* str);
            std::unique_ptr<obelisk::PrototypeAST> logErrorPrototype(const char* str);

            std::unique_ptr<obelisk::ExpressionAST> parseExpression();
            std::unique_ptr<obelisk::ExpressionAST> parseNumberExpression();
            std::unique_ptr<obelisk::ExpressionAST> parseParenthesisExpression();
            std::unique_ptr<obelisk::ExpressionAST> parseIdentifierExpression();
            std::unique_ptr<obelisk::ExpressionAST> parsePrimary();
            std::unique_ptr<obelisk::PrototypeAST> parsePrototype();
            std::unique_ptr<obelisk::FunctionAST> parseDefinition();
            std::unique_ptr<obelisk::FunctionAST> parseTopLevelExpression();
            std::unique_ptr<obelisk::PrototypeAST> parseExtern();
            std::unique_ptr<obelisk::ExpressionAST> parseAction();
            std::unique_ptr<obelisk::ExpressionAST> parseRule();
            void parseFact(std::vector<obelisk::Fact>& facts);

        public:
            Parser(std::shared_ptr<obelisk::Lexer> lexer) :
                lexer_(lexer)
            {
            }

            std::shared_ptr<obelisk::Lexer> getLexer();
            void setLexer(std::shared_ptr<obelisk::Lexer> lexer);

            int getCurrentToken();

            int getNextToken();

            void handleDefinition();
            void handleExtern();
            void handleTopLevelExpression();
            void handleAction(std::unique_ptr<obelisk::KnowledgeBase>& kb);
            void handleRule(std::unique_ptr<obelisk::KnowledgeBase>& kb);
            void handleFact(std::unique_ptr<obelisk::KnowledgeBase>& kb);
    };

    class ParserException : public std::exception
    {
        private:
            const std::string errorMessage_;

        public:
            ParserException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            ParserException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }
    };
} // namespace obelisk

#endif
