#include "../include/builder.h"
#include "../include/parser.h"

using namespace slang;

ExpressionBuilder::ExpressionBuilder(std::string exp_string) {
    this->exp_string = exp_string;
}

// ExpressionBuilder::~ExpressionBuilder() { delete exp_string; }

Exp *ExpressionBuilder::getExpression(CompilationContext *ctx) {
    try {
        RDParser parser(exp_string);
        return parser.CallExpr(ctx);

    } catch (const std::exception &e) {
        std::cerr << e.what() << '\n';
    }
    return NULL;
}
