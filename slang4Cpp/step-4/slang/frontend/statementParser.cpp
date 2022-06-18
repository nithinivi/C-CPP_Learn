#include "../include/lexer.h"
#include "../include/parser.h"

Stmt *RDParser::Statement() {
  Stmt *returnValue;
  switch (currentToken) {
  case TOK_PRINT:
    returnValue = ParsePrintStatement();
    getNext();
    break;
  case TOK_PRINTLN:
    returnValue = ParsePrintLnStatement();
    getNext();
    break;
  default:
    throw std::runtime_error("Illegal Token");
  }
  return returnValue;
}

Stmt *RDParser::ParsePrintStatement() {
  getNext();
  Exp *exp = Expr();
  if (currentToken != TOK_SEMI)
    throw std::runtime_error("Expected ;");
  PrintStatement *spt = new PrintStatement(exp);
  return spt;
}

Stmt *RDParser::ParsePrintLnStatement() {
  getNext();
  Exp *exp = Expr();
  if (currentToken != TOK_SEMI)
    throw std::runtime_error("Expected ;");
  PrintLnStatement *spt = new PrintLnStatement(exp);
  return spt;
}

std::vector<Stmt *> RDParser::Parse() {
  getNext();
  return StatementList();
}

std::vector<Stmt *> RDParser::StatementList() {
  std::vector<Stmt *> newArry;
  while (currentToken != TOK_NULL) {
    Stmt *stmt = RDParser::Statement();
    if (stmt)
      newArry.push_back(stmt);
  }
  return newArry;
};
