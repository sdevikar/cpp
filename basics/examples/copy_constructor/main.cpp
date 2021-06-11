#include <iostream>
#include "complex.h"

using namespace std;

void PassByValue(Complex cformal);

int main(void){

  cout << "Creating C1 object" << endl;
  Complex c1(1,2);

  cout << "Constructing C2 by passing C1 object" << endl;
  Complex c2(c1);

  cout << "Constructing C3 by usig = assignment" << endl;
  Complex c3 = c1;

  cout << " Calling PassByValue... expecting copy constructor to be called" << endl;
  PassByValue(c3);

  return 0;
}

void PassByValue(Complex cformal)
{
  cout << "PassByValue called..." << endl;
}
