#include <iostream>

using namespace std;

int return_by_value(int &x);
int& return_by_reference(int &x); // notice the return type is int&

int main(void){
  int a = 10;

  cout << "Calling return_by_value(): "<< "a ="<<a << "&a= "<< &a << endl;

  // notice here that the reference b is a const. This is because return value
  // of this function is a constant value
  const int &b = return_by_value(a);

  // b should have the same value but a different address
  cout << "return_by_value() returned: "<< "b ="<<b << "&b= "<< &b << endl;

  cout << "Calling return_by_reference(): "<< "a ="<<a << "&a= "<< &a << endl;
  // note here that c is a const reference. This is consistent with with the concept of reference
  // a reference is something that is alias for something else.
  // in this case, that something is a value returned by an expression on the right
  // the reference expects that value to be a constant.
  const int &c = return_by_reference(a);

  // c should have the same value and same address as a
  cout << "return_by_reference() returned: "<< "c ="<<c << "&c= "<< &c << endl;

  // Since return value of return_by_reference is nothing but a reference to a,
  // we can assign a value to this function itself
  return_by_reference(a) = 3;

  cout << "new value of a is: " << a << endl;


}


int return_by_value(int &x){
  cout << "Inside return_by_value(): "<< "x ="<<x << "&x= "<< &x << endl;
  return x; // note here that the VALUE of x is returned. This is same as return 10;
}

int& return_by_reference(int &x){ //notice in return value in the signature
  cout << "Inside return_by_reference(): "<< "x ="<<x << "&x= "<< &x << endl;
  return x; // here the reference to x is returned, which is exactly what was received
}
