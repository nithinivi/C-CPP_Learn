#include "../include/ast_expression.h"
#include "../include/common.h"

BooleanConstant::BooleanConstant(bool value) {
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = "";
    symbolInfo->boolValue = value;
    symbolInfo->type_ = TYPE_BOOL;
}

BooleanConstant::~BooleanConstant() { delete symbolInfo; }

SymbolInfo *BooleanConstant::evaluate(RuntimeContext *ctx) {
    return symbolInfo;
}

TYPE_INFO BooleanConstant::typeCheck(CompilationContext *ctx) {
    return symbolInfo->type_;
}

TYPE_INFO BooleanConstant::getType() { return symbolInfo->type_; }
