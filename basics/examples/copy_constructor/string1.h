#include <iostream>

using namespace std;

class StringWithUserDefinedCopyConstructor{

public: // kept these public for convenience
  char* _str;
  int _len;

public:
  // this is the class constructor
  StringWithUserDefinedCopyConstructor(const char *str): _str(strdup(str)), _len(strlen(str)){
    cout << "Inside constructor of StringWithUserDefinedCopyConstructor" << endl;
  }

  ~StringWithUserDefinedCopyConstructor(){
      cout << "Inside StringWithUserDefinedCopyConstructor desctructor" << endl;
      free(_str);
  }

  // this is the copy constructor
  StringWithUserDefinedCopyConstructor(const StringWithUserDefinedCopyConstructor& source):
  _str(strdup(source._str)), _len(strlen(source._str)){
    cout << "Inside COPY constructor of StringWithUserDefinedCopyConstructor" << endl;
  }


void print(){
  cout << "I am: " << _str << endl;
}
};
