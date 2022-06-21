#pragma once
#ifndef AST_STATEMENTS_H

#include "ast.h"
#include "ast_expression.h"
#include "context.h"

#define AST_STATEMENTS_H

class VariableDeclStatement : public Stmt {
    SymbolInfo *info;
    Variable *var = nullptr;

public:
    VariableDeclStatement(SymbolInfo *info);
    ~VariableDeclStatement();
    SymbolInfo *execute(RuntimeContext *ctx);
};

class AssignmentStatement : public Stmt {
    Variable *var;
    Exp *exp;

public:
    AssignmentStatement(Variable *var, Exp *exp);
    AssignmentStatement(SymbolInfo *info, Exp *exp);
    ~AssignmentStatement();
    SymbolInfo *execute(RuntimeContext *ctx);
};

class PrintStatement : public Stmt {
    Exp *exp;

public:
    PrintStatement(Exp *exp);
    SymbolInfo *execute(RuntimeContext *ctx);
    ~PrintStatement();
};

class PrintLnStatement : public Stmt {
    Exp *exp;

public:
    PrintLnStatement(Exp *exp);
    SymbolInfo *execute(RuntimeContext *ctx);
    ~PrintLnStatement();
};

#endif /* AST_STATEMENTS_H */
