#include <iostream>
#include "string3.h"
#include "string4.h"

using namespace std;


// In this example, we will write our own string classes
// and demonstrate how default copy operator can be
// dangerous when not used carefully
int main(void){

  // In this section, we will instantiate StringWithOverloadedCopyOperator
  // and print string value
  const char *name = "Swapnil";
  StringWithOverloadedCopyOperator string1(name); // constructor should be called
  string1.print();

  //Now let's do something that will trigger copy operator
  StringWithOverloadedCopyOperator string2("Devikar");
  string2 = string1;

  // this will work
  cout << "After invoking copy operator: " << endl;
  string2.print();

  // now let's try self copy. This is expected to crash
  // since we are currently freeing the StringWithOverloadedCopyOperator._str
  // before strdup in =operator logic
  cout << "Invoking copy operator for self...: " << endl;
  string1.print();
  string1 = string1; // segmentation fault here
  string1.print();


  cout << "After fixing the bug in copy operator ..." << endl;
  const char *company = "Google";
  StringWithOverloadedCopyOperator2 string3(company); // constructor should be called
  string3.print();
  string3 = string3;
  string3.print();

  return 0;
}
