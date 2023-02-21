#ifndef OBELISK_INCLUDE_OBELISK_H
#define OBELISK_INCLUDE_OBELISK_H

#include <string>

/**
 * @brief The obelisk namespace contains everything needed to compile obelisk
 * code.
 *
 */
namespace obelisk
{
    /**
     * @brief The obelisk library provides everything needed to consult the
     * KnowledgeBase.
     *
     */
    class Obelisk
    {
        public:
            /**
             * @brief Construct a new Obelisk object.
             *
             */
            Obelisk() = default;

            /**
             * @brief Destroy the Obelisk object.
             *
             */
            ~Obelisk() = default;

            /**
             * @brief Get the obelisk version.
             *
             * @return std::string The version.
             */
            std::string getVersion();

            /**
             * @brief Get the obelisk library so version.
             *
             * @return int The version.
             */
            int getLibVersion();

            /**
             * @brief Query the Obelisk KnowledgeBase to see if the Fact is true
             * or not.
             *
             * @param[in] leftEntity The left entity.
             * @param[in] verb The verb.
             * @param[in] rightEntity The right entity.
             * @return double Returns a value between 0 and 1 depending on
             * whether it is true or false.
             */
            double query(const std::string& leftEntity,
                const std::string& verb,
                const std::string& rightEntity);

            /**
             * @brief Query the Obelisk KnowledgeBase and return the suggested
             * action to take.
             *
             * @param[in] leftEntity The left entity.
             * @param[in] verb The verb.
             * @param[in] rightEntity The right entity.
             * @return std::string Returns the suggested action.
             */
            std::string query_action(const std::string& leftEntity,
                const std::string& verb,
                const std::string& rightEntity);
    };
} // namespace obelisk

#endif
