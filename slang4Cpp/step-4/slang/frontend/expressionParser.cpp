#include "../include/ast_expression.h"
#include "../include/lexer.h"
#include "../include/parser.h"

RDParser::RDParser(std::string exp) : Lexer(exp){};
RDParser::~RDParser(){};

Token RDParser::getNext() {
    lastToken = currentToken;
    currentToken = getToken();
    return currentToken;
}

Exp *RDParser::CallExpr(CompilationContext *ctx) {
    currentToken = getToken();
    return Expr(ctx);
}

Exp *RDParser::Expr(CompilationContext *ctx) {
    Exp *retValue = Term(ctx);
    while (currentToken == TOK_PLUS || currentToken == TOK_SUB) //
    {
        getNext();
        Exp *right = Expr(ctx);

        if (lastToken == TOK_PLUS)
            retValue = new BinaryPlus(retValue, right);
        else
            retValue = new BinaryMinus(retValue, right);
    }
    return retValue;
}

Exp *RDParser::Term(CompilationContext *ctx) {
    Exp *retValue = Factor(ctx);
    while (currentToken == TOK_MUL || currentToken == TOK_DIV) {
        getNext();
        Exp *right = Term(ctx);
        if (lastToken == TOK_MUL)
            retValue = new BinaryMul(retValue, right);
        else
            retValue = new BinaryDiv(retValue, right);
    }
    return retValue;
}

Exp *RDParser::Factor(CompilationContext *ctx) {
    Exp *retValue;
    if (currentToken == TOK_DOUBLE) {
        retValue = new NumericConstant(getNumber());
        currentToken = getToken();
    }

    else if (currentToken == TOK_OPAREN) {
        currentToken = getToken();
        retValue = Expr(ctx);

        if (currentToken != TOK_CPAREN) {
            if (retValue)
                delete retValue;
            throw std::runtime_error("Missing Closing Parenthesis");
        }
        currentToken = getToken();
    }

    else if (currentToken == TOK_PLUS || currentToken == TOK_SUB) {
        getNext();
        Exp *expression = Factor(ctx);
        if (lastToken == TOK_PLUS)
            retValue = new UnaryPlus(expression);
        else
            retValue = new UnaryMinus(expression);
    }

    else if (currentToken == TOK_UNQUOTED_STRING) {
        std::string variable = getString();
        SymbolInfo *info = ctx->table->get(variable);
        if (!info)
            throw "Undefine symbol";
        getNext();
        retValue = new Variable(info);
    }

    else {
        throw std::runtime_error("Illegal Token");
    }
    return retValue;
}
