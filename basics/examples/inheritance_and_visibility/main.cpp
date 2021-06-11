#include <iostream>
#include "public_child.h"
#include "private_child.h"

using namespace std;


int main(void){

  PublicChild pbc;

  cout << "Inherited public: " << pbc.GetPublicInheritences() << endl;
  cout << "Inherited protected: " << pbc.GetProtectedInheritences() << endl;
//  cout << "Inherited private: " << pbc.GetPrivateInheritences() << endl; // this will result in error

  PrivateChild pvc;
  cout << "Inherited public: " << pvc.GetPublicInheritences() << endl;
  cout << "Inherited protected: " << pvc.GetProtectedInheritences() << endl;
  cout << "Inherited private: " << pvc.GetPrivateInheritences() << endl; // this will result in error


  return 0;
}
