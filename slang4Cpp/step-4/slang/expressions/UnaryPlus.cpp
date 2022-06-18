#include "../include/ast_expression.hpp"
#include "../include/common.hpp"

UnaryPlus::UnaryPlus(Exp *exp) { //
    exp = exp;
}

UnaryPlus::~UnaryPlus() { delete exp; }

SymbolInfo *UnaryPlus::evaluate(RuntimeContext *ctx) {
    SymbolInfo *eval_exp = exp->evaluate(ctx);

    if (eval_exp->type_ == TYPE_NUMERIC) {
        SymbolInfo *info = new SymbolInfo();
        info->type_ = TYPE_NUMERIC;
        info->stringValue = eval_exp->doubleValue;
        info->symbolName = "";
        return info;
    } else
        throw "type Mismatch";

    return nullptr;
}

TYPE_INFO UnaryPlus::typeCheck(CompilationContext *ctx) {
    TYPE_INFO exp_t_ = exp->typeCheck(ctx);

    if (exp_t_ != TYPE_NUMERIC)
        throw "Type mismatch failure";

    type_ = TYPE_NUMERIC;
    return type_;
}

TYPE_INFO UnaryPlus::getType() { return type_; }
