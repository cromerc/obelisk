#include "models/suggest_action.h"

const char* obelisk::SuggestAction::createTable()
{
    return R"(
        CREATE TABLE "suggest_action" (
            "id"           INTEGER NOT NULL UNIQUE,
            "fact"         INTEGER NOT NULL,
            "true_action"  INTEGER NOT NULL,
            "false_action" INTEGER NOT NULL,
            PRIMARY KEY("id" AUTOINCREMENT),
            UNIQUE("fact", "true_action", "false_action"),
            FOREIGN KEY("fact") REFERENCES "fact"("id") ON DELETE RESTRICT,
            FOREIGN KEY("true_action") REFERENCES "action"("id") ON DELETE RESTRICT,
            FOREIGN KEY("false_action") REFERENCES "action"("id") ON DELETE RESTRICT
        );
    )";
}

int& obelisk::SuggestAction::getId()
{
    return id_;
}

void obelisk::SuggestAction::setId(int id)
{
    id_ = id;
}

obelisk::Fact& obelisk::SuggestAction::getFact()
{
    return fact_;
}

void obelisk::SuggestAction::setFact(obelisk::Fact fact)
{
    fact_ = fact;
}

obelisk::Action& obelisk::SuggestAction::getTrueAction()
{
    return trueAction_;
}

void obelisk::SuggestAction::setTrueAction(obelisk::Action trueAction)
{
    trueAction_ = trueAction;
}

obelisk::Action& obelisk::SuggestAction::getFalseAction()
{
    return falseAction_;
}

void obelisk::SuggestAction::setFalseAction(obelisk::Action falseAction)
{
    falseAction_ = falseAction;
}
