#ifndef OBELISK_MODELS_VERB_H
#define OBELISK_MODELS_VERB_H

#include <string>

namespace obelisk
{
    class Verb
    {
        private:
            int id_;
            std::string verb_;

        public:
            Verb();
            Verb(std::string verb);
            Verb(int id, std::string verb);

            int getId();
            void setId(int id);

            std::string getVerb();
            void setVerb(std::string verb);
    };
} // namespace obelisk

#endif
