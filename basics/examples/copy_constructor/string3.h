#include <iostream>


using namespace std;

class StringWithOverloadedCopyOperator{

public: // kept these public for convenience
  char* _str;
  int _len;

public:
  // this is the class constructor
  StringWithOverloadedCopyOperator(const char *str): _str(strdup(str)), _len(strlen(str)){
    cout << "Inside constructor of StringWithOverloadedCopyOperator: "<< str << endl;
  }

  ~StringWithOverloadedCopyOperator(){
    cout << "Inside StringWithOverloadedCopyOperator desctructor" << endl;

      free(_str);
  }

  StringWithOverloadedCopyOperator& operator=(const StringWithOverloadedCopyOperator& input){
    cout << "Inside StringWithOverloadedCopyOperator =operator function" << endl;

    // it is important to free the space for existing allocated memory for _str
    // before we can duplicate other string
    // As we will find out in subsequent example, there is one catch here
    // see string4.h for the fix
    free(_str);
    _str = NULL; // I added this hack to have the program crash.
                 // otherwise, the free operation had no effect
    _str = strdup(input._str);
    _len = input._len;
    return *this; // to allow for the chain assignment
  }


void print(){
  cout << "I am: " << _str << endl;
}
};
