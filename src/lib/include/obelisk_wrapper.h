#ifndef OBELISK_INCLUDE_OBELISK_WRAPPER_H
#define OBELISK_INCLUDE_OBELISK_WRAPPER_H

typedef struct CObelisk CObelisk;

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Create a obelisk object.
     *
     * @return CObelisk* Returns the obelisk object.
     */
    CObelisk *create_obelisk();

    /**
     * @brief Calls the obelisk method getVersion.
     *
     * @param[in] p_obelisk The obelisk object pointer.
     * @return const char* Returns the version. Must be freed by caller.
     */
    const char *call_obelisk_getVersion(CObelisk *p_obelisk);

    /**
     * @brief Calls the obelisk method getLibVersion.
     *
     * @param[in] p_obelisk The obelisk object pointer.
     * @return int Returns the library so version.
     */
    int call_obelisk_getLibVersion(CObelisk *p_obelisk);

    /**
     * @brief Delete a obelisk object.
     *
     * @param[in] p_obelisk The obelisk object pointer.
     */
    void destroy_obelisk(CObelisk *p_obelisk);

#ifdef __cplusplus
};
#endif

#endif
