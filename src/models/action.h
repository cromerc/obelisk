#ifndef OBELISK_MODELS_ACTION_H
#define OBELISK_MODELS_ACTION_H

#include <string>

namespace obelisk
{
    /**
     * @brief The Action model represents an action to take when a fact is true
     * or false.
     *
     */
    class Action
    {
        private:
            /**
             * @brief The ID of the Action in the knowledge base.
             *
             */
            int id_;

            /**
             * @brief The name of the Action.
             *
             */
            std::string name_;

        public:
            /**
             * @brief Construct a new Action object.
             *
             */
            Action() :
                id_(0),
                name_("")
            {
            }

            /**
             * @brief Construct a new Action object.
             *
             * @param[in] id The ID of the Action.
             */
            Action(int id) :
                id_(id),
                name_("")
            {
            }

            /**
             * @brief Construct a new Action object.
             *
             * @param[in] name The name of the Action.
             */
            Action(std::string name) :
                id_(0),
                name_(name)
            {
            }

            /**
             * @brief Construct a new Action object.
             *
             * @param[in] id The ID of the Action.
             * @param[in] name The name of the Action.
             */
            Action(int id, std::string name) :
                id_(id),
                name_(name)
            {
            }

            /**
             * @brief Create the Action table in the knowledge base.
             *
             * @return const char* Returns the query used to create the table.
             */
            static const char* createTable();

            /**
             * @brief Get the ID of the Action.
             *
             * @return int& Returns the ID.
             */
            int& getId();

            /**
             * @brief Set the ID of the Action.
             *
             * @param[in] id Set the ID of the Action.
             */
            void setId(int id);

            /**
             * @brief Get the name of the Action.
             *
             * @return std::string& The Action name.
             */
            std::string& getName();

            /**
             * @brief Set the name of the Action.
             *
             * @param[in] name The name of the Action.
             */
            void setName(std::string name);
    };
} // namespace obelisk

#endif
