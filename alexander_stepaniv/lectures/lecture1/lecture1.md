# Lecture 1

## Introduction lecture Part 1

- [Lecture 1](#lecture-1)
  - [Introduction lecture Part 1](#introduction-lecture-part-1)
  - [Introduction lecture Part 2](#introduction-lecture-part-2)
  - [Lecture 1 class assignment](#lecture-1-class-assignment)

## Introduction lecture Part 2

- When we write some code, it is essential to determine how efficient it is. There is no need to ALWAYS go into big O analysis. Instead, there are some things we can do to benchmark the code performance, WITHOUT modifying the original code at all.
- When STL library was written, the goal was to make the STL libraries work for all built-in datatypes, but also pointers and datatypes that are "like" built-in datatypes. To make non built-in types to behave like built-in types, some containers were written (as wrappers?). e.g. a vector of strings will accept a string as a template parameter and provide another type, that's a vector of strings. These containers were to support the operations that a regular datatype supports. And thus different algorithms (like sorting) can directly run on these datatypes.

- **Semiregular types:** These are the datatypes that provide only constructor, destructor and assignment (this means we need to provide copy consrtuctor and assignment operator implementations).
- **Regular types:** (a.k.a Totally ordered types): Like Semiregular, but also supports equality and maybe non-equality too (i.e. == and !=)
  - As per Alexander Stepinov, "regular" datatypes should also support <, <=, >, and >=
- So, what kind of operations do we really need to count? The answer is - whatever operations a regular datatype may reasonably support. Regular datatype being, a datatype that is expected to behave like a built-in datatype, like `int` for example. For instance, when you construct a vector of `int`s, the vector itself can be expected to support reasonable operations that `int` may support. So, these operations are:
  - copy: For example, copy constructor, stuff like vector a = b
  - assign: For example, we have T a, and T b, and we do a = b (i.e. assigning one already constructed object to other)
  - default: Default constructor for example, T a;
  - destruct: as the name says, destructor
  - equal: For example, a == b. Note that the measure of equality is different for different types.
  - compare

## Lecture 1 class assignment

- The goal here is to write some code that counts number of different types of operations above by doing something like:

```cpp
  count_operations(16, 16 * 1024 * 1024, sort_functor());
```

- Sort functor above is basically a wrapper around a regular C++ standard sort function. See functorized.h for this. `std::sort` takes the beginning and the end of the iterator as arguments. So, the implementation of count_operations constructs a random vector and passes iterator beginning and end of that vector to sort_functor
- sort_functor is taken as a "pointer to a function" type argument by count_operations
- The idea is that, std::sort calls different operations on the iterator that is passed to it. We are simply providing
