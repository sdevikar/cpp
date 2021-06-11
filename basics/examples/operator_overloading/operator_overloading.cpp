#include <iostream>
#include <string>

using namespace std;

string operator+(string string1, string string2);

int main(void){
string firstName = "Swapnil";
string lastName = "Devikar";
string fullName;

fullName = firstName + lastName;

cout << fullName << endl;

}

string operator+(string string1, string string2){
  char* fullname;
  fullname = (char *)malloc(strlen(string1.c_str()) + strlen(string2.c_str()));
  strcpy(fullname,string1.c_str());
  strcat(fullname,string2.c_str());
  return fullname;
}
