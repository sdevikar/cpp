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

  // used as a size of decimals array
  // reprensents how many operations are we supporting: construction, destruction, copy etc.
  size_t cols = instrumented<double>::number_ops;
 

  size_t decimals[cols];

  // creating an integer with initial value either 0 or 2
  size_t normalized((norm == dont_normalize) ? 0 : 2);
  
  // decimals[0] = 0
  *decimals = 0;

  // fill the decimals array: decimals[1] = normalized... decimals[cols] = normalized
  std::fill(decimals + 1, decimals + cols, normalized);
  
  table_util table;
  table.print_headers(instrumented<double>::counter_names, instrumented<double>::number_ops, 12); 
 
  // this loop will run starting from i, i*2, i*4 ...
  while (i <= j) {
   
    // create a vector with size i
    // each iteration will create a vector of size = i, i*2, i*4...
    std::vector<instrumented<double> > vec(i);

    // fill out this vector with increasing values from 0,1,2...i
    // then shuffle it
    course::iota(vec.begin(), vec.end(), 0.0);	
    std::random_shuffle(vec.begin(), vec.end());


    instrumented<double>::initialize(i);

    // now you're passing the vector iterator to the function
    // which, in this case, is "sort"
    // sort will do its thing then
    fun(vec.begin(), vec.end());
    
    // read the counts array from instrumented class
    // this is where you will have to update all the counts
    double* count_p = instrumented<double>::counts;
    
    for (size_t k(1); k < cols; ++k) count_p[k] = norm(count_p[k], count_p[0]);

    table.print_row(count_p, decimals);

    i <<= 1;
  }
}

#endif
