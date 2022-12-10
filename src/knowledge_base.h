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
    class KnowledgeBase
    {
        private:
            const int DEFAULT_FLAGS
                = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
            const char* filename_;
            sqlite3* dbConnection_ = nullptr;
            int flags_;

            void enableForeignKeys();
            void createTable(std::function<const char*()> function);

        public:
            KnowledgeBase(const char* filename, int flags);

            KnowledgeBase(const char* filename) :
                KnowledgeBase(filename,
                    SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE)
            {
            }

            ~KnowledgeBase();

            void addEntities(std::vector<obelisk::Entity>& entities);
            void addVerbs(std::vector<obelisk::Verb>& verbs);
            void addFacts(std::vector<obelisk::Fact>& facts);

            void getEntity(obelisk::Entity& entity);
            void getVerb(obelisk::Verb& verb);
            void getFact(obelisk::Fact& fact);

            void getDouble(double& result, float var1, float var2);
            void getFloat(float& result1, float& result2, double var);
    };

    class KnowledgeBaseException : public std::exception
    {
        private:
            const std::string errorMessage_;

        public:
            KnowledgeBaseException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            KnowledgeBaseException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }
    };
} // namespace obelisk

#endif
