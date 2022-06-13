#ifndef BFINCLUDES_H
#include <cstdint>
#include <cstring>
#include <vector>

#define BFINCLUDES_H


#define NUM_MEMORY_CELLS 30000

enum TOKEN {
  TOK_PLUS,
  TOK_MINUS,
  TOK_RIGHT,
  TOK_LEFT,
  TOK_PUTCHAR,
  TOK_READCHAR,
  TOK_JUMPIFZERO,
  TOK_JUMPIFNOTZERO,
};

class Instruction {
  TOKEN token;
  int arguemnt;
  public:
  Instruction(TOKEN tok , int argument){
    this->token = tok;
    this->arguemnt = argument;
  }
  void setArg(int arg){
    this->arguemnt = arg;
  };

};

class Parser {


  char *code;
  int codeLength;
  int index;
  char current_char;
  std::vector<Instruction*> instructions;


  void FoldInstruction(char c, TOKEN token);
  int EmitWithArg(TOKEN token, int count);

public:
  Parser(char *code);
  virtual ~Parser();
  void lexer();
};

#endif /* BFINCLUDES_H */
