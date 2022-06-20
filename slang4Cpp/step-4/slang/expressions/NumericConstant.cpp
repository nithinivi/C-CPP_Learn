#include "../include/ast_expression.h"
#include "../include/common.h"

NumericConstant::NumericConstant(double value) {
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = "";
    symbolInfo->doubleValue = value;
    symbolInfo->type_ = TYPE_NUMERIC;
}

NumericConstant::~NumericConstant() {
  delete symbolInfo;
}

SymbolInfo *NumericConstant::evaluate(RuntimeContext *ctx) {
    return symbolInfo;
}

TYPE_INFO NumericConstant::typeCheck(CompilationContext *ctx) {
    return symbolInfo->type_;
}

TYPE_INFO NumericConstant::getType() { return symbolInfo->type_; }
