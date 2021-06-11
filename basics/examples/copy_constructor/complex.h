#include<iostream>

using namespace std;

class Complex{

private:
  int re;
  int im;

public:

  Complex(int re, int im): re(re), im(im){
    cout << "Constructor called" << endl;
  }

  ~Complex(){
    cout << "Desctructor called" << endl;
  }

  // This is the copy Constructor

  Complex(const Complex &c): re(c.re), im(c.im){
    cout << "Copy constructor called" << endl;
  }

};
