
#ifndef DEBUG_H
#define DEBUG_H

#include "../contexts/Symbol.hpp"
#include "../meta/Meta.hpp"
#include "Visitor.hpp"

class Expr //
{
protected:
    Type type;

public:
    Expr();
    virtual ~Expr() = default;
    virtual Symbol accept(IExprVisitor& expr_visitor) = 0;
    virtual Type getType() { return type; };
    virtual void setType(Type type) { this->type = type; };
};

class NumericConstant : public Expr {
    double value;

public:
    NumericConstant(double value);
    ~NumericConstant();
    Symbol accept(IExprVisitor& expr_visitor);
    double getValue();
};

class BinaryExpr : public Expr {
private:
    Expr *left, *right;
    OPERATOR op;

public:
    BinaryExpr(Expr* l, Expr* r, OPERATOR op);
    ~BinaryExpr();
    Expr& getLeft();
    Expr& getRight();
    OPERATOR getOp();
    Symbol accept(IExprVisitor& expr_visitor);
};

class UnaryExpr : public Expr {
private:
    Expr* exp;
    OPERATOR op;

public:
    UnaryExpr(Expr* exp, OPERATOR op);
    ~UnaryExpr();
    Expr& getExp();
    OPERATOR getOp();
    Symbol accept(IExprVisitor& expr_visitor);
};

#endif // DEBUG
