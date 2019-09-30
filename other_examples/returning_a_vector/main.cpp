#include <iostream>
#include <vector>
#include <functional>
#include "vector_populator.h"

using namespace std;
using namespace std::placeholders;

int main(void)
{
  VectorPopulator vpop;
  vector <MyDataStructure_t> my_ds_list;
  cout << "Initial vector size = " << my_ds_list.size() << endl;

  // this works because populate is accepting the vector as a reference.
  bool result = vpop.populateByRef(my_ds_list);

  cout << "Vector size after populateByRef = " << my_ds_list.size() << "and result = " << result << endl;


  for(int i = 0; i < 10; i++)
  {
    MyDataStructure_t temp = my_ds_list[i];
    cout << temp.x << ", " << temp.y << ", " << temp.z << endl;
  }

  // But this will not work because the populate function here is accepting
  // the vector by value
  // this case is particularly dangerous because, the function populateByVal
  // will made a copy of my_ds_list2 and use that copy to do push_back
  // meanwhile, my_ds_list2 is always empty
  vector <MyDataStructure_t> my_ds_list2;
  cout << "Initial vector size = " << my_ds_list2.size() << endl;
  result = vpop.populateByVal(my_ds_list2);
  cout << "Vector size after populateByVal = " << my_ds_list2.size() << " and result = " << result << endl;

  // the solution to this problem (when you cannot change the predefined function)
  // is to use a reference wrapper

  // TODO - This is not working. Figure out why.
  reference_wrapper<vector<MyDataStructure_t>> vector_ref(my_ds_list2);
  cout << "Initial vector size = " << my_ds_list2.size() << endl;
  result = vpop.populateByVal(vector_ref);
  cout << "Vector size after populateByVal = " << my_ds_list2.size() << " and result = " << result << endl;

}
