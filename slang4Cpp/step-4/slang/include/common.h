#pragma once
#ifndef COMMON_H

#include <map>
#include <string>

#define COMMON_H

enum TYPE_INFO { TYPE_ILLEGAL, TYPE_NUMERIC, TYPE_BOOL, TYPE_STRING };

class SymbolInfo {
public:
    TYPE_INFO type_;
    std::string symbolName;

    std::string stringValue;
    double doubleValue;
    bool boolValue;
};

class SymbolTable {
    std::map<std::string, SymbolInfo> table;

public:
    void add(SymbolInfo s);
    SymbolInfo *get(std::string symbolname);
    void assign(std::string varbleName, SymbolInfo symbol);
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

#endif /* COMMON_H */
