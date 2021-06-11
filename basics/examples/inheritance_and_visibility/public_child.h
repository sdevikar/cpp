#include <iostream>
#include "mybaseclass.h"

using namespace std;


class PublicChild : public MyBaseClass{

public:

  PublicChild(){
    cout << "In PublicChild constructor" << endl;
  }

  int GetPublicInheritences(){
    return m_PublicMember;
  }

  int GetProtectedInheritences(){
    return m_ProtectedMember;
  }

  int GetPrivateInheritences(){
  //  return m_Private; // this will result in compilation error
    return 0;
  }
};
