//****************************************************************************//
// The fact that every class object with IS A relationship with base class
// holds an instance of its base class implicitly, it is necessary to create base
// class object first.
// This is true for private inheritance as well,
// BUT, IN PRIVATE INHERITANCE, THERE IS NO IS A RELATIONSHIP
// So, in effect, with private inheritance. we're creating an effect of
// composition
//****************************************************************************//

#include <iostream>
#include "engine.h"

using namespace std;


class Car : private Engine{

public:

  Car(){
    cout << "Car Created!" << endl;
  }

  ~Car(){
    cout << "Car Destroyed!" << endl;
  }

  // In normal circumstances, Car::Start() will be called when we call
  // car.Start() Car instance

  // But we want Engine::Start to be called, when we say Car::Start()
  // The following notation will help achieve that:

  using Engine::Start;
};
