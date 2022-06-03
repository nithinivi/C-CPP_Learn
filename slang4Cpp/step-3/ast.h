#pragma once
#ifndef AST_H
#include <iostream>
#include <stdexcept>
#define AST_H
namespace slang {
class RuntimeContext {
public:
  RuntimeContext(){};
};

enum Operator { OP_PLUS, OP_MINUS, OP_MUL, OP_DIV };

class Exp {

public:
  Exp();
  virtual double evaluate(RuntimeContext *ctx) = 0;
  virtual ~Exp();
};

class NumericConst : public Exp {
  double value;

public:
  NumericConst(double value);
  double evaluate(RuntimeContext *ctx);
  ~NumericConst();
};

class BinaryExp : public Exp {
  Exp *left, *right;
  Operator op;

public:
  BinaryExp(Exp *left, Exp *right, Operator op);
  double evaluate(RuntimeContext *ctx);
  ~BinaryExp();
};

// 1 + (1 + 2)
//+ 1
// -1
// BinaryExp( NUM(1), BinaryExp( NUM(1), NUM(2)))

class UnaryExp : public Exp {
  Exp *exp;
  Operator op;

public:
  UnaryExp(Exp *exp, Operator op);
  double evaluate(RuntimeContext *ctx);
  ~UnaryExp();
};

} // namespace slang

#endif /* AST_H */