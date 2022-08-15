// forward declaration
class NumericConstant;
class BinaryExpr;
class UnaryExpr;
class IExprVisitor;

#ifndef VISITOR_H
#define VISITOR_H
#include "Symbol.hpp"

class IExprVisitor {
public:
    virtual Symbol visit(NumericConstant& num) = 0;
    virtual Symbol visit(BinaryExpr& bin) = 0;
    virtual Symbol visit(UnaryExpr& un) = 0;
};

#endif // !1
