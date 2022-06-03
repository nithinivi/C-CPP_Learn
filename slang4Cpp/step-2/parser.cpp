#include "parser.h"

RDParser::RDParser(char *exp) : Lexer(exp){};
RDParser::~RDParser(){};

Exp *RDParser::CallExpr() {
  currentToken = getToken();
  return Expr();
}

Exp *RDParser::Expr() {
  Token lToken;
  Exp *retValue = Term();
  while (currentToken == TOK_PLUS || currentToken == TOK_SUB) //
  {
    lToken = currentToken;
    currentToken = getToken();
    Exp *right = Expr();
    retValue =
        new BinaryExp(retValue, right, lToken == TOK_PLUS ? OP_PLUS : OP_MINUS);
  }
  return retValue;
}

Exp *RDParser::Term() {
  Token lToken;
  Exp *retValue = Factor();
  while (currentToken == TOK_MUL || currentToken == TOK_DIV) {
    lToken = currentToken;
    currentToken = getToken();
    Exp *right = Term();
    retValue =
        new BinaryExp(retValue, right, lToken == TOK_MUL ? OP_MUL : OP_DIV);
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
    Token lToken = currentToken;
    currentToken = getToken();
    retValue = Factor();
    retValue = new UnaryExp(retValue, lToken == TOK_PLUS ? OP_PLUS : OP_MINUS);
  }

  else {
    throw std::runtime_error("Illegal Token");
  }
  return retValue;
}