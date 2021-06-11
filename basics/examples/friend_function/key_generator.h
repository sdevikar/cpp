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

  // I don't want to add a GetKey function here, because I don't want
  // just anyone to be able to display the secret key
  // Instead, only Utility class is allowed to do that
  friend void Utility::Display(KeyGenerator& keygen);
};

#endif
