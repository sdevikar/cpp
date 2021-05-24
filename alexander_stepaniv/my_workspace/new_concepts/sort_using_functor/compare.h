#ifndef _COMPARE_H_
#define _COMPARE_H_

#include "complex.h"

double magnitude(Complex x)
{
  return sqrt((x.real * x.real) + (x.img * x.img));
};

// this Compare will work for any totally ordered datatype T
template <typename T>
struct Compare
{

  bool operator()(const T &a, const T &b) const
  {
    return a < b;
  }
};

// this will work for complex
template <>
struct Compare<Complex>
{
  bool operator()(const Complex &a, const Complex &b)
  {
    return magnitude(a) < magnitude(b);
  }
};

#endif // !_COMPARE_H_
