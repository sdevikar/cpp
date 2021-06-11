#ifndef _RECTANGLE_H_
#define _RECTANGLE_H_

#include <iostream>
#include "point.h"

using namespace std;

class Rectangle
{
private:
  // The order of this is important. This is the order in which the class members
  // will get initialized

  // CASE1: If we do this, then no matter what order the constructor init lists the
  // class members, mTopLeft will always be initialized first

  //Point mTopLeft;
  //Point mBottomRight;

  // CASE2: If we do this, no matter what order the constructor init lists the
  // class members, mBottomRight will always be initialized first
  Point mBottomRight;
  Point mTopLeft;

public:
  // Here we are overrding the constructor
  Rectangle(int topLeftX, int topLeftY, int bottomRightX, int bottomRightY):
  mTopLeft(Point(topLeftX, topLeftY)), mBottomRight(Point(bottomRightX, bottomRightY)){
    std::cout << "Inside Rectangle constructor"<<endl;
  }

  ~Rectangle(){
    std::cout << "Inside Rectangle destructor"<<endl;
  }

  void Describe(){
    cout << "Top: (" << mTopLeft.GetX() << "," << mTopLeft.GetY() << ")" << endl;
    cout << "Bottom: (" << mBottomRight.GetX() << "," << mBottomRight.GetY() << ")" << endl;
  }
};
#endif
