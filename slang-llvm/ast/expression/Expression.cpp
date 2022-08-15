// visitor pattern for processing composite

#include <iostream>
#include <string>

#include "Expression.hpp"
#include "Visitor.hpp"

Expr::Expr() {}
// Numeric constants implementations

NumericConstant::NumericConstant(double value) { this->value = value; };
NumericConstant::~NumericConstant(){};

double NumericConstant::accept(IExprVisitor& expr_visitor) {
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

double BinaryExpr::accept(IExprVisitor& expr_visitor) {
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
double UnaryExpr::accept(IExprVisitor& expr_visitor) {
    return expr_visitor.visit(*this);
}

Expr& UnaryExpr::getExp() { return *exp; }
OPERATOR UnaryExpr::getOp() { return op; }
