#ifndef _COMPLEX_H_
#define _COMPLEX_H_

#include <math.h>

class Complex
{
public:
    double real;
    double img;

    Complex(double real, double img) : real(real), img(img){};
};

#endif // !__COMPLEX_H_
