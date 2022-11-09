#ifndef OBELISK_MODELS_ACTION_H
#define OBELISK_MODELS_ACTION_H

#include <string>

namespace obelisk
{
    class Action
    {
        private:
            int id_;
            std::string name_;

        public:
            Action() :
                id_(0),
                name_("")
            {
            }

            Action(int id) :
                id_(id),
                name_("")
            {
            }

            Action(std::string name) :
                id_(0),
                name_(name)
            {
            }

            Action(int id, std::string name) :
                id_(id),
                name_(name)
            {
            }

            static const char* createTable();

            int getId();
            void setId(int id);

            std::string getName();
            void setName(std::string name);
    };
} // namespace obelisk

#endif
