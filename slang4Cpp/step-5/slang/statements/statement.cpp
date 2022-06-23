#include "../include/ast_statement.h"
#include "../include/common.h"

Stmt::Stmt(){};
Stmt::~Stmt(){};

PrintStatement::PrintStatement(Exp *exp) { this->exp = exp; }

SymbolInfo *PrintStatement::execute(RuntimeContext *ctx) {
    SymbolInfo *info = exp->evaluate(ctx);

    if (info->type_ == TYPE_NUMERIC)
        std::cout << info->doubleValue << std::endl;

    else if (info->type_ == TYPE_STRING)
        std::cout << info->stringValue << std::endl;

    else if (info->type_ == TYPE_BOOL)
        std::cout << info->boolValue << std::endl;

    return nullptr;
}
PrintStatement::~PrintStatement() {}

PrintLnStatement::PrintLnStatement(Exp *exp) { this->exp = exp; }
SymbolInfo *PrintLnStatement::execute(RuntimeContext *ctx) {
    SymbolInfo *info = exp->evaluate(ctx);

    if (info->type_ == TYPE_NUMERIC)
        std::cout << info->doubleValue << "\n" << std::endl;

    else if (info->type_ == TYPE_STRING)
        std::cout << info->stringValue << "\n" << std::endl;

    else if (info->type_ == TYPE_BOOL)
        std::cout << info->boolValue << "\n" << std::endl;

    return nullptr;
}
PrintLnStatement::~PrintLnStatement() {}
