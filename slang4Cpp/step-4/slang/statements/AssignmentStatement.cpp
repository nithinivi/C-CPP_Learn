#include "../include/ast_statement.h"
#include "../include/ast_expression.h"

AssignmentStatement::AssignmentStatement(Variable *var, Exp *exp) {
  var = var ;
  exp = exp;
}
AssignmentStatement::AssignmentStatement(SymbolInfo *info, Exp *exp) {
  var = new Variable(info);
  exp = exp;
    
}
AssignmentStatement::~AssignmentStatement() {
  delete var;
  delete exp;
}
SymbolInfo *AssignmentStatement::execute(RuntimeContext *ctx) {
  SymbolInfo *val = exp->evaluate(ctx);
  ctx->symbolTable->assign(var->getName(), val);
  return nullptr;
}
