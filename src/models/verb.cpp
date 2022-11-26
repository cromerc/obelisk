#include "models/verb.h"

#include <iostream>

const char* obelisk::Verb::createTable()
{
    return R"(
        CREATE TABLE "verb" (
            "id"   INTEGER NOT NULL UNIQUE,
            "name" TEXT NOT NULL CHECK(trim(name) != "") UNIQUE,
            PRIMARY KEY("id" AUTOINCREMENT)
        );
    )";
}

obelisk::Verb obelisk::Verb::selectVerb(sqlite3* dbConnection, std::string name)
{
    // TODO: check if database is open

    sqlite3_stmt* ppStmt = nullptr;
    const char* pzTail   = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "SELECT id, name FROM verb WHERE name=?;",
        -1,
        &ppStmt,
        &pzTail);
    if (result != SQLITE_OK)
    {
        // TODO: something went wrong throw an error
    }

    if (pzTail != nullptr)
    {
        // TODO: Something was not used... throw an error
    }

    result = sqlite3_bind_text(ppStmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    if (result != SQLITE_OK)
    {
        // TODO: Something is wrong... throw an error
    }

    result = sqlite3_step(ppStmt);
    if (result != SQLITE_DONE)
    {
        // TODO: Something is wrong... throw an error
    }

    if (result == SQLITE_ROW)
    {
        auto id = sqlite3_column_int(ppStmt, 0);
        std::string name((char*) sqlite3_column_text(ppStmt, 1));

        result = sqlite3_finalize(ppStmt);
        if (result != SQLITE_OK)
        {
            // TODO: Something is wrong... throw an error
        }
        return Verb(id, name);
    }
    else
    {
        result = sqlite3_finalize(ppStmt);
        if (result != SQLITE_OK)
        {
            // TODO: Something is wrong... throw an error
        }
        return Verb();
    }
}

int obelisk::Verb::insertVerb(sqlite3* dbConnection)
{
    // TODO: make sure database is open

    if (selectVerb(dbConnection, getName()).getId() != 0)
    {
        // TODO: Verb is already in database, throw an error? Or just skip it?
        return -1;
    }

    sqlite3_stmt* ppStmt = nullptr;
    const char* pzTail   = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "INSERT INTO verb (name) VALUES (?);",
        -1,
        &ppStmt,
        &pzTail);
    if (result != SQLITE_OK)
    {
        // TODO: something went wrong throw an error
    }

    if (pzTail != nullptr)
    {
        // TODO: Something was not used... throw an error
    }

    result
        = sqlite3_bind_text(ppStmt, 1, getName().c_str(), -1, SQLITE_TRANSIENT);
    if (result != SQLITE_OK)
    {
        // TODO: Something is wrong... throw an error
    }

    result = sqlite3_step(ppStmt);
    if (result != SQLITE_DONE)
    {
        // TODO: Something is wrong... throw an error
    }

    setId((int) sqlite3_last_insert_rowid(dbConnection));

    result = sqlite3_finalize(ppStmt);
    if (result != SQLITE_OK)
    {
        // TODO: Something is wrong... throw an error
    }

    return 0;
}

int& obelisk::Verb::getId()
{
    return id_;
}

void obelisk::Verb::setId(int id)
{
    id_ = id;
}

std::string& obelisk::Verb::getName()
{
    return name_;
}

void obelisk::Verb::setName(std::string name)
{
    name_ = name;
}
