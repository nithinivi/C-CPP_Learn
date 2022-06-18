#include "../include/ast.h"
#include "../include/common.h"
#include <string>

StringLiteral::StringLiteral(std::string value) { 
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = "";
    symbolInfo->stringValue = value;
    symbolInfo->Type = TYPE_STRING;
}

SymbolInfo *StringLiteral::evaluate(RuntimeContext *ctx) {
    return symbolInfo;
}

TYPE_INFO StringLiteral::typeCheck(CompilationContext *ctx) {
    return symbolInfo->Type;
}

TYPE_INFO StringLiteral::getType() { return symbolInfo->Type; }
