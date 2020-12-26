#include <iostream>

using namespace std;

inline void hello() //inline functions are faster :)
{
  cout<<"hello";
}
int main()
{
  hello(); //Call it like a normal function...
  cin.get();
}
