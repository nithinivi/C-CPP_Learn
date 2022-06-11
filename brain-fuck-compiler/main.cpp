#include "bfCompiler.h"
#include <cstdio>
#include <cstring>
#include <iostream>

Machine::Machine(char *code) {
     this->code = code;
     this->dp = 0;
     this->ip = 0;
     this->length = strlen(code);
};

Machine::~Machine() {
     delete [] code;
}

void Machine::readChar() {
     scanf("%d", &buf);
     memory[dp] = (unsigned char)buf;
}

void Machine::putChar() { printf("%c", (int)memory[dp]); }

void Machine::excute() {
     int brace_cout = 1;
     while (ip != length) {
          lexer();
          ip++;
     }
}

void Machine::brOpen() {
     int brace_count = 1;
     while (brace_count != 0) {
          ++ip;
          if (code[ip] == '[')
               ++brace_count;
          else if (code[ip] == ']')
               --brace_count;
     }
}

void Machine::brClose() {
     int brace_count = 1;
     while (brace_count != 0) {
          --ip;
          if (code[ip] == '[')
               --brace_count;
          else if (code[ip] == ']')
               ++brace_count;
     }
}

void Machine::lexer() {
     switch (code[ip]) {
     case '+':
          memory[dp]++;
          break;

     case '-':
          memory[dp]--;
          break;

     case '>':
          dp++;
          break;

     case '<':
          dp--;
          break;

     case '.':
          putChar();
          break;

     case ',':
          readChar();
          break;

     case '[':
          if (memory[dp] == 0)
               brOpen();
          break;

     case ']':
          if (memory[dp] != 0)
               brClose();
          break;
     }
}

int main() {
  char arr[] = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.++++++"
               "+..+++.>>.<-.<.+++.------.--------.>>+.>++.";
  Machine *machine = new Machine(arr);
  machine->excute();
  return 0;
}
