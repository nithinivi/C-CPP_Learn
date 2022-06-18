#include "../include/ast_statement.hpp"


VariableDeclStatement::VariableDeclStatement(SymbolInfo *info) { info = info; }

VariableDeclStatement::~VariableDeclStatement() {
  delete info;
  delete var;
}

SymbolInfo *VariableDeclStatement::execute(RuntimeContext *ctx) {
  ctx->symbolTable->add(info);
  var = new Variable(info);
  return nullptr;
}
