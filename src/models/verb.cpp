#include "models/verb.h"

obelisk::Verb::Verb()
{
}

obelisk::Verb::Verb(std::string verb)
{
    verb_ = verb;
}

obelisk::Verb::Verb(int id, std::string verb)
{
    id_   = id;
    verb_ = verb;
}

int obelisk::Verb::getId()
{
    return id_;
}

void obelisk::Verb::setId(int id)
{
    id_ = id;
}

std::string obelisk::Verb::getVerb()
{
    return verb_;
}

void obelisk::Verb::setVerb(std::string verb)
{
    verb_ = verb;
}
