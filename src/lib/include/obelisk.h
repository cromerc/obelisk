#include <string>

/**
 * @brief The obelisk namespace contains everything needed to compile obelisk.
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
    };
} // namespace obelisk
