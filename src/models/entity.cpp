#include "models/entity.h"

obelisk::Entity::Entity()
{
}

obelisk::Entity::Entity(std::string name)
{
    name = name;
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
    name_ = name_;
}
