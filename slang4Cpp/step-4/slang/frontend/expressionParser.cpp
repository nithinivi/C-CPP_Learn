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
    currentToken = getNext();
    return Expr(ctx);
}

Exp *RDParser::Expr(CompilationContext *ctx) {
    Token l_token;
    Exp *retValue = Term(ctx);
    while (currentToken == TOK_PLUS || currentToken == TOK_SUB) //
    {
        l_token = currentToken;
        getNext();
        Exp *right = Expr(ctx);

        if (l_token == TOK_PLUS)
            retValue = new BinaryPlus(retValue, right);
        else
            retValue = new BinaryMinus(retValue, right);
    }
    return retValue;
}

Exp *RDParser::Term(CompilationContext *ctx) {
    Token l_token;
    Exp *retValue = Factor(ctx);
    while (currentToken == TOK_MUL || currentToken == TOK_DIV) {
        l_token = currentToken;
        getNext();
        Exp *right = Factor(ctx); // for math to work in this universe
        if (l_token == TOK_MUL)
            retValue = new BinaryMul(retValue, right);
        else
            retValue = new BinaryDiv(retValue, right);
    }
    return retValue;
}

Exp *RDParser::Factor(CompilationContext *ctx) {
    Token l_token;
    Exp *retValue;
    if (currentToken == TOK_DOUBLE) {
        retValue = new NumericConstant(getNumber());
        currentToken = getNext();
    } else if (currentToken == TOK_STRING) {
        retValue = new StringLiteral(getString());
        currentToken = getNext();
    } else if (currentToken == TOK_BOOL_FALSE ||
               currentToken == TOK_BOOL_TRUE) {
        retValue =
            new BooleanConstant(currentToken == TOK_BOOL_TRUE ? true : false);
        currentToken = getNext();
    }

    else if (currentToken == TOK_OPAREN) {
        currentToken = getNext();
        retValue = Expr(ctx);

        if (currentToken != TOK_CPAREN) {
            if (retValue)
                delete retValue;
            throw std::runtime_error("Missing Closing Parenthesis");
        }
        currentToken = getNext();
    }

    else if (currentToken == TOK_PLUS || currentToken == TOK_SUB) {
        l_token = currentToken;
        getNext();

        Exp *expression = Factor(ctx);
        if (l_token == TOK_PLUS)
            retValue = new UnaryPlus(expression);
        else if (l_token == TOK_SUB)
            retValue = new UnaryMinus(expression);
        else
            throw "error";
    }

    else if (currentToken == TOK_UNQUOTED_STRING) {
        std::string variable = getString();
        SymbolInfo *info = ctx->table->get(variable);
        if (!info)
            throw "Undefined symbol";
        getNext();
        retValue = new Variable(info);
    }

    else {
        throw "Illegal Token";
    }
    return retValue;
}
