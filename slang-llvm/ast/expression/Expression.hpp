class IExprVisitor;

#ifndef DEBUG_H
#define DEBUG_H

#include "Context.hpp"
#include "Meta.hpp"
#include "Symbol.hpp"

class Expr //
{
protected:
    TypeInfo Type;

public:
    Expr();
    virtual ~Expr() = default;
    virtual Symbol accept(Context context, IExprVisitor& expr_visitor) = 0;
    virtual TypeInfo getType() { return Type; };
    virtual void setType(TypeInfo Type) { this->Type = Type; };
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
    Symbol accept(Context context, IExprVisitor& expr_visitor);
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
    Symbol accept(Context context, IExprVisitor& expr_visitor);
};

#endif // DEBUG
