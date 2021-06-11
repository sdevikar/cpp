#include "point.h"


Point::Point(){
  cout << "Called default constructor" << endl;
}

Point::Point(int x, int y):x(init(x)), y(init(y)){
  cout << "Inside Point constructor: (" << x << ", " << y << ")"<<endl;
}

Point::~Point(){
  cout << "Inside Point destructor: " << "(" << x << ", "<< y << ")"<<endl;
}

int Point::GetX(){
  return x;
}

int Point::GetY(){
  return y;
}

void Point::SetX(int x){
  this->x =  x;
}

void Point::SetY(int y){
  this->y = y;
}

int Point::init(int val){
  cout << "Init called from initializer list for:" << val << endl;
  return val;
}
