#include "../include/ast_statement.h"

Stmt::Stmt(){};
Stmt::~Stmt(){};

PrintStatement::PrintStatement(Exp *exp) { this->exp = exp; }
SymbolInfo *PrintStatement::execute(RuntimeContext *ctx) {
    SymbolInfo *evaluated_exp = exp->evaluate(ctx);
    printf("%f", evaluated_exp->doubleValue);
    return nullptr;
}
PrintStatement::~PrintStatement() {}

PrintLnStatement::PrintLnStatement(Exp *exp) { this->exp = exp; }
SymbolInfo *PrintLnStatement::execute(RuntimeContext *ctx) {
    SymbolInfo *evaluated_exp = exp->evaluate(ctx);
    printf("%f \n", evaluated_exp->doubleValue);
    return nullptr;
}
PrintLnStatement::~PrintLnStatement() {}
