#include <iostream>

using namespace std;

class MyClass{

private:
  static int _counter; // this is just a declaration and NOT initialization/definition
  int instance_counter;

public:

  static bool flag; // this is just a declaration and NOT initialization/defnition

  static int GetCounter(){
    return _counter;
  }

  static void SetCounter(int val){
    _counter = val;
  }

  static void Up(){
    _counter++;
  }

  static void Down(){
    _counter--;
  }

  void Status(){
    // this is possible because no matter what the instance of class,
    // _counter will exist and be available
    cout << "Current count is:" << _counter << endl;
  }

  void static StaticStatus(){
#if 0
    // this is not possible because static member function can't access non static data members
    // because - static method does not have this object, so it cannot do
    // this->instance_counter
    cout << "Instance counter is:" << instance_counter << endl;
#endif
  }
};
