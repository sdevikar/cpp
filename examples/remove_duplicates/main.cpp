#include <iostream>
#include <algorithm>

using namespace std;

int main(void){
  cout << "Hello World!" << endl;

  int a[] = {1,2,1,5,4,1};
  int len = sizeof(a)/sizeof(*a);
  std::sort(a, a+len);
  std::cout << std::unique(a, a+len) - a << std::endl;
}
