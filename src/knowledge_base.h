#ifndef OBELISK_KNOWLEDGE_BASE_H
#define OBELISK_KNOWLEDGE_BASE_H

#include "models/entity.h"
#include "models/fact.h"
#include "models/verb.h"

#include <sqlite3.h>

#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace obelisk
{
    /**
     * @brief The KnowledgeBase class represents a collection of facts, rules,
     * actions, and related language connectors.
     *
     */
    class KnowledgeBase
    {
        private:
            /**
             * @brief The filename of the opened knowledge base.
             *
             */
            const char* filename_;

            /**
             * @brief The SQLite connection handle.
             *
             */
            sqlite3* dbConnection_ = nullptr;

            /**
             * @brief The user passed flags to use when opening the database.
             *
             */
            int flags_;

            /**
             * @brief Enable foreign key functionality in the open database.
             *
             * This must always be done when the connection is opened or it will
             * not enforce the foreign key constraints.
             */
            void enableForeignKeys();

            /**
             * @brief Create the tables in the database.
             *
             * @param[in] function This function is called to create the table.
             */
            void createTable(std::function<const char*()> function);

        public:
            /**
             * @brief Construct a new KnowledgeBase object.
             *
             * @param[in] filename The name of the file to save the knowledge
             * base as.
             * @param[in] flags The flags to open the knowledge base with.
             */
            KnowledgeBase(const char* filename, int flags);

            /**
             * @brief Construct a new KnowledgeBase object.
             *
             * @param[in] filename The name of the file to save the knowledge
             * base as.
             */
            KnowledgeBase(const char* filename) :
                KnowledgeBase(filename,
                    SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE)
            {
            }

            /**
             * @brief Destroy the KnowledgeBase object.
             *
             * This will close the opened knowledge base before destroying it.
             */
            ~KnowledgeBase();

            /**
             * @brief Add entities to the knowledge base.
             *
             * @param[in,out] entities The entities to add. If the insert is
             * successful it will have a row ID, if not the ID will be 0.
             */
            void addEntities(std::vector<obelisk::Entity>& entities);

            /**
             * @brief Add verbs to the knowledge base.
             *
             * @param[in,out] verbs The verbs to add. If the insert is
             * successful it will have a row ID, if not the ID will be 0.
             */
            void addVerbs(std::vector<obelisk::Verb>& verbs);

            /**
             * @brief Add facts to the database.
             *
             * @param[in,out] facts The facts to add. If the insert is
             * successful it will have a row ID, if not the ID will be 0.
             */
            void addFacts(std::vector<obelisk::Fact>& facts);

            /**
             * @brief Get an entity object based on the ID it contains.
             *
             * @param[in,out] entity The Entity object should contain just the
             * ID and the rest will be filled in.
             */
            void getEntity(obelisk::Entity& entity);

            /**
             * @brief Get a verb object based on the ID it contains.
             *
             * @param[in,out] verb The Verb object should contain just the ID
             * and the rest will be filled in.
             */
            void getVerb(obelisk::Verb& verb);

            /**
             * @brief Get a fact object based on the ID it contains.
             *
             * @param[in,out] fact The fact object should contain just the ID
             * and the rest will be filled in.
             */
            void getFact(obelisk::Fact& fact);

            /**
             * @brief Take a float and divide it into 2 floats.
             *
             * This is useful to store doubles in SQLite since SQLite doesn't
             * have a double type.
             * Instead just store the 2 floats in the database. Then after
             * selecting them combine them.
             *
             * @param[out] result1 The first float generated from the double.
             * @param[out] result2 The second float generated from the double.
             * @param[in] var The double to split into the 2 floats.
             */
            void getFloat(float& result1, float& result2, double var);

            /**
             * @brief Combines 2 separated floats back into a double.
             *
             * This will recombine the separated floats from the getFloat
             * method.
             *
             * @param[out] result The double generated from the combined floats.
             * @param[in] var1 The first float to combine.
             * @param[in] var2 The second float to combine.
             */
            void getDouble(double& result, float var1, float var2);
    };

    /**
     * @brief Exception thrown by the KnowledgeBase.
     *
     */
    class KnowledgeBaseException : public std::exception
    {
        private:
            /**
             * @brief The error message given.
             *
             */
            const std::string errorMessage_;

        public:
            /**
             * @brief Construct a new KnowledgeBaseException object.
             *
             */
            KnowledgeBaseException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            /**
             * @brief Construct a new KnowledgeBaseException object.
             *
             * @param[in] errorMessage The error message given when thrown.
             */
            KnowledgeBaseException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            /**
             * @brief Get the error message that occurred.
             *
             * @return const char* Returns the error message.
             */
            const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }
    };
} // namespace obelisk

#endif
