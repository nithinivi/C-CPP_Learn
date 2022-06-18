
#include <cstring>
#include <iostream>

#include "SLANG.h"
#include "ast/ast.h"
#include "builder/builder.h"
#include "frontend/lexer.h"
#include "frontend/parser.h"

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

void testParser() {
  char expStr[] = "(5/3) + 10";
  ExpressionBuilder builder(expStr);
  Exp *exp = builder.getExpression();
  if (exp) {
    std::cout << exp->evaluate(NULL) << std::endl;
    delete exp;
  } else {
    std::cout << "Unable to parse the expression: " << expStr << std::endl;
  }
}

void testFirstScript() {
  char a[] = "PRINTLINE 2*10; \r\n PRINTLINE 10;\r\n PRINT 2*10;\r\n";
  RDParser *p = new RDParser(a);
  std::vector<Stmt *> arr = p->Parse();
  for (Stmt *s : arr)
    s->evaluate(NULL);
}

int main(int argc, char *argv[])
{
  std::cout << argv[0] << " Version " << SLANG_VERSION_MAJOR << "."
            << SLANG_VERSION_MINOR << std::endl;
  std::cout << "Usage: " << argv[0] << " number" << std::endl;
  testFirstScript();

  return 0;
}


