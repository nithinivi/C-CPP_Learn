#include <iostream>

#include "Expression.hpp"
#include "Parser.hpp"
#include "Visitor.hpp"

int main(int argc, char* argv[]) {
    IRVisitor* visitor = new IRVisitor();
    std::string expr_string = "20";
    std::cout << expr_string << std::endl;
    Context ctx;
    try {
        RDParser* parser = new RDParser(expr_string);
        Expr* nd = parser->callExpr();
        nd->accept(ctx, *visitor);
        visitor->getLlvmModule()->print(llvm::errs(), nullptr);

        delete parser;
        delete nd;
    } catch (std::string e) {
        std::cout << "error evaluating expression" << e << std::endl;
    }
    return 0;
}
