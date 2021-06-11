#ifndef _MYBASECLASS_H_
#define _MYBASECLASS_H_

#include <iostream>

using namespace std;


class MyBaseClass{

private:
  int m_PrivateMember = 10;

protected:
  int m_ProtectedMember = 20;

public:
  int m_PublicMember = 30;


  MyBaseClass(){
    cout << "In MyBaseClass constructor" << endl;
  }
};


#endif
