#include "knowledge_base.h"
#include "models/error.h"

#include <cstring>
#include <filesystem>
#include <iostream>
#include <string>

obelisk::KnowledgeBase::KnowledgeBase(const char* filename, int flags)
{
    filename_ = std::move(filename);
    flags_    = std::move(flags);

    std::filesystem::path path {filename};
    auto dbExists = std::filesystem::exists(path);

    auto result = sqlite3_open_v2(filename, &dbConnection_, flags, NULL);
    if (result != SQLITE_OK)
    {
        throw new KnowledgeBaseException("database could not be opened");
    }

    enableForeignKeys();

    if (!dbExists)
    {
        createTable(obelisk::Action::createTable);
        createTable(obelisk::Entity::createTable);
        createTable(obelisk::Verb::createTable);
        createTable(obelisk::Fact::createTable);
        createTable(obelisk::Rule::createTable);
        createTable(obelisk::SuggestAction::createTable);
    }
}

obelisk::KnowledgeBase::~KnowledgeBase()
{
    if (dbConnection_)
    {
        sqlite3_close_v2(dbConnection_);
    }
}

void obelisk::KnowledgeBase::enableForeignKeys()
{
    char* errmsg;
    int result = sqlite3_exec(dbConnection_,
        "PRAGMA foreign_keys = ON;",
        NULL,
        NULL,
        &errmsg);
    if (result != SQLITE_OK)
    {
        if (errmsg)
        {
            throw obelisk::KnowledgeBaseException(errmsg);
        }
        else
        {
            throw obelisk::KnowledgeBaseException();
        }
    }
}

void obelisk::KnowledgeBase::createTable(std::function<const char*()> function)
{
    char* errmsg;
    int result = sqlite3_exec(dbConnection_, function(), NULL, NULL, &errmsg);
    if (result != SQLITE_OK)
    {
        if (errmsg)
        {
            throw obelisk::KnowledgeBaseException(errmsg);
        }
        else
        {
            throw obelisk::KnowledgeBaseException();
        }
    }
}

void obelisk::KnowledgeBase::addEntities(std::vector<obelisk::Entity>& entities)
{
    for (auto& entity : entities)
    {
        try
        {
            entity.insert(dbConnection_);
        }
        catch (obelisk::DatabaseConstraintException& exception)
        {
            // ignore unique constraint error
            if (std::strcmp(exception.what(),
                    "UNIQUE constraint failed: entity.name")
                != 0)
            {
                throw;
            }
        }
    }
}

void obelisk::KnowledgeBase::addVerbs(std::vector<obelisk::Verb>& verbs)
{
    for (auto& verb : verbs)
    {
        try
        {
            verb.insert(dbConnection_);
        }
        catch (obelisk::DatabaseConstraintException& exception)
        {
            // ignore unique constraint error
            if (std::strcmp(exception.what(),
                    "UNIQUE constraint failed: verb.name")
                != 0)
            {
                throw;
            }
        }
    }
}

void obelisk::KnowledgeBase::addActions(std::vector<obelisk::Action>& actions)
{
    for (auto& action : actions)
    {
        try
        {
            action.insert(dbConnection_);
        }
        catch (obelisk::DatabaseConstraintException& exception)
        {
            // ignore unique constraint error
            if (std::strcmp(exception.what(),
                    "UNIQUE constraint failed: action.name")
                != 0)
            {
                throw;
            }
        }
    }
}

void obelisk::KnowledgeBase::addFacts(std::vector<obelisk::Fact>& facts)
{
    for (auto& fact : facts)
    {
        try
        {
            fact.insert(dbConnection_);
        }
        catch (obelisk::DatabaseConstraintException& exception)
        {
            // ignore unique constraint error
            if (std::strcmp(exception.what(),
                    "UNIQUE constraint failed: fact.left_entity, fact.right_entity, fact.verb")
                != 0)
            {
                throw;
            }
        }
    }
}

void obelisk::KnowledgeBase::addSuggestActions(
    std::vector<obelisk::SuggestAction>& suggestActions)
{
    for (auto& suggestAction : suggestActions)
    {
        try
        {
            suggestAction.insert(dbConnection_);
        }
        catch (obelisk::DatabaseConstraintException& exception)
        {
            // ignore unique constraint error
            if (std::strcmp(exception.what(),
                    "UNIQUE constraint failed: suggest_action.fact, suggest_action.true_action, suggest_action.false_action")
                != 0)
            {
                throw;
            }
        }
    }
}

void obelisk::KnowledgeBase::addRules(std::vector<obelisk::Rule>& rules)
{
    for (auto& rule : rules)
    {
        try
        {
            rule.insert(dbConnection_);
        }
        catch (obelisk::DatabaseConstraintException& exception)
        {
            // ignore unique constraint error
            if (std::strcmp(exception.what(),
                    "UNIQUE constraint failed: rule.fact, rule.reason")
                != 0)
            {
                throw;
            }
        }
    }
}

void obelisk::KnowledgeBase::getEntity(obelisk::Entity& entity)
{
    entity.selectByName(dbConnection_);
}

void obelisk::KnowledgeBase::getVerb(obelisk::Verb& verb)
{
    verb.selectByName(dbConnection_);
}

void obelisk::KnowledgeBase::getAction(obelisk::Action& action)
{
    action.selectByName(dbConnection_);
}

void obelisk::KnowledgeBase::getFact(obelisk::Fact& fact)
{
    fact.selectById(dbConnection_);
}

void obelisk::KnowledgeBase::getSuggestAction(
    obelisk::SuggestAction& suggestAction)
{
    suggestAction.selectById(dbConnection_);
}

void obelisk::KnowledgeBase::getRule(obelisk::Rule& rule)
{
    rule.selectById(dbConnection_);
}

void obelisk::KnowledgeBase::checkRule(obelisk::Fact& fact)
{
    std::vector<obelisk::Rule> rules;
    obelisk::Rule::selectByReason(dbConnection_, fact.getId(), rules);
    for (auto& rule : rules)
    {
        auto reason = rule.getReason();
        getFact(reason);
        if (reason.getIsTrue() > 0)
        {
            auto updateFact = rule.getFact();
            updateFact.setIsTrue(1.0);
            updateFact.updateIsTrue(dbConnection_);
        }
    }
}

void obelisk::KnowledgeBase::updateIsTrue(obelisk::Fact& fact)
{
    fact.updateIsTrue(dbConnection_);
}

void obelisk::KnowledgeBase::queryFact(obelisk::Fact& fact)
{
    fact.selectByName(dbConnection_);
}

void obelisk::KnowledgeBase::querySuggestAction(obelisk::Fact& fact,
    obelisk::Action& action)
{
    fact.selectActionByFact(dbConnection_, action);
}

void obelisk::KnowledgeBase::getFloat(float& result1,
    float& result2,
    double var)
{
    result1 = (float) var;
    result2 = (float) (var - (double) result1);
}

void obelisk::KnowledgeBase::getDouble(double& result, float var1, float var2)
{
    result = (double) ((double) var2 + (double) var1);
}
