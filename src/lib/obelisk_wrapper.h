#ifndef OBELISK_INCLUDE_OBELISK_WRAPPER_H
#define OBELISK_INCLUDE_OBELISK_WRAPPER_H

#include "include/obelisk_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

    /**
     * @brief Create a obelisk object.
     *
     * @param[in] filename The name of the obelisk KnowledgeBase file to use.
     * @return CObelisk* Returns the obelisk object.
     */
    CObelisk *create_obelisk(const char *filename);

    /**
     * @brief Calls the obelisk method getVersion.
     *
     * @param[in] p_obelisk The obelisk object pointer.
     * @return const char* Returns the version. This must be freed by the
     * caller.
     */
    char *call_obelisk_getVersion(CObelisk *p_obelisk);

    /**
     * @brief Calls the obelisk method getLibVersion.
     *
     * @param[in] p_obelisk The obelisk object pointer.
     * @return int Returns the library so version.
     */
    int call_obelisk_getLibVersion(CObelisk *p_obelisk);

    /**
     * @brief Calls the obelisk method query.
     *
     * @param[in] p_obelisk The obelisk object pointer.
     * @param[in] left_entity The left entity.
     * @param[in] verb The verb.
     * @param[in] right_entity The right entity.
     * @return double Returns whether or not the Fact is true.
     */
    double call_obelisk_query(CObelisk *p_obelisk,
        const char *left_entity,
        const char *verb,
        const char *right_entity);

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
