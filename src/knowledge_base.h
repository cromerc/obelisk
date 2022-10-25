#ifndef OBELISK_KNOWLEDGE_BASE_H
#define OBELISK_KNOWLEDGE_BASE_H

#include <sqlite3.h>

#include <iostream>
#include <string>

namespace obelisk
{
    class KnowledgeBase
    {
        private:
            const int DEFAULT_FLAGS
                = SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE;
            const char* filename_;
            sqlite3* dbConnection_;
            int flags_;
            void logSqliteError(int result);

        public:
            KnowledgeBase(const char* filename);
            KnowledgeBase(const char* filename, int flags);
            ~KnowledgeBase();

            template<typename T, typename U>
            int addFacts(std::string verb, T leftEntities, U rightEntities);
            // TODO: add parameter for fact
            template<typename T, typename U>
            int addRules(std::string verb, T leftEntities, U rightEntities);
            template<typename T, typename U> int addActions();

            void getDouble(double* result, float var1, float var2);
            void getFloat(float* result1, float* result2, double var);
    };

    class Sql
    {
        public:
            static const std::string create_facts_table;
    };

    class KnowledgeBaseException : public std::exception
    {
        private:
            std::string errorMessage_;

        public:
            KnowledgeBaseException(std::string errorMessage) :
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
