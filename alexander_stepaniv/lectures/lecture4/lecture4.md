# Lecture 4 part 1

- [Lecture 4 part 1](#lecture-4-part-1)
  - [The swap program](#the-swap-program)
  - [the min function](#the-min-function)
- [Lecture 4 part 2](#lecture-4-part-2)
  - [Optimizing the min program](#optimizing-the-min-program)
  - [More on the equality](#more-on-the-equality)

- What is a component?
  - A piece of software that lets you do something in a general way
  - It has to be functional (i.e. ripping some lines of code out from a program and running them won't qualify those lines as components)
  - It has to be efficient (as efficient as the logic inside the component was executed without the wrapper)
- Is C++ the right language for component programming?
  - There are two factors to consider
    - Generality: You need to be able to write as generic of a program as you want
    - Efficiency: The program needs to be efficient
  - We will determine if these two criteria are met based on three programs:
    - swap, min and linear search

## The swap program

- here's the basic code

```cpp
// it has to be generic, so lets' templatize the function
template <typename T>

// it has to be efficient, so make it inline
// it will return nothing -- if if had to, we won't be sure what to return (a or b)
inline void swap(T&a, T&b){
  // tmp needs to hold a value here, so it is not a reference, unlike the arguments
  // T tmp = a; // this is identical to T tmp(a) or tmp{a} in C++11 i.e. assignment operator here is implicitly copy constructor
  T tmp(a)
  a = b;
  b = tmp;
}
```

- Are there any requirements that type T needs to satisfy?

  - looking at the code, we know that
    - T has to have a working copy constructor (because we did T tmp = a)
    - T also has to have a working assignment operator
    - In short, T needs to be Semiregular in this case.

- Post-mortem of this code:

  - Let's say we were using this function to swap containers (e.g. vectors for 1 million elements)
  - This code is super inefficient because:
    - we are constructing a tmp vector of a million elements, then we're copying two vectors of size 1 million twice
  - So, this solution is very bad for contailers
  - In case of vectors, there is a pointer to the header, there is a pointer to the position until which the vector is filled and there is a pointer to the end of the vector. So, for swapping, it's sufficient to just change the header pointer
  - More generally, for any container, we should be good with just a couple of things:
    - swap headers of a and b
    - fix back pointers (i.e. if the next element points to the previous element, we will have to deal with that)
  - Solution: write a specialized template function with specialized signature

- More efficient code: we can use xor algorithm to swap two objects. Although the xor algorithm only works when the two objects are not identical. So, in this case, it makes sense to actually check whether the arguments are identical

```cpp
template <typename T>
inline // good idea to put inline on a separate line for search convenience (i.e. search void swap instead of inline void swap)
void swap(std::vector<T> &a, std::vector<T> &b){
  // swap headers of a and b
  // fix back pointers (if they exist)
  // (we will do this later)
}
```

## the min function

```cpp
template <typename T>
// T is totally ordered (i.e. < operator is defined for T)
inline
const T& min(const T&a, const T&b){
  if(a < b) return a;
  else return b;
}
```

- Notice the use of const reference here.
  - We need args as const reference because we need the function to work for c++ literals (like swap(3,5)) (in C++ literals are converted implicitly to const integers)
  - the return type is also const reference instead of a value to avoid copying at a calling place

# Lecture 4 part 2

## Optimizing the min program

The min program discussed above works but there are subtle issues with it

- There is a usability problem with returning a constant reference in min. Let's say we wanted to do something like this:

  ```cpp
  int a = 3;
  int b = 5;
  int x = min(a,b)
  ```

  Here we are passing a and b as references (not constant references), that will be converted to constant reference arguments and used by the function to do its job. Then a constant reference to a is returned. So, at the calling location, x is now a constant reference. And you can't do anything to mutate it.

  - There is a usability problem with returning the second argument when two arguments are equal. Let's discuss that later, but for now, change the code to below

  ```cpp
  template <typename T>
  // requires T is totally ordered (i.e. < operator is defined for T)
  inline
  const T& min(const T&a, const T&b){
    if(b < a) return b; // i.e. b is returned ONLY when it is less than a. Otherwise, the first argument is returned
    else return a;
  }
  ```

- Let's revisit some concepts

  - Transitivity: This says is a < b & b < c then a must be less than c
  - Trichotamy: If a and b are two totally ordered objects of the same type, then one of the following is definitely true:
    - a < b
    - b < a
    - a == b
  - Weakly ordered: Trichotamy can hold a different meaning for complex datastructures. For example, if we have structures with first name and last name to sort, we may choose to sort them by last name let's say. What we did was determine what's less than the other type based on one individual element. But that doesn't mean that the entire structure is less than the other and so on. i.e. two people with same first and last name are not equal. But we will consider them as **equivalent**s. So, for the weakly ordered objects (like structures), the following is true:
    - a < b
    - b < a
    - a and b are equivalent but not equal

- So with this equivalence in mind, let's fix the min function to work for the weakly ordered types as well. In this case, we will need to know how to compare these types

```cpp
  template <typename T, typename Compare>
  // requires Compare defines a StrictWeakOrdering on T
  inline
  const T& min(const T&a, const T&b, Compare cmp){
    if(cmp(b,a)) return b; // i.e. b is returned ONLY when it is less than a. Otherwise, the first argument is returned
    else return a;
  }
```

## More on the equality

- programmers make reasolable assumptions on how equality should work. i.e. if we write something like this

```cpp
std::cout << a == a ? "yes" : "no" << std::endl
```

We expect the output of the program to be "yes".

- However, as we will find out, for invalid floating point numbers, equality doesn't hold true. So, for example, if we did this:

```cpp
double a(0.0/0.0);
std::cout << a == a ? "yes" : "no" << std::endl
```

the output here will be "no".

We have two ways to go about this. One, we break the laws around the logic. (i.e. accept that this is an exception) or two, we can make sure that these exceptional situations are taken care of (by adding special cases?)
