#include "../include/ast_expression.h"
#include "../include/context.h"

BinaryPlus::BinaryPlus(Exp *left, Exp *right) {
    this->left = left;
    this->right = right;
}

BinaryPlus::~BinaryPlus() {
    delete left;
    delete right;
}

SymbolInfo *BinaryPlus::evaluate(RuntimeContext *ctx) {
    SymbolInfo *eval_l = left->evaluate(ctx);
    SymbolInfo *eval_r = right->evaluate(ctx);

    if (eval_l->type_ == TYPE_STRING && eval_r->type_ == TYPE_STRING) {
        SymbolInfo *info = new SymbolInfo();
        info->type_ = TYPE_STRING;
        info->stringValue = eval_l->stringValue + eval_r->stringValue;
        info->symbolName = "";
        return info;
    }

    else if (eval_l->type_ == TYPE_NUMERIC && eval_r->type_ == TYPE_NUMERIC) {
        SymbolInfo *info = new SymbolInfo();
        info->type_ = TYPE_NUMERIC;
        info->doubleValue = eval_l->doubleValue + eval_r->doubleValue;
        info->symbolName = "";
        return info;
    }

    else
        throw "type Mismatch";

    return nullptr;
}

TYPE_INFO BinaryPlus::typeCheck(CompilationContext *ctx) {
    TYPE_INFO left_t_ = left->typeCheck(ctx);
    TYPE_INFO right_t_ = right->typeCheck(ctx);

    if (left_t_ != right_t_ && right_t_ == TYPE_BOOL)
        throw "Type mismatch failure";

    type_ = right_t_;
    return type_;
}

TYPE_INFO BinaryPlus::getType() { return type_; }
