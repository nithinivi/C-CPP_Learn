#include <cstdint>
#ifndef BFCOMPILER_H

#include <cstring>
#include <cstdint>
#define BFCOMPILER_H

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



class Machine {

      public : char *code; int ip; int dp; int length;
      unsigned char memory[NUM_MEMORY_CELLS] = {0};
      int buf;

      Machine(char *code);
      virtual ~Machine();
      void lexer();
      void excute();
      void readChar();
      void putChar();
      void brOpen();
      void brClose();
    };

#endif /* BFCOMPILER_H */
