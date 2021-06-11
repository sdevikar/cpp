#include <iostream>


using namespace std;

class StringWithOverloadedCopyOperator2{

public: // kept these public for convenience
  char* _str;
  int _len;

public:
  // this is the class constructor
  StringWithOverloadedCopyOperator2(const char *str): _str(strdup(str)), _len(strlen(str)){
    cout << "Inside constructor of StringWithOverloadedCopyOperator2: "<< str << endl;
  }

  ~StringWithOverloadedCopyOperator2(){
    cout << "Inside StringWithOverloadedCopyOperator2 desctructor" << endl;

      free(_str);
      _str = NULL;
  }

  StringWithOverloadedCopyOperator2& operator=(const StringWithOverloadedCopyOperator2& input){
    cout << "Inside StringWithOverloadedCopyOperator2 =operator function" << endl;

    // here we will check if the formal argument is the same as current instance

    if(this != &input){
      free(_str);
      _str = NULL; // I added this hack to have the program crash.
                   // otherwise, the free operation had no effect
      _str = strdup(input._str);
      _len = input._len;
  }
    return *this; // to allow for the chain assignment
  }


void print(){
  cout << "I am: " << _str << endl;
}
};
