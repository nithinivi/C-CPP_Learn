#include "lexer.h"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace slang;

std::ostream &operator<<(std::ostream &strm, Token tt) {
  const std::string nameTT[] = {"ILLEGAL_TOKEN", "TOK_NULL",
                                "TOK_PLUS",      "TOK_SUB",
                                "TOK_MUL",       "TOK_DIV",
                                "TOK_OPAREN",    "TOK_CPAREN",
                                "TOK_DOUBLE",    "TOK_UNQUOTED_STRING",
                                "TOK_SEMI"};
  return strm << nameTT[tt];
}

Lexer::Lexer(char *exp) {
  this->exp = exp;
  this->length = strlen(exp);
  this->index = 0;
}

double Lexer::getNumber() { return number; }

Token Lexer::getToken() {
  Token tok = ILLEGAL_TOKEN;

  while (index < length && (exp[index] == ' ' || exp[index] == '\t'))
    index++;

  if (index == length)
    return TOK_NULL;

  switch (exp[index]) {
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
  default:

    if (isdigit(exp[index]) != 0) {
      int numStartIndex = index;
      while (index < length && isdigit(exp[index]) != 0)
        index++;

      std::size_t lenOfNum = index - numStartIndex;
      number = std::stod(exp + numStartIndex, &lenOfNum);
      tok = TOK_DOUBLE;

    } else
      throw std::runtime_error("Unknown character found while tokenizing ");
  }

  std::cout << tok << std::endl;
  return tok;
}
