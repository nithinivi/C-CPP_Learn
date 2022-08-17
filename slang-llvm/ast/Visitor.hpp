
// forward declaration
class NumericConstant;
class BinaryExpr;
class UnaryExpr;
class IExprVisitor;

#ifndef VISITOR_H
#define VISITOR_H

#include "Context.hpp"
#include "Symbol.hpp"
#include <map>
#include <string>

class IExprVisitor {
public:
    virtual Symbol visit(Context ctx, NumericConstant& num) = 0;
    virtual Symbol visit(Context ctx, BinaryExpr& bin) = 0;
    virtual Symbol visit(Context ctx, UnaryExpr& un) = 0;
};

class IRVisitor : public IExprVisitor {

public:
    IRVisitor();
    ~IRVisitor();

    Symbol visit(Context ctx, NumericConstant& num);
    Symbol visit(Context ctx, BinaryExpr& bin);
    Symbol visit(Context ctx, UnaryExpr& un);
};

#endif // !1
