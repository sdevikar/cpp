#include <stdio.h>

/*
Let's define a function whose pointer we'll use later
*/
void greet1(char *name){
  printf("Hello, %s\n", name);
}

void greet2(char *name){
  printf("How are you today? %s\n", name);
}

int main(void){
  //declare a function pointer that will hold the pointer to the above two function pointers
  void (*mygreetfunctionptr)(char *);

  printf("***Case1: Without typedef***\n");
  mygreetfunctionptr = &greet1;
  mygreetfunctionptr("Swapnil");
  mygreetfunctionptr = &greet2;
  mygreetfunctionptr("Swapnil");

  printf("***Case2: With typedef***\n");
  //We can also use typedef to make things simpler
  typedef void (*Greetfunction)(char *);

  Greetfunction greetfunc;
  greetfunc = &greet1;
  greetfunc("Swapnil");

  printf("***Case3: Without &***\n");
  greetfunc = greet1;
  greetfunc("Swapnil");

  printf("***Case4: Using arrays and without &***\n");
  //More advanced usage of function pointers:
  // By the virtue of typedefs, we can use function pointers in more efficient ways.
  Greetfunction GreetfunctionArray[] = {greet1, greet2};
  int i = 0;
  for(; i < 2; i++){
    GreetfunctionArray[i]("Swapnil");
  }


  return 0;

}
