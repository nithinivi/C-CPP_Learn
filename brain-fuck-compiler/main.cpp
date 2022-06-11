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

Machine::~Machine() {}

void Machine::readChar() {
     scanf("%d", &buf);
     memory[dp] = (unsigned char)buf;
}

void Machine::putChar() { printf("%d ", (int)memory[dp]); }

void Machine::excute() {
     while (ip < length) {
          lexer();
          ip++;
     }
}

void Machine::brOpen() {
          int depth = 1;
          while (depth != 0) {
               ip--;
               if (code[ip] == '[')
                    depth++;

               else if (code[ip] == ']')
                    depth--;
          }

          }


void Machine::brClose() {

     int depth = 1;
     while (depth != 0) {
          ip--;
          if (code[ip] == '[')
               depth++;

          else if (code[ip] == ']')
               depth--;
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
          brOpen();
          break;

     case ']':
          brClose();
          break;
     }
}

int main() {
     char arr[] = "++  > ++ [<+ >-]<.";
     Machine *machine = new Machine(arr);
     machine->excute();
     return 0;
}
