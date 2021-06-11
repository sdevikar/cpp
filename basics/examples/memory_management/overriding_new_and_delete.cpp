#include<iostream>
#include<cstdlib>

using namespace std;


// notice the return type is void*. It is mandatory that return type is void*
// and parameter type is size_t
// we can potentially add more parameters
void* operator new(size_t n);

// operator new[]
void* operator new [] (size_t n);

// we can also override new[] with initialization values
void* operator new [] (size_t n, char setvals);


// notice the argument void*
// NOTE: Try not to overload delete with extra parameters
// That kind of behavior is reserved for the user defined datatypes
// we'll see that later
void operator delete(void *p);




int main(void){
  int *a = new int;
  delete a;

  // surprisingly, the following works too
  // even though, there is no explicit logic in overloaded new operator.
  // This must mean that the assignment of value happens after new operator
  // has returned the requested pointer
  int *b = new int(5);
  cout << "Value of b:" << *b << endl;
  delete b;

  // Allocation and de-allocation for arrays
  char *p = new char[6];

  delete [] p;

  // Calling new [] operator with initializer values
  char *q = new ('#') char[5];
  for(int i = 0; i< 5; i++){
    cout << q[i] << endl;
  }

  delete [] q;
  return 0;

}

// notice that the size here is implicitly passed
// the calling location simply says new int
// compiler translates that into sizeof(int) when calling  operator new
void * operator new(size_t n){
  cout << "Inside operator new" << endl;
  void *p = malloc(n);
  return p;
}

void operator delete(void *p){
  cout << "Inside operator delete" << endl;
  free(p);

}

// notice that the size here is implicitly passed. i.e.
// calling location says new char[6]
// compiler translates it to sizeof(char)*6 and passes it to the definition site
// then we go ahead and pass that size on to operator new
void* operator new [] (size_t n){
  cout << "Inside operator new[]" << endl;
  void *p = operator new(n);
  return p;
}

void operator delete [](void *p){
  cout << "Inside operator delete[]" << endl;
  operator delete(p);
}

void* operator new [] (size_t n, char setvals){
  void *p = operator new(n);
  memset(p, setvals, n);
  return p;
}
