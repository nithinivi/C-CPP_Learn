#include "../include/ast_expression.h"
#include "../include/common.h"

NumericConstant::NumericConstant(double value) {
    this->info = new SymbolInfo();
    this->info->symbolName = "";
    this->info->doubleValue = value;
    this->info->type_ = TYPE_NUMERIC;
}

NumericConstant::~NumericConstant() { delete info; }

SymbolInfo *NumericConstant::evaluate(RuntimeContext *ctx) { return info; }

TYPE_INFO NumericConstant::typeCheck(CompilationContext *ctx) {
    return info->type_;
}

TYPE_INFO NumericConstant::getType() { return info->type_; }
