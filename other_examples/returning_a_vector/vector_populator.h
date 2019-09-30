#ifndef _VECTOR_POPULATOR_H_
#define _VECTOR_POPULATOR_H_

#include <vector>

using namespace std;

typedef struct _MyDataStructure_t {
  int x;
  int y;
  int z;
} MyDataStructure_t;


class VectorPopulator{
public:
  bool populateByRef(vector<MyDataStructure_t> &input);
  bool populateByVal(vector<MyDataStructure_t> input);
};

#endif
