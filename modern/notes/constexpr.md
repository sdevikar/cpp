# constexpr keyword

constexpr:

- stands for constant expression and it represents an expression that is constant
- applicable to variables and functions.
- may increase performance by causing the expression to be evaluated at compile time
- very similar to `const` keyword for expressions in the sense that some const literals are also evaluated at the same time. e.g. there's no difference between `const int x = 10;` and `constexpr int x = 10`. However, note that the keyword const actually has a different meaning for functions. A const function makes the function so that it cannot modify the state of the object.

constexpr function:

- A function that is marked constexpr can therefore only return const and can operate on a limited set of datatypes like void, scalars (like premitive datatypes), references, etc.
- In c++11 this function can only have one line and that line should be a return statement. In c++14, you can also have conditional statements
- Are implicitly inlined, therefore should be in headers

Here are a couple of examples for clarification:

```cpp

// since constexpr is evaluated at compile time,
// it's possible to use it for initialization of array size, for example.
constexpr int i = 10;
int arr[i];

// And the above is *no* different than the following for this specific case:
const int i = 10;
int arr[i];

// this is a runtime add function
// it is evaluated at runtime
int runtimeAdd(int x, int y){
    return x+y;
}

// this is a compile time add function
// it can be evaluated at compile time
// because the args and return value are scalars
// and can be evaluated at compile time
constexpr int compiletimeAdd(int x, int y){
    return x+y;
}

// this is illegal, since runtimeAdd can't be evaluated at compile time
constexpr int j = runtimeAdd(5,6); // ERROR!
constexpr int j = compiletimeAdd(5,6); // This is OK
const int j = compiletimeAdd(5,6); // This is also OK

// constexpr function can be used at compile and runtime both.
// i.e. the following expression is valid
int k = compiletimeAdd(5,10);

// the following won't work because k is not a literal
// and isn't evaluated at compile time
compiletimeAdd(k,9);
```

## const and constexpr differences

- const initialization can be deferred until runtime (think initializer lists for example). But for constexpr, the evaluation must happen at compile time
- In that sense, const is a subset of constexpr. i.e. all constexpr variables are const but not the other way round
- We should use const to indicate immutability
- We should use constexpr to indicate evaluation at compile time
