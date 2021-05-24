#ifndef _FUNCTOR_H_
#define _FUNCTOR_H_

#include <iostream>

class MyFunctor
{
    // there are three types of things that you could do with the () operator

public:
    //1a. default constructor
    MyFunctor()
    {
        std::cout << "Default Constructor called" << std::endl;
    }

    //1b. default constructor
    MyFunctor(int x)
    {
        std::cout << "Constructor called with arg " << x << std::endl;
    }

    //2a. functor using operator () overload
    void operator()(){
        std::cout << "Functor called with no arguments" << std::endl;
    }

    //2b. functor using operator() overload with an argument
    std::string operator()(char x){
        std::cout << "Functor called with an arguments" << std::endl;
        return std::string(1, x);
    }
    //3. type conversion function
    // operator std::string(char x) const { return std::string(x);}
};

#endif //_FUNCTOR_H_