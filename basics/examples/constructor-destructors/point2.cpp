#include "point2.h"


Point2::Point2(){
  cout << "Called default constructor of Point2" << endl;
}

Point2::Point2(int x, int y):x(init(x)), y(init(y)){
  cout << "Inside Point2 constructor: (" << x << ", " << y << ")"<<endl;
}

Point2::~Point2(){
  cout << "Inside Point2 destructor: " << "(" << x << ", "<< y << ")"<<endl;
}

int Point2::GetX(){
  return x;
}

int Point2::GetY(){
  return y;
}

void Point2::SetX(int x){
  this->x =  x;
}

void Point2::SetY(int y){
  this->y = y;
}

int Point2::init(int val){
  cout << "Point2 Init called" << endl;
  return val;
}
