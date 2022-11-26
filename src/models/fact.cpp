#include "models/fact.h"

const char* obelisk::Fact::createTable()
{
    return R"(
        CREATE TABLE "fact" (
            "id"           INTEGER NOT NULL UNIQUE,
            "left_entity"  INTEGER NOT NULL,
            "right_entity" INTEGER NOT NULL,
            "verb"         INTEGER NOT NULL,
            PRIMARY KEY("id" AUTOINCREMENT),
            FOREIGN KEY("verb") REFERENCES "verb"("id") ON DELETE RESTRICT,
            FOREIGN KEY("right_entity") REFERENCES "entity"("id") ON DELETE RESTRICT,
            FOREIGN KEY("left_entity") REFERENCES "entity"("id") ON DELETE RESTRICT
        );
    )";
}

obelisk::Fact obelisk::Fact::selectFact(sqlite3* dbConnection,
    int idLeftEntity,
    int idRightEntity,
    int idVerb)
{
    // TODO: check if database is open

    sqlite3_stmt* ppStmt = nullptr;
    const char* pzTail   = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "SELECT id, left_entity, right_entity, verb FROM fact WHERE (left_entity=? AND right_entity=? AND verb=?);",
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

    result = sqlite3_bind_int(ppStmt, 1, getLeftEntity().getId());
    if (result != SQLITE_OK)
    {
        // TODO: Something is wrong... throw an error
    }

    result = sqlite3_bind_int(ppStmt, 2, getRightEntity().getId());
    if (result != SQLITE_OK)
    {
        // TODO: Something is wrong... throw an error
    }

    result = sqlite3_bind_int(ppStmt, 3, getVerb().getId());
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
        auto id          = sqlite3_column_int(ppStmt, 0);
        auto leftEntity  = sqlite3_column_int(ppStmt, 1);
        auto rightEntity = sqlite3_column_int(ppStmt, 2);
        auto verb        = sqlite3_column_int(ppStmt, 3);

        result = sqlite3_finalize(ppStmt);
        if (result != SQLITE_OK)
        {
            // TODO: Something is wrong... throw an error
        }
        return Fact(id, leftEntity, rightEntity, verb);
    }
    else
    {
        result = sqlite3_finalize(ppStmt);
        if (result != SQLITE_OK)
        {
            // TODO: Something is wrong... throw an error
        }
        return Fact();
    }
}

int obelisk::Fact::insertFact(sqlite3* dbConnection)
{
    // TODO: make sure database is open

    // check if the fact id exists, based on the ids of the entities and verb
    if (selectFact(dbConnection,
            getLeftEntity().getId(),
            getRightEntity().getId(),
            getVerb().getId())
            .getId()
        != 0)
    {
        // TODO: Verb is already in database, throw an error? Or just skip it?
        return -1;
    }

    // TODO: verify that verbId, leftEntityId, and rightEntityId are not 0

    sqlite3_stmt* ppStmt = nullptr;
    const char* pzTail   = nullptr;

    auto result = sqlite3_prepare_v2(dbConnection,
        "INSERT INTO fact (left_entity, right_entity, verb) VALUES (?, ?, ?);",
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

    result = sqlite3_bind_int(ppStmt, 1, getLeftEntity().getId());
    if (result != SQLITE_OK)
    {
        // TODO: Something is wrong... throw an error
    }

    result = sqlite3_bind_int(ppStmt, 2, getRightEntity().getId());
    if (result != SQLITE_OK)
    {
        // TODO: Something is wrong... throw an error
    }

    result = sqlite3_bind_int(ppStmt, 3, getVerb().getId());
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
