#ifndef OBELISK_MODELS_ENTITY_H
#define OBELISK_MODELS_ENTITY_H

#include <string>

namespace obelisk
{
    class Entity
    {
        private:
            int id_;
            std::string name_;

        public:
            Entity();
            Entity(std::string name);

            int getId();
            void setId(int id);

            std::string getName();
            void setName(std::string name);
    };
} // namespace obelisk

#endif
