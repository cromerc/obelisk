#ifndef OBELISK_INCLUDE_OBELISK_PROGRAM_H
#define OBELISK_INCLUDE_OBELISK_PROGRAM_H

/**
 * @brief Struct wrapper around Obelisk class.
 *
 */
typedef struct CObelisk CObelisk;

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Create an obelisk object.
     *
     * @return CObelisk* Returns an obelisk object.
     */
    extern CObelisk* obelisk_open();

    /**
     * @brief Delete an obelisk object.
     *
     * @param[in] obelisk The obelisk object.
     */
    extern void obelisk_close(CObelisk* obelisk);

    /**
     * @brief Get the obelisk version.
     *
     * @param[in] obelisk The obelisk object.
     * @return const char* Returns a string containing the version. This must be
     * freed by the caller.
     */
    extern char* obelisk_get_version(CObelisk* obelisk);

    /**
     * @brief Get the obelisk library so version.
     *
     * @param[in] obelisk The obelisk object.
     * @return int Returns the so version.
     */
    extern int obelisk_get_lib_version(CObelisk* obelisk);

#ifdef __cplusplus
};
#endif

#endif
