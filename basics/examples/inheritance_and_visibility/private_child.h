#include <iostream>
#include "mybaseclass.h"

using namespace std;


class PrivateChild : private MyBaseClass{

public:

  PrivateChild(){
    cout << "In PrivateChild constructor" << endl;
  }

  int GetPublicInheritences(){
    return m_PublicMember; // results in an error - there is no IS A relationship for private inheritance
  }

  int GetProtectedInheritences(){
    return m_ProtectedMember; // results in an error - there is no IS A relationship for private inheritance
  }

  int GetPrivateInheritences(){
    return m_Private; // results in an error - there is no IS A relationship for private inheritance
  }
};
