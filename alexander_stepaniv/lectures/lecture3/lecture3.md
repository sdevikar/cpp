# Lecture 3

- [Lecture 3](#lecture-3)
  - [Conversion methods of Singleton](#conversion-methods-of-singleton)
    - [singleton class as a template parameter](#singleton-class-as-a-template-parameter)
  - [Templatized class constructor](#templatized-class-constructor)

## Conversion methods of Singleton

- These are the methods that allow conversion from T to Singleton<T> and from Singleton<T> to T.
- Background:
  - If there exists a class that has a constructor with a single parameter, it is possible to convert the parameter to the class and vice versa. Here's an example:

```cpp
// this is the class with single parameter constructor
MyClass
{
  public:
  MyClass(int x)
  {
    _x = x;
  }

  private:
  int _x;
}

// We can instantiate this call using something like this:
MyClass mc = 3;
```

- What's happening above is an "implicit conversion", same as below:

```cpp
double a;
int b;
a = b; // conversion from int to double will happen here.
```

- Why do implicit conversions exist?
  - This is because C++ intended to keep its compatibility with C .
  - C had to support implicit conversions to avoid providing separate definition for different datatypes. e.g. sqrtint, sqrtfloat etc.
  - So, instead the writers of C language introduced implicit conversions that allowed implicit upcasting of dataype to the broadest possible datatype. e.g. A pointer can be upcasted to bool (when we do if (pointer), pointer is implicitly imterpreted to a boolean type). A boolean in turn can be upcasted to int and int can be upcasted to float etc.
- This implicit typecasting works out for C. But for C++ things get more complicated. e.g. in C++, `std::cin << 10;` compiles. Because in C++ when std::cin fails, it will be return a void pointer to NULL, which is 0 and so 0 << 42 becomes a left shift operation
- so, to fix this situation, there are additional set of rules that are introduced in C++. One workaround is to disable a conversion using `explicit` keyword. But then it messed up while, if and other conditionals. So an exception was made to allow implicit conversions only for these conditional cases.

- **Conversion from T to singleton<T>**
- It would need
  - a constructor with a single parameter for sure
  - the parameter will be T (a const reference to it actually)

```cpp
singleton(const T& x): value(x)
{

}

// this will allow for something like:

// implicit
singleton s = x; // where x is of type T

//explicit
singleton s(x);
```

- This looks exactly the same as copy constructor. Except, copy constructor takes as it's input a reference to a singleton class and here the function is accepting a raw T value reference.
- In order to avoid implicit creation of object using T value we should make the constructor explicit.

```cpp
explicit singleton(const T& x): value(x)
{

}
```

- **Conversion from singleton\<T\> to T**

- Background
  - This is the inverse of what we were doing above. Here we have a singleton object made with type T. And we want to in a sense, downcast it to a raw T type.
  - This kind of conversion is achieve with a conversion operator, `T()`
  - Conversion operator is just like any other operator overriding. i.e. it's a function and we define it as: `operator <ReturnValueType>() { // logic of conversion }`
  - Notice that this signature a little different from the regular operator override syntax, where we do something like: `returnType operator operatorSymbol( arguments) { // conversion logic}`
- With the above is background, we'd write a conversion operator for singleton class as below:

```cpp
explicit operator T() const { return value;}
```

Here,

- `T` is the return type
- function is marked as const, because it won't modify the argument to it. The argument to the function in this case is the Singleton class and the return type is the raw value (of type T) that is extracted from singleton class
- explicit keyword is used to avoid and disable implicit conversion

### singleton class as a template parameter

- Imagine the template class being passed as a template parameter to some function
- There is no provision on C++ to find out what the type of T that singleton is wrapping around
- In this case, we might add the statement `typedef T value_type` to singleton class. This will allow users to do something like this:

```cpp

// suppose we have a function
template  <class MyType>
myFunction(MyType x)
{
  // this is why we need ` typedef T value_type` in singleton call
  // here, even though we don't know that singleton is consists of type T
  MyType::valueType var;

  // now you have a var which is of type T in singleton, without knowing that
  // singleton was actually made of type T
}
```

## Templatized class constructor

- It is also possible to templatize class constructor. This is not recommended because of the underlying assumptions we have to make while doing this.
- An example use case would be, for example, when you want to be able to convert a singleton<int> to singleton<float> or vice versa. This is how you would do it:

```cpp
template <classname U>

// copy constructor which allows copying to/from singleton<onetype> from/to singleton<anothertype>
singleton(const singleton<U>& x) : value(x.value)
{}
```

- This will work, except that here, we're making an assumption that there is a conversion available from x.vale to this.value. Obviously, if this was something like this:

```cpp
singleton<int> first;

// then we do this:
singleton<double> second(first);

// and this wil work, because second.value = first.value will work just fine
```

- But in general, we shouldn't allow this kind of template constructors, because one cannot guarantee what kind of template parameter is used for the singleton class that is passed as an argument to copy constructor. i.e. second.value = first.value may not be possible, because the value types are incompatible