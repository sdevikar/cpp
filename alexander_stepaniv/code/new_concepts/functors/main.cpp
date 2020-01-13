#include "functor.h"
#include <iostream>

int main(void)
{
    std::cout << "Hello functor!" << std::endl;

    // this should call the constructor
    MyFunctor functor;

    // functor called with no arguments
    // notice that we're invoking () operator on  the instance
    functor();

    // call same functor with an argument
    // this is possible because C++ allows for multiple arguments to () operator overload
    // unlike, for example = operator that only allows for 2 arguments
    std::string result = functor('x');
    std::cout << "output: " << result << std::endl;


    // note that calling () operator on an already constructed object
    // this way, we can use the object that already has an internal state
    MyFunctor functor2(4);
}