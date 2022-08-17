// Numeric constants implementations
#include "NumericExpression.h"
#include "Context.hpp"
#include "Meta.hpp"
#include "Symbol.hpp"
#include "Visitor.hpp"

NumericConstant::NumericConstant(double value) {
    this->symbol = new Symbol();
    symbol->setName("");
    symbol->setType(TYPE_NUMERIC);
    symbol->setBoolValue(value);
};

NumericConstant::~NumericConstant(){};

Symbol& NumericConstant::accept(Context ctx, IExprVisitor& expr_visitor) {
    return expr_visitor.visit(ctx, *this);
}

double NumericConstant::getValue() { return value; }
