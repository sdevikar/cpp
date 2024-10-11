# code notes

In `count_operations.h` we're doing this:

```cpp
    std::vector<instrumented<double> > vec(i);
```

- So, basically, instead of constructing a vector of doubles, we're constructing a vector of `instrumented` datatype which in turn is typed with `T`. i.e. a wrapper class around `T`
- This will allow for implementing the functions and operators in instrumented, while also keeping the count

## Things that need to be implemented

1. Default construction: Constructing something as if it was a built in datatype. e.g. `T a;`
2. Construction from underlying datatype, i.e. construct `instrumented` from `T`
3. Copy operations: There are two variants of this. We can either do something like `T a(b);` or `T a = b;` , where `b` is also of type `T`
4. Assignment: `a = b;` where a and b are both of the same type. Note here that in C++, assignments can be chained like `a=b=c` therefore, when `b=c` happens, `b` must be returned, so it can be assigned to `a`
5. Comparison: `a == b` note here that if a and b are of type `instrumented`, then the comparison like `a.value == b.value` (i.e. the underlying double datatype value comparison), will require access to the private members of `instrumented` class. Therefore, this function must be defined outside the class scope and within the class itself, it should be declared as a friend function.
