#include "obelisk.h"
#include "obelisk_wrapper.h"

#include <string.h>

extern "C"
{
    CObelisk* create_obelisk(const char* filename)
    {
        obelisk::Obelisk* obelisk = new obelisk::Obelisk(filename);
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

    double call_obelisk_query(CObelisk* p_obelisk,
        const char* left_entity,
        const char* verb,
        const char* right_entity)
    {
        obelisk::Obelisk* obelisk
            = reinterpret_cast<obelisk::Obelisk*>(p_obelisk);
        return obelisk->query(std::string(left_entity),
            std::string(verb),
            std::string(right_entity));
    }

    void destroy_obelisk(CObelisk* p_obelisk)
    {
        obelisk::Obelisk* obelisk
            = reinterpret_cast<obelisk::Obelisk*>(p_obelisk);
        delete obelisk;
    }
};
