class IExprVisitor;

#ifndef DEBUG_H
#define DEBUG_H

#include "Context.hpp"
#include "Meta.hpp"
#include "Symbol.hpp"

class Expr //
{
protected:
    Symbol* symbol;

public:
    Expr();
    virtual ~Expr() = default;
    virtual Symbol& accept(Context context, IExprVisitor& expr_visitor) = 0;

    Symbol& getSymbol() { return *symbol; };
    void setSymbol(Symbol* symb) { this->symbol = symb; };

    TypeInfo getType() { return symbol->getType(); }
    void setType(TypeInfo type) { symbol->setType(type); }
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
    Symbol& accept(Context context, IExprVisitor& expr_visitor);
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
    Symbol& accept(Context context, IExprVisitor& expr_visitor);
};

#endif // DEBUG
