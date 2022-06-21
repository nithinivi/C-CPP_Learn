#include "../include/context.h"
#include "../include/lexer.h"
#include "../include/parser.h"
#include <typeinfo>

std::vector<Stmt *> RDParser::Parse(CompilationContext *ctx) {
    getNext();
    return StatementList(ctx);
}

std::vector<Stmt *> RDParser::StatementList(CompilationContext *ctx) {
    std::vector<Stmt *> newArry;
    while (currentToken != TOK_NULL) {
        Stmt *stmt = RDParser::Statement(ctx);
        if (stmt)
            newArry.push_back(stmt);
    }
    return newArry;
};

Stmt *RDParser::Statement(CompilationContext *ctx) {
    Stmt *returnValue;
    switch (currentToken) {
    case TOK_VAR_NUMBER:
    case TOK_VAR_STRING:
    case TOK_VAR_BOOL:
        returnValue = ParseVariableStatement(ctx);
        getNext();
        break;
    case TOK_PRINT:
        returnValue = ParsePrintStatement(ctx);
        getNext();
        break;
    case TOK_PRINTLN:
        returnValue = ParsePrintLnStatement(ctx);
        getNext();
        break;
    case TOK_UNQUOTED_STRING:
        returnValue = ParseAssignmentStatement(ctx);
        getNext();
        break;
    default:
        throw std::runtime_error("Illegal Token");
    }
    return returnValue;
}

Stmt *RDParser::ParsePrintStatement(CompilationContext *ctx) {
    getNext();
    Exp *expr = Expr(ctx);
    if (currentToken != TOK_SEMI)
        throw std::runtime_error("Expected ;");
    PrintStatement *spt = new PrintStatement(expr);
    return spt;
}

Stmt *RDParser::ParsePrintLnStatement(CompilationContext *ctx) {
    getNext();
    Exp *expr = Expr(ctx);
    if (currentToken != TOK_SEMI)
        throw std::runtime_error("Expected ;");
    PrintLnStatement *spt = new PrintLnStatement(expr);
    return spt;
}

Stmt *RDParser::ParseVariableStatement(CompilationContext *ctx) {
    Token tok = currentToken;

    // parse varaible name
    getNext();
    if (currentToken != TOK_UNQUOTED_STRING)
        throw("Invalid variable decleration");

    SymbolInfo *info = new SymbolInfo();
    info->symbolName = getString();
    info->type_ = tok == TOK_VAR_BOOL
                      ? TYPE_BOOL
                      : (tok == TOK_VAR_NUMBER) ? TYPE_NUMERIC : TYPE_STRING;

    // skip to next line to execpt semi colon
    getNext();
    if (currentToken != TOK_SEMI)
        throw("Expected ;");

    // add to symbolTable for type analysis
    ctx->table->add(info);
    return new VariableDeclStatement(info);
}

Stmt *RDParser::ParseAssignmentStatement(CompilationContext *ctx) {
    // retrieve the variable and look up in the symbol table
    std::string varaible = getString();
    SymbolInfo *info = ctx->table->get(varaible);
    if (!info)
        throw "Variable not found";

    // next token ought to be assignment
    getNext();
    if (currentToken != TOK_ASSIGN)
        throw "Expected =";

    // evaluate expression
    getNext();
    Exp *expr = Expr(ctx);

    // type checking
    if (expr->typeCheck(ctx) != info->type_)
        throw "type mismatch";

    // check for ;
    if (currentToken != TOK_SEMI)
        throw "Expected semi";

    return new AssignmentStatement(info, expr);
}
