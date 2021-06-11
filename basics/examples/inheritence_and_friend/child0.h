#include <iostream>
#include "base.h"

using namespace std;

class Child0: public Base {

  //private by default
  int info = 3000;


#if 1 // here, we will override << operator for child class
public:

  // This is executed when cout << base; is called
  // We happened to define the friend function here along with its declaration
  // we could have totally just declared friend function here and declared somewher else globally
  // ALSO, this is not overriding the child class <<operator
  // instead, this is a completely new global function, because it's a friend function
  friend ostream& operator<<(ostream& os, Child0& c0){
    cout << "I am Child0";
    return os;
  }
#endif
};
