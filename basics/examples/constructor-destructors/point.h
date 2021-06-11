#ifndef _POINT_H_
#define _POINT_H_
#include <iostream>

using namespace std;

class Point{
private:
  int x;
  int y;
  int init(int x);

public:
  Point(int x, int y);
  Point();
  ~Point();
  int GetX();
  int GetY();
  void SetX(int x);
  void SetY(int y);
};
#endif
