#include "../include/ast_expression.h"

#include "../include/common.h"
#include "llvm/IR/Constants.h"

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

llvm::Value *NumericConstant::codegen() {
    return llvm::ConstantFP::get(*TheContext, llvm::APFloat(info->doubleValue))
}