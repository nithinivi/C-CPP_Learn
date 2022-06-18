#include "../include/ast_expression.hpp"
#include "../include/common.hpp"

NumericConstant::NumericConstant(double value) {
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = "";
    symbolInfo->doubleValue = value;
    symbolInfo->type_ = TYPE_NUMERIC;
}

SymbolInfo *NumericConstant::evaluate(RuntimeContext *ctx) {
    return symbolInfo;
}

TYPE_INFO NumericConstant::typeCheck(CompilationContext *ctx) {
    return symbolInfo->type_;
}

TYPE_INFO NumericConstant::getType() { return symbolInfo->type_; }
