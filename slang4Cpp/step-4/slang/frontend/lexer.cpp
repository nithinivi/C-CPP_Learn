#include "../include/lexer.h"
#include <cctype>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <stdexcept>
#include <string>

using namespace slang;

std::string to_string(char *a, int size) {
  std::string str = "";
  for (int i = 0; i < size; i++)
    str += a[i];
  return str;
}

Lexer::Lexer(char *exp) {
  this->exp = exp;
  this->length = strlen(exp);
  this->index = 0;

  value_table[0] = new ValueTable(TOK_PRINT, "PRINT");
  value_table[1] = new ValueTable(TOK_PRINTLN, "PRINTLINE");
}

double Lexer::getNumber() { return number; }

Token Lexer::getToken() {
start:
  Token tok = ILLEGAL_TOKEN;

  while (index < length && (exp[index] == ' ' || exp[index] == '\t'))
    index++;

  if (index == length)
    return TOK_NULL;

  switch (exp[index]) {
  case '\n':
  case '\r':
    index++;
    goto start;
  case '+':
    tok = TOK_PLUS;
    index++;
    break;
  case '-':
    tok = TOK_SUB;
    index++;
    break;
  case '/':
    tok = TOK_DIV;
    index++;
    break;
  case '*':
    tok = TOK_MUL;
    index++;
    break;
  case ')':
    tok = TOK_CPAREN;
    index++;
    break;
  case '(':
    tok = TOK_OPAREN;
    index++;
    break;
  case ';':
    tok = TOK_SEMI;
    index++;
    break;
  default:
    if (isdigit(exp[index])) {
      int numStartIndex = index;
      while (index < length && isdigit(exp[index]))
        index++;

      std::size_t lenOfNum = index - numStartIndex;
      number = std::stod(exp + numStartIndex, &lenOfNum);
      tok = TOK_DOUBLE;

    } else if (isalpha(exp[index])) {
      int numStartIndex = index;
      while (index < length && isalpha(exp[index]))
        index++;

      std::size_t lenOfNum = index - numStartIndex;
      std::string str = to_string(exp + numStartIndex, lenOfNum);
      std::cout << str << std::endl;
      last_str = str.c_str();

      for (int i = 0; i < KEYWORDS_COUNT; ++i) {
        if (last_str == value_table[i]->value) {
          ValueTable *t = value_table[i];
          return t->token;
        }
      }
      return TOK_UNQUOTED_STRING;
    } else
      throw std::runtime_error("Unknown character found while tokenizing ");
  }

  // std::cout << tok << std::endl;
  return tok;
}
