#include "models/rule.h"

const char* obelisk::Rule::createTable()
{
    return R"(
        CREATE TABLE "rule" (
            "id"     INTEGER NOT NULL UNIQUE,
            "fact"   INTEGER NOT NULL,
            "reason" INTEGER NOT NULL CHECK("reason" != "fact"),
            PRIMARY KEY("id" AUTOINCREMENT),
            FOREIGN KEY("fact") REFERENCES "fact"("id") ON DELETE RESTRICT,
            FOREIGN KEY("reason") REFERENCES "fact"("id") ON DELETE RESTRICT
        );
    )";
}

int obelisk::Rule::getId()
{
    return id_;
}

void obelisk::Rule::setId(int id)
{
    id_ = id;
}

obelisk::Fact obelisk::Rule::getFact()
{
    return fact_;
}

void obelisk::Rule::setFact(obelisk::Fact fact)
{
    fact_ = fact;
}

obelisk::Fact obelisk::Rule::getReason()
{
    return reason_;
}

void obelisk::Rule::setReason(obelisk::Fact reason)
{
    reason_ = reason;
}
