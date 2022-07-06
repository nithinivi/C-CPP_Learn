#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <sys/mman.h>
#include <unistd.h>
#include <bitset>
#include <iostream>

char addfunc[] =
    "\xf3\x0f\x1e\xfa\x55\x48\x89\xe5\x89\x7d\xfc\x89\x75\xf8\x8b\x55\xfc"
    "\x8b\x45\xf8\x01\xd0\x5f\xc3";

int main(int argc, char *argv[]) {
  char *Code = (char *)malloc(100);
  std::cout << std::bitset<32>((unsigned long)Code) << std::endl;
  // Compute the Page

  std::cout << std::bitset<32>(getpagesize()) << std::endl;
  std::cout << std::bitset<32>(getpagesize() - 1) << std::endl;
  std::cout << std::bitset<32>(~(getpagesize() - 1)) << std::endl;
  std::cout << std::bitset<32>((unsigned long)Code) << std::endl;
  std::cout << std::bitset<32>
    (((unsigned long)Code) & ~(getpagesize() - 1))
            << std::endl;

  
  unsigned long page = ((unsigned long)Code) & ~(getpagesize() - 1);
  if (mprotect((char *)page, getpagesize(),
               PROT_READ | PROT_WRITE | PROT_EXEC)) {
      perror("mprotect failed");
      exit(errno);
  }

  // copy the code from addfunc to code 
  memcpy(Code, addfunc, sizeof(addfunc));

  //Casting the code to function pointer
  int (*AddFunc)(int , int ) = (int(*)(int, int))((void*) Code);
  int retval = AddFunc(10 ,6);
  printf("%d\n", retval);
    
  return 0;
}
