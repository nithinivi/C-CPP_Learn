#pragma once
#ifndef LEXER_H
#define LEXER_H

namespace slang {

enum Token {
  ILLEGAL_TOKEN = -1,
  TOK_NULL,
  TOK_PLUS,
  TOK_SUB,
  TOK_MUL,
  TOK_DIV,
  TOK_OPAREN,
  TOK_CPAREN,
  TOK_DOUBLE,
  TOK_UNQUOTED_STRING,
  TOK_SEMI
};

class Lexer {
  char *exp;
  int index;
  int length;
  double number;

public:
  Lexer(char *exp);
  Token getToken();
  double getNumber();
};

} // namespace slang

#endif /* LEXER_H */
