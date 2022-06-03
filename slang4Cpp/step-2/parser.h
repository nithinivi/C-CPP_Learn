#pragma once

#ifndef PARSER_H
#include "ast.h"
#include "lexer.h"

#define PARSER_H

using namespace slang;

class RDParser : public Lexer {
  Token currentToken;

public:
  RDParser(char *exp);
  ~RDParser();

  Exp *CallExpr();
  Exp *Expr();
  Exp *Term();
  Exp *Factor();
};

#endif /* PARSER_H */
