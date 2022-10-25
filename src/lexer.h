#ifndef OBELISK_LEXER_H
#define OBELISK_LEXER_H

#include <string>

namespace obelisk
{

    class Lexer
    {
        private:
            std::string identifier_;
            double numberValue_;

            void setIdentifier(const std::string identifier);
            void eraseIdentifier();
            void appendIdentifier(int lastChar);
            void setNumberValue(double numberValue);
            void commentLine(int* lastChar);

        public:
            enum Token
            {
                kTokenInvalid = -1,
                kTokenEof     = -2,

                // commands
                kTokenFact   = -3,
                kTokenRule   = -4,
                kTokenDef    = -5,
                kTokenExtern = -6,

                // primary
                kTokenIdentifier = -7,
                kTokenNumber     = -8,
                kTokenString     = -9
            };

            int getToken();

            std::string getIdentifier();
            double getNumberValue();
    };
} // namespace obelisk

#endif
