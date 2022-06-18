#include "../include/ast_expression.hpp"
#include "../include/common.hpp"

BooleanConstant::BooleanConstant(bool value) {
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = "";
    symbolInfo->boolValue = value;
    symbolInfo->type_ = TYPE_BOOL;
}

SymbolInfo *BooleanConstant::evaluate(RuntimeContext *ctx) {
    return symbolInfo;
}

TYPE_INFO BooleanConstant::typeCheck(CompilationContext *ctx) {
    return symbolInfo->type_;
}

TYPE_INFO BooleanConstant::getType() { return symbolInfo->type_; }
