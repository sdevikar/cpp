#include<iostream>
#include<cstdlib>

using namespace std;

int main(void){

  // traditional memory allocation using malloc
  // these come from stdlib and not a part of core language
  int *p1 = (int *)malloc(sizeof(int));
  *p1= 5;
  cout << "p1: " << *p1 << endl;
  free(p1);

  // We can do the same thing in C++ with new opertor as follow
  // keep in mind that new is an operator
  // this operator will return the type of pointer int* in this case
  // as such new will return the pointer of type specified by it's operands
  // the "int" in "new int" is a type operand to new operator
  // also note that we can also pass an initial value of 5, as shown below
  int *p2 = new int(5);
  cout << "p2: " << *p2 << endl;

  // delete is also an operator, similar to free function.
  // Note that malloc and free are functions
  // whereas new and delete are operands
  delete(p2);

  // by the way, since new, delete, these are operators, we can call them
  // by their function calls
  int *p3 = (int *) operator new(sizeof(int));
  *p3 = 100;
  cout << "p3: " << *p3 << endl;

  operator delete(p3);

  // IMPORTANT: the function for operator new/delete and the operator itself
  // are interchangeable only for primitive data types

  /*
  * Array oeprator new
  * Array operator delete
  */

  // We have a couple of other operators to allocate and delete memory for arrays
  int *arr = new int[10]; // equivalent to malloc for sizeof(int)*10

  for(int index=0; index < 10; index++){
    arr[index] = index;
  }

  delete [] arr;

  /*
  * Allocating memory from a predefined location
  */

  // let's say we have a memory pool available
  char *pool = new char[100];

  // we can use the above pool to allocate memory, instead of letting compiler choose
  int *p4 = new (pool) int(2); //this is creating

  cout << "address of pool:" << &pool[0] << endl;
  cout << "address of p4:" << p4 << endl;


}
