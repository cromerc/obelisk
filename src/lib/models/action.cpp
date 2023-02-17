#include "models/action.h"

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
