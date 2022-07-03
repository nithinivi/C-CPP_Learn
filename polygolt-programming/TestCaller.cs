using System;
using Systen.Runtime.InteropServices;

namespace Test
{
class TestCaller
{
  [DllImport("Test.dll", EntryPoint="Add")];
  static extern int Add(int, int);


  public static void Main(String [] args){
         int n = Add(10, 10);
  }
}

}