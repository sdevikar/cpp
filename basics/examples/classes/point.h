#ifndef _POINT_H_
#define _POINT_H_
#include <iostream>

using namespace std;

class Point{
private:
  int x;
  int y;

public:
  Point(int x, int y):x(x), y(y){
    cout << "Inside Point constructor: (" << x << ", " << y << ")"<<endl;
  }

  ~Point(){
    cout << "Inside Point destructor" << endl;
  }

  int GetX(){
    return x;
  }

  int GetY(){
    return y;
  }
};
#endif
