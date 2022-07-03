#include <stdio.h>
#include <windos.h>


typedef int (__stdcall *BIN_FUNC)(int int );

int main(int argc, char *argv[])
{

  HMODULE ht = (HMODULE)LoadLibrary("arithTest.dll");
  if (ht == 0 | ht == INVALID_HANDLE_VALUE) {
    printf("Failed to load valueu ");
    return -1;

  }


  BIN_FUNC addfunc = (BIN_FUNC)GetProcAddress(ht, "Add");
  int nc  = (*addfunc)(10,10);
  printf("%d \n", nc);



  FreeLibrary(ht);
  return 0;

}
