#ifndef COUNT_OPERATIONS_H
#define COUNT_OPERATIONS_H

#include <vector>
#include <algorithm>
#include <cmath>

#include "iota.h"
#include "instrumented.h"
#include "table_util.h"

double normalized_by_n(double x, double n) { return x / n; }
double normalized_by_nlogn(double x, double n) { 
  return x / (n * (log(n) / log(2))); 
}
double dont_normalize(double x, double) { return x; }

template <typename Function>
void count_operations(size_t i, size_t j, Function fun, double (*norm)(double, double) = dont_normalize) { 
// measure operations on an interval of a given length 
// ranging from i to j and going through i, 2i, 4i, ... up to and including j

  size_t cols = instrumented<double>::number_ops;
 
  size_t decimals[cols];
  size_t normalized((norm == dont_normalize) ? 0 : 2);
  *decimals = 0;
  std::fill(decimals + 1, decimals + cols, normalized);
  
  table_util table;
  table.print_headers(instrumented<double>::counter_names, instrumented<double>::number_ops, 12); 
 
  while (i <= j) {
   
    // vector of size 16,32,64, etc will be constructed
    std::vector<instrumented<double> > vec(i);
    // vector is populated from 0 to end range
    course::iota(vec.begin(), vec.end(), 0.0);
    // vector is shuffled	
    std::random_shuffle(vec.begin(), vec.end());

    //results are initialized
    instrumented<double>::initialize(i);

    // function  is called on vector
    fun(vec.begin(), vec.end());
    
    // table is printed
    double* count_p = instrumented<double>::counts;
    
    for (size_t k(1); k < cols; ++k) count_p[k] = norm(count_p[k], count_p[0]);

    table.print_row(count_p, decimals);

    i <<= 1;
  }
}

#endif
