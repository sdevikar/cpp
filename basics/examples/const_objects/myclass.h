#ifndef _MYCLASS_
#define _MYCLASS_

#include <iostream>

using namespace std;

class MyClass
{

public:
  MyClass(){
    cout << "Default constructor" << endl;
  }

private:
  int _a;
  int _b;
  int mutable _z;

public:
  int x;
  int y;

int geta(){
  return _a;
}

int getb(){
  return _b;
}

int getx(){
  return x;
}

int gety(){
  return y;
}

void message(){
  cout << "Hello!" << endl;
}

/*
* Special section with const functions are defined below
*/
void setaForReal(int val) const {
  // this will cause error
  _a = val;
}

int getaForReal() const {
  return _a;
}

void setMutableZ(int z) const{
  _z = z;
}
};
#endif
