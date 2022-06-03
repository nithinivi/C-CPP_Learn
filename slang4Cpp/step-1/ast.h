a#pragma once
#ifndef AST_H
#include <iostream>
#include <stdexcept>
#define AST_H


namespace ast {

     class RuntimeContext{
          RuntimeContext(){};
     };

     class Exp{

     public:
          Exp();
          virtual double evaluate(RuntimeContext* ctx)=0;
          virtual ~Exp();
     };

     enum Operator { OP_PLUS, OP_MINUS, OP_MUL, OP_DIV };

     class NumericConstant : public Exp {
          double value;

     public:
          NumericConstant(double value);
          double evaluate(RuntimeContext* ctx);
          ~NumericConstant();
     };


     class BinaryExp{
          Exp* left, * right;
          Operator op;


     public:
          BinaryExp(Exp *left, Exp *right, Operator op);
          double evaluate(RuntimeContext *ctx);
          ~BinaryExp();
     };


     class UnaryExp : public Exp{
          Exp *expression;
          Operator op;

     public:
          UnaryExp(Exp* expression, Operator op);
          double evaluate(RuntimeContext *ctx);
          ~UnaryExp();
     };


} // namespace ast

#endif /* AST_H */
