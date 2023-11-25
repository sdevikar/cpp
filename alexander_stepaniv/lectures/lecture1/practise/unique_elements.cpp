#include <iostream>
#include <algorithm>

int main(void){
    int a[]{1,5,1,4,6,2,1,3,1,4};
    std::sort(a, a+10); //this will result in {1,1,1,1,2,3,4,4,5,6}
    int n = std::unique(a, a+10) - a; // this removes consecutive duplicates and returns the iterator.end() for the container
    std::cout << "Number of unique elements: " << n << std::endl;
    int* begin = a;
    int* end = &a[10]; // yes, I know out of bound access
    std::cout << "Expected: 10, Actual:" <<  end - begin << std::endl;
}