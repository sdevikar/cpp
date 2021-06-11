#include <iostream>
#include "string1.h"
#include "string2.h"

using namespace std;

bool ChangeToUpperCase1(StringWithUserDefinedCopyConstructor string);
bool ChangeToUpperCase2(StringWithDefaultCopyConstructor string);

// In this example, we will write our own string classes
// and demonstrate how default copy constructors can be
// dangerous when not used carefully
int main(void){

  // In this section, we will instantiate StringWithUserDefinedCopyConstructor
  // and print string value
  const char *name = "Swapnil";
  StringWithUserDefinedCopyConstructor string1(name); // constructor should be called
  string1.print();

  //Now let's do something that will trigger copy constructor

  // Since, here, we're passing by value, formal parameter will make copy of
  // actual parameter and copy constructor will be invoked
  ChangeToUpperCase1(string1);

  // this will work
  cout << "after uppercasing: " << endl;
  string1.print();


  // Now let's try the same steps for a string class without user defined copy constructor

  const char *last = "Devikar";
  StringWithDefaultCopyConstructor string2(last); // constructor should be called
  string2.print();

  //Now let's do something that will trigger copy constructor

  // Since, here, we're passing by value, formal parameter will make copy of
  // actual parameter and copy constructor will be invoked
  // this will be the default copy constructor, so no print message should be seen
  // before "ChangeToUpperCase called" is seen
  ChangeToUpperCase2(string2);

  // If we do this now, the program should cause segmentation fault
  // this is because, string2.print() is printing _str member from string2 class
  // since we used default copy constructor, "string2", which is actual argument
  // gets copied to formal argument, "formalarg2" of StringWithDefaultCopyConstructor
  // on bit by bit basis
  // this mean, formalarg2._str and string2._str point to the same memory location
  // after StringWithDefaultCopyConstructor returns, the formalarg2 destructor is called
  // and formalarg2._str is freed
  // therefore, when string2.print() tries to print string2._str, which is same as
  // freed formalarg2._str, segmentation fault occurs


  // so, inside the instance of formalarg2, i.e. string_
  cout << "after uppercasing: " << endl;
  string2.print();


  return 0;
}

// This function will work as expected,
// because in the StringWithUserDefinedCopyConstructor class
//copy constructor is defined and copying the string as expected
bool ChangeToUpperCase1(StringWithUserDefinedCopyConstructor formalarg1){
  cout << "ChangeToUpperCase1 called for..." << formalarg1._str << endl;
  return true;
}

bool ChangeToUpperCase2(StringWithDefaultCopyConstructor formalarg2){
  cout << "ChangeToUpperCase2 called for..." << formalarg2._str << endl;
  return true;
}
