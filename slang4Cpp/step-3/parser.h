#pragma once

#ifndef PARSER_H
#include "ast.h"
#include "lexer.h"

#define PARSER_H

using namespace slang;

class RDParser : public Lexer {
  Token currentToken;
  Token lastToken;
  Token getNext();

  Exp *CallExpr();
  Exp *Expr();
  Exp *Term();
  Exp *Factor();

  Stmt *Statement();
  Stmt *ParsePrintStatement();
  Stmt *ParsePrintLnStatement();

public:
  RDParser(char *exp);
  ~RDParser();

  Stmt[] Parse();
};

#endif /* PARSER_H */
