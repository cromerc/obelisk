#ifndef OBELISK_MODELS_VERB_H
#define OBELISK_MODELS_VERB_H

#include <sqlite3.h>

#include <string>

namespace obelisk
{
    class Verb
    {
        private:
            int id_;
            std::string name_;

        public:
            Verb() :
                id_(0),
                name_("")
            {
            }

            Verb(int id) :
                id_(id),
                name_("")
            {
            }

            Verb(std::string name) :
                id_(0),
                name_(name)
            {
            }

            Verb(int id, std::string name) :
                id_(id),
                name_(name)
            {
            }

            static const char* createTable();

            int& getId();
            void setId(int id);

            std::string& getName();
            void setName(std::string name);

            Verb selectVerb(sqlite3* dbConnection, std::string name);
            int insertVerb(sqlite3* dbConnection);
    };
} // namespace obelisk

#endif
