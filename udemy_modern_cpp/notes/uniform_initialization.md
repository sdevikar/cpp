## Uniform Initialization

- Uniform initialization works both for scalar and array types. We can use `{}` type initialization for all types.
- In C++98, there were two different ways of initialization depending on whether the data type is premitive. e.g.

```cpp

// Summary

// 1. value initialization => T obj{}
// 2. direct initialization => T obj{v}
// 3. copy initialization => T obj = v

// primitive datatype initializtion

int x; // uninitialized
int y = 10; // copy initialization (avoid it for user defined datatypes and array types)
int z(10); // direct initialization


// array type initialization

char msg1[5]; // uninitialized
char msg2[5] = {'\0'}; // initialized but null terminated
char msg3[5] = {'a', 'b', 'c', 'd' , '\0'}; // cpoy initialization / aggregate initialization
char msg4[5] = {"abcd"}; // copy initialization
```

- Uniform initialization example

```cpp

// primitive datatype

int x{}; // x is initialized to default value of 0
int y{5}; // y is initialized to 5

// array type initilalization on the stack

char d[8]{}; // all elements of array initialized to default value ('\0')
char msg4[5] = {"abcd"}; // same as previous


// array type initilalization on the heap

char* h1 = new[8]{};
char* h2 = new[8]{"Hello"};

```

- Additional advantages of uniform initialization 
    - forces initialization 
    - prevents narrowing conversion e.g. the following will result in an error or a warning depending on the compiler:
    `float x{5.0}; int y{x};`