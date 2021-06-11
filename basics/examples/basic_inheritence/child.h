#include <iostream>
#include "base.h"

using namespace std;

// Notice that the Child class is inheriting the Base class
class Child : public Base{

public:

  Child(){
    cout << "Constructor of child class called..." << endl;
  }

  ~Child(){
    cout << "Destructor of child class called..." << endl;
  }

  // We will NOT override this function from base class here
  //void FooBarPublicOne(){}

  // Function from base class is OVERRIDDEN as-is, i.e. with same signature
  void FooBarPublicTwo(){
    cout << "FooBarPublicOne in Child class" << endl;
  }


  // Function from base class is OVERLOADED (with different signature)
  void FooBarPublicThree(int x){
    cout << "FooBarPublicThree in Child class" << endl;
  }

  int GetInheritedProtected(){
    cout << "Returning base class protected member from child class" << endl;
    // following is equivalent to return Base::m_baseProtected
    return m_baseProtected;
  }

};
