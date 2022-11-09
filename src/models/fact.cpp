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

int obelisk::Fact::getId()
{
    return id_;
}

void obelisk::Fact::setId(int id)
{
    id_ = id;
}

obelisk::Entity obelisk::Fact::getLeftEntity()
{
    return leftEntity_;
}

void obelisk::Fact::setLeftEntity(obelisk::Entity leftEntity)
{
    leftEntity_ = leftEntity;
}

obelisk::Entity obelisk::Fact::getRightEntity()
{
    return rightEntity_;
}

void obelisk::Fact::setRightEntity(obelisk::Entity rightEntity)
{
    rightEntity_ = rightEntity;
}

obelisk::Verb obelisk::Fact::getVerb()
{
    return verb_;
}

void obelisk::Fact::setVerb(obelisk::Verb verb)
{
    verb_ = verb;
}
