//****************************************************************************//
// The shape class has a method called draw.
// This is a pure virtual method
// Because of this pure virtual function, the class cannot be instantiated
// The constructor and desctructor of shape are still called as usual
// since, the child class has to contain an object of parent class
//****************************************************************************//

#include <iostream>

using namespace std;


class Shape{

public:

  Shape(){
    cout << "Shape created" << endl; // this should never be called since there can be no instances
  }

  ~Shape(){
    cout << "Shape Destroyed!" << endl;
  }

  virtual void Draw()=0; // this is a pure virutual function and MUST be overridden in the base class

  // note that even when the function is purely virtual, we can still provide an Implementation to it
  // See definition below
  virtual void UnDraw() = 0;
};


void Shape::UnDraw(){
  cout << "A common implementation that every shape can call" << endl;
}
