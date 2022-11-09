#include "models/verb.h"

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

int obelisk::Verb::getId()
{
    return id_;
}

void obelisk::Verb::setId(int id)
{
    id_ = id;
}

std::string obelisk::Verb::getName()
{
    return name_;
}

void obelisk::Verb::setName(std::string name)
{
    name_ = name;
}
