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

            void setIdentifier(const std::string& identifier);
            void eraseIdentifier();
            void appendIdentifier(int lastChar);
            void setNumberValue(double numberValue);
            void commentLine(int* lastChar);

        public:
            enum Token
            {
                kTokenEof = -1,

                // commands
                kTokenFact   = -2,
                kTokenRule   = -3,
                kTokenAction = -4,
                kTokenDef    = -5,
                kTokenExtern = -6,

                // primary
                kTokenIdentifier = -7,
                kTokenNumber     = -8,
                kTokenString     = -9
            };

            int getToken();

            const std::string& getIdentifier();
            double getNumberValue();
    };

    class LexerException : public std::exception
    {
        private:
            const std::string errorMessage_;

        public:
            LexerException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            LexerException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }
    };
} // namespace obelisk

#endif
