#ifndef OBELISK_PARSER_H
#define OBELISK_PARSER_H

#include "ast/expression_ast.h"
#include "ast/function_ast.h"
#include "ast/prototype_ast.h"
#include "knowledge_base.h"
#include "lexer.h"
#include "models/action.h"
#include "models/entity.h"
#include "models/fact.h"
#include "models/rule.h"
#include "models/suggest_action.h"
#include "models/verb.h"

#include <memory>

namespace obelisk
{
    /**
     * @brief The Parser is responsible for analyzing the language's key words and taking action based on its analysis.
     *
     */
    class Parser
    {
        private:
            /**
             * @brief The Lexer object that the Parser is using to Parse a specific source file.
             *
             */
            std::shared_ptr<obelisk::Lexer> lexer_;

            /**
             * @brief The current token that the lexer has retrieved.
             *
             */
            int currentToken_ = 0;

            /**
             * @brief Set the current token.
             *
             * @param[in] currentToken The token should be ASCII character.
             */
            void setCurrentToken(int currentToken);

            /**
             * @brief Log errors from the LLVM parsing.
             *
             * @param[in] str The error message.
             * @return std::unique_ptr<obelisk::ExpressionAST> Returns the AST expression that caused the error.
             */
            std::unique_ptr<obelisk::ExpressionAST> logError(const char* str);

            /**
             * @brief Log errors from the LLVM parsing involving the prototypes.
             *
             * @param[in] str The error message.
             * @return std::unique_ptr<obelisk::PrototypeAST> Returns the AST for the prototype.
             */
            std::unique_ptr<obelisk::PrototypeAST> logErrorPrototype(const char* str);

            /**
             * @brief The AST expression parser.
             *
             * @return std::unique_ptr<obelisk::ExpressionAST> Returns the parsed AST expression.
             */
            std::unique_ptr<obelisk::ExpressionAST> parseExpression();

            /**
             * @brief The AST number expression parser.
             *
             * @return std::unique_ptr<obelisk::ExpressionAST> Returns the parsed AST expression.
             */
            std::unique_ptr<obelisk::ExpressionAST> parseNumberExpression();

            /**
             * @brief The AST parenthesis expression parser.
             *
             * @return std::unique_ptr<obelisk::ExpressionAST> Returns the parsed AST expression.
             */
            std::unique_ptr<obelisk::ExpressionAST> parseParenthesisExpression();

            /**
             * @brief The AST identifier expression parser.
             *
             * @return std::unique_ptr<obelisk::ExpressionAST> Returns the parsed AST expression.
             */
            std::unique_ptr<obelisk::ExpressionAST> parseIdentifierExpression();

            /**
             * @brief The AST primary expression parser.
             *
             * @return std::unique_ptr<obelisk::ExpressionAST> Returns the parsed AST expression.
             */
            std::unique_ptr<obelisk::ExpressionAST> parsePrimary();

            /**
             * @brief The AST prototype parser.
             *
             * @return std::unique_ptr<obelisk::PrototypeAST> Returns the parsed AST prototype expression.
             */
            std::unique_ptr<obelisk::PrototypeAST> parsePrototype();

            /**
             * @brief The AST definition parser.
             *
             * @return std::unique_ptr<obelisk::FunctionAST> Returns the parsed AST definition expression.
             */
            std::unique_ptr<obelisk::FunctionAST> parseDefinition();

            /**
             * @brief The AST top level expression parser.
             *
             * @return std::unique_ptr<obelisk::FunctionAST> Returns the parsed AST top level expression.
             */
            std::unique_ptr<obelisk::FunctionAST> parseTopLevelExpression();

            /**
             * @brief The AST external definition parser.
             *
             * @return std::unique_ptr<obelisk::PrototypeAST> Returns the parsed AST external definition.
             */
            std::unique_ptr<obelisk::PrototypeAST> parseExtern();

            /**
             * @brief Parse a SuggestAction.
             *
             * @param[out] suggestAction The parsed SuggestAction.
             */
            void parseAction(obelisk::SuggestAction& suggestAction);

            /**
             * @brief Parse a Rule.
             *
             * @param[out] rule The parsed Rule.
             */
            void parseRule(obelisk::Rule& rule);

            /**
             * @brief Parse Facts.
             *
             * @param[out] facts The parsed Facts.
             */
            void parseFact(std::vector<obelisk::Fact>& facts);

        public:
            /**
             * @brief Construct a new Parser object.
             *
             * @param[in] lexer The lexer the parser uses to retrieve parts of the language.
             */
            Parser(std::shared_ptr<obelisk::Lexer> lexer) :
                lexer_(lexer)
            {
            }

            /**
             * @brief Get the Lexer.
             *
             * @return std::shared_ptr<obelisk::Lexer> Returns the current Lexer in use by the Parser.
             */
            std::shared_ptr<obelisk::Lexer> getLexer();

            /**
             * @brief Set the Lexer to use during the parsing phase.
             *
             * @param[in] lexer The Lexer.
             */
            void setLexer(std::shared_ptr<obelisk::Lexer> lexer);

            /**
             * @brief Gets the current token held inside the Lexer.
             *
             * @return int Returns the current token.
             */
            int getCurrentToken();

            /**
             * @brief Instructs the Lexer to retrieve a new token.
             *
             * @return int Returns the next token.
             */
            int getNextToken();

            /**
             * @brief Parse the SuggestAction and then insert it into the KnowledgeBase.
             *
             * @param[in] kb The KnowledgeBase to insert the SuggestAction into.
             */
            void handleAction(std::unique_ptr<obelisk::KnowledgeBase>& kb);

            /**
             * @brief Parse the Rule and then insert it into the KnowledgeBase.
             *
             * @param[in] kb The KnowledgeBase to insert the Rule into.
             */
            void handleRule(std::unique_ptr<obelisk::KnowledgeBase>& kb);

            /**
             * @brief Parse the Fact and then insert it into the KnowledgeBase.
             *
             * @param[in] kb The KnowledgeBase to insert the Fact into.
             */
            void handleFact(std::unique_ptr<obelisk::KnowledgeBase>& kb);

            /**
             * @brief Helper used to insert an Entity into the KnowledgeBase.
             *
             * @param[in] kb The KnowledgeBase to use.
             * @param[in,out] entity The Entity to insert. It will contain the ID of the Entity after inserting it.
             */
            void insertEntity(std::unique_ptr<obelisk::KnowledgeBase>& kb, obelisk::Entity& entity);

            /**
             * @brief Helper used to insert a Verb into the KnowledgeBase.
             *
             * @param[in] kb The KnowledegeBase to use.
             * @param[in,out] verb The Verb to insert. It will contain the ID of the Verb after inserting it.
             */
            void insertVerb(std::unique_ptr<obelisk::KnowledgeBase>& kb, obelisk::Verb& verb);

            /**
             * @brief Helper used to insert an Action into the KnowledgeBase.
             *
             * @param[in] kb The KnowledgeBase to use.
             * @param[in,out] action The Action to insert. It will contain the ID of the Action after inserting it.
             */
            void insertAction(std::unique_ptr<obelisk::KnowledgeBase>& kb, obelisk::Action& action);

            /**
             * @brief Helper used to insert a Fact into the KnowledgeBase.
             *
             * @param[in] kb The KnowledgeBase to use.
             * @param[in,out] fact The Fact to insert. It will contain the ID of the Fact after inserting it.
             * @param[in] updateIsTrue If true, it will update the value of is_true in the KnowledgeBase if the Fact
             * already exists.
             */
            void insertFact(std::unique_ptr<obelisk::KnowledgeBase>& kb,
                obelisk::Fact& fact,
                bool updateIsTrue = false);

            /**
             * @brief Helper used to insert a SuggestAction into the KnowledgeBase.
             *
             * @param[in] kb The KnowledgeBase to use.
             * @param[in,out] suggestAction The SuggestAction to insert. It will contain the ID of the SuggestAction
             * after inserting it.
             */
            void insertSuggestAction(std::unique_ptr<obelisk::KnowledgeBase>& kb,
                obelisk::SuggestAction& suggestAction);

            /**
             * @brief Helper usedto insert a Rule into the KnowledgeBase.
             *
             * @param[in] kb The KnowledgeBase to use.
             * @param[in,out] rule The Rule to insert. It will contain the ID of the Rule after inserting it.
             */
            void insertRule(std::unique_ptr<obelisk::KnowledgeBase>& kb, obelisk::Rule& rule);
    };

    /**
     * @brief The exceptions thrown by the Parser.
     *
     */
    class ParserException : public std::exception
    {
        private:
            /**
             * @brief The error message.
             *
             */
            const std::string errorMessage_;

        public:
            /**
             * @brief Construct a new ParserException object.
             *
             */
            ParserException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            /**
             * @brief Construct a new ParserException object.
             *
             * @param[in] errorMessage The error message.
             */
            ParserException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            /**
             * @brief Return the error message as a C style string.
             *
             * @return const char* Returns the error message.
             */
            const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }
    };
} // namespace obelisk

#endif
