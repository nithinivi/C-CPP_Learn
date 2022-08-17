#ifndef CONTEXT_HPP
#define CONTEXT_HPP
#include "SymbolTable.hpp"

#include "llvm/IR/LLVMContext.h"

static LLVMContext* TheContext;

class Context {
protected:
    SymbolTable* symbolTable;

public:
    Context() { SymbolTable* symbolTable = new SymbolTable(); };
    SymbolTable* getSymbolTable() { return symbolTable; };
};

class RuntimeContext : public Context {};
class CompliationContext : public Context {};

#endif // CONTEXT_HPP
