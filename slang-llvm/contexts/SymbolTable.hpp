
#include <string>
#include <unordered_map>

#if !defined(SYMBOLTABLE_HPP)
#define SYMBOLTABLE_HPP

#include "Symbol.hpp"

class SymbolTable {
private:
    std::unordered_map<std::string, Symbol> symbolTable;
    /* data */
public:
    SymbolTable();
    ~SymbolTable() { delete &symbolTable; };

    void setSymbol(Symbol symbol) { symbolTable[symbol.getName()] = symbol; };
    Symbol getSymbol(std::string name) { return symbolTable[name]; };
    
};

#endif // SYMBOLTABLE_HPP
