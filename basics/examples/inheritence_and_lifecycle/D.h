#include <iostream>

#include "C.h"

using namespace std;


class D : public B{

  C c;


public:
  D(){
    cout << "Constructor of D" << endl;
  }

  ~D(){
    cout << "Destructor of D" << endl;
  }

};
