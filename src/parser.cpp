#include "ast/call_expression_ast.h"
#include "ast/number_expression_ast.h"
#include "ast/variable_expression_ast.h"
#include "parser.h"

#include <memory>
#include <stack>
#include <string>
#include <vector>

obelisk::Parser::Parser()
{
    lexer_ = std::unique_ptr<obelisk::Lexer> {new obelisk::Lexer()};
}

std::unique_ptr<obelisk::Lexer>& obelisk::Parser::getLexer()
{
    return lexer_;
}

int obelisk::Parser::getNextToken()
{
    setCurrentToken(getLexer()->getToken());
    return getCurrentToken();
}

int obelisk::Parser::getCurrentToken()
{
    return currentToken_;
}

void obelisk::Parser::setCurrentToken(int currentToken)
{
    currentToken_ = currentToken;
}

std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::logError(
    const char* str)
{
    fprintf(stderr, "Error: %s\n", str);
    return nullptr;
}

std::unique_ptr<obelisk::PrototypeAST> obelisk::Parser::logErrorPrototype(
    const char* str)
{
    logError(str);
    return nullptr;
}

std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parseExpression()
{
    auto LHS = parsePrimary();
    if (!LHS)
    {
        return nullptr;
    }

    return LHS;
}

std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parsePrimary()
{
    switch (getCurrentToken())
    {
        case obelisk::Lexer::kTokenIdentifier :
            return parseIdentifierExpression();
        case obelisk::Lexer::kTokenNumber :
            return parseNumberExpression();
        case '(' :
            return parseParenthesisExpression();
        default :
            return logError("unknown token when expecting and expression");
    }
}

std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parseNumberExpression()
{
    auto result = std::make_unique<obelisk::NumberExpressionAST>(
        getLexer()->getNumberValue());
    getNextToken();
    return result;
}

std::unique_ptr<obelisk::ExpressionAST>
    obelisk::Parser::parseParenthesisExpression()
{
    getNextToken();
    auto v = parseExpression();
    if (!v)
    {
        return nullptr;
    }

    if (getCurrentToken() != ')')
    {
        return logError("expected ')'");
    }
    getNextToken();
    return v;
}

std::unique_ptr<obelisk::ExpressionAST>
    obelisk::Parser::parseIdentifierExpression()
{
    std::string idName = getLexer()->getIdentifier();
    getNextToken();
    if (getCurrentToken() != '(')
    {
        return std::make_unique<obelisk::VariableExpressionAST>(idName);
    }

    getNextToken();
    std::vector<std::unique_ptr<obelisk::ExpressionAST>> args;
    if (getCurrentToken() != ')')
    {
        while (true)
        {
            if (auto arg = parseExpression())
            {
                args.push_back(std::move(arg));
            }
            else
            {
                return nullptr;
            }

            if (getCurrentToken() == ')')
            {
                break;
            }

            if (getCurrentToken() != ',')
            {
                return logError("Expected ')' or ',' in argument list");
            }

            getNextToken();
        }
    }

    getNextToken();
    return std::make_unique<CallExpressionAST>(idName, std::move(args));
}

std::unique_ptr<obelisk::PrototypeAST> obelisk::Parser::parsePrototype()
{
    if (getCurrentToken() != obelisk::Lexer::kTokenIdentifier)
    {
        return logErrorPrototype("Expected function name in prototype");
    }

    std::string functionName = getLexer()->getIdentifier();
    getNextToken();

    if (getCurrentToken() != '(')
    {
        return logErrorPrototype("Expected '(' in prototype");
    }

    std::vector<std::string> argNames;
    while (getNextToken() == obelisk::Lexer::kTokenIdentifier)
    {
        argNames.push_back(getLexer()->getIdentifier());
    }

    if (getCurrentToken() != ')')
    {
        return logErrorPrototype("Expected ')' in prototype");
    }

    getNextToken();

    return std::make_unique<obelisk::PrototypeAST>(functionName,
        std::move(argNames));
}

std::unique_ptr<obelisk::FunctionAST> obelisk::Parser::parseDefinition()
{
    getNextToken();
    auto prototype = parsePrototype();
    if (!prototype)
    {
        return nullptr;
    }

    if (auto expression = parseExpression())
    {
        return std::make_unique<FunctionAST>(std::move(prototype),
            std::move(expression));
    }

    return nullptr;
}

std::unique_ptr<obelisk::FunctionAST> obelisk::Parser::parseTopLevelExpression()
{
    if (auto expression = parseExpression())
    {
        // Make an anonymous prototype
        auto prototype = std::make_unique<obelisk::PrototypeAST>("__anon_expr",
            std::vector<std::string>());
        return std::make_unique<obelisk::FunctionAST>(std::move(prototype),
            std::move(expression));
    }
    return nullptr;
}

std::unique_ptr<obelisk::PrototypeAST> obelisk::Parser::parseExtern()
{
    getNextToken();
    return parsePrototype();
}

std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parseAction()
{
}

std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parseRule()
{
}

// fact("chris cromer" and "martin" and "Isabella" can "program" and "speak english");
// fact("" and "martin")
std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parseFact()
{
    std::stack<char> syntax;

    getNextToken();
    if (getCurrentToken() != '(')
    {
        throw obelisk::ParserException(
            "expected '(' but got '" + std::to_string(getCurrentToken()) + "'");
    }

    syntax.push('(');

    // ("

    bool getEntity {true};
    std::vector<std::string> leftEntities;
    std::vector<std::string> rightEntities;
    std::string entityName {""};
    std::string verb {""};
    getNextToken();
    while (true) //left side of fact
    {
        if (getEntity)
        {
            if (getCurrentToken() == '"')
            {
                if (syntax.top() != '"')
                {
                    // open a double quote
                    syntax.push('"');
                    getNextToken();
                }
                else if (syntax.top() == '"')
                {
                    // close a double quote
                    syntax.pop();
                    if (verb == "")
                    {
                        leftEntities.push_back(entityName);
                    }
                    else
                    {
                        rightEntities.push_back(entityName);
                    }
                    entityName = "";
                    getEntity  = false;
                    getNextToken();
                    continue;
                }
            }

            if (syntax.top() == '"')
            {
                if (entityName != "")
                {
                    entityName += " ";
                }
                entityName += getLexer()->getIdentifier();
            }
            getNextToken();
        }
        else
        {
            if (getCurrentToken() == ')')
            {
                // closing parenthesis found, make sure we have everything needed
                if (verb == "")
                {
                    throw obelisk::ParserException("verb is empty");
                }

                if (leftEntities.size() == 0)
                {
                    throw obelisk::ParserException(
                        "missing left side entities");
                }

                if (rightEntities.size() == 0)
                {
                    throw obelisk::ParserException(
                        "missing right side entities");
                }
                break;
            }

            if (getCurrentToken() == '"')
            {
                throw obelisk::ParserException("unexpected '\"'");
                break;
            }

            if (getLexer()->getIdentifier() == "and")
            {
                getNextToken();
                getEntity = true;
                continue;
            }
            else
            {
                verb      = getLexer()->getIdentifier();
                getEntity = true;
                continue;
            }
        }
    }

    return nullptr;
}

void obelisk::Parser::handleAction()
{
}

void obelisk::Parser::handleRule()
{
}

void obelisk::Parser::handleFact()
{
    parseFact();
}
