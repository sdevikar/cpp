#include <iostream>
#include "point.h"
#include "rectangle.h"

using namespace std;

int main(void){
  Rectangle rectangle(1,2,3,4);
  rectangle.Describe();

  // The following won't work because we overrode the constructor of Rectangle
  Rectangle r2;

}
