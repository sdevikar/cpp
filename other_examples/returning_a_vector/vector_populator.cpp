#include "vector_populator.h"

bool VectorPopulator::populateByRef(vector<MyDataStructure_t> &input)
{
  bool retval = false;
  int mysize = 10;

  for(int i = 0; i < mysize; i++)
  {
    MyDataStructure_t temp;
    temp.x = i;
    temp.y = i;
    temp.z = i;
    input.push_back(temp);
  }

  if(input.size() == mysize)
    retval = true;

  return retval;
}

bool VectorPopulator::populateByVal(vector<MyDataStructure_t> input)
{
  bool retval = false;
  int mysize = 10;

  for(int i = 0; i < mysize; i++)
  {
    MyDataStructure_t temp;
    temp.x = i;
    temp.y = i;
    temp.z = i;
    input.push_back(temp);
  }

  if(input.size() == mysize)
    retval = true;

  return retval;
}
