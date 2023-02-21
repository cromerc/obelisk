#include "include/obelisk.h"
#include "version.h"

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
}

std::string obelisk::Obelisk::query_action(const std::string& leftEntity,
    const std::string& verb,
    const std::string& rightEntity)
{
}
