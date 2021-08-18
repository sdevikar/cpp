#include <iostream>

using namespace std;

class Complex{

private:

  int re;
  int im;

public:

  Complex(int _re=0, int _im=0):re(_re), im(_im){
    cout << "Complex constructor called" << endl;
  }

  ~Complex(){
    cout << "Complex destructor called" << endl;
  }

  Complex operator+(const Complex& comp){
    cout << "Operator + called - #1" << endl;
    Complex c;
    c.re = re + comp.re;
    c.im = im + comp.im;
    return c;
  }

  // this will account for complex.operator+(int z) i.e. complex_number + n
  Complex operator+(const int z){
    cout << "Operator + called - #2" << endl;
    Complex d(z,0); // create a new complex number with 0 imaginary part
    Complex result = d + comp; // this will call the + operator defined above
    return result;
  }

  // this will account for n+ complex_number
  // this is not a member function of the class
  // but a friend function can be *defined* within the class if desired
  // here, even though re and im are private members of Complex class,
  // because operator+ is a friend function, we can directly access these members
  friend Complex operator+(const int z, const Complex& comp){
    cout << "Operator + called - #3" << endl;
    return Complex(comp.re+z, comp.im);
  }

};
