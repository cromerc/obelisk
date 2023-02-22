#include "obelisk.h"
#include "obelisk_wrapper.h"

#include <string.h>

extern "C"
{
    CObelisk* create_obelisk()
    {
        obelisk::Obelisk* obelisk = new obelisk::Obelisk();
        return reinterpret_cast<CObelisk*>(obelisk);
    }

    char* call_obelisk_getVersion(CObelisk* p_obelisk)
    {
        obelisk::Obelisk* obelisk
            = reinterpret_cast<obelisk::Obelisk*>(p_obelisk);
        auto version = strdup(obelisk->getVersion().c_str());
        return version;
    }

    int call_obelisk_getLibVersion(CObelisk* p_obelisk)
    {
        obelisk::Obelisk* obelisk
            = reinterpret_cast<obelisk::Obelisk*>(p_obelisk);
        return obelisk->getLibVersion();
    }

    void destroy_obelisk(CObelisk* p_obelisk)
    {
        obelisk::Obelisk* obelisk
            = reinterpret_cast<obelisk::Obelisk*>(p_obelisk);
        delete obelisk;
    }
};
