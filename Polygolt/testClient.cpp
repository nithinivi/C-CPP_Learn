#include <windows.h>
#include <iostream>


using namespace std;

#include "arithTest.h"


int main(int argc, char *argv[])
{

  int addans = Add(3, 4);
  int subans = Sub(31, 4);
  int mulans = Mul(311, 4);
  int divans = Div(311, 4);

  cout << addans << "\t" <<  subans << "\t" << mulans <<
    "\t" << divans << endl;

  return 0;
}
