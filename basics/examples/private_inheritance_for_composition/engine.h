#include <iostream>


using namespace std;

class Engine{

public:

  Engine(){
    cout << "Engine Created!" << endl;
  }

  ~Engine(){
    cout << "Engine Destroyed!" << endl;
  }

  void Start(){
    cout << "Engine started!" << endl;
  };

};
