#include <iostream>
#include "rectangle.h"
//#include "closed_conics.h"

using namespace std;

int main(void){
  // Shape shape; // this is not possible

  Rectangle rect;

  rect.Draw();
  rect.UnDraw(); // this calls Shape::UnDraw() too

  //ClosedConics cc; // this gives error
}
