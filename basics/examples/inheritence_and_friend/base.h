#ifndef _BASE_H_
#define _BASE_H_

#include <iostream>

using namespace std;

class Base{

  //private by default
  int seed = 1000;

public:

  // Note that this is not a member function of the base class
  // This is executed when cout << base; is called
  // We happened to define the friend function here along with its declaration
  // we could have totally just declared friend function here and declared somewher else globally
  friend ostream& operator<<(ostream& os, Base& b){
    cout << "I am Base";
    return os;
  }
};

#endif
