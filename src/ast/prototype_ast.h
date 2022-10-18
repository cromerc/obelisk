#ifndef OBELISK_AST_PROTOTYPE_AST_H
#define OBELISK_AST_PROTOTYPE_AST_H

#include <string>
#include <vector>

namespace obelisk
{
    class PrototypeAST
    {
        private:
            std::string name_;
            std::vector<std::string> args_;

            void setName(const std::string& name);
            std::vector<std::string> getArgs();
            void setArgs(std::vector<std::string> args);

        public:
            PrototypeAST(const std::string& name,
                std::vector<std::string> args) :
                name_(name),
                args_(std::move(args))
            {
            }

            const std::string& getName() const
            {
                return name_;
            }
    };
} //namespace obelisk

#endif
