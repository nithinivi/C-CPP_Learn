#include "builder.h"
#include "../frontend/parser.h"

using namespace slang;

ExpressionBuilder::ExpressionBuilder(char *exp_string) {
  this->exp_string = exp_string;
}

// ExpressionBuilder::~ExpressionBuilder() { delete exp_string; }

Exp *ExpressionBuilder::getExpression() {
  try {
    RDParser parser(exp_string);
    return parser.CallExpr();

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return NULL;
}