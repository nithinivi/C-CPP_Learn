#include "../include/ast_expression.h"
#include "../include/ast_statement.h"

AssignmentStatement::AssignmentStatement(Variable *var, Exp *exp) {
    this->var = var;
    this->exp = exp;
}

AssignmentStatement::AssignmentStatement(SymbolInfo *info, Exp *exp) {
    this->var = new Variable(info);
    this->exp = exp;
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
