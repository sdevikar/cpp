//****************************************************************************//
// This class does not override any of the pure virtual method and thus
// remains an abstract class that cannot be instantiated
//****************************************************************************//

#include <iostream>
#include "shape.h"


using namespace std;

class ClosedConics : protected Shape{

public:

  ClosedConics(){
    cout << "ClosedConics Created!" << endl;
  }

  ~ClosedConics(){
    cout << "ClosedConics Destroyed!" << endl;
  }


};
