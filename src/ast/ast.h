#ifndef OBELISK_AST_AST_H
#define OBELISK_AST_AST_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Type.h>

#include <map>
#include <memory>

namespace obelisk
{
    /**
     * @brief The LLVM context.
     *
     */
    static std::unique_ptr<llvm::LLVMContext> TheContext;

    /**
     * @brief The LLVM module.
     *
     */
    static std::unique_ptr<llvm::Module> TheModule;

    /**
     * @brief The LLVM IR builder.
     *
     */
    static std::unique_ptr<llvm::IRBuilder<>> Builder;

    /**
     * @brief The LLVM named values.
     *
     */
    static std::map<std::string, llvm::Value *> NamedValues;
} // namespace obelisk

#endif
