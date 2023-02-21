#ifndef OBELISK_AST_PROTOTYPE_AST_H
#define OBELISK_AST_PROTOTYPE_AST_H

#include <llvm/IR/Function.h>

#include <string>
#include <vector>

namespace obelisk
{
    /**
     * @brief The prototype AST node.
     *
     */
    class PrototypeAST
    {
        private:
            /**
             * @brief The name of the prototype.
             *
             */
            std::string name_;
            /**
             * @brief The arguments the protype accepts.
             *
             */
            std::vector<std::string> args_;

            /**
             * @brief Set the name of the prototype.
             *
             * @param[in] name The name.
             */
            void setName(const std::string& name);

            /**
             * @brief Get the arguments the prototype accepts.
             *
             * @return std::vector<std::string> Returns the arguments.
             */
            std::vector<std::string> getArgs();

            /**
             * @brief Set the arguments the prototype accepts.
             *
             * @param[in] args The arguments.
             */
            void setArgs(std::vector<std::string> args);

        public:
            /**
             * @brief Construct a new PrototypeAST object.
             *
             * @param[in] name The name of the prototype.
             * @param[in] args The arguments the prototype accepts.
             */
            PrototypeAST(const std::string& name, std::vector<std::string> args) :
                name_(name),
                args_(std::move(args))
            {
            }

            /**
             * @brief Get the name of the prototype.
             *
             * @return const std::string& Returns the name of the prototype.
             */
            const std::string& getName() const
            {
                return name_;
            }

            /**
             * @brief Generate LLVM IR code for the prototype.
             *
             * @return llvm::Function* Returns IR code for the prototype.
             */
            llvm::Function* codegen();
    };
} // namespace obelisk

#endif
