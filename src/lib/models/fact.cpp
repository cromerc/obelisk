#include "models/error.h"
#include "models/fact.h"

const char* obelisk::Fact::createTable()
{
    return R"(
        CREATE TABLE "fact" (
            "id"           INTEGER NOT NULL UNIQUE,
            "left_entity"  INTEGER NOT NULL,
            "verb"         INTEGER NOT NULL,
            "right_entity" INTEGER NOT NULL,
            "is_true"      INTEGER NOT NULL DEFAULT 0,
            PRIMARY KEY("id" AUTOINCREMENT),
            UNIQUE("left_entity", "right_entity", "verb")
            FOREIGN KEY("verb") REFERENCES "verb"("id") ON DELETE RESTRICT,
            FOREIGN KEY("right_entity") REFERENCES "entity"("id") ON DELETE RESTRICT,
            FOREIGN KEY("left_entity") REFERENCES "entity"("id") ON DELETE RESTRICT
        );
    )";
}

void obelisk::Fact::selectById(sqlite3* dbConnection)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    const char* query;
    if (getId() == 0)
    {
        query
            = "SELECT id, left_entity, right_entity, verb, is_true FROM fact WHERE (left_entity=? AND right_entity=? AND verb=?)";
    }
    else
    {
        query = "SELECT id, left_entity, right_entity, verb, is_true FROM fact WHERE (id=?)";
    }
    auto result = sqlite3_prepare_v2(dbConnection, query, -1, &ppStmt, nullptr);
    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }

    if (getId() == 0)
    {
        result = sqlite3_bind_int(ppStmt, 1, getLeftEntity().getId());
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

        result = sqlite3_bind_int(ppStmt, 2, getRightEntity().getId());
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

        result = sqlite3_bind_int(ppStmt, 3, getVerb().getId());
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
    }
    else
    {
        result = sqlite3_bind_int(ppStmt, 1, getId());
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
    }

    result = sqlite3_step(ppStmt);
    switch (result)
    {
        case SQLITE_DONE :
            // no rows in the database
            break;
        case SQLITE_ROW :
            setId(sqlite3_column_int(ppStmt, 0));
            getLeftEntity().setId(sqlite3_column_int(ppStmt, 1));
            getRightEntity().setId(sqlite3_column_int(ppStmt, 2));
            getVerb().setId(sqlite3_column_int(ppStmt, 3));
            setIsTrue(sqlite3_column_int(ppStmt, 4));
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

void obelisk::Fact::insert(sqlite3* dbConnection)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "INSERT INTO fact (left_entity, right_entity, verb, is_true) VALUES (?, ?, ?, ?)",
        -1,
        &ppStmt,
        nullptr);
    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }

    result = sqlite3_bind_int(ppStmt, 1, getLeftEntity().getId());
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

    result = sqlite3_bind_int(ppStmt, 2, getRightEntity().getId());
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

    result = sqlite3_bind_int(ppStmt, 3, getVerb().getId());
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

    result = sqlite3_bind_int(ppStmt, 4, getIsTrue());
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

void obelisk::Fact::updateIsTrue(sqlite3* dbConnection)
{
    if (dbConnection == nullptr)
    {
        throw obelisk::DatabaseException("database isn't open");
    }

    sqlite3_stmt* ppStmt = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection, "UPDATE fact SET is_true=? WHERE id=?", -1, &ppStmt, nullptr);
    if (result != SQLITE_OK)
    {
        throw obelisk::DatabaseException(sqlite3_errmsg(dbConnection));
    }

    result = sqlite3_bind_int(ppStmt, 1, getIsTrue());
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

    result = sqlite3_bind_int(ppStmt, 2, getId());
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
            // Row updated
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

int& obelisk::Fact::getId()
{
    return id_;
}

void obelisk::Fact::setId(int id)
{
    id_ = id;
}

obelisk::Entity& obelisk::Fact::getLeftEntity()
{
    return leftEntity_;
}

void obelisk::Fact::setLeftEntity(obelisk::Entity leftEntity)
{
    leftEntity_ = leftEntity;
}

obelisk::Entity& obelisk::Fact::getRightEntity()
{
    return rightEntity_;
}

void obelisk::Fact::setRightEntity(obelisk::Entity rightEntity)
{
    rightEntity_ = rightEntity;
}

obelisk::Verb& obelisk::Fact::getVerb()
{
    return verb_;
}

void obelisk::Fact::setVerb(obelisk::Verb verb)
{
    verb_ = verb;
}

bool& obelisk::Fact::getIsTrue()
{
    return isTrue_;
}

void obelisk::Fact::setIsTrue(bool isTrue)
{
    isTrue_ = isTrue;
}
