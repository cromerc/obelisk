#include "obelisk_c.h"
#include "obelisk_wrapper.h"

#include <stdlib.h>
#include <string.h>

CObelisk* obelisk_open()
{
    return create_obelisk();
}

void obelisk_close(CObelisk* obelisk)
{
    destroy_obelisk(obelisk);
}

char* obelisk_get_version(CObelisk* obelisk)
{
    return call_obelisk_getVersion(obelisk);
}

int obelisk_get_lib_version(CObelisk* obelisk)
{
    return call_obelisk_getLibVersion(obelisk);
}
