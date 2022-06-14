#include "BFIncludes.hpp"
#include <iostream>
#include <vector>

int main() {
  char c[] = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++."
             ".+++.>>.<-.<.+++.------.--------.>>+.>++.";
  Parser *parser = new Parser(c);
  std::vector<Instruction *> incs = parser->lexer();
  Machine *machine = new Machine(incs);
  machine->excute();
  return 0;
}
