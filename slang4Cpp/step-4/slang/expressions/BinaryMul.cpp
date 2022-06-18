#include "../include/ast_expression.hpp"
#include "../include/common.hpp"

BinaryMul::BinaryMul(Exp *left, Exp *right) { //
    left = left;
    right = right;
}

BinaryMul::~BinaryMul() {
    delete left;
    delete right;
}

SymbolInfo *BinaryMul::evaluate(RuntimeContext *ctx) {
    SymbolInfo *eval_l = left->evaluate(ctx);
    SymbolInfo *eval_r = right->evaluate(ctx);

    if (eval_l->type_ == TYPE_NUMERIC && eval_r->type_ == TYPE_NUMERIC) {
        SymbolInfo *info = new SymbolInfo();
        info->type_ = TYPE_NUMERIC;
        info->stringValue = eval_l->doubleValue * eval_r->doubleValue;
        info->symbolName = "";
        return info;
    } else
        throw "type Mismatch";

    return nullptr;
}

TYPE_INFO BinaryMul::typeCheck(CompilationContext *ctx) {
    TYPE_INFO left_t_ = left->typeCheck(ctx);
    TYPE_INFO right_t_ = left->typeCheck(ctx);

    if (left_t_ != right_t_ && right_t_ != TYPE_NUMERIC)
        throw "Type mismatch failure";

    type_ = TYPE_NUMERIC;
    return type_;
}

TYPE_INFO BinaryMul::getType() { return type_; }
