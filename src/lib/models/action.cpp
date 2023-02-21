#include "models/action.h"
#include "models/error.h"

const char* obelisk::Action::createTable()
{
    return R"(
        CREATE TABLE "action" (
            "id"   INTEGER NOT NULL UNIQUE,
            "name" TEXT NOT NULL CHECK(trim(name) != '') UNIQUE,
            PRIMARY KEY("id" AUTOINCREMENT)
        );
    )";
}

void obelisk::Action::selectByName(sqlite3* dbConnection)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "SELECT id, name FROM action WHERE name=?",
        -1,
        &ppStmt,
        nullptr);

    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }

    result = sqlite3_bind_text(ppStmt, 1, getName().c_str(), -1, SQLITE_STATIC);
    switch (result)
    {
        case SQLITE_OK :
            break;
        case SQLITE_TOOBIG :
            throw obelisk::DatabaseSizeException();
            break;
        case SQLITE_RANGE :
            throw obelisk::DatabaseRangeException();
            break;
        case SQLITE_NOMEM :
            throw obelisk::DatabaseMemoryException();
            break;
        default :
            throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
            break;
    }

    result = sqlite3_step(ppStmt);
    switch (result)
    {
        case SQLITE_DONE :
            // no rows in the database
            break;
        case SQLITE_ROW :
            setId(sqlite3_column_int(ppStmt, 0));
            setName((char*) sqlite3_column_text(ppStmt, 1));
            break;
        case SQLITE_BUSY :
            throw obelisk::DatabaseBusyException();
            break;
        case SQLITE_MISUSE :
            throw obelisk::DatabaseMisuseException();
            break;
        default :
            throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
            break;
    }

    result = sqlite3_finalize(ppStmt);

    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }
}

void obelisk::Action::insert(sqlite3* dbConnection)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "INSERT INTO action (name) VALUES (?)",
        -1,
        &ppStmt,
        nullptr);
    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }

    result
        = sqlite3_bind_text(ppStmt, 1, getName().c_str(), -1, SQLITE_TRANSIENT);
    switch (result)
    {
        case SQLITE_OK :
            break;
        case SQLITE_TOOBIG :
            throw obelisk::DatabaseSizeException();
            break;
        case SQLITE_RANGE :
            throw obelisk::DatabaseRangeException();
            break;
        case SQLITE_NOMEM :
            throw obelisk::DatabaseMemoryException();
            break;
        default :
            throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
            break;
    }

    result = sqlite3_step(ppStmt);
    switch (result)
    {
        case SQLITE_DONE :
            setId((int) sqlite3_last_insert_rowid(dbConnection));
            sqlite3_set_last_insert_rowid(dbConnection, 0);
            break;
        case SQLITE_CONSTRAINT :
            throw obelisk::DatabaseConstraintException(
                sqlite3_errmsg(dbConnection));
        case SQLITE_BUSY :
            throw obelisk::DatabaseBusyException();
            break;
        case SQLITE_MISUSE :
            throw obelisk::DatabaseMisuseException();
            break;
        default :
            throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
            break;
    }

    result = sqlite3_finalize(ppStmt);
    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }
}

int& obelisk::Action::getId()
{
    return id_;
}

void obelisk::Action::setId(int id)
{
    id_ = id;
}

std::string& obelisk::Action::getName()
{
    return name_;
}

void obelisk::Action::setName(std::string name)
{
    name_ = name;
}
