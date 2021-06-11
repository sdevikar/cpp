#include <iostream>
#include "base.h"
#include "child.h"

using namespace std;


int main(void){

  cout << "Instantiating Base class" << endl;
  Base b;

  cout << "Instantiating Child class" << endl;
  Child c;

  // Inheritance, Overloading and Overridding
  cout << "Calling INHERITED base class method on child class object" << endl;
  c.FooBarPublicOne();

  cout << "Calling OVERRIDDEN base class method on child class object" << endl;
  c.FooBarPublicTwo();

  cout << "Calling OVERLOADED base class method on child class object (changed signature)" << endl;
  c.FooBarPublicThree(3);

  // Access specifiers
  cout << "Child class can access PUBLIC members of base class: " << endl;
  cout << "m_basePublic = " << c.m_basePublic << endl;

  cout << "Child class can NOT access PROTECTED members of base class using its own instance: " << endl;
  //cout << "m_baseProtected = " << c.m_baseProtected << endl;

  cout << "Child class can access PROTECTED members of base class using base class instance: " << endl;
  cout << "m_baseProtected = " << c.GetInheritedProtected() << endl;

  cout << "Child class can NOT access PRIVATE members of base class: " << endl;
  //cout << "m_basePublic = " << c.m_basePrivate << endl;



  return 0;
}
