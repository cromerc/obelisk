#ifndef OBELISK_MODELS_FACT_H
#define OBELISK_MODELS_FACT_H

#include "models/entity.h"
#include "models/verb.h"

#include <string>

namespace obelisk
{
    class Fact
    {
        private:
            int id_;
            obelisk::Entity leftEntity_;
            obelisk::Entity rightEntity_;
            obelisk::Verb verb_;

        public:
            Fact() :
                id_(0),
                leftEntity_(),
                rightEntity_(),
                verb_()
            {
            }

            Fact(int id) :
                id_(id),
                leftEntity_(),
                rightEntity_(),
                verb_()
            {
            }

            Fact(obelisk::Entity leftEntity,
                obelisk::Entity rightEntity,
                obelisk::Verb verb) :
                id_(0),
                leftEntity_(leftEntity),
                rightEntity_(rightEntity),
                verb_(verb)
            {
            }

            Fact(int id,
                obelisk::Entity leftEntity,
                obelisk::Entity rightEntity,
                obelisk::Verb verb) :
                id_(id),
                leftEntity_(leftEntity),
                rightEntity_(rightEntity),
                verb_(verb)
            {
            }

            static const char* createTable();

            int getId();
            void setId(int id);

            obelisk::Entity getLeftEntity();
            void setLeftEntity(obelisk::Entity leftEntity);

            obelisk::Entity getRightEntity();
            void setRightEntity(obelisk::Entity leftEntity);

            obelisk::Verb getVerb();
            void setVerb(obelisk::Verb verb);
    };
} // namespace obelisk

#endif
