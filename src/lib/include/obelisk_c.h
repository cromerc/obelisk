#ifndef OBELISK_INCLUDE_OBELISK_PROGRAM_H
#define OBELISK_INCLUDE_OBELISK_PROGRAM_H

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Get the obelisk version.
     *
     * @return const char* Returns a string containing the version. This must be
     * freed by the caller.
     */
    extern const char* obelisk_get_version();

    /**
     * @brief Get the obelisk library so version.
     *
     * @return int Returns the so version.
     */
    extern int obelisk_get_lib_version();

#ifdef __cplusplus
};
#endif

#endif
