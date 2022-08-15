#include <iostream>

#include "expression.hpp"
#include "parser.hpp"

int main(int argc, char* argv[]) {
    std::string expr_string = "20/5*2+4";

    try {
        TreeEvalVisitor* tree_visitor = new TreeEvalVisitor();
        RDParser* parser = new RDParser(expr_string);
        Expr* nd = parser->callExpr();
        double value = nd->accept(*tree_visitor);
        std::cout << value << std::endl;
        delete parser;
        delete nd;
    } catch (std::string e) {
        std::cout << "error evaluating expression" << e << std::endl;
    }
    return 0;
}
