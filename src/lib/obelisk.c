#include "obelisk_c.h"
#include "obelisk_wrapper.h"

#include <stdlib.h>
#include <string.h>

CObelisk* obelisk_open(const char* filename)
{
    return create_obelisk(filename);
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

double obelisk_query(CObelisk* obelisk,
    const char* left_entity,
    const char* verb,
    const char* right_entity)
{
    return call_obelisk_query(obelisk, left_entity, verb, right_entity);
}
