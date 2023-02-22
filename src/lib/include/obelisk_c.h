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
     * @param[in] filename The obelisk KnowledgeBase file to use.
     * @return CObelisk* Returns an obelisk object.
     */
    extern CObelisk* obelisk_open(const char* filename);

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
     * @brief Query the obelisk KnowledgeBase to see if a Fact is true or false.
     *
     * @param[in] obelisk The obelisk object.
     * @param[in] left_entity The left entity.
     * @param[in] verb The verb.
     * @param[in] right_entity The right entity.
     * @return double Returns whether the Fact is true or false.
     */
    extern double obelisk_query(CObelisk* obelisk,
        const char* left_entity,
        const char* verb,
        const char* right_entity);

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
