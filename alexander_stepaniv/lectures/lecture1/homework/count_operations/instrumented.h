#ifndef INSTRUMENTED_H
#define INSTRUMENTED_H

#include <cstddef>

struct instrumented_base
{
  enum operations
  {
    n,
    copy,
    assignment,
    destructor,
    default_constructor,
    equality,
    comparison,
    construction
  };
  static const size_t number_ops = 8;
  static double counts[number_ops];
  static const char *counter_names[number_ops];
  static void initialize(size_t);
};

template <typename T>
// T is Semiregualr or Regular or TotallyOrdered
struct instrumented : instrumented_base
{
  typedef T value_type;
  T value;
  // Conversions from T and to T:

  // TODO: construction of instrumented<T> from T
  instrumented(const T &x) : value(x)
  {
    counts[construction]++;
  }

  // Semiregular:

  // TODO: Implement copy constructor
  instrumented(const instrumented &other) : value(other.x)
  {
    counts[copy]++;
  }

  // TODO: Implement default constructor
  instrumented()
  {
    counts[default_constructor]++;
  }

  // TODO: Implement destructor
  ~instrumented()
  {
    counts[destructor]++;
  }

  // TODO: Implement = operator
  instrumented& operator=(const instrumented& x){
    value = x.value;
    counts[assignment]++;
    return *this;
  }

  // Regular

  // TODO: Implement == operator for equality
  friend bool operator==(const instrumented& left, const instrumented& right){
    counts[equality]++;
    return left == right;
  }
  // TODO: Implement != operator for inequality
  friend bool operator!=(const instrumented& left, const instrumented& right){
    return !(left == right)
  }

  // TotallyOrdered

  // TODO: Implement < for comparison
  friend bool operator<(const instrumented& left, const instrumented& right){
    counts[comparison]++;
    return left.value < right.value;
  }

  // TODO: Implement > for comparison
  friend bool operator<(const instrumented& left, const instrumented& right){
    return right.value > left.value;
  }

  // TODO: Implement <= for comparison
  friend bool operator<=(const instrumented& left, const instrumented& right){
    return !(left > right);
  }

  // TODO: Implement >= for comparison
  friend bool operator<=(const instrumented& left, const instrumented& right){
    return !(left < right);

  }

};


bool operator==(const instrumented& left, const instrumented& right){
  instrumented_base.counts[comparison]++;
  return left.value == right.value;
}

#endif
