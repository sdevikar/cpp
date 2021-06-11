#include <iostream>
#include "complex.h"

using namespace std;

//overriding the <<operator globally
// the only thing << needs to do is to know how to print a complex number
// since this is a friend function of complex class, accessing re and im is
//not a problem
ostream& operator<<(ostream& os, const Complex& c){
  cout << c.re << ", i" << c.im;
  return os;
}

//globally overridden istream operator
// the only thing that this function needs to do, is to read a complex number as re and im into c
// notice here that, for that reason c is NOT constant, because we will be reading INTO c
istream& operator>>(istream& is, Complex& c){
  cout << "inside operator >>" << endl;
  is >> c.re >> c.im; // first number in insteeam will go in re and second in im
  return is;
}

int main(){

  Complex c1(1,2);
  Complex c2(3,4);
  Complex c3;

  cout << "c1:\t" << c1 << endl;
  cout << "c2:\t" << c2 << endl;

  cout << "Enter re and im: "<<endl;
  cin >> c3;
  cout << "c3:\t" << c3 << endl;

  return 0;
}
