#include <iostream>

#define ERROR_CASE_ENABLED  (0)

using namespace std;

void c_style_swap(int *x, int *y);
void cpp_style_swap(int &x, int &y);
int pass_by_const_ref_bad(const int &x);
int pass_by_const_ref_good(const int &x);



int main(void){
  int a = 10;
  int b = 15;

  cout << "Before swap: " << endl;
  cout << "a =" << a << " b =" << b << endl;

  c_style_swap(&a, &b);

  cout << "After C style swap: " << endl;
  cout << "a =" << a << " b =" << b << endl;

  cout << "Swap again, C++ style: " << endl;
  cpp_style_swap(a,b);
  cout << "a =" << a << " b =" << b << endl;

  cout << "This shall result in a error: " << endl;
  a = pass_by_const_ref_bad(a);
  cout << "a= " << a << endl;

  cout << "This should be OK: " << endl;
  a = pass_by_const_ref_good(a);
  cout << "a= " << a << endl;



return 0;
}

void c_style_swap(int *x, int *y){
  int temp;
  temp = *x;
  *x = *y;
  *y = temp;
};

void cpp_style_swap(int &x, int &y){
  int temp;
  temp = x;
  x = y;
  y = temp;
}

int pass_by_const_ref_bad(const int &x){
  int retval = 0;
#if ERROR_CASE_ENABLED
  // we cannot mutate x here because this function refers to input as a constant
  retval = ++x;
#endif

return retval;
}

int pass_by_const_ref_good(const int &x){
  // this is the correct way to achieve the above
  return x+1;
}
