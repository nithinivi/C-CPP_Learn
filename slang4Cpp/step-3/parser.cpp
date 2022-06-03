#include "parser.h"

RDParser::RDParser(char *exp) : Lexer(exp){};
RDParser::~RDParser(){};

Token RDParser::getNext() {
  lastToken = currentToken;
  currentToken = getToken();
  return currentToken;
}

Exp *RDParser::CallExpr() {
  currentToken = getToken();
  return Expr();
}

Exp *RDParser::Expr() {
  Exp *retValue = Term();
  while (currentToken == TOK_PLUS || currentToken == TOK_SUB) //
  {
    getNext();
    Exp *right = Expr();
    retValue = new BinaryExp(retValue, right,
                             lastToken == TOK_PLUS ? OP_PLUS : OP_MINUS);
  }
  return retValue;
}

Exp *RDParser::Term() {
  Exp *retValue = Factor();
  while (currentToken == TOK_MUL || currentToken == TOK_DIV) {
    getNext();
    Exp *right = Term();
    retValue =
        new BinaryExp(retValue, right, lastToken == TOK_MUL ? OP_MUL : OP_DIV);
  }
  return retValue;
}

Exp *RDParser::Factor() {
  Exp *retValue;
  if (currentToken == TOK_DOUBLE) {
    retValue = new NumericConst(getNumber());
    currentToken = getToken();
  }

  else if (currentToken == TOK_OPAREN) {
    currentToken = getToken();
    retValue = Expr();

    if (currentToken != TOK_CPAREN) {
      if (retValue)
        delete retValue;
      throw std::runtime_error("Missing Closing Parenthesis");
    }
    currentToken = getToken();
  }

  else if (currentToken == TOK_PLUS || currentToken == TOK_SUB) {
    getNext();
    retValue = Factor();
    retValue =
        new UnaryExp(retValue, lastToken == TOK_PLUS ? OP_PLUS : OP_MINUS);
  }

  else {
    throw std::runtime_error("Illegal Token");
  }
  return retValue;
}

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
  if (currentToken == TOK_SEMI)
    throw std::runtime_error("Expected ;");
  PrintStatement *spt = new PrintStatement(exp);
  return spt;
}

Stmt *RDParser::ParsePrintLnStatement() {
  getNext();
  Exp *exp = Expr();
  if (currentToken == TOK_SEMI)
    throw std::runtime_error("Expected ;");
  PrintLnStatement *spt = new PrintLnStatement(exp);
  return spt;
}