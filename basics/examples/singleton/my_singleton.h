#include <iostream>

using namespace std;

class MySingleton{

private:

  // this will hold the instance of class
  static MySingleton* instance;

  // by making the constructor private,
  // we will prevent calling constructors from the application

  MySingleton(){
    // do nothing here
  }

public:
  ~MySingleton(){

  }

  static const MySingleton & GetInstance(){
    if(!instance){
      instance = new MySingleton();
    }
    return *instance;
  }

  void Message(){
    cout << "Success!" << endl;
  }

};
