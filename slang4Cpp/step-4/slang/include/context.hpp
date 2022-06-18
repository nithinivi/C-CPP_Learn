#include <string>
#ifndef CONTEXT_H
#include "common.hpp"
#define CONTEXT_H

class SymbolInfo {
public:
    TYPE_INFO type_;
    std::string symbolName;

    std::string stringValue;
    double doubleValue;
    bool boolValue;
};

class SymbolTable {
    std::map<std::string, SymbolInfo *> table;

public:
    void add(SymbolInfo *s);
    SymbolInfo *get(std::string symbolname);
    void assign(std::string varName, SymbolInfo *info);
};

class RuntimeContext {
public:
    SymbolTable *symbolTable;
    RuntimeContext() { symbolTable = new SymbolTable(); };
};

class CompilationContext {
public:
    SymbolTable *symbolTable;
    CompilationContext() { symbolTable = new SymbolTable(); };
    ~CompilationContext(){};
};

#endif /* CONTEXT_H */
