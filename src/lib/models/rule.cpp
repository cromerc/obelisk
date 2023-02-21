#include "models/error.h"
#include "models/rule.h"

const char* obelisk::Rule::createTable()
{
    return R"(
        CREATE TABLE "rule" (
            "id"     INTEGER NOT NULL UNIQUE,
            "fact"   INTEGER NOT NULL,
            "reason" INTEGER NOT NULL CHECK("reason" != "fact"),
            PRIMARY KEY("id" AUTOINCREMENT),
            UNIQUE("fact", "reason"),
            FOREIGN KEY("fact") REFERENCES "fact"("id") ON DELETE RESTRICT,
            FOREIGN KEY("reason") REFERENCES "fact"("id") ON DELETE RESTRICT
        );
    )";
}

void obelisk::Rule::selectById(sqlite3* dbConnection)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "SELECT id, fact, reason FROM rule WHERE (fact=? AND reason=?)",
        -1,
        &ppStmt,
        nullptr);
    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }

    result = sqlite3_bind_int(ppStmt, 1, getFact().getId());
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

    result = sqlite3_bind_int(ppStmt, 2, getReason().getId());
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
            getFact().setId(sqlite3_column_int(ppStmt, 1));
            getReason().setId(sqlite3_column_int(ppStmt, 2));
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

void obelisk::Rule::insert(sqlite3* dbConnection)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "INSERT INTO rule (fact, reason) VALUES (?, ?)",
        -1,
        &ppStmt,
        nullptr);
    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }

    result = sqlite3_bind_int(ppStmt, 1, getFact().getId());
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

    result = sqlite3_bind_int(ppStmt, 2, getReason().getId());
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

void obelisk::Rule::selectByReason(sqlite3* dbConnection,
    int reasonId,
    std::vector<obelisk::Rule>& rules)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "SELECT id, fact, reason FROM rule WHERE (reason=?)",
        -1,
        &ppStmt,
        nullptr);
    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }

    result = sqlite3_bind_int(ppStmt, 1, reasonId);
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

    while ((result = sqlite3_step(ppStmt)) != SQLITE_DONE)
    {
        switch (result)
        {
            case SQLITE_ROW :
                rules.push_back(obelisk::Rule(sqlite3_column_int(ppStmt, 0),
                    obelisk::Fact(sqlite3_column_int(ppStmt, 1)),
                    obelisk::Fact(sqlite3_column_int(ppStmt, 2))));
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
    }

    result = sqlite3_finalize(ppStmt);
    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }
}

int& obelisk::Rule::getId()
{
    return id_;
}

void obelisk::Rule::setId(int id)
{
    id_ = id;
}

obelisk::Fact& obelisk::Rule::getFact()
{
    return fact_;
}

void obelisk::Rule::setFact(obelisk::Fact fact)
{
    fact_ = fact;
}

obelisk::Fact& obelisk::Rule::getReason()
{
    return reason_;
}

void obelisk::Rule::setReason(obelisk::Fact reason)
{
    reason_ = reason;
}
