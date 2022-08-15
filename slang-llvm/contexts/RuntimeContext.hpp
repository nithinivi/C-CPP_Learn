#if !defined(RUNTIMECONTEXT_HPP)
#define RUNTIMECONTEXT_HPP

#include "SymbolTable.hpp"

class RuntimeContext {
    SymbolTable* symbolTable;

public:
    RuntimeContext() { SymbolTable* symbolTable = new SymbolTable(); };
};

#endif // RUNTIMECONTEXT_HPP
