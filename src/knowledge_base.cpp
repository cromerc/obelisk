#include "knowledge_base.h"

#include <iostream>

const std::string obelisk::Sql::create_facts_table
    = "CREATE TABLE fact (id INT PRIMARY KEY NOT NULL);";

obelisk::KnowledgeBase::KnowledgeBase(const char* filename)
{
    KnowledgeBase(filename, DEFAULT_FLAGS);
}

obelisk::KnowledgeBase::KnowledgeBase(const char* filename, int flags)
{
    filename_ = std::move(filename);
    flags_    = std::move(flags);

    auto result = sqlite3_open_v2(filename, &dbConnection_, flags, NULL);
    if (result != SQLITE_OK)
    {
        logSqliteError(result);
    }

    char* tmp;
    result = sqlite3_exec(dbConnection_,
        obelisk::Sql::create_facts_table.c_str(),
        NULL,
        NULL,
        &tmp);
    if (tmp)
    {
        std::string errmsg(tmp);
        throw obelisk::KnowledgeBaseException(errmsg);
    }
}

obelisk::KnowledgeBase::~KnowledgeBase()
{
    sqlite3_close_v2(dbConnection_);
}

// TODO: log files?
void obelisk::KnowledgeBase::logSqliteError(int result)
{
    std::cout << sqlite3_errstr(result) << std::endl;
}

void obelisk::KnowledgeBase::getFloat(float* result1,
    float* result2,
    double var)
{
    *result1 = (float) var;
    *result2 = (float) (var - (double) *result1);
}

void obelisk::KnowledgeBase::getDouble(double* result, float var1, float var2)
{
    *result = (double) ((double) var2 + (double) var1);
}
