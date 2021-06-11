#include <iostream>
#include "my_singleton.h"

using namespace std;

MySingleton* MySingleton::instance = 0; // necessary to avoid linker error

int main(void){

  MySingleton singleton = MySingleton::GetInstance();
  singleton.Message();
  return 0;
}
