#ifndef OBELISK_MODELS_ERROR_H
#define OBELISK_MODELS_ERROR_H

#include <exception>
#include <string>

namespace obelisk
{
    class DatabaseException : public std::exception
    {
        private:
            const std::string errorMessage_;

        public:
            DatabaseException() :
                errorMessage_("an unknown error ocurred")
            {
            }

            DatabaseException(const int errorCode) :
                errorMessage_(
                    "database error " + std::to_string(errorCode) + " ocurred")
            {
            }

            DatabaseException(const std::string& errorMessage) :
                errorMessage_(errorMessage)
            {
            }

            const char* what() const noexcept
            {
                return errorMessage_.c_str();
            }

            class SizeException : public std::exception
            {
                private:
                    const std::string errorMessage_;

                public:
                    SizeException() :
                        errorMessage_("size of string or blob exceeds limits")
                    {
                    }

                    const char* what() const noexcept
                    {
                        return errorMessage_.c_str();
                    }
            };

            class RangeException : public std::exception
            {
                private:
                    const std::string errorMessage_;

                public:
                    RangeException() :
                        errorMessage_("parameter index is out of range")
                    {
                    }

                    const char* what() const noexcept
                    {
                        return errorMessage_.c_str();
                    }
            };

            class MemoryException : public std::exception
            {
                private:
                    const std::string errorMessage_;

                public:
                    MemoryException() :
                        errorMessage_("not enough memory for operation")
                    {
                    }

                    const char* what() const noexcept
                    {
                        return errorMessage_.c_str();
                    }
            };

            class BusyException : public std::exception
            {
                private:
                    const std::string errorMessage_;

                public:
                    BusyException() :
                        errorMessage_(
                            "database was busy and operation not performed")
                    {
                    }

                    const char* what() const noexcept
                    {
                        return errorMessage_.c_str();
                    }
            };

            class MisuseException : public std::exception
            {
                private:
                    const std::string errorMessage_;

                public:
                    MisuseException() :
                        errorMessage_("misuse of the database routine")
                    {
                    }

                    const char* what() const noexcept
                    {
                        return errorMessage_.c_str();
                    }
            };

            class ConstraintException : public std::exception
            {
                private:
                    const std::string errorMessage_;

                public:
                    ConstraintException() :
                        errorMessage_("a constraint exception occurred")
                    {
                    }

                    ConstraintException(const std::string& errorMessage) :
                        errorMessage_(errorMessage)
                    {
                    }

                    const char* what() const noexcept
                    {
                        return errorMessage_.c_str();
                    }
            };
    };
} // namespace obelisk

#endif
