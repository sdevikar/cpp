#include <iostream>
#include "shape.h"


using namespace std;

class Rectangle : protected Shape{

public:

  Rectangle(){
    cout << "Rectangle Created!" << endl;
  }

  ~Rectangle(){
    cout << "Rectangle Destroyed!" << endl;
  }

  void Draw(){
    cout << "Rectangle Drawn!" << endl;
  };


  void UnDraw(){
    // Notice how parent class function is called here
    Shape::UnDraw();
    cout << "Rectangle UnDrawn!" << endl;
  };

};
