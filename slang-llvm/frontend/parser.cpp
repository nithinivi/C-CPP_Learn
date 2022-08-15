#include "parser.hpp"
#include "expression.hpp"
#include <stdexcept>

Lexer::Lexer(std::string expr) {
    this->expr = expr;
    this->length = expr.length();
    this->index = 0;
}

Lexer::~Lexer() { expr.erase(); }

Token Lexer::getToken() {
    Token token = ILLEGAL_TOKEN;
    while (index < length && (expr[ index ] == ' ' || expr[ index ] == '\t')) {
        index++;
    }

    if (index == length) {
        return TOK_NULL;
    }

    switch (expr[ index ]) {
    case '+':
        token = TOK_PLUS;
        index++;
        break;
    case '-':
        token = TOK_SUB;
        index++;
        break;
    case '/':
        token = TOK_DIV;
        index++;
        break;
    case '*':
        token = TOK_MUL;
        index++;
        break;
    case '(':
        token = TOK_OPAREN;
        index++;
        break;
    case ')':

        token = TOK_CPAREN;
        index++;
        break;

    default:
        if (std::isdigit(expr[ index ])) {
            int numStartIndex = index;
            while (index < length && isdigit(expr[ index ]))
                index++;
            std::string numStr =
                expr.substr(numStartIndex, index - numStartIndex);
            number = std::stod(numStr);
            token = TOK_DOUBLE;
        } else
            throw std::runtime_error(
                "Unknown character found while tokenizing ");
    }
    return token;
}
double Lexer::getNumber() { return number; }

RDParser::RDParser(std::string string) : Lexer(string){};
RDParser::~RDParser() {}

Expr* RDParser::callExpr() {
    current_token = getToken();
    return expr();
}

Expr* RDParser::expr() {
    Token l_token;
    Expr* returnValue = term();
    while (current_token == TOK_PLUS || current_token == TOK_SUB) {
        l_token = current_token;
        current_token = getToken();
        Expr* right = term();
        returnValue = new BinaryExpr(right, returnValue,
                                     l_token == TOK_PLUS ? OPERATOR::PLUS
                                                         : OPERATOR::MINUS);
    }
    return returnValue;
}

Expr* RDParser::term() {
    Token l_token;
    Expr* returnValue = factor();
    while (current_token == TOK_MUL || current_token == TOK_DIV) {
        l_token = current_token;
        current_token = getToken();
        Expr* right = factor();
        returnValue =
            new BinaryExpr(right, returnValue,
                           l_token == TOK_PLUS ? OPERATOR::MUL : OPERATOR::DIV);
    }
    return returnValue;
}

Expr* RDParser::factor() {
    Token l_token;
    Expr* returnValue = NULL;

    if (current_token == TOK_DOUBLE) {
        returnValue = new NumericConstant(getNumber());
        current_token = getToken();
    } else if (current_token == TOK_OPAREN) {
        current_token = getToken();
        returnValue = expr();
        if (current_token != TOK_CPAREN)
            throw std::runtime_error("Missing Closing parens ");
        current_token = getToken();
    } else if (current_token == TOK_PLUS || current_token == TOK_SUB) {
        l_token = current_token;
        current_token = getToken();
        returnValue = factor();
        returnValue =
            new UnaryExpr(returnValue, l_token == TOK_PLUS ? OPERATOR::PLUS
                                                           : OPERATOR::MINUS);
    } else {
        throw std::runtime_error("Illegal tokens ");
    }
    return returnValue;
}
