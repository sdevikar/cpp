#include <iostream>
#include "child.h"
#include "parent.h"


using namespace std;

int main(void){
  Parent p;
  Child c;


  //same is the case with the pointers
  Parent *p1;
  Child *c1;

  cout << "Simplest case1: Calling methods on concrete objects" << endl;
  // if we call ANY method on corresponding objects, they should be invoked as usual
  p.Foo();
  c.Foo();
  p.FooVirtual();
  c.FooVirtual();


  cout << "Simplest case2: Calling methods on object pointers" << endl;

  p1 = new Parent();
  c1 = new Child();

  p1->Foo();
  c1->Foo();
  p1->FooVirtual();
  c1->FooVirtual();

  cout << "Case3: Assigning the child class pointer to base class type - this is  where virtual comes into picture:" << endl;
  p1 = &c; // this is allowed

  // even though p1 is technically pointing to child class, Parent::Foo is called because Foo() is not virtual -- this is the case of static binding still
  // the reason is that compiler knows that p1 is an object of Parent type and statically binds Foo() call to Parent class
  p1->Foo();

  // since FooVirtual was defined as Virtual, Child::FooVirtual will be called -- this is the case of dynamic binding
  p1->FooVirtual();


  cout << "Case4: Same as the above case, but with concrete objects instead of pointers:" << endl;

  Parent p3 = c;

  p3.Foo();
  p3.FooVirtual(); 

}
