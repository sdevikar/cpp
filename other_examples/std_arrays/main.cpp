#include <iostream>
#include <vector>
#include <array>
#include "printer.h"

using namespace std;


void fillme(uint8_t *carray, int index)
{
  for (int i = 0; i < 5; i++)
  {
    char c = (65 + index);
    carray[i] = c; // this will go like A, B, C, D, E
  }
}

void fillme(std::array<uint8_t, 5> &stdarray, int index)
{
    stdarray.fill(65+index);
}

void fillme(vector<uint8_t> vec, int index)
{
  for (int i = 0; i < vec.size(); ++i)
  {
    vec[i] = 65 + index;
  }
}

int main(void)
{

  vector<uint8_t *> doomed_vector;
  vector<std::array<uint8_t, 5>> winner_vector;
  vector<vector<uint8_t>> real_winner_vector;

  printer *prtr = new printer();

  int counter = 10;

  uint8_t carray[5];
  std::array<uint8_t, 5> stdarray;

  for (int i = 0; i < counter; i++)
  {
    fillme(carray, i);
    // cout << "before pushing to vector, this carray is:" << endl;

    // for(int i = 0; i < 5; i++)
    // {
    //   cout<<carray[i] << " ,";
    // }

    // cout << endl;

    doomed_vector.push_back(carray);
  }

  for (int i = 0; i < counter; i++)
  {
    fillme(stdarray, i);

    cout << "before pushing to vector, this stdarray is:" << endl;

    for(int i = 0; i < 5; i++)
    {
      cout << stdarray[i] << " ,";
    }

    cout << endl;
    winner_vector.push_back(stdarray);
  }

  // for (int i = 0; i < counter; i++)
  // {
  //   vector<uint8_t> vec;
  //   fillme(vec, i);
  //   real_winner_vector.push_back(vec);
  // }

  cout << "doomed vector has size:" << doomed_vector.size() << endl;
  // cout << "winner vector has size:" << winner_vector.size() << endl;

  cout << "Retrieving from doomed vector:" << endl;
  prtr->print_vector(doomed_vector, 5);

  cout << "Retrieving from winner vector:" << endl;
  prtr->print_vector(winner_vector);

  // cout << "Retrieving from real winner vector:" << endl;
  // prtr->print_vector(real_winner_vector);

  return 0;
}
