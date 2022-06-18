#include "BFIncludes.hpp"
#include <cstdio>
#include <iostream>
#include <ostream>
#include "string"
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

void Machine::putChar() {
  printf("%c \n ", memory[dp]);
  printf("%d \n ", memory[dp]);
}

void print_tok(int dp,std::string token , Instruction *ins ){
  std::cout << token << " "<< ins->arguemnt << " " << dp
                << std::endl;
}

void Machine::excute() {
  for (int i = 0; i < code.size(); ++i) {
    Instruction *ins = code[i];

    switch (ins->token) {

    case TOK_PLUS:
      print_tok(dp, "TOK_PLUS", ins);
      memory[dp] += ins->arguemnt;
      break;

    case TOK_MINUS:

      print_tok(dp, "TOK_MINUS", ins);
      memory[dp] -= ins->arguemnt;
      break;

    case TOK_RIGHT:

      print_tok(dp, "TOK_RIGHT", ins);
      dp += ins->arguemnt;
      break;

    case TOK_LEFT:

      print_tok(dp, "TOK_LEFT", ins);
      dp -= ins->arguemnt;
      break;

    case TOK_PUTCHAR:

      print_tok(dp, "TOK_PUTCHAR", ins);
      for (int j = 0; j < ins->arguemnt; ++j)
        putChar();
      break;

    case TOK_READCHAR:

      for (int j = 0; j < ins->arguemnt; ++j)
        readChar();
      break;

    case TOK_JUMPIFZERO:
      print_tok(dp, "TOK_JUMPIFZERO", ins);

      if (memory[dp] == 0) {
        ip = ins->arguemnt;
        continue;
      }
      break;

    case TOK_JUMPIFNOTZERO:
      print_tok(dp, "TOK_JUMPIFNOTZERO", ins);

      if (memory[dp] != 0) {
        ip = ins->arguemnt;
        continue;
      }
      break;
    }
  }
}
