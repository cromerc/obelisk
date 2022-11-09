#ifndef OBELISK_MODELS_RULE_H
#define OBELISK_MODELS_RULE_H

#include "models/fact.h"

#include <string>

namespace obelisk
{
    class Rule
    {
        private:
            int id_;
            obelisk::Fact fact_;
            obelisk::Fact reason_;

        public:
            Rule() :
                id_(0),
                fact_(),
                reason_()
            {
            }

            Rule(int id) :
                id_(id),
                fact_(),
                reason_()
            {
            }

            Rule(obelisk::Fact fact, obelisk::Fact reason) :
                id_(0),
                fact_(fact),
                reason_(reason)
            {
            }

            Rule(int id, obelisk::Fact fact, obelisk::Fact reason) :
                id_(id),
                fact_(fact),
                reason_(reason)
            {
            }

            static const char* createTable();

            int getId();
            void setId(int id);

            obelisk::Fact getFact();
            void setFact(obelisk::Fact fact);

            obelisk::Fact getReason();
            void setReason(obelisk::Fact reason);
    };
} // namespace obelisk

#endif
