#include "../include/ast.h"

using namespace slang;

Exp::Exp(){};
Exp::~Exp(){};

NumericConst::NumericConst(double value) { this->value = value; }

double NumericConst::evaluate(RuntimeContext *ctx) { return value; }

NumericConst::~NumericConst() {}

BinaryExp::BinaryExp(Exp *left, Exp *right, Operator op) {
  this->left = left;
  this->right = right;
  this->op = op;
}

double BinaryExp::evaluate(RuntimeContext *ctx) {
  switch (op) {

  case OP_PLUS:
    return left->evaluate(ctx) + right->evaluate(ctx);
  case OP_MINUS:
    return left->evaluate(ctx) - right->evaluate(ctx);
  case OP_MUL:
    return left->evaluate(ctx) * right->evaluate(ctx);
  case OP_DIV:
    return left->evaluate(ctx) / right->evaluate(ctx);

  default:
    throw std::runtime_error("Unsupported Operator");
  }
}

BinaryExp::~BinaryExp() {
  delete left;
  delete right;
}

UnaryExp::UnaryExp(Exp *exp, Operator op) {
  this->exp = exp;
  this->op = op;
}

double UnaryExp::evaluate(RuntimeContext *ctx) {
  switch (op) {

  case OP_PLUS:
    return exp->evaluate(ctx);
  case OP_MINUS:
    return -exp->evaluate(ctx);
  default:
    throw std::runtime_error("Unsupported Operator");
  }
}

UnaryExp::~UnaryExp() { delete exp; }
