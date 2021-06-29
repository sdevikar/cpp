#ifndef INSTRUMENTED_H
#define INSTRUMENTED_H

#include <cstddef>

struct instrumented_base
{
  enum operations {
    n, copy, assignment, destructor, default_constructor, equality, comparison, construction
  };
  static const size_t number_ops = 8;
  static double counts[number_ops];
  static const char* counter_names[number_ops];
  static void initialize(size_t);
};


template <typename T> 
// T is Semiregualr or Regular or TotallyOrdered
struct instrumented :  instrumented_base
{
  typedef T value_type;
  T value;
  // Conversions from T and to T:
  // TODO: construction of instrumented<T> from T


  // Semiregular:
  
  // TODO: Implement copy constructor

  // TODO: Implement default constructor

  // TODO: Implement destructor

  // TODO: Implement = operator

  
  
  // Regular

  // TODO: Implement == operator for equality
  // TODO: Implement != operator for inequality


  // TotallyOrdered

  // TODO: Implement < for comparison
  // TODO: Implement > for comparison
  // TODO: Implement <= for comparison
  // TODO: Implement >= for comparison

};

#endif







