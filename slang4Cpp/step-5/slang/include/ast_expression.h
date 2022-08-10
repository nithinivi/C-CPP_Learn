#pragma once
#ifndef AST_EXPRESSION_H

#include "ast.h"
#include "common.h"
#include "context.h"
#include "llvm/IR/Value.h"
#define AST_EXPRESSION_H

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
    SymbolInfo *info;

public:
    NumericConstant(double value);
    ~NumericConstant();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
    llvm::Value *codegen();
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
    SymbolInfo *info;
    TYPE_INFO type_;

public:
    Variable(SymbolInfo *symbolInfo);
    Variable(CompilationContext *ctx, std::string name, double value);
    Variable(CompilationContext *ctx, std::string name, bool value);
    Variable(CompilationContext *ctx, std::string name, std::string value);
    ~Variable();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();

    std::string getName();
};

class BinaryPlus : public Exp {
    Exp *left, *right;
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

class UnaryPlus : public Exp {
    Exp *expr;
    TYPE_INFO type_;

public:
    UnaryPlus(Exp *expr);
    ~UnaryPlus();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
};

class UnaryMinus : public Exp {
    Exp *expr;
    TYPE_INFO type_;

public:
    UnaryMinus(Exp *expr);
    ~UnaryMinus();

    SymbolInfo *evaluate(RuntimeContext *ctx);
    TYPE_INFO typeCheck(CompilationContext *ctx);
    TYPE_INFO getType();
};

#endif /* AST_EXPRESSION_H */
