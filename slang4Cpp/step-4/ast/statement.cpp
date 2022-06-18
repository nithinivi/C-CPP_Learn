#include "ast.h"

using namespace slang; // namespace slang

Stmt::Stmt(){};
Stmt::~Stmt(){};

PrintStatement::PrintStatement(Exp *exp) { this->exp = exp; }
double PrintStatement::evaluate(RuntimeContext *ctx) {
  double evaluated_exp = exp->evaluate(ctx);
  printf("%f", evaluated_exp);
}
PrintStatement::~PrintStatement() {}

PrintLnStatement::PrintLnStatement(Exp *exp) { this->exp = exp; }
double PrintLnStatement::evaluate(RuntimeContext *ctx) {
  double evaluated_exp = exp->evaluate(ctx);
  printf("%f \n", evaluated_exp);
}
PrintLnStatement::~PrintLnStatement() {}
