#include <iostream>
#include "myclass.h"

using namespace std;

int main(void){
  MyClass obj1;

  // the following will execute with no problem
  obj1.geta();
  obj1.getb();
  obj1.getx();
  obj1.gety();
  obj1.message();

  const MyClass obj2;

  // the following will throw an error
#if 0
  obj2.geta();
  obj2.getb();
  obj2.getx();
  obj2.gety();
  obj2.message();
#endif

  // However, we can call constant functions on constant object
  cout << obj2.getaForReal() << endl;

  // Although, we cannot change member variable in const object, even if the function is const function
  //obj2.setaForReal(5); // this will error out

  obj2.setMutableZ(5);


}
