#include "models/error.h"
#include "models/suggest_action.h"

const char* obelisk::SuggestAction::createTable()
{
    return R"(
        CREATE TABLE "suggest_action" (
            "id"           INTEGER NOT NULL UNIQUE,
            "fact"         INTEGER NOT NULL,
            "true_action"  INTEGER NOT NULL,
            "false_action" INTEGER NOT NULL,
            PRIMARY KEY("id" AUTOINCREMENT),
            UNIQUE("fact", "true_action", "false_action"),
            FOREIGN KEY("fact") REFERENCES "fact"("id") ON DELETE RESTRICT,
            FOREIGN KEY("true_action") REFERENCES "action"("id") ON DELETE RESTRICT,
            FOREIGN KEY("false_action") REFERENCES "action"("id") ON DELETE RESTRICT
        );
    )";
}

void obelisk::SuggestAction::selectById(sqlite3* dbConnection)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "SELECT id, fact, true_action, false_action FROM suggest_action WHERE (fact=? AND true_action=? AND false_action=?)",
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

    result = sqlite3_bind_int(ppStmt, 2, getTrueAction().getId());
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

    result = sqlite3_bind_int(ppStmt, 3, getFalseAction().getId());
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
            getTrueAction().setId(sqlite3_column_int(ppStmt, 2));
            getFalseAction().setId(sqlite3_column_int(ppStmt, 3));
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

void obelisk::SuggestAction::insert(sqlite3* dbConnection)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "INSERT INTO suggest_action (fact, true_action, false_action) VALUES (?, ?, ?)",
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

    result = sqlite3_bind_int(ppStmt, 2, getTrueAction().getId());
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

    result = sqlite3_bind_int(ppStmt, 3, getFalseAction().getId());
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
            throw obelisk::DatabaseConstraintException(sqlite3_errmsg(dbConnection));
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

int& obelisk::SuggestAction::getId()
{
    return id_;
}

void obelisk::SuggestAction::setId(int id)
{
    id_ = id;
}

obelisk::Fact& obelisk::SuggestAction::getFact()
{
    return fact_;
}

void obelisk::SuggestAction::setFact(obelisk::Fact fact)
{
    fact_ = fact;
}

obelisk::Action& obelisk::SuggestAction::getTrueAction()
{
    return trueAction_;
}

void obelisk::SuggestAction::setTrueAction(obelisk::Action trueAction)
{
    trueAction_ = trueAction;
}

obelisk::Action& obelisk::SuggestAction::getFalseAction()
{
    return falseAction_;
}

void obelisk::SuggestAction::setFalseAction(obelisk::Action falseAction)
{
    falseAction_ = falseAction;
}
