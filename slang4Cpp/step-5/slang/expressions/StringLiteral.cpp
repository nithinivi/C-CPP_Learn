#include "../include/ast_expression.h"

#include <string>

StringLiteral::StringLiteral(std::string value) { 
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = "";
    symbolInfo->stringValue = value;
    symbolInfo->type_ = TYPE_STRING;
}

StringLiteral::~StringLiteral() {
  delete symbolInfo;
}
SymbolInfo *StringLiteral::evaluate(RuntimeContext *ctx) {
    return symbolInfo;
}

TYPE_INFO StringLiteral::typeCheck(CompilationContext *ctx) {
    return symbolInfo->type_;
}

TYPE_INFO StringLiteral::getType() { return symbolInfo->type_; }
