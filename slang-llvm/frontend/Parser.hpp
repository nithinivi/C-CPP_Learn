#ifndef PARSER_H
#define PARSER_H

#include "../ast/Expression.hpp"
#include <string>

enum Token {
    ILLEGAL_TOKEN = 0,
    TOK_NULL,

    TOK_PLUS,
    TOK_SUB,
    TOK_MUL,
    TOK_DIV,
    TOK_OPAREN,
    TOK_CPAREN,
    TOK_DOUBLE,

};

class Lexer {
private:
    std::string expr;
    int index;
    int length;
    double number;

public:
    Lexer(std::string expr);
    ~Lexer();

    Token getToken();
    double getNumber();
};

class RDParser : Lexer {
private:
    Token current_token;
    Expr* expr();
    Expr* term();
    Expr* factor();

public:
    RDParser(std::string string);
    virtual ~RDParser();
    Expr* callExpr();
};

#endif // !PARSER_H
