#include <iostream>
#include "complex.h"

using namespace std;

// globally overloaded operator minus (-)

Complex operator-(Complex &c1, Complex &c2){
  cout << " Operator minus called" << endl;
  cout << "First argument: " << "(" << c1.re << ", i" << c1.im << ")" << endl;
  cout << "Second argument: " << "(" << c2.re << ", i" << c2.im << ")" << endl;
  Complex c3;
  c3.re = c1.re-c2.re;
  c3.im = c1.im-c2.im;
  return c3;
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



}
