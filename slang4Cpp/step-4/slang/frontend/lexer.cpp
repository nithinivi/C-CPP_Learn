#include "../include/lexer.h"
#include <cctype>
#include <cstddef>
#include <cstring>
#include <ctype.h>
#include <iostream>
#include <stdexcept>
#include <string>

Lexer::Lexer(std::string exp) {
    this->exp = exp;
    this->length = exp.length();
    this->index = 0;

    value_table[0] = new ValueTable(TOK_PRINT, "PRINT");
    value_table[1] = new ValueTable(TOK_PRINTLN, "PRINTLINE");
    value_table[2] = new ValueTable(TOK_BOOL_FALSE, "FALSE");
    value_table[3] = new ValueTable(TOK_BOOL_TRUE, "TRUE");
    value_table[4] = new ValueTable(TOK_VAR_STRING, "STRING");
    value_table[5] = new ValueTable(TOK_VAR_BOOL, "BOOLEAN");
    value_table[6] = new ValueTable(TOK_VAR_NUMBER, "NUMERIC");
}

double Lexer::getNumber() { return number; }
std::string Lexer::getString() { return last_str; }

Token Lexer::getToken() {
start:
    Token tok = ILLEGAL_TOKEN;

    while (index < length && (exp[index] == ' ' || exp[index] == '\t'))
        index++;

    if (index == length)
        return TOK_NULL;

    switch (exp[index]) {
    case '\n':
    case '\r':
        index++;
        goto start;
    case '=':
        tok = TOK_ASSIGN;
        index++;
        break;
    case '+':
        tok = TOK_PLUS;
        index++;
        break;
    case '-':
        tok = TOK_SUB;
        index++;
        break;
    case '/':
        if (exp[index + 1] == '/') {
            skipToEOL();
            goto start;
        }
        tok = TOK_DIV;
        index++;
        break;
    case '*':
        tok = TOK_MUL;
        index++;
        break;
    case ')':
        tok = TOK_CPAREN;
        index++;
        break;
    case '(':
        tok = TOK_OPAREN;
        index++;
        break;
    case ';':
        tok = TOK_SEMI;
        index++;
        break;

    case '"':
        int numStartIndex;
        numStartIndex = index;

        while (index < length && exp[index] != '"')
            index++;

        if (index == length) {
            tok = ILLEGAL_TOKEN;
            return tok;
        }

        last_str = exp.substr(numStartIndex, index - numStartIndex);

        tok = TOK_STRING;
        index++;
        break;

    default:
        if (isdigit(exp[index])) {
            int numStartIndex = index;
            while (index < length && isdigit(exp[index]))
                index++;

            std::string numStr =
                exp.substr(numStartIndex, index - numStartIndex);
            number = std::stod(numStr);
            tok = TOK_DOUBLE;

        } else if (isalpha(exp[index])) {
            int numStartIndex = index;
            while (index < length && isalpha(exp[index]))
                index++;

            last_str = exp.substr(numStartIndex, index - numStartIndex);

            for (int i = 0; i < KEYWORDS_COUNT; ++i) {
                if (last_str == value_table[i]->value) {
                    ValueTable *t = value_table[i];
                    return t->token;
                }
            }
            return TOK_UNQUOTED_STRING;
        } else
            throw std::runtime_error(
                "Unknown character found while tokenizing ");
    }

    return tok;
}

void Lexer::skipToEOL() {
    while (exp[index] != '\n' && index < length)
        index++;

    if (index == length) 
        throw "error while parsing comments";
}
