#include "../include/ast.h"
#include "../include/common.h"

BooleanConstant::BooleanConstant(bool value) {
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = "";
    symbolInfo->boolValue = value;
    symbolInfo->Type = TYPE_BOOL;
}

SymbolInfo *BooleanConstant::evaluate(RuntimeContext *ctx) {
    return symbolInfo;
}

TYPE_INFO BooleanConstant::typeCheck(CompilationContext *ctx) {
    return symbolInfo->Type;
}

TYPE_INFO BooleanConstant::getType() { return symbolInfo->Type; }
