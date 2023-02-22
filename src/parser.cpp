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

void obelisk::Parser::parseAction(obelisk::SuggestAction& suggestAction)
{
    std::stack<char> syntax;

    getNextToken();
    if (getCurrentToken() != '(')
    {
        throw obelisk::ParserException(
            "expected '(' but got '" + std::to_string(getCurrentToken()) + "'");
    }

    syntax.push('(');

    getNextToken();
    if (getLexer()->getIdentifier() != "if")
    {
        throw obelisk::ParserException(
            "expected 'if' but got '" + getLexer()->getIdentifier() + "'");
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
                        leftEntity = std::move(entityName);
                    }
                    else
                    {
                        rightEntity = std::move(entityName);
                    }
                    getEntity = false;
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
            }

            if (getLexer()->getIdentifier() == "then")
            {
                break;
            }
            else
            {
                verb = getLexer()->getIdentifier();
                for (const auto& letter : verb)
                {
                    if (!isalpha(letter))
                    {
                        throw new obelisk::ParserException(
                            "non alphabetic symbol in verb");
                    }
                }
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
                        trueAction = std::move(entityName);
                    }
                    else
                    {
                        falseAction = std::move(entityName);
                    }
                    getAction = false;
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
                // closing parenthesis found, make sure we have everything
                // needed
                if (syntax.top() != '(')
                {
                    throw obelisk::ParserException("unexpected ')'");
                }
                else
                {
                    syntax.pop();
                }

                if (leftEntity == "")
                {
                    throw obelisk::ParserException("missing left entity");
                }

                if (rightEntity == "")
                {
                    throw obelisk::ParserException("missing left entity");
                }

                if (verb == "")
                {
                    throw obelisk::ParserException("missing verb");
                }

                if (trueAction == "")
                {
                    throw obelisk::ParserException("missing true action");
                }

                if (falseAction == "")
                {
                    throw obelisk::ParserException("missing false action");
                }

                getNextToken();
                if (getCurrentToken() != ';')
                {
                    throw obelisk::ParserException("missing ';'");
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

    suggestAction.setFact(obelisk::Fact(obelisk::Entity(leftEntity),
        obelisk::Entity(rightEntity),
        obelisk::Verb(verb)));
    suggestAction.setTrueAction(obelisk::Action(trueAction));
    suggestAction.setFalseAction(obelisk::Action(falseAction));
}

void obelisk::Parser::parseRule(obelisk::Rule& rule)
{
    std::stack<char> syntax;

    getNextToken();
    if (getCurrentToken() != '(')
    {
        throw obelisk::ParserException(
            "expected '(' but got '" + std::to_string(getCurrentToken()) + "'");
    }

    syntax.push('(');

    bool getEntity {true};
    bool getReason {false};
    std::string leftEntity {""};
    std::string rightEntity {""};
    std::string verb {""};
    std::string leftReasonEntity {""};
    std::string rightReasonEntity {""};
    std::string reasonVerb {""};
    std::string entityName {""};
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
                    if (!getReason)
                    {
                        if (verb == "")
                        {
                            leftEntity = std::move(entityName);
                        }
                        else
                        {
                            rightEntity = std::move(entityName);
                        }
                    }
                    else
                    {
                        if (reasonVerb == "")
                        {
                            leftReasonEntity = std::move(entityName);
                        }
                        else
                        {
                            rightReasonEntity = std::move(entityName);
                        }
                    }
                    getEntity = false;
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
                // closing parenthesis found, make sure we have everything
                // needed
                if (syntax.top() != '(')
                {
                    throw obelisk::ParserException("unexpected ')'");
                }
                else
                {
                    syntax.pop();
                }

                if (leftEntity == "")
                {
                    throw obelisk::ParserException("missing left entity");
                }

                if (rightEntity == "")
                {
                    throw obelisk::ParserException("missing left entity");
                }

                if (verb == "")
                {
                    throw obelisk::ParserException("missing verb");
                }

                if (leftReasonEntity == "")
                {
                    throw obelisk::ParserException(
                        "missing left reason entity");
                }

                if (rightReasonEntity == "")
                {
                    throw obelisk::ParserException(
                        "missing right reason entity");
                }

                if (reasonVerb == "")
                {
                    throw obelisk::ParserException("missing reason verb");
                }

                getNextToken();
                if (getCurrentToken() != ';')
                {
                    throw obelisk::ParserException("missing ';'");
                }

                break;
            }

            if (getCurrentToken() == '"')
            {
                throw obelisk::ParserException("unexpected '\"'");
            }

            if (getLexer()->getIdentifier() == "if")
            {
                getReason = true;
                getEntity = true;
                getNextToken();
                continue;
            }
            else
            {
                if (!getReason)
                {
                    verb = getLexer()->getIdentifier();
                    for (const auto& letter : verb)
                    {
                        if (!isalpha(letter))
                        {
                            throw new obelisk::ParserException(
                                "non alphabetic symbol in verb");
                        }
                    }
                    getEntity = true;
                    continue;
                }
                else
                {
                    reasonVerb = getLexer()->getIdentifier();
                    for (const auto& letter : reasonVerb)
                    {
                        if (!isalpha(letter))
                        {
                            throw new obelisk::ParserException(
                                "non alphabetic symbol in verb");
                        }
                    }
                    getEntity = true;
                    continue;
                }
            }
        }
    }

    rule.setFact(obelisk::Fact(obelisk::Entity(leftEntity),
        obelisk::Entity(rightEntity),
        obelisk::Verb(verb)));
    rule.setReason(obelisk::Fact(obelisk::Entity(leftReasonEntity),
        obelisk::Entity(rightReasonEntity),
        obelisk::Verb(reasonVerb)));
}

void obelisk::Parser::parseFact(std::vector<obelisk::Fact>& facts)
{
    std::stack<char> syntax;

    getNextToken();
    if (getCurrentToken() != '(')
    {
        throw obelisk::ParserException(
            "expected '(' but got '" + std::to_string(getCurrentToken()) + "'");
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
                // closing parenthesis found, make sure we have everything
                // needed
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
                    throw obelisk::ParserException(
                        "missing left side entities");
                }

                if (rightEntities.size() == 0)
                {
                    throw obelisk::ParserException(
                        "missing right side entities");
                }

                getNextToken();
                if (getCurrentToken() != ';')
                {
                    throw obelisk::ParserException("missing ';'");
                }

                break;
            }

            if (getCurrentToken() == '"')
            {
                throw obelisk::ParserException("unexpected '\"'");
            }

            if (getLexer()->getIdentifier() == "and")
            {
                getNextToken();
                getEntity = true;
                continue;
            }
            else
            {
                verb = getLexer()->getIdentifier();
                for (const auto& letter : verb)
                {
                    if (!isalpha(letter))
                    {
                        throw new obelisk::ParserException(
                            "non alphabetic symbol in verb");
                    }
                }
                getEntity = true;
                continue;
            }
        }
    }

    for (auto& leftEntity : leftEntities)
    {
        for (auto& rightEntity : rightEntities)
        {
            facts.push_back(obelisk::Fact(obelisk::Entity(leftEntity),
                obelisk::Entity(rightEntity),
                obelisk::Verb(verb),
                true));
        }
    }
}

void obelisk::Parser::handleAction(std::unique_ptr<obelisk::KnowledgeBase>& kb)
{
    obelisk::SuggestAction suggestAction;

    try
    {
        parseAction(suggestAction);
        insertEntity(kb, suggestAction.getFact().getLeftEntity());
        insertEntity(kb, suggestAction.getFact().getRightEntity());
        insertVerb(kb, suggestAction.getFact().getVerb());
        insertFact(kb, suggestAction.getFact());
        insertAction(kb, suggestAction.getTrueAction());
        insertAction(kb, suggestAction.getFalseAction());
        insertSuggestAction(kb, suggestAction);
    }
    catch (obelisk::ParserException& exception)
    {
        throw;
    }
}

void obelisk::Parser::handleRule(std::unique_ptr<obelisk::KnowledgeBase>& kb)
{
    obelisk::Rule rule;

    try
    {
        parseRule(rule);

        insertEntity(kb, rule.getReason().getLeftEntity());
        insertEntity(kb, rule.getReason().getRightEntity());
        insertVerb(kb, rule.getReason().getVerb());
        insertFact(kb, rule.getReason());

        // The rule is true, so the fact must be true to.
        if (rule.getReason().getIsTrue() > 0)
        {
            rule.getFact().setIsTrue(1.0);
        }

        insertEntity(kb, rule.getFact().getLeftEntity());
        insertEntity(kb, rule.getFact().getRightEntity());
        insertVerb(kb, rule.getFact().getVerb());
        insertFact(kb, rule.getFact());

        insertRule(kb, rule);
    }
    catch (obelisk::ParserException& exception)
    {
        throw;
    }
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
            insertFact(kb, fact, true);
        }
        catch (obelisk::ParserException& exception)
        {
            throw;
        }

        kb->checkRule(fact);
    }
}

void obelisk::Parser::insertEntity(std::unique_ptr<obelisk::KnowledgeBase>& kb,
    obelisk::Entity& entity)
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
            throw obelisk::ParserException(
                "entity could not be inserted into the database");
        }
    }
}

void obelisk::Parser::insertVerb(std::unique_ptr<obelisk::KnowledgeBase>& kb,
    obelisk::Verb& verb)
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
            throw obelisk::ParserException(
                "verb could not be inserted into the database");
        }
    }
}

void obelisk::Parser::insertAction(std::unique_ptr<obelisk::KnowledgeBase>& kb,
    obelisk::Action& action)
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
            throw obelisk::ParserException(
                "action could not be inserted into the database");
        }
    }
}

void obelisk::Parser::insertFact(std::unique_ptr<obelisk::KnowledgeBase>& kb,
    obelisk::Fact& fact,
    bool updateIsTrue)
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
            throw obelisk::ParserException(
                "fact could not be inserted into the database");
        }
        else
        {
            if (updateIsTrue)
            {
                fact.setIsTrue(1.0);
                kb->updateIsTrue(fact);
            }
        }
    }
}

void obelisk::Parser::insertSuggestAction(
    std::unique_ptr<obelisk::KnowledgeBase>& kb,
    obelisk::SuggestAction& suggestAction)
{
    std::vector<obelisk::SuggestAction> suggestActions {suggestAction};
    kb->addSuggestActions(suggestActions);
    suggestAction = std::move(suggestActions.front());

    // the id was not inserted, so check if it exists in the database
    if (suggestAction.getId() == 0)
    {
        kb->getSuggestAction(suggestAction);
        if (suggestAction.getId() == 0)
        {
            throw obelisk::ParserException(
                "suggest_action could not be inserted into the database");
        }
    }
}

void obelisk::Parser::insertRule(std::unique_ptr<obelisk::KnowledgeBase>& kb,
    obelisk::Rule& rule)
{
    std::vector<obelisk::Rule> rules {rule};
    kb->addRules(rules);
    rule = std::move(rules.front());

    // the id was not inserted, so check if it exists in the database
    if (rule.getId() == 0)
    {
        kb->getRule(rule);
        if (rule.getId() == 0)
        {
            throw obelisk::ParserException(
                "rule could not be inserted into the database");
        }
    }
}
