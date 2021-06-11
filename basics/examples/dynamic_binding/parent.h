#ifndef __PARENT_H__
#define __PARENT_H__

#include <iostream>

using namespace std;

class Parent{

public:
  void Foo(){
    std::cout << "I am Foo in Parent" << '\n';
  }

  virtual void FooVirtual(){
    std::cout << "I am FooVirtual in Parent" << '\n';
  }
};

#endif
