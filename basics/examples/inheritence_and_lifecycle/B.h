#ifndef _B_
#define _B_

#include <iostream>

using namespace std;


class B {


public:
  B(){
    cout << "Constructor of B" << endl;
  }

  ~B(){
    cout << "Destructor of B" << endl;
  }

};

#endif
