#pragma once
#include <string>
#ifndef BUIDLER_H
#include "../include/ast.h"
#define BUIDLER_H

namespace slang {

class AbstractExpression {};
class ExpressionBuilder : public AbstractExpression {
  std::string exp_string;

public:
  ExpressionBuilder(std::string exp_string);
  // ~ExpressionBuilder();
  Exp* getExpression(CompilationContext *ctx);
};

} // namespace slang
#endif /* BUIDLER_H*/
