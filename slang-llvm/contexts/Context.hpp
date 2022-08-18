#ifndef CONTEXT_HPP
#define CONTEXT_HPP

// #include "SymbolTable.hpp"
#include "Symbol.hpp"
#include <string>
#include <unordered_map>

class SymbolTable {
private:
    std::unordered_map<std::string, Symbol> symbolTable;
    /* data */
public:
    SymbolTable(){};
    ~SymbolTable() { delete &symbolTable; };

    void setSymbol(Symbol symbol) {
        symbolTable.insert({symbol.getName(), symbol});
    };
    Symbol getSymbol(std::string name) { return symbolTable[name]; };
};

class Context {
protected:
    SymbolTable* symbolTable;

public:
    Context() { this->symbolTable = new SymbolTable(); };
    SymbolTable* getSymbolTable() { return symbolTable; };
};

class RuntimeContext : public Context {};
class CompliationContext : public Context {};

#endif // CONTEXT_HPP
