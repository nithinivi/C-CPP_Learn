#pragma once

#ifndef PARSER_H
#include "../include/context.h"
#include "ast.h"
#include "ast_statement.h"
#include "lexer.h"
#include <vector>
#define PARSER_H

class RDParser : public Lexer {
    Token currentToken;
    Token lastToken;
    Token getNext();

    Exp *Expr(CompilationContext *ctx);
    Exp *Term(CompilationContext *ctx);
    Exp *Factor(CompilationContext *ctx);

    Stmt *Statement(CompilationContext *ctx);
    Stmt *ParsePrintStatement(CompilationContext *ctx);
    Stmt *ParsePrintLnStatement(CompilationContext *ctx);
    Stmt *ParseVariableStatement(CompilationContext *ctx);
    Stmt *ParseAssignmentStatement(CompilationContext *ctx);

    std::vector<Stmt *> StatementList(CompilationContext *ctx);

public:
    RDParser(std::string exp);
    ~RDParser();
    Exp *CallExpr(CompilationContext *ctx);
    std::vector<Stmt *> Parse(CompilationContext *ctx);
};

#endif /* PARSER_H */
