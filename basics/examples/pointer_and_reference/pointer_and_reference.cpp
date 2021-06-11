#include <iostream>

using namespace std;

#define ERROR_CASES_ENABLED     (0)

void pass_by_reference_function(
  int &b,
  int c
);


int main(void){
  // this is a normal variable
  int i = 15;

// here, we're assigning i to it's reference
// i.e. i can also be referred as j from now on
  int &j = i;

// as such, the following statement is invalid, because z is a reference that's
// not referring to anything right now
#if ERROR_CASES_ENABLED
int &z;
#endif

  cout << "value of j: " << j << endl;

  // change in the value of j, causes i to change
  // this is to prove the point that they're the same thing

  j = 20;

  cout << "new value of i: " << i << endl;

  // j is not a pointer to an integer variable
  // hence following should result in an error
#if ERROR_CASES_ENABLED
  int k = 50;
  j = &k; // j is not a pointer, so this is an invalid statement
#endif

// You cannot assign a value to a reference
#if ERROR_CASES_ENABLED
&j = 90; // this is saying that j refers to 90. 90 is not a variable that can be aliased.
         // rather, it's a constant value
#endif

// You can however assign a const value to a const reference

const int &const_ref = 999; // notice here that we're doing declaration and
                            // definition together, since reference is constant
cout << "Value of const_ref = " << const_ref << endl;

const int &const_ref2 = 100+200;
cout << "Value of const_ref2 = " << const_ref2 << endl;

cout << "value of i = " << i << "address of i = "<< &i <<endl;
pass_by_reference_function(i,i);
return 0;

}

void pass_by_reference_function(int &b, int c){
  cout << "value of b = " << b << "address of b = "<< &b <<endl;
  cout << "value of c = " << b << "address of c = "<< &c <<endl;
};
