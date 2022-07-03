#pragma once

#ifndef AST_H
#include "common.h"
#include "context.h"
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <string>

#define AST_H

// Expression

class Exp {

public:
    Exp();
    virtual ~Exp();
    virtual SymbolInfo *evaluate(RuntimeContext *ctx) = 0;
    virtual TYPE_INFO typeCheck(CompilationContext *ctx) = 0;
    virtual TYPE_INFO getType() = 0;

};

// Statement

class Stmt {

public:
    Stmt();
    virtual SymbolInfo *execute(RuntimeContext *ctx) = 0; //
    virtual ~Stmt();
};

#endif /* AST_H */
