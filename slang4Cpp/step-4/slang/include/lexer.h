#pragma once
#ifndef LEXER_H
#include <string>
#define LEXER_H

namespace slang {

#define KEYWORDS_COUNT 2

enum Token {
  ILLEGAL_TOKEN = 0,
  TOK_NULL,

  TOK_PLUS,
  TOK_SUB,
  TOK_MUL,
  TOK_DIV,
  TOK_OPAREN,
  TOK_CPAREN,
  TOK_DOUBLE,

  // Statements
  TOK_PRINT,
  TOK_PRINTLN,
  TOK_UNQUOTED_STRING,
  TOK_SEMI,

};

class ValueTable {
public:
  Token token;
  std::string value;

  ValueTable(Token token, std::string value) {
    this->token = token;
    this->value = value;
  }
};

class Lexer {
  char *exp;
  int index;
  int length;
  double number;
  char *last_str;
  ValueTable *value_table[KEYWORDS_COUNT];

public:
  Lexer(char *exp);
  Token getToken();
  double getNumber();
};

} // namespace slang

#endif /* LEXER_H */
