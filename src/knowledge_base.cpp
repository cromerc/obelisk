#include "knowledge_base.h"
#include "models/action.h"
#include "models/entity.h"
#include "models/error.h"
#include "models/fact.h"
#include "models/rule.h"
#include "models/suggest_action.h"
#include "models/verb.h"

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

/**
 * @brief Enable foreign key functionality in the open database.
 *
 * This must always be done when the connection is opened or it will not
 * enforce the foreign key constraints.
 */
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
            entity.insertEntity(dbConnection_);
        }
        catch (obelisk::DatabaseException::ConstraintException& exception)
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
            verb.insertVerb(dbConnection_);
        }
        catch (obelisk::DatabaseException::ConstraintException& exception)
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

void obelisk::KnowledgeBase::addFacts(std::vector<obelisk::Fact>& facts)
{
    for (auto& fact : facts)
    {
        try
        {
            fact.insertFact(dbConnection_);
        }
        catch (obelisk::DatabaseException::ConstraintException& exception)
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

void obelisk::KnowledgeBase::getEntity(obelisk::Entity& entity)
{
    entity.selectEntity(dbConnection_);
}

void obelisk::KnowledgeBase::getVerb(obelisk::Verb& verb)
{
    verb.selectVerb(dbConnection_);
}

void obelisk::KnowledgeBase::getFact(obelisk::Fact& fact)
{
    fact.selectFact(dbConnection_);
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
