#ifndef _BASECLASS_

#define _BASECLASS_

#include <iostream>

using namespace std;


class Base{

private:
  int m_basePrivate = 0;

  void FooBarPrivate(){
    cout << "FooBarPrivate in Base class" << endl;
  }

protected:
  int m_baseProtected = 500;

public:

  Base(){
    cout << "Constructor of base class called..." << endl;
  }

  ~Base(){
    cout << "Destructor of base class called..." << endl;
  }


  int m_basePublic = 1000;


  void FooBarPublicOne(){
    cout << "FooBarPublicOne in Base class" << endl;
  }

  void FooBarPublicTwo(){
    cout << "FooBarPublicOne in Base class" << endl;
  }

  void FooBarPublicThree(){
    cout << "FooBarPublicThree in Base class" << endl;
  }
};

#endif
