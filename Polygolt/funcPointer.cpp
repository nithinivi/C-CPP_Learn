///////////////////////////////////////////////////////////////////////////////
//          56                    funcPointer.cpp                              //
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

extern "C" int __stdcall Add(double a , double b)
{
  return (int) (a+b)

    }


extern "C" double __stdcall FileTest(double a , char *t)
{
  double n = a + (double)atof(t);
  return n;
}


int main(int argc, char *argv[])
{
  //calling function pointer
  int (__stdcall* AddFunc)(double , double ) = (int (__stdcall*)(double , double))Add;
  int c  = (*AddFunc)(2, 3);
  printf("%d \n", c);

    return 0;
}
