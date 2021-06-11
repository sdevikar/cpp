#include <iostream>
#include "myclass.h"

using namespace std;


bool MyClass::flag = false; // this is the definition

//!!!! Note this very very carefully !!!!
// _counter is a private static variable
// it can still be accessed using the scope resolution operator
// for initialization
int MyClass::_counter = 0;



int main(void){

  //!!!! HOWEVER, the following is not allowed
  // Redeclaration of _counter is NOT allowed inside a function
  //int MyClass::_counter = 0;

  MyClass obj1;
  MyClass obj2;
  int counter;

  // Static method can be accessed using any of the two ways
  MyClass::SetCounter(0);
  obj1.SetCounter(0);

  //!!! We saw that accession _counter was allowed at the time of declaration,
  // even though it's private
  // HERE, it is NOT allowed
  //cout << "Initial counter value: " << MyClass::_counter << endl;

  counter = obj1.GetCounter();
  counter = MyClass::GetCounter();

  cout << "Initial counter value: " << counter << endl;
  cout << "Initial counter value: " << counter << endl;

  // the static member value will be retained across objects, since it's a per class member

  obj1.Up(); // _counter is now 1
  obj2.Up(); // _counter is now 2
  MyClass::Up(); // _counter is now 3

  cout << "Initial counter value: " << MyClass::GetCounter() << endl;

  obj1.Down(); // _counter is now 2
  obj2.Down(); // _counter is now 1
  MyClass::Down(); // _counter is now 0

  cout << "Initial counter value: " << MyClass::GetCounter() << endl;


  // Obviously, we can't call Status() like we call static member function
  //MyClass::Status(); // this won't work

  obj1.Status();






  return 0;
}
