#include "complex.h"
#include "compare.h"
#include <iostream>
#include <algorithm>
#include <vector>

int main(void)
{
    Complex c1(5,12); // magnitude 13
    Complex c2(3,4); // magnitude 5
    Complex c3(11,60); // magnitude 61


    std::vector<Complex> v{c1,c2,c3};

    std::cout << "Before: " << std::endl;

    for(Complex c:v)
    {
        std::cout<< "magnitude: " << magnitude(c) << std::endl;
    }

    // this will fail because compiler doesn't know how to compare Complex objects
    // std::sort(v.begin(), v.end());

    std::sort(v.begin(), v.end(), Compare<Complex>());

    std::cout << "After: " << std::endl;
    for(Complex c:v)
    {
        std::cout<< "magnitude: " << magnitude(c) << std::endl;
    }


    return 0;

}

// // sort algorithm example
// #include <iostream>     // std::cout
// #include <algorithm>    // std::sort
// #include <vector>       // std::vector
// #include "compare.h"


// bool myfunction (int i,int j) { return (i<j); }

// int main () {
//   int myints[] = {32,71,12,45,26,80,53,33};
//   std::vector<int> myvector (myints, myints+8);               // 32 71 12 45 26 80 53 33

//   // using default comparison (operator <):
//   std::sort (myvector.begin(), myvector.begin()+4);           //(12 32 45 71)26 80 53 33

//   // using function as comp
//   std::sort (myvector.begin()+4, myvector.end(), myfunction); // 12 32 45 71(26 33 53 80)

//   // using object as comp
//   std::sort (myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

//   // print out content:
//   std::cout << "myvector contains:";
//   for (std::vector<int>::iterator it=myvector.begin(); it!=myvector.end(); ++it)
//     std::cout << ' ' << *it;
//   std::cout << '\n';

//   return 0;
// }