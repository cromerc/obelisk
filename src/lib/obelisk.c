#include "obelisk_c.h"
#include "obelisk_wrapper.h"

#include <stdlib.h>
#include <string.h>

const char* obelisk_get_version()
{
    CObelisk* obelisk = create_obelisk();
    size_t len        = strlen(call_obelisk_getVersion(obelisk)) + 1;
    char* version     = malloc(len);
    memcpy(version, call_obelisk_getVersion(obelisk), len);
    destroy_obelisk(obelisk);
    return version;
}

int obelisk_get_lib_version()
{
    CObelisk* obelisk = create_obelisk();
    int version       = call_obelisk_getLibVersion(obelisk);
    destroy_obelisk(obelisk);
    return version;
}
