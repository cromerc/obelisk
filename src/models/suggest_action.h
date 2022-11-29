#ifndef OBELISK_MODELS_SUGGEST_ACTION_H
#define OBELISK_MODELS_SUGGEST_ACTION_H

#include "models/action.h"
#include "models/fact.h"

#include <string>

namespace obelisk
{
    class SuggestAction
    {
        private:
            int id_;
            obelisk::Fact fact_;
            obelisk::Action trueAction_;
            obelisk::Action falseAction_;

        public:
            SuggestAction() :
                id_(0),
                fact_(),
                trueAction_(),
                falseAction_()
            {
            }

            SuggestAction(int id) :
                id_(id),
                fact_(),
                trueAction_(),
                falseAction_()
            {
            }

            SuggestAction(obelisk::Fact fact,
                obelisk::Action trueAction,
                obelisk::Action falseAction) :
                id_(0),
                fact_(fact),
                trueAction_(trueAction),
                falseAction_(falseAction)
            {
            }

            SuggestAction(int id,
                obelisk::Fact fact,
                obelisk::Action trueAction,
                obelisk::Action falseAction) :
                id_(id),
                fact_(fact),
                trueAction_(trueAction),
                falseAction_(falseAction)
            {
            }

            static const char* createTable();

            int& getId();
            void setId(int id);

            obelisk::Fact& getFact();
            void setFact(obelisk::Fact fact);

            obelisk::Action& getTrueAction();
            void setTrueAction(obelisk::Action trueAction);

            obelisk::Action& getFalseAction();
            void setFalseAction(obelisk::Action falseAction);
    };
} // namespace obelisk

#endif
