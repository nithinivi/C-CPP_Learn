#pragma once
#ifndef BUIDLER_H
#include "../include/ast.h"
#define BUIDLER_H

namespace slang {

class AbstractExpression {};
class ExpressionBuilder : public AbstractExpression {
  char *exp_string;

public:
  ExpressionBuilder(char *exp_string);
  // ~ExpressionBuilder();
  Exp *getExpression();
};

} // namespace slang
#endif /* BUIDLER_H*/
