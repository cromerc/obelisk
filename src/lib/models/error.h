#ifndef OBELISK_MODELS_ERROR_H
#define OBELISK_MODELS_ERROR_H

#include <exception>
#include <string>

namespace obelisk
{
    /**
     * @brief Exception thrown by database models.
     *
     */
    class DatabaseException : public std::exception
    {
        protected:
            /**
             * @brief The error message describing the exception.
             *
             */
            std::string errorMessage_;

        public:
            /**
             * @brief Construct a new DatabaseException object.
             *
             */
            DatabaseException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            /**
             * @brief Construct a new DatabaseException object.
             *
             * @param[in] errorCode The error code that came from sqlite.
             */
            DatabaseException(const int errorCode) :
                errorMessage_("database error " + std::to_string(errorCode) + " ocurred")
            {
            }

            /**
             * @brief Construct a new DatabaseException object.
             *
             * @param[in] errorMessage The error message to describe the
             * exception.
             */
            DatabaseException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            /**
             * @brief Retreive the exception message as a C type string.
             *
             * @return const char* The error message.
             */
            virtual const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }

            /**
             * @brief Set the error message.
             *
             * @param[in] errorMessage The error message.
             */
            virtual void setErrorMessage(const std::string errorMessage)
            {
                errorMessage_ = errorMessage;
            }
    };

    /**
     * @brief Exception thrown if the string or blob size exceeds sqlite's
     * limits.
     *
     */
    class DatabaseSizeException : public obelisk::DatabaseException
    {
        public:
            /**
             * @brief Construct a new DatabaseSizeException object.
             *
             */
            DatabaseSizeException()
            {
                setErrorMessage("size of string or blob exceeds limits");
            }
    };

    /**
     * @brief Exception thrown if the index used it out of range.
     *
     */
    class DatabaseRangeException : public obelisk::DatabaseException
    {
        public:
            /**
             * @brief Construct a new DatabaseRangeException object.
             *
             */
            DatabaseRangeException()
            {
                setErrorMessage("parameter index is out of range");
            }
    };

    /**
     * @brief Exception thrown if there is not enough memory to perform the
     * operation.
     *
     */
    class DatabaseMemoryException : public obelisk::DatabaseException
    {
        public:
            /**
             * @brief Construct a new DatabaseMemoryException object.
             *
             */
            DatabaseMemoryException()
            {
                setErrorMessage("not enough memory for operation");
            }
    };

    /**
     * @brief Exception thrown if the database was busy.
     *
     */
    class DatabaseBusyException : public obelisk::DatabaseException
    {
        public:
            /**
             * @brief Construct a new DatabaseBusyException object.
             *
             */
            DatabaseBusyException()
            {
                setErrorMessage("database was busy and operation was not performed");
            }
    };

    /**
     * @brief Exception thrown if there is a misuse of the databse.
     *
     */
    class DatabaseMisuseException : public obelisk::DatabaseException
    {
        public:
            /**
             * @brief Construct a new DatabaseMisuseException object.
             *
             */
            DatabaseMisuseException()

            {
                setErrorMessage("misuse of the database routine");
            }
    };

    /**
     * @brief Exception thrown if a constraint was violated.
     *
     */
    class DatabaseConstraintException : public obelisk::DatabaseException
    {
        public:
            /**
             * @brief Construct a new DatabaseConstraintException object.
             *
             */
            DatabaseConstraintException()
            {
                setErrorMessage("a constraint exception occurred");
            }

            /**
             * @brief Construct a new DatabaseConstraintException object.
             *
             * @param[in] errorMessage The error message to send when the
             * constraint is violated.
             */
            DatabaseConstraintException(const std::string& errorMessage)
            {
                setErrorMessage(errorMessage);
            }
    };
} // namespace obelisk

#endif
