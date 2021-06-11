# Recap of C

## Structures
Can be defined in two ways. With or without typedef.

- Without _typedef_

```cpp
struct _Complex{
  int real;
  int imaginary;
} Complex; // Complex is just an alias for _Complex

// using the structure
struct Complex comp = {2, 3};
```

- With _typedef_

```cpp
typedef struct _Complex{
  int real;
  int imaginary;
} Complex;

// using the structure
Complex comp = {2, 3};
```

## Function pointers
- Syntax for declaration of function pointers: <return_type> (\*<function_pointer_name\>)(_arguments_)
For example:

```cpp
void (* myfunctionptrname)(int, int);
```
- It is worth noting that, the myfunctionptrname above is simply a name that we declared. We will assign a value to this function pointer and then pass arguments to it
- the above also means that we can simply add a typedef keyword at the beginning of this declaration and use that typedef for declaring an actual function pointer name later. e.g.
```cpp
void (* MyFunctionptrType)(int, int);
MyFunctionptrType myfptr;
myfptr = &SomeFunction();
```
