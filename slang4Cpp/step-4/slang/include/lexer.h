#pragma once
#ifndef LEXER_H
#include <string>
#define LEXER_H


#define KEYWORDS_COUNT 7

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


  TOK_VAR_NUMBER,
  TOK_VAR_STRING,
  TOK_VAR_BOOL,
  TOK_NUMERIC,
  TOK_COMMENT,
  TOK_BOOL_TRUE,
  TOK_BOOL_FALSE,
  TOK_STRING,
  TOK_ASSIGN
  
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
  std::string exp;
  int index;
  int length;
  double number;
  std::string last_str;
  ValueTable *value_table[KEYWORDS_COUNT];

public:
  Lexer(std::string exp);
  Token getToken();
  double getNumber();
  std::string getString();
};



#endif /* LEXER_H */
