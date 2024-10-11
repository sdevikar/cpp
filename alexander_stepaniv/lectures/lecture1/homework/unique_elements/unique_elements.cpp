#include <iostream>
#include <algorithm>

int a[]{1,1,2,3, 4};


// This is my implementation based on the algorithm below:
// The algorithm works as follows:
// a. Initialize 'i' to the first element and 'j' to the second element of the range.
// b. Compare the elements pointed to by 'i' and 'j':

// If they are different, increment 'i' and copy the element at 'j' to the new position of 'i'.
// If they are the same, just move 'j' forward.
// c. Repeat step b until 'j' reaches the end of the range.

template <class ForwardIterator>
ForwardIterator my_unique(ForwardIterator first, ForwardIterator last)
{
    if(first == last){
        return last;
    }

    ForwardIterator result = first;

    while(++first != last){
        if(*result != *first){
            result++;
            *result=*first;
        }
    }
    return ++result;
}

// this is the standard library implementation
// template<class ForwardIt>
// ForwardIt my_unique2(ForwardIt first, ForwardIt last)
// {
//     if (first == last)
//         return last;
 
//     ForwardIt result = first;
//     while (++first != last)
//         if (!(*result == *first) && ++result != first)
//             *result = std::move(*first);
 
//     return ++result;
// }


int main(void){
    // int a[]{1,5,1,4,6,2,1,3,1,4}; 

    // std::unique removes duplicates from the sorted array and returns iterator to the end of the sorted array
    auto b = my_unique(a, a+5);
    // std::sort(a, a+10); //this will result in {1,1,1,1,2,3,4,4,5,6}
    // int n = std::unique(a, a+10) - a; // this removes consecutive duplicates and returns the iterator.end() for the container
    // std::cout << "Number of unique elements: " << n << std::endl;
    // int* begin = a;
    // int* end = &a[10]; // yes, I know out of bound access
    // std::cout << "Expected: 10, Actual:" <<  end - begin << std::endl;
    return 0;
}