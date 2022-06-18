#pragma once
#include <cstddef>
#include <string>
#ifndef AST_H

#include "common.h"
#include <iostream>
#include <stdexcept>

#define AST_H

enum Operator { OP_PLUS, OP_MINUS, OP_MUL, OP_DIV };

// Expression

class Exp {

public:
    Exp();
    virtual SymbolInfo *evaluate(RuntimeContext *ctx) = 0;
    virtual TYPE_INFO typeCheck(CompilationContext *ctx) = 0;
    virtual TYPE_INFO getType() = 0;
    virtual ~Exp();
};

class BooleanConstant : public Exp {
    SymbolInfo *symbolInfo;

public:
    BooleanConstant(bool value);
    ~BooleanConstant();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
};

class NumericConstant : public Exp {
    SymbolInfo *symbolInfo;

public:
    NumericConstant(double value);
    ~NumericConstant();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
};

class StringLiteral : public Exp {
    SymbolInfo *symbolInfo;

public:
    StringLiteral(std::string value);
    ~StringLiteral();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
};


class Variable : public Exp {
  SymbolInfo *symbolInfo;
  TYPE_INFO type_;
  std::string getName();

  public:
  Variable(SymbolInfo *symbolInfo);
  Variable(CompilationContext *ctx, std::string name, double value);
  Variable(CompilationContext *ctx, std::string name, bool value);
  Variable(CompilationContext *ctx, std::string name, std::string value);
  ~Variable();

  SymbolInfo *evaluate(RuntimeContext *ctx);
  TYPE_INFO typeCheck(CompilationContext *ctx);
  TYPE_INFO getType();

    
};

class BinaryPlus : public Exp {
    Exp *left , *right;
    TYPE_INFO type_;

public:
    BinaryPlus(Exp *left, Exp *right);
    ~BinaryPlus();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
};

class BinaryMinus : public Exp {
    Exp *left, *right;
    TYPE_INFO type_;

public:
    BinaryMinus(Exp *left, Exp *right);
    ~BinaryMinus();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
};

class BinaryMul : public Exp {
    Exp *left, *right;
    TYPE_INFO type_;

public:
    BinaryMul(Exp *left, Exp *right);
    ~BinaryMul();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
};

class BinaryDiv : public Exp {
    Exp *left, *right;
    TYPE_INFO type_;

public:
    BinaryDiv(Exp *left, Exp *right);
    ~BinaryDiv();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
};

// class UnaryExp : public Exp {
//     Exp *exp;
//     Operator op;

// public:
//     UnaryExp(Exp *exp, Operator op);
//     double evaluate(RuntimeContext *ctx);
//     ~UnaryExp();
// };

// Statements

class Stmt {

public:
    Stmt();
    virtual double evaluate(RuntimeContext *ctx) = 0;
    virtual ~Stmt();
};

class PrintStatement : public Stmt {
    Exp *exp;

public:
    PrintStatement(Exp *exp);
    double evaluate(RuntimeContext *ctx);
    ~PrintStatement();
};

class PrintLnStatement : public Stmt {
    Exp *exp;

public:
    PrintLnStatement(Exp *exp);
    double evaluate(RuntimeContext *ctx);
    ~PrintLnStatement();
};

// namespace slang
#endif /* AST_H */
