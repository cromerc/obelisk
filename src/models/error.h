#ifndef OBELISK_MODELS_ERROR_H
#define OBELISK_MODELS_ERROR_H

#include <exception>
#include <string>

namespace obelisk
{
    class DatabaseException : public std::exception
    {
        protected:
            std::string errorMessage_;

        public:
            DatabaseException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            DatabaseException(const int errorCode) :
                errorMessage_("database error " + std::to_string(errorCode) + " ocurred")
            {
            }

            DatabaseException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            virtual const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }

            virtual void setErrorMessage(const std::string errorMessage)
            {
                errorMessage_ = errorMessage;
            }
    };

    class DatabaseSizeException : public obelisk::DatabaseException
    {
        public:
            DatabaseSizeException()
            {
                setErrorMessage("size of string or blob exceeds limits");
            }
    };

    class DatabaseRangeException : public obelisk::DatabaseException
    {
        public:
            DatabaseRangeException()
            {
                setErrorMessage("parameter index is out of range");
            }
    };

    class DatabaseMemoryException : public obelisk::DatabaseException
    {
        public:
            DatabaseMemoryException()
            {
                setErrorMessage("not enough memory for operation");
            }
    };

    class DatabaseBusyException : public obelisk::DatabaseException
    {
        public:
            DatabaseBusyException()
            {
                setErrorMessage("database was busy and operation was not performed");
            }
    };

    class DatabaseMisuseException : public obelisk::DatabaseException
    {
        public:
            DatabaseMisuseException()

            {
                setErrorMessage("misuse of the database routine");
            }
    };

    class DatabaseConstraintException : public obelisk::DatabaseException
    {
        public:
            DatabaseConstraintException()
            {
                setErrorMessage("a constraint exception occurred");
            }

            DatabaseConstraintException(const std::string& errorMessage)
            {
                setErrorMessage(errorMessage);
            }
    };
} // namespace obelisk

#endif
