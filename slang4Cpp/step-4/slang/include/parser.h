#pragma once

#ifndef PARSER_H
#include "ast.h"
#include "lexer.h"
#include <vector>

#define PARSER_H

using namespace slang;

class RDParser : public Lexer {
  Token currentToken;
  Token lastToken;
  Token getNext();

  
  Exp *Expr();
  Exp *Term();
  Exp *Factor();

  Stmt *Statement();
  Stmt *ParsePrintStatement();
  Stmt *ParsePrintLnStatement();

  std::vector<Stmt *> StatementList();

public:
  RDParser(char *exp);
  ~RDParser();
  Exp *CallExpr();
  std::vector<Stmt *> Parse();
};

#endif /* PARSER_H */
