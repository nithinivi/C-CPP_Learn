#include "../include/ast_expression.hpp"
#include "../include/common.hpp"
#include <string>

StringLiteral::StringLiteral(std::string value) { 
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = "";
    symbolInfo->stringValue = value;
    symbolInfo->type_ = TYPE_STRING;
}

SymbolInfo *StringLiteral::evaluate(RuntimeContext *ctx) {
    return symbolInfo;
}

TYPE_INFO StringLiteral::typeCheck(CompilationContext *ctx) {
    return symbolInfo->type_;
}

TYPE_INFO StringLiteral::getType() { return symbolInfo->type_; }
