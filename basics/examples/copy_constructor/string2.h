#include <iostream>

using namespace std;

class StringWithDefaultCopyConstructor{

public: // kept these public for convenience
  char* _str;
  int _len;

public:
  // this is the class constructor
  StringWithDefaultCopyConstructor(const char *str): _str(strdup(str)), _len(strlen(str)){
    cout << "Inside constructor of StringWithUserDefinedCopyConstructor" << endl;
  }

  ~StringWithDefaultCopyConstructor(){
    cout << "Inside StringWithDefaultCopyConstructor desctructor" << endl;

      free(_str);
  }

  // User did not define copy constructor this time
  // so compiler will provide one
  // and git by bit copy will take place
  // this means, the _str in this class will contain the address of _str in
  // formal argument


void print(){
  cout << "I am: " << _str << endl;
}
};
