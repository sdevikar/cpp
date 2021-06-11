#include <iostream>
#include "base.h"
#include "child.h"
#include "child0.h"


using namespace std;

int main(void){
  Base b;

  cout << b << endl; // output = I am Base

  Child c;

  // here, << was never overridden for Child class
  // In fact, the signature of << in base class expects a Base class reference as input
  // Yet, we're able to call << on child class, because,
  // 1. it's inherited from base class to the child class
  // 2. It being a friend function, has access to base classes' private and protected members
  // so, calling << on c is equivalent to copy pasting << operator function inside the child class itself
  cout << c << endl; //// output = I am Base

  // As we can see, the output is "I am Base" in both cases. i.e. even when we print child
  // this is because:
  // 1. operator<< call is routed to Base class (using implicit casting)
  // 2. child class already has a reference to the base class in the memory footprint



  Child0 c0;
  cout << c0 << endl; //// output = I am Child



}
