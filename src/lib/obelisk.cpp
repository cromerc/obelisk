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
