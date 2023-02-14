#ifndef OBELISK_LEXER_H
#define OBELISK_LEXER_H

#include <fstream>
#include <string>

namespace obelisk
{
    /**
     * @brief The Lexer reads and identifies tokens in the obelisk source code.
     *
     */
    class Lexer
    {
        private:
            int lastChar = ' ';
            /**
             * @brief The stream of the source file being read.
             *
             */
            std::ifstream fileStream_;
            /**
             * @brief The last found identifier.
             *
             */
            std::string identifier_;
            /**
             * @brief The last found number.
             *
             */
            double numberValue_ = 0;

            /**
             * @brief Set the identifier.
             *
             * @param[in] identifier The new identifier.
             */
            void setIdentifier(const std::string& identifier);
            /**
             * @brief Erase the last identifier.
             *
             */
            void eraseIdentifier();
            /**
             * @brief Add the last found char to the end of the identifier.
             *
             * @param[in] lastChar  The last char that was found.
             */
            void appendIdentifier(int lastChar);
            /**
             * @brief Set the number value.
             *
             * @param[in] numberValue The new number value.
             */
            void setNumberValue(double numberValue);
            /**
             * @brief Comment the rest of the line.
             *
             * @param[in] lastChar The char to check to see if it in the end of
             * the line.
             */
            void commentLine(int* lastChar);

        public:
            /**
             * @brief These token represent recognized language keywords and
             * language functionality.
             *
             */
            enum Token
            {
                /**
                 * @brief End of file is returned when the source code is
                 * finished.
                 *
                 */
                kTokenEof = -1,

                /**
                 * @brief A fact which is a relationship between 2 entities.
                 *
                 */
                kTokenFact   = -2,
                /**
                 * @brief A rule which is a relationship between a new fact a
                 * existing fact.
                 *
                 */
                kTokenRule   = -3,
                /**
                 * @brief An action to take if a fact is true.
                 *
                 */
                kTokenAction = -4,
                /**
                 * @brief A definition of a new function.
                 *
                 */
                kTokenDef    = -5,
                /**
                 * @brief An external function that will be linked to.
                 *
                 */
                kTokenExtern = -6,

                /**
                 * @brief An identifier which is a alphanumeric value.
                 *
                 */
                kTokenIdentifier = -7,
                /**
                 * @brief A double floating point value.
                 *
                 */
                kTokenNumber     = -8,
                /**
                 * @brief A string.
                 *
                 */
                kTokenString     = -9
            };

            /**
             * @brief Construct a new Lexer object.
             *
             * @param[in] sourceFile The source file to read.
             */
            Lexer(const std::string& sourceFile);

            /**
             * @brief Destroy the Lexer object.
             *
             */
            ~Lexer();

            /**
             * @brief Gets the next token in the source code.
             *
             * @throws LexerException when an invalid token is found.
             * @return int Returns a Token value or char if no known token was
             * found.
             */
            int getToken();

            /**
             * @brief Get the last identifier.
             *
             * @return const std::string& Returns a string that contains the
             * last found identifier.
             */
            const std::string& getIdentifier();

            /**
             * @brief Get the last number value.
             *
             * @return double Return the last number that was found.
             */
            double getNumberValue();
    };

    /**
     * @brief Lexer exception class.
     *
     */
    class LexerException : public std::exception
    {
        private:
            /**
             * @brief The error message from the exception.
             *
             */
            const std::string errorMessage_;

        public:
            /**
             * @brief Construct a new LexerException object.
             *
             */
            LexerException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            /**
             * @brief Construct a new LexerException object.
             *
             * @param[in] errorMessage Error message to include.
             */
            LexerException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            /**
             * @brief Return the exception's error message.
             *
             * @return const char* Returns a string containing the error
             * message.
             */
            const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }
    };
} // namespace obelisk

#endif
