#ifndef _POINT2_H_
#define _POINT2_H_
#include <iostream>

using namespace std;

class Point2{
private:
  int x;
  int y;
  int init(int x);

public:
  Point2(int x, int y);
  Point2();
  ~Point2();
  int GetX();
  int GetY();
  void SetX(int x);
  void SetY(int y);
};
#endif
