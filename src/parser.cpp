#include "ast/call_expression_ast.h"
#include "ast/number_expression_ast.h"
#include "ast/variable_expression_ast.h"
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

void obelisk::Parser::parseAction(obelisk::SuggestAction& suggestAction)
{
    std::stack<char> syntax;

    getNextToken();
    if (getCurrentToken() != '(')
    {
        throw obelisk::ParserException("expected '(' but got '" + std::to_string(getCurrentToken()) + "'");
    }

    syntax.push('(');

    getNextToken();
    if (getLexer()->getIdentifier() != "if")
    {
        throw obelisk::ParserException("expected 'if' but got '" + getLexer()->getIdentifier() + "'");
    }

    bool getEntity {true};
    std::string leftEntity {""};
    std::string rightEntity {""};
    std::string trueAction {""};
    std::string falseAction {""};
    std::string entityName {""};
    std::string verb {""};
    getNextToken();

    // get the entity side of statement
    while (true)
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
                        leftEntity = entityName;
                    }
                    else
                    {
                        rightEntity = entityName;
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
                throw obelisk::ParserException("unexpected ')'");
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
            else if (getLexer()->getIdentifier() == "then")
            {
                break;
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

    // get the action side of statement
    bool getAction {true};
    while (true)
    {
        if (getAction)
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
                    if (trueAction == "")
                    {
                        trueAction = entityName;
                    }
                    else
                    {
                        falseAction = entityName;
                    }
                    entityName = "";
                    getAction  = false;
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
                if (syntax.top() != '(')
                {
                    throw obelisk::ParserException("unexpected ')'");
                }
                else
                {
                    syntax.pop();
                }

                if (trueAction == "")
                {
                    throw obelisk::ParserException("missing true action");
                }

                if (falseAction == "")
                {
                    throw obelisk::ParserException("missing false action");
                }

                break;
            }

            if (getCurrentToken() == '"')
            {
                throw obelisk::ParserException("unexpected '\"'");
                break;
            }

            if (getLexer()->getIdentifier() == "else")
            {
                getNextToken();
                getAction = true;
                continue;
            }
            else
            {
                getAction = true;
                continue;
            }
        }
    }

    suggestAction.setFact(
        obelisk::Fact(obelisk::Entity(leftEntity), obelisk::Entity(rightEntity), obelisk::Verb(verb)));
    suggestAction.setTrueAction(obelisk::Action(trueAction));
    suggestAction.setFalseAction(obelisk::Action(falseAction));
}

void obelisk::Parser::parseRule(std::vector<obelisk::Rule>& rules)
{
}

void obelisk::Parser::parseFact(std::vector<obelisk::Fact>& facts)
{
    std::stack<char> syntax;

    getNextToken();
    if (getCurrentToken() != '(')
    {
        throw obelisk::ParserException("expected '(' but got '" + std::to_string(getCurrentToken()) + "'");
    }

    syntax.push('(');

    bool getEntity {true};
    std::vector<std::string> leftEntities;
    std::vector<std::string> rightEntities;
    std::string entityName {""};
    std::string verb {""};
    getNextToken();
    while (true)
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
                if (syntax.top() != '(')
                {
                    throw obelisk::ParserException("unexpected ')'");
                }
                else
                {
                    syntax.pop();
                }

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
                obelisk::Fact(obelisk::Entity(leftEntity), obelisk::Entity(rightEntity), obelisk::Verb(verb), true));
        }
    }
}

void obelisk::Parser::handleAction(std::unique_ptr<obelisk::KnowledgeBase>& kb)
{
    obelisk::SuggestAction suggestAction;
    parseAction(suggestAction);

    try
    {
        insertEntity(kb, suggestAction.getFact().getLeftEntity());
        insertEntity(kb, suggestAction.getFact().getRightEntity());
        insertVerb(kb, suggestAction.getFact().getVerb());
        insertFact(kb, suggestAction.getFact());
        insertAction(kb, suggestAction.getTrueAction());
        insertAction(kb, suggestAction.getFalseAction());

        // TODO: insert the actions, then insert the suggested action
    }
    catch (obelisk::ParserException& exception)
    {
        throw;
    }
}

void obelisk::Parser::handleRule(std::unique_ptr<obelisk::KnowledgeBase>& kb)
{
}

void obelisk::Parser::handleFact(std::unique_ptr<obelisk::KnowledgeBase>& kb)
{
    std::vector<obelisk::Fact> facts;
    try
    {
        parseFact(facts);
    }
    catch (obelisk::ParserException& exception)
    {
        throw;
    }

    int verbId = 0;
    for (auto& fact : facts)
    {
        try
        {
            insertEntity(kb, fact.getLeftEntity());
            insertEntity(kb, fact.getRightEntity());
        }
        catch (obelisk::ParserException& exception)
        {
            throw;
        }

        if (verbId == 0)
        {
            try
            {
                insertVerb(kb, fact.getVerb());
            }
            catch (obelisk::ParserException& exception)
            {
                throw;
            }
            verbId = fact.getVerb().getId();
        }
        else
        {
            fact.getVerb().setId(verbId);
        }

        try
        {
            insertFact(kb, fact);
        }
        catch (obelisk::ParserException& exception)
        {
            throw;
        }
    }
}

void obelisk::Parser::insertEntity(std::unique_ptr<obelisk::KnowledgeBase>& kb, obelisk::Entity& entity)
{
    std::vector<obelisk::Entity> entities {entity};
    kb->addEntities(entities);
    entity = std::move(entities.front());

    // the id was not inserted, so check if it exists in the database
    if (entity.getId() == 0)
    {
        kb->getEntity(entity);
        if (entity.getId() == 0)
        {
            throw obelisk::ParserException("entity could not be inserted into the database");
        }
    }
}

void obelisk::Parser::insertVerb(std::unique_ptr<obelisk::KnowledgeBase>& kb, obelisk::Verb& verb)
{
    std::vector<obelisk::Verb> verbs {verb};
    kb->addVerbs(verbs);
    verb = std::move(verbs.front());

    // the id was not inserted, so check if it exists in the database
    if (verb.getId() == 0)
    {
        kb->getVerb(verb);
        if (verb.getId() == 0)
        {
            throw obelisk::ParserException("verb could not be inserted into the database");
        }
    }
}

void obelisk::Parser::insertAction(std::unique_ptr<obelisk::KnowledgeBase>& kb, obelisk::Action& action)
{
    std::vector<obelisk::Action> actions {action};
    kb->addActions(actions);
    action = std::move(actions.front());

    // the id was not inserted, so check if it exists in the database
    if (action.getId() == 0)
    {
        kb->getAction(action);
        if (action.getId() == 0)
        {
            throw obelisk::ParserException("action could not be inserted into the database");
        }
    }
}

void obelisk::Parser::insertFact(std::unique_ptr<obelisk::KnowledgeBase>& kb, obelisk::Fact& fact)
{
    std::vector<obelisk::Fact> facts {fact};
    kb->addFacts(facts);
    fact = std::move(facts.front());

    // the id was not inserted, so check if it exists in the database
    if (fact.getId() == 0)
    {
        kb->getFact(fact);
        if (fact.getId() == 0)
        {
            throw obelisk::ParserException("fact could not be inserted into the database");
        }
    }
}
