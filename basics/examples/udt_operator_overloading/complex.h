#include <iostream>

using namespace std;

class Complex{

public:

  // we will keep these public for now, for simplicity
  int re;
  int im;

  Complex(int _re=0, int _im=0):re(_re), im(_im){
    cout << "Complex constructor called" << endl;
  }

  ~Complex(){
    cout << "Complex destructor called" << endl;
  }

  Complex operator+(const Complex& comp){
    cout << "Operator + called" << endl;
    Complex c;
    c.re = re + comp.re;
    c.im = im + comp.im;
    return c;
  }

  // this is pre-increment operator

  // Notice here that the return value is reference to Complex object
  // i.e. whoever is calling ++ operator will receive the **reference** to
  // this object
  Complex& operator++(){
    cout << "Pre increment operator called" << endl;
    re++;
    im++;
    return *this;
  }

  // this is post-increment operator
  // notice the additional int argument
  // also notice that we're returning a new object Complex c
  // therefore, this is not returning a reference
  // BEcause the caller will make a copy of Complex c, when they
  // access it using = operator
  Complex operator++(int){
    cout << "Post increment operator called" << endl;
    Complex c(re, im); // create a new object
    re++; // change internal state
    im++; // change internal state
    return c; // return the copy of original object
  }

};
