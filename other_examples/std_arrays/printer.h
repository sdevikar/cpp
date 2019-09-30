#include <iostream>
#include <vector>
#include <array>

using namespace std;

class printer
{
public:
    void print_vector(vector<uint8_t *> vec, int data_size);
    void print_vector(vector<std::array<uint8_t, 5>> vec);
    void print_vector(vector<vector<uint8_t>> vec);
};

void printer::print_vector(vector<uint8_t *> vec, int data_size)
{
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        uint8_t *data = *it;

        for (int index = 0; index < data_size; index++)
        {
            cout << data[index] << ", ";
        }
        cout << endl;
    }
}

void printer::print_vector(vector<std::array<uint8_t, 5>> vec)
{
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        std::array<uint8_t, 5> data = *it;

        for (auto it2 = data.begin(); it2 != data.end(); ++it2)
        {
            cout << *it2 << ", ";
        }
        cout << endl;
    }
}

void printer::print_vector(vector<vector<uint8_t>> vec)
{
    for (auto it = vec.begin(); it != vec.end(); ++it)
    {
        vector<uint8_t> data = *it;

        for (auto it2 = data.begin(); it2 != data.end(); ++it2)
        {
            cout << *it2 << ", ";
        }
        cout << endl;
    }
}
