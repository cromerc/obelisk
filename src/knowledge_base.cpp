#include "knowledge_base.h"
#include "models/action.h"
#include "models/entity.h"
#include "models/fact.h"
#include "models/rule.h"
#include "models/suggest_action.h"
#include "models/verb.h"

#include <filesystem>
#include <iostream>

obelisk::KnowledgeBase::KnowledgeBase(const char* filename, int flags)
{
    filename_ = std::move(filename);
    flags_    = std::move(flags);

    std::filesystem::path path {filename};
    auto dbExists = std::filesystem::exists(path);

    auto result = sqlite3_open_v2(filename, &dbConnection_, flags, NULL);
    if (result != SQLITE_OK)
    {
        logSqliteError(result);
    }

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

void obelisk::KnowledgeBase::createTable(std::function<const char*()> function)
{
    char* tmp;
    auto result = sqlite3_exec(dbConnection_, function(), NULL, NULL, &tmp);
    if (result != SQLITE_OK)
    {
        logSqliteError(result);
        if (tmp)
        {
            std::string errmsg(tmp);
            throw obelisk::KnowledgeBaseException(errmsg);
        }
        else
        {
            throw obelisk::KnowledgeBaseException();
        }
    }
}

int obelisk::KnowledgeBase::addEntities(std::vector<obelisk::Entity>& entities)
{
    for (auto& entity : entities)
    {
        entity.insertEntity(dbConnection_);
    }
    return 0;
}

int obelisk::KnowledgeBase::addVerbs(std::vector<obelisk::Verb>& verbs)
{
    for (auto& verb : verbs)
    {
        verb.insertVerb(dbConnection_);
    }
    return 0;
}

int obelisk::KnowledgeBase::addFacts(std::vector<obelisk::Fact>& facts)
{
    for (auto& fact : facts)
    {
        fact.insertFact(dbConnection_);
    }
    return 0;
}

// TODO: log files?
void obelisk::KnowledgeBase::logSqliteError(int result)
{
    std::cout << sqlite3_errstr(result) << std::endl;
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
