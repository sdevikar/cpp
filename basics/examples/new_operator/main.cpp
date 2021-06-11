#include <iostream>
#include "point.h"

using namespace std;


int main(void){

  // new operator will:
  // - allocate memory for the object being created
  // - call constructor
  Point *point = new Point(1,2);

  // delete operator will:
  // -call the destructor
  // - deallocate the memory allocated to this object
  delete point;

  // we will use this buffer for object memory allocation
  unsigned char buff[200];
  Point *point2 = new (buff) Point(100,200);

  // The only way to call destructor in this situation, is to call is explicitly
  point2->~Point();

  return 0;
}
