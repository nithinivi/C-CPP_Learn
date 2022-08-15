#include <iostream>

#include "../ast/Expression.hpp"
#include "../frontend/Parser.hpp"
// #include "../frontend/Parser.hpp"

int main(int argc, char* argv[]) {
    std::string expr_string = "20/5*2+4";
    std::cout << expr_string << std::endl;
    try {
        RDParser* parser = new RDParser(expr_string);
        Expr* nd = parser->callExpr();
        delete parser;
        delete nd;
    } catch (std::string e) {
        std::cout << "error evaluating expression" << e << std::endl;
    }
    return 0;
}
