#include <iostream>
#include "base.h"

using namespace std;

class Child : public Base {

  //private by default
  int info = 3000;


#if 0 // here, we won't define << operator
// NOTE: Even if we define the << operator, we're not overriding the base class << operator
// Instead, it's a completely new global function, because it's a friend function
public:

  // This is executed when cout << base; is called
  // We happened to define the friend function here along with its declaration
  // we could have totally just declared friend function here and declared somewher else globally
  friend ostream& operator<<(ostream& os, Child& c){
    cout << "I am Child";
    return os;
  }
#endif
};
