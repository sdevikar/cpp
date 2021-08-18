#include <iostream>

#include "B.h"
#include "D.h"

using namespace std;

int main(){

  // here we are simply creating an object of class D
  D d;

  // The above statement results in a call to constructor of D
  // But before construction process can continue, base class B of class D is a prerequisite
  // So constructor of class B will be called
  // After base class is constructed, we're back to construction process of D
  // D also instantiates an object of class C, so, that will be constructed next
  // After C is constructed, D has everything to get instantiated
  // So the output during construction is:
  // Constructor of B
  // Constructor of C
  // Constructor of D

  // Destruction happens in reverse order
  // Destructor of D
  // Destructor of C
  // Destructor of B


  return 0;
}
