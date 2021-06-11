#ifndef __CHILD_H__
#define __CHILD_H__

#include <iostream>
#include "parent.h"

using namespace std;

class Child : public Parent{

public:
  void Foo(){
    std::cout << "I am Foo in Child" << '\n';
  }

// It is not mandatory to write virtual keyword here. The function will be virtual by default
// as long as it is virtual in the base class
//  virtual void FooVirtual(){
  void FooVirtual(){
    std::cout << "I am FooVirtual in Child" << '\n';
  }
};

#endif
