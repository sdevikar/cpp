#include "count_operations.h"
#include "functorized.h"

int main()
{
  // count operations with n ranging from 16 to 16*1024*1024 while n doubles in each iteration
  count_operations(16, 16 * 1024 * 1024, sort_functor());
}
