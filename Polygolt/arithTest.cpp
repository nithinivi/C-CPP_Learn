#include <windows.h>


extern "C" __declspec(dllexport) int __stdcall Add(int a, int b)
{
  return a + b ;
}

extern "C" __declspec(dllexport) int __stdcall Sub(int a, int b)
{
  return a - b ;
}


extern "C" __declspec(dllexport) int __stdcall Mul(int a, int b)
{
  return a * b ;
}

extern "C" __declspec(dllexport) int __stdcall Div(int a, int b)
{
  return a / b ;
}
