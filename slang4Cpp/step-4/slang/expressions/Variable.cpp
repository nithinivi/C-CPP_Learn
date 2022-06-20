#include "../include/ast_expression.h"
#include "../include/context.h"

#include <cstddef>
#include <iostream>
#include <string>

Variable::Variable(SymbolInfo *symbolInfo) { symbolInfo = symbolInfo; }

Variable::Variable(CompilationContext *ctx, std::string name, double value) {
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = name;
    symbolInfo->doubleValue = value;
    symbolInfo->type_ = TYPE_NUMERIC;
}
Variable::Variable(CompilationContext *ctx, std::string name, bool value) {
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = name;
    symbolInfo->boolValue = value;
    symbolInfo->type_ = TYPE_BOOL;
}

Variable::Variable(CompilationContext *ctx, std::string name,
                   std::string value) {
    symbolInfo = new SymbolInfo();
    symbolInfo->symbolName = name;
    symbolInfo->stringValue = value;
    symbolInfo->type_ = TYPE_STRING;
}
Variable::~Variable() { delete symbolInfo; }

SymbolInfo *Variable::evaluate(RuntimeContext *ctx) {
    SymbolTable *table = ctx->symbolTable;
    if (!table)
        return nullptr;

    SymbolInfo *info = table->get(getName());
    return info;
}

TYPE_INFO Variable::typeCheck(CompilationContext *ctx) {
    if (!ctx->table)
        return TYPE_ILLEGAL;

    SymbolInfo *info = ctx->table->get(getName());
    if (!info)
        return TYPE_ILLEGAL;

    type_ = info->type_;
    return type_;
}

// should only be invoked after using typecheck on AST
TYPE_INFO Variable::getType() { return type_; }

std::string Variable::getName() { return symbolInfo->symbolName; }
