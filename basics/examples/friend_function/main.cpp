#include <iostream>
#include "key_generator.h"
#include "utility.h"

using namespace std;


// This function has to be defined here
// because utility.h, does not know about keygenerator
// We used forward declaration for keygenerator in utility.h instead
void Utility::Display(KeyGenerator& keygen){
  // Since this is a friend function, it has access to
  // private data member of keygen
  std::cout << keygen.mSecretKey << endl;
}


int main(void){
  KeyGenerator keygen;
  Utility utility;
  utility.Display(keygen);

  return 0;
}
