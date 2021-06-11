#include <iostream>

using namespace std;

class Complex{

private:

  // we will keep these public for now, for simplicity
  int re;
  int im;

public:

  Complex(int _re=0, int _im=0):re(_re), im(_im){
    cout << "Complex constructor called" << endl;
  }

  ~Complex(){
    cout << "Complex destructor called" << endl;
  }

  friend ostream& operator<<(ostream& os, const Complex& c);
  friend istream& operator>>(istream& is, Complex& c);

};
