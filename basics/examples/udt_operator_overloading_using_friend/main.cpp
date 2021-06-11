#include <iostream>
#include "complex.h"

using namespace std;

// overriding << globally
// this function should simply be able to print out complex number in x + iy format
ostream& operator<<(ostream& os, const Complex c){
  cout << c.re << ", i" << c.im;
  return ostream;
}

int main(){

  Complex c1(1,2);
  Complex c2(2,1);

  // This is the overloaded operator inside the class
  Complex c3 = c1+c2;
  cout << "Result of addition:" << endl;
  cout << "("<< c3.re << ", i" << c3.im << ")" << endl;

  Complex c4 = c1 - c2;
  cout << "Result of subtraction:" << endl;
  cout << "("<< c4.re << ", i" << c4.im << ")" << endl;

  Complex c5 = ++c4;
  cout << "("<< c5.re << ", i" << c5.im << ")" << endl;

  c5 = c4++;
  cout << "("<< c5.re << ", i" << c5.im << ")" << endl;

  cout << "Value of post incremented instance" << endl;
  cout << "("<< c4.re << ", i" << c4.im << ")" << endl;

  cout << "Another version of overloaded + operator:" << endl;

  cout << "Before: ("<< c5.re << ", i" << c5.im << ")" << endl;

  c5 = 5+c5; // this calls Complex operator+(const int z, const Complex& comp)
            // this wouldn't have been possible if the operator overload function was a member function
            // because for a member function, this would translate to 5.operator+(c5)

  cout << "After: ("<< c5.re << ", i" << c5.im << ")" << endl;





}
