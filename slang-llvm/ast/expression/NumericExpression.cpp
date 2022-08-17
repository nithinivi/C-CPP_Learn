// Numeric constants implementations
#include "NumericExpression.h"
#include "Context.hpp"
#include "Meta.hpp"
#include "Symbol.hpp"
#include "Visitor.hpp"

NumericConstant::NumericConstant(double value) {
    this->info = new Symbol();
    info->setName("");
    info->setType(TYPE_NUMERIC);
    info->setBoolValue(value);
};
NumericConstant::~NumericConstant(){};

Symbol NumericConstant::accept(Context ctx, IExprVisitor& expr_visitor) {
    return expr_visitor.visit(ctx, *this);
}

double NumericConstant::getValue() { return value; }
