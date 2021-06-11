#include "stdio.h"

struct _Complex2{
  int real;
  int imaginary;
}complex;

typedef struct _Employee{
  int id;
  char *name;
}Employee;

int main(){
  printf("Hello world!\n");
  printf("Size of structure = %d \n",sizeof(struct _Complex2));
  printf("Size of structure = %d \n",sizeof(complex));

  // since we defined Complex structure without a typedef,
  // we need to qualify it with a struct keyword
  struct _Complex2 mycomplex;
  mycomplex.real = 5;
  mycomplex.imaginary = 10;

  printf("real = %d\t, imaginary = %d\n",mycomplex.real, mycomplex.imaginary);

  // Whereas, we can use Employee structure as if it was a datatype
  Employee myEmployee;
  myEmployee.id = 1;
  myEmployee.name = "Swapnil";
  printf("id = %d\t, name = %s\n",myEmployee.id, myEmployee.name);
}
