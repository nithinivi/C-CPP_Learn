#include "BFIncludes.hpp"
#include <vector>

Machine::Machine(std::vector<Instruction *> code) {
  this->code = code;
  this->dp = 0;
  this->ip = 0;
}
Machine::~Machine(){};

void Machine::readChar() {
  scanf("%d", &buf);
  memory[dp] = (unsigned char)buf;
}

void Machine::putChar() { printf("%c ", (int)memory[dp]); }

void Machine::excute() {
  for (int i = 0; i < code.size(); ++i) {
    Instruction *ins = code[i];
    switch (ins->token) {

    case TOK_PLUS:
      memory[dp] += ins->arguemnt;
      break;

    case TOK_MINUS:
      memory[dp] -= ins->arguemnt;
      break;

    case TOK_RIGHT:
      dp += ins->arguemnt;
      break;

    case TOK_LEFT:
      dp -= ins->arguemnt;
      break;

    case TOK_PUTCHAR:
      for (int j = 0; j < ins->arguemnt; ++j)
        putChar();
      break;

    case TOK_READCHAR:

      for (int j = 0; j < ins->arguemnt; ++j)
        readChar();
      break;

    case TOK_JUMPIFZERO:
      if (memory[dp] == 0) {
        ip = ins->arguemnt;
        continue;
      }
      break;

    case TOK_JUMPIFNOTZERO:
      if (memory[dp] != 0) {
        ip = ins->arguemnt;
        continue;
      }
      break;
    }
  }
}
