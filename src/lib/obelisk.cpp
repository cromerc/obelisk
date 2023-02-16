#include "include/obelisk.h"
#include "version.h"

// TODO: Move the models to the library then link the compiler to the library

std::string obelisk::Obelisk::getVersion()
{
    return obelisk::version;
}

int obelisk::Obelisk::getLibVersion()
{
    return obelisk::soVersion;
}
