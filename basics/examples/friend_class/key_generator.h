#ifndef _KEYGENERATOR_H
#define _KEYGENERATOR_H


#include <iostream>
#include <string>
#include <random>
#include "utility.h"

using namespace std;


class KeyGenerator{

private:
  string mSecretKey;

public:
  KeyGenerator(){
    mSecretKey = "fjdkldfdh38975049875dhfjkdh344jfhkfhd";
  }

  // Instead of Utility::Display, we will now make Utility class itself as a friend
  //friend class Utility::Display(KeyGenerator& keygen);
  friend class Utility;
};

#endif
