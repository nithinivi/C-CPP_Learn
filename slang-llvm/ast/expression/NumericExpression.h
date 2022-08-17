#ifndef NUMERICEXPRESSION_H
#define NUMERICEXPRESSION_H

#include "Context.hpp"
#include "Expression.hpp"
#include "Symbol.hpp"

class NumericConstant : public Expr {
    double value;

public:
    NumericConstant(double value);
    ~NumericConstant();
    Symbol& accept(Context context, IExprVisitor& expr_visitor);
    double getValue();
};

#endif // NUMERICEXPRESSION_H
