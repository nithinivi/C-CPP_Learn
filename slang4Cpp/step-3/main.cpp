#include "ast.h"
#include "lexer.h"
#include <cstring>
#include <iostream>

using namespace slang;

void test_lexer() {
  char expStr[] = "1 2 + - / * ( ) 9831337  ";
  Lexer *lexer = new Lexer(expStr);
  Token token;

  while ((token = lexer->getToken()) != TOK_NULL) {
    if (token == TOK_DOUBLE)
      std::cout << "Number: " << lexer->getNumber() << std::endl;
  }

  delete lexer;
}

void callSlang() {

  RuntimeContext *ctx;

  NumericConst *v1 = new NumericConst(30.0);
  NumericConst *v2 = new NumericConst(50.0);
  NumericConst *v3 = new NumericConst(10.0);

  BinaryExp *addExp = new BinaryExp(v1, v2, OP_PLUS);
  BinaryExp *outerAddExp = new BinaryExp(v3, addExp, OP_PLUS);
  UnaryExp *exp = new UnaryExp(outerAddExp, OP_MINUS);

  std::cout << "Result is : " << exp->evaluate(ctx) << std::endl;

  delete (addExp);
  delete (outerAddExp);
  delete (exp);
}

int main() { callSlang(); }
