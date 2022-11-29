#ifndef OBELISK_MODELS_ENTITY_H
#define OBELISK_MODELS_ENTITY_H

#include <sqlite3.h>

#include <string>

namespace obelisk
{
    class Entity
    {
        private:
            int id_;
            std::string name_;

        public:
            Entity() :
                id_(0),
                name_("")
            {
            }

            Entity(int id) :
                id_(id),
                name_("")
            {
            }

            Entity(std::string name) :
                id_(0),
                name_(name)
            {
            }

            Entity(int id, std::string name) :
                id_(id),
                name_(name)
            {
            }

            static const char* createTable();

            int& getId();
            void setId(int id);

            std::string& getName();
            void setName(std::string name);

            void selectEntity(sqlite3* dbConnection);
            void insertEntity(sqlite3* dbConnection);
    };
} // namespace obelisk

#endif
