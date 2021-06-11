#include <iostream>
#include "point.h"
#include "point2.h"

using namespace std;

// this is a global object in static area.
// This code block is executed even before main is executed
// This behavior is different from C
// constructor for this instance is called before main 
// and destructor is called last
Point point(100,200);

int main(void){

  cout << "Main started..."<<endl;

  // We will examine the order in which the constructor and destructor is called
  // using the examples below
  cout << "Creating Point instance"<<endl;
  Point point(1,2);

  // For a situation like below: where mass construction of an object takes place,
  // default constructor is called.

  Point p[3];

  // Now we will construct point2 objects and veryfy that the destructor for
  // point2 is called first and then the destructor of point class is called
  Point2 p2[3];

  cout << "Returning from main"<<endl;


  return 0;
}
