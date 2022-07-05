#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
  int c;
  while ((c=getchar()) != EOF) 
    putchar( c);
  
  return 0;
}

