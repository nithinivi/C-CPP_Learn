#include "../include/context.h"


void SymbolTable::add(SymbolInfo *s) {
  table.insert({s->symbolName, s}) ;
}
void SymbolTable::assign(std::string varName, SymbolInfo *info) {
  table.insert({varName , info});    
}

SymbolInfo *SymbolTable::get(std::string symbolname) {
  return table.at(symbolname);
    
}

