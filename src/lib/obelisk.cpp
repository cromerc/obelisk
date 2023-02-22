#include "include/obelisk.h"
#include "version.h"

obelisk::Obelisk::Obelisk(std::string filename)
{
    kb_ = std::unique_ptr<obelisk::KnowledgeBase> {
        new obelisk::KnowledgeBase(filename.c_str())};
}

std::string obelisk::Obelisk::getVersion()
{
    return obelisk::version;
}

int obelisk::Obelisk::getLibVersion()
{
    return obelisk::soVersion;
}

double obelisk::Obelisk::query(const std::string& leftEntity,
    const std::string& verb,
    const std::string& rightEntity)
{
    obelisk::Fact fact = obelisk::Fact(obelisk::Entity(leftEntity),
        obelisk::Entity(rightEntity),
        obelisk::Verb(verb));

    kb_->queryFact(fact);

    return fact.getIsTrue();
}

std::string obelisk::Obelisk::query_action(const std::string& leftEntity,
    const std::string& verb,
    const std::string& rightEntity)
{
    return "yes";
}
