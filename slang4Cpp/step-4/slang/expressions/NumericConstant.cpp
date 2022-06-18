#include "../include/ast.h"
#include "../include/common.h"

NumericConstant::NumericConstant(double value) {
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = "";
    symbolInfo->doubleValue = value;
    symbolInfo->Type = TYPE_NUMERIC;
}

SymbolInfo *NumericConstant::evaluate(RuntimeContext *ctx) {
    return symbolInfo;
}

TYPE_INFO NumericConstant::typeCheck(CompilationContext *ctx) {
    return symbolInfo->Type;
}

TYPE_INFO NumericConstant::getType() { return symbolInfo->Type; }
