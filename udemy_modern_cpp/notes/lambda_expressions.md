# Lambda Expressions

## Background

In C, it's common to use function pointers to achieve sort of a customizable behavior for a function. e.g. we can write a sort function that can sort integers as well as strings, as long as we pass it a function that's able to provide implementation for the `<` operator for a given datatype.

There are a couple of problems with this approach:
- compiler cannot optimize the code with function pointer regardless of the optimization level because the function pointer is simply a pointer to a memory location, so it cannot be inlined.
- a function pointed to by a function pointer cannot have a state, so it can't make use of stored data, etc.
- even though function pointer approach sounds generic, it really isn't. We can only templatize the function calling the function pointer so much and at some point, we'll have to start providing custom comparators. e.g. maybe we can provide comparators as args for strings with specialized template, but what about the user defined objects? We'll have to start writing comparators for every type in global scope.

## Lambda expression concept

C++11 introduced lambda expressions as a replacement for function objects (functors). Lambda expressions are nameless function objects with the following syntax. Lambda expressions behave just like functions. i.e. they accept arguments and return a value.

```cpp
// lambda expression syntax
[](<args>) <mutable> <exception specification> -> <return type>
{

}
```

In the above syntax:

- [] is lambda introducer. i.e. it marks the start of lambda expression and contains something called as "capture clause"
- `<args>` optional args
- `<mutable>`
- `<exception specifications>`
- `<return type>` at the end it called the trailing return type
