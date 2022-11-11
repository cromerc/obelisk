#include "models/entity.h"

const char* obelisk::Entity::createTable()
{
    return R"(
        CREATE TABLE "entity" (
            "id"   INTEGER NOT NULL UNIQUE,
            "name" TEXT NOT NULL CHECK(trim(name) != '') UNIQUE,
            PRIMARY KEY("id" AUTOINCREMENT)
        );
    )";
}

int obelisk::Entity::getId()
{
    return id_;
}

void obelisk::Entity::setId(int id)
{
    id_ = id;
}

std::string obelisk::Entity::getName()
{
    return name_;
}

void obelisk::Entity::setName(std::string name)
{
    name_ = name;
}
