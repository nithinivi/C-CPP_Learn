#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "SlangConfig.h"
#include "include/ast.h"
#include "include/builder.h"
#include "include/lexer.h"
#include "include/parser.h"

std::string getScriptFile(std::string filepath) {
    std::ifstream f(filepath);
    std::string str;
    if (!f)
        throw "unable read script file";

    std::ostringstream ss;
    ss << f.rdbuf();
    str = ss.str();
    return str;
}

void testFileScipt(char *f) {
    std::string file = getScriptFile(f);

    CompilationContext *ctx = new CompilationContext();
    RuntimeContext *rtx = new RuntimeContext();

    RDParser *parser = new RDParser(file.c_str());
    std::vector<Stmt *> stmts = parser->Parse(ctx);

    for (Stmt *s : stmts)
        s->execute(rtx);

    delete parser;
    ;
    delete ctx;
}

int main(int argc, char *argv[]) {
    std::cout << argv[0] << "\n SLANG Version " << SLANG_VERSION_MAJOR << "."
              << SLANG_VERSION_MINOR << "\n\n"
              << std::endl;

    char str[] = "../slang_scripts/First.sl";
    if (argv[1])
        testFileScipt(argv[0]);
    else
        testFileScipt(str);

    return 0;
}
