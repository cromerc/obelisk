#include "ast/call_expression_ast.h"
#include "ast/number_expression_ast.h"
#include "ast/variable_expression_ast.h"
#include "models/entity.h"
#include "models/fact.h"
#include "models/verb.h"
#include "parser.h"

#include <memory>
#include <stack>
#include <string>
#include <vector>

std::shared_ptr<obelisk::Lexer> obelisk::Parser::getLexer()
{
    return lexer_;
}

void obelisk::Parser::setLexer(std::shared_ptr<obelisk::Lexer> lexer)
{
    lexer_        = lexer;
    currentToken_ = 0;
}

int obelisk::Parser::getNextToken()
{
    try
    {
        setCurrentToken(getLexer()->getToken());
    }
    catch (obelisk::LexerException& exception)
    {
        throw;
    }
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

std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::logError(const char* str)
{
    fprintf(stderr, "Error: %s\n", str);
    return nullptr;
}

std::unique_ptr<obelisk::PrototypeAST> obelisk::Parser::logErrorPrototype(const char* str)
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
    auto result = std::make_unique<obelisk::NumberExpressionAST>(getLexer()->getNumberValue());
    getNextToken();
    return result;
}

std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parseParenthesisExpression()
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

std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parseIdentifierExpression()
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

    return std::make_unique<obelisk::PrototypeAST>(functionName, std::move(argNames));
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
        return std::make_unique<FunctionAST>(std::move(prototype), std::move(expression));
    }

    return nullptr;
}

std::unique_ptr<obelisk::FunctionAST> obelisk::Parser::parseTopLevelExpression()
{
    if (auto expression = parseExpression())
    {
        // Make an anonymous prototype
        auto prototype = std::make_unique<obelisk::PrototypeAST>("__anon_expr", std::vector<std::string>());
        return std::make_unique<obelisk::FunctionAST>(std::move(prototype), std::move(expression));
    }
    return nullptr;
}

std::unique_ptr<obelisk::PrototypeAST> obelisk::Parser::parseExtern()
{
    getNextToken();
    return parsePrototype();
}

//action("martin" is "dangerous" then "avoid" or "ignore");
std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parseAction()
{
}

//rule("chris" and "martin" is "happy" if "chris" plays "playstation");
std::unique_ptr<obelisk::ExpressionAST> obelisk::Parser::parseRule()
{
}

// fact("chris cromer" and "martin" and "Isabella" can "program" and "speak english");
// fact("" and "martin")
void obelisk::Parser::parseFact(std::vector<obelisk::Fact>& facts)
{
    std::stack<char> syntax;

    getNextToken();
    if (getCurrentToken() != '(')
    {
        throw obelisk::ParserException("expected '(' but got '" + std::to_string(getCurrentToken()) + "'");
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
                    throw obelisk::ParserException("missing left side entities");
                }

                if (rightEntities.size() == 0)
                {
                    throw obelisk::ParserException("missing right side entities");
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
                // TODO: make sure verb is alphabetic
                getEntity = true;
                continue;
            }
        }
    }

    for (auto& leftEntity : leftEntities)
    {
        for (auto& rightEntity : rightEntities)
        {
            facts.push_back(
                obelisk::Fact(obelisk::Entity(leftEntity), obelisk::Entity(rightEntity), obelisk::Verb(verb)));
        }
    }
}

void obelisk::Parser::handleAction(std::unique_ptr<obelisk::KnowledgeBase>& kb)
{
}

void obelisk::Parser::handleRule(std::unique_ptr<obelisk::KnowledgeBase>& kb)
{
}

void obelisk::Parser::handleFact(std::unique_ptr<obelisk::KnowledgeBase>& kb)
{
    std::vector<obelisk::Fact> facts;
    parseFact(facts);

    int verbId = 0;
    for (auto& fact : facts)
    {
        std::vector<obelisk::Entity> entities {fact.getLeftEntity()};
        kb->addEntities(entities);
        fact.setLeftEntity(entities.front());

        // the id was not inserted, so check if it exists in the database
        if (fact.getLeftEntity().getId() == 0)
        {
            obelisk::Entity entity = fact.getLeftEntity();
            kb->getEntity(entity);
            if (entity.getId() == 0)
            {
                throw obelisk::ParserException("left entity could not be inserted into the database");
            }
            else
            {
                fact.setLeftEntity(entity);
            }
        }

        entities = {fact.getRightEntity()};
        kb->addEntities(entities);
        fact.setRightEntity(entities.front());

        if (fact.getRightEntity().getId() == 0)
        {
            obelisk::Entity entity = fact.getRightEntity();
            kb->getEntity(entity);
            if (entity.getId() == 0)
            {
                throw obelisk::ParserException("right entity could not be inserted into the database");
            }
            else
            {
                fact.setRightEntity(entity);
            }
        }

        if (verbId == 0)
        {
            std::vector<obelisk::Verb> verbs = {fact.getVerb()};
            kb->addVerbs(verbs);
            if (verbs.front().getId() != 0)
            {
                fact.setVerb(verbs.front());
                verbId = fact.getVerb().getId();
            }
            else
            {
                obelisk::Verb verb = fact.getVerb();
                kb->getVerb(verb);
                if (verb.getId() == 0)
                {
                    throw obelisk::ParserException("verb could not be inserted into the database");
                }
                else
                {
                    fact.setVerb(verb);
                    verbId = fact.getVerb().getId();
                }
            }
        }
        else
        {
            fact.getVerb().setId(verbId);
        }

        std::vector<obelisk::Fact> facts {fact};
        kb->addFacts(facts);
        fact = facts.front();

        if (fact.getId() == 0)
        {
            kb->getFact(fact);
            if (fact.getId() == 0)
            {
                throw obelisk::ParserException("fact could not be inserted into the database");
            }
        }
    }
}

// fact("chris cromer" and "martin" and "Isabella" can "program" and "speak english");
