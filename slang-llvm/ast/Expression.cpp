// visitor pattern for processing composite

#include <iostream>
#include <string>

#include "../meta/Meta.hpp"
#include "Expression.hpp"
#include "Symbol.hpp"
#include "Visitor.hpp"

Expr::Expr() {}
// Numeric constants implementations

NumericConstant::NumericConstant(double value) { this->value = value; };
NumericConstant::~NumericConstant(){};

Symbol NumericConstant::accept(IExprVisitor& expr_visitor) {
    return expr_visitor.visit(*this);
}

double NumericConstant::getValue() { return value; }

// Binary Expression  implementations

BinaryExpr::BinaryExpr(Expr* left, Expr* right, OPERATOR op) {
    this->left = left;
    this->right = right;
    this->op = op;
}
BinaryExpr::~BinaryExpr() {}

Symbol BinaryExpr::accept(IExprVisitor& expr_visitor) {
    return expr_visitor.visit(*this);
}

Expr& BinaryExpr::getLeft() { return *left; }
Expr& BinaryExpr::getRight() { return *right; }
OPERATOR BinaryExpr::getOp() { return op; }

// Unary Expression implementations

UnaryExpr::UnaryExpr(Expr* exp, OPERATOR op) {
    this->exp = exp;
    this->op = op;
}
UnaryExpr::~UnaryExpr() {}
Symbol UnaryExpr::accept(IExprVisitor& expr_visitor) {
    return expr_visitor.visit(*this);
}

Expr& UnaryExpr::getExp() { return *exp; }
OPERATOR UnaryExpr::getOp() { return op; }
