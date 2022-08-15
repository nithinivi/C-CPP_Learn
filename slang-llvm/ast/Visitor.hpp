// forward declaration
class NumericConstant;
class BinaryExpr;
class UnaryExpr;
class IExprVisitor;

#include "Context.hpp"
#include "Symbol.hpp"

#ifndef VISITOR_H
#define VISITOR_H

class IExprVisitor {
public:
    virtual Symbol visit(Context ctx, NumericConstant& num) = 0;
    virtual Symbol visit(Context ctx, BinaryExpr& bin) = 0;
    virtual Symbol visit(Context ctx, UnaryExpr& un) = 0;
};

#endif // !1
