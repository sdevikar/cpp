#include <iostream>   //std::cout
#include <vector>     // std::vector
#include <functional> // std::plus

#include "binary_counter.h"

using namespace std;

int main(void)
{
    std::cout << "Hello Binary Counter" << std::endl;
    std::vector<double> values = {11, 10, 19, 13, 18, 4, 15};
    std::vector<double> counter = {0, 0, 0};
    double zero = 0;

    for (int i = 0; i < values.size(); ++i)
    {
        double carry = add_to_counter(counter.begin(), counter.end(), std::less<double>(), zero, values[i]);
        std::cout << "carry is: \t" << carry << std::endl;
    }

    for (int i = 0; i < counter.size(); ++i)
    {
        std::cout << counter[i] << ", ";
    }

    std::cout << std::endl;

    // double reduced_counter = reduce_counter(counter.begin(), counter.end(), std::plus<double>(), zero);
    // std::cout << "reduce counter result is: \t" << reduced_counter << std::endl;

    return 0;
}