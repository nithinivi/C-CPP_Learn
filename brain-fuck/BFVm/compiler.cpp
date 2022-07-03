#include "BFIncludes.hpp"
#include <iterator>
#include <vector>

Parser::Parser(char *code) {
  this->code = code;
  this->codeLength = std::strlen(code);
  this->index = 0;
};

Parser::~Parser(){};

std::vector<Instruction *> Parser::lexer() {
  std::vector<int> loopstack;
  int open_ins_pos;
  int close_ins_pos;

  while (index != codeLength) {
    current_char = code[index];

    switch (current_char) {
    case '+':
      FoldInstruction('+', TOK_PLUS);
      break;
    case '-':
      FoldInstruction('-', TOK_MINUS);
      break;
    case '<':
      FoldInstruction('<', TOK_LEFT);
      break;
    case '>':
      FoldInstruction('>', TOK_RIGHT);
      break;
    case '.':
      FoldInstruction('.', TOK_PUTCHAR);
      break;
    case ',':
      FoldInstruction(',', TOK_READCHAR);
      break;

    case '[':
      open_ins_pos = EmitWithArg(TOK_JUMPIFZERO, 0);
      loopstack.push_back(open_ins_pos);
      break;

    case ']':
      open_ins_pos = loopstack.back();
      loopstack.pop_back();
      close_ins_pos = EmitWithArg(TOK_JUMPIFNOTZERO, open_ins_pos);
      instructions[open_ins_pos]->setArg(close_ins_pos);
      break;
    }
    index++;
  }
  return instructions;
}

void Parser::FoldInstruction(char c, TOKEN token) {
  int char_count = 1;
  while (index < codeLength && code[index + 1] == c) {
    char_count++;
    index++;
  }
  EmitWithArg(token, char_count);
}

int Parser::EmitWithArg(TOKEN token, int count) {
  Instruction *ins = new Instruction(token, count);
  instructions.push_back(ins);
  return instructions.size() - 1;
}
