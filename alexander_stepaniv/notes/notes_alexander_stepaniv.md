# Efficient Programming in C++

These notes are written with reference to video lectures here:
[YouTube](https://www.youtube.com/watch?v=aIHAEYyoTUc&list=PLHxtyCq_WDLXryyw91lahwdtpZsmo4BGD)

## Introduction lecture Part 1

- Always use the simplest data structure possible. In C++, **USE VECTORS!** if you can. If you can't use vectors, figure out a way to **USE VECTORS**
- An example discussed in the class discusses why using a combination of `std::sort` and `std::unique` for finding number of unique elements in an array is better than using a `set`. (The reason is that set is designed to efficiently handle the constant growing and shrinking i.e. insertions and removals. And if you have a big list of elements, constructing a set itself will take a lot of time and we will never be able to reap the benefits of using a set, because we're not really going to insert and remove from the set multiple times)

## Introduction lecture Part 2

- When we write some code, it is essential to determine how efficient it is. There is no need to ALWAYS go into big O analysis. Instead, there are some things we can do to benchmark the code performance, WITHOUT modifying the original code at all.
- When STL library was written, the goal was to make the STL libraries work for all built-in datatypes, but also pointers and datatypes that are "like" built-in datatypes. To make non built-in types to behave like built-in types, some containers were written (as wrappers?). e.g. a vector of strings will accept a string as a template parameter and provide another type, that's a vector of strings. These containers were to support the operations that a regular datatype supports. And thus different algorithms (like sorting) can directly run on these datatypes.

- **Semiregular types:** These are the datatypes that provide only constructor, destructor and assignment.
- **Regular types:** (a.k.a Totally ordered types): Like Semiregular, but also supports equality and maybe non-equality too (i.e. == and !=)
- So, what kind of operations do we really need to count? The answer is - whatever operations a regular datatype may reasonably support. Regular datatype being, a datatype that is expected to behave like a built-in datatype, like `int` for example. For instance, when you construct a vector of `int`s, the vector itself can be expected to support reasonable operations that `int` may support. So, these operations are:
  - copy: For example, copy constructor, stuff like vector a = b
  - assign: For example, we have T a, and T b, and we do a = b (i.e. assigning one already constructed object to other)
  - default: Default constructor for example, T a;
  - destruct: as the name says, destructor
  - equal: For example, a == b. Note that the measure of equality is different for different types.
  - compare

### Lecture 1 class assignment

- The goal here is to write some code that counts number of different types of operations above by doing something like:

```cpp
  count_operations(16, 16 * 1024 * 1024, sort_functor());
```

- Sort functor above is basically a wrapper around a regular C++ standard sort function. See functorized.h for this. `std::sort` takes the beginning and the end of the iterator as arguments. So, the implementation of count_operations constructs a random vector and passes iterator beginning and end of that vector to sort_functor
- sort_functor is taken as a "pointer to a function" type argument by count_operations
- The idea is that, std::sort calls different operations on the iterator that is passed to it. We are simply providing

## Lecture 2

Intro lecture ended on a note that the goal for the entire class is to write identical code for the same problem. Subtle conventions are necessary to achieve this. For example, when to capitalize something, when to use what alternative, even though the two alternatives are synonyms etc. Following are the examples discussed at the beginning of lecture:

- when we use template and do something like `template<typename T>` or `template<class T>`, although the two declarations mean the same, one is indicative that the template parameter is an actual class, vs probably a primitive datatype. Also, pay attention to capitalized T. Capitalization is convention here.
- Use of struct vs class: We know that the difference between two in cpp is just the default scope of class members. i.e. in struct, class members are public by default. But there is a deeper reason behind when to use what.
- Public vs Private: Discussed that the common understanding that class properties should ALWAYS be private is BS. Private is only requires when "invariance" is important. Meaning that, you actively want to prevent someone or something from writing anything to that class property.
- Writing a complete class:

  - To make things as simple as possible, we will write a class called Singleton class.
  - Singleton class is not the same as singleton design pattern. It is a class that only has one thing. Let's call that thing as some value. This value can be any datatype like int, float, double, a pointer. So, we will make it a template class
  - Our goal is to take a type T and make it into another type. Which, in this case, will be a singleton wrapped around T.

### Semiregular methods of singleton classs

- Remember the definition of a **semiregular**. It needs to have a constructor, destructor and should be copyable/assignable. As such, it will need the following:
  - a default constructor
  - a destructor
  - a copy constructor
  - assignment operator
- By making the class semiregular, we want it to behave as a normal person would expect it to behave. e.g.

`T a(b);` should have the same effect as `T a = b;` in terms of the result and hopefully the performance too. Note that in the first case, a copy constructor is invoked and in the second case a default constructor followed by an assignment operator is invoked.

- **copy constructor:**
  Compiler implicitly synthesizes copy constructor for you. i.e. compiler will automatically write something like this for you:

```cpp
singleton(const singleton& x): value(x.value) { // do nothing here}
```

Remember the NPTEL discussion where it was discussed that compiler will copy a class reference passed as an argument to the copy constructor byte by byte. This is the same thing. Because singleton has only one member value, this member will be copied implicitly, in case copy constructor is not overridden by the programmer.
There is of course a caveat here. That is, in our case, singleton is a templated class and the template parameter could be a pointer too. So, in an implicitly defined (aka compiler provided) copy constructor, a pointer will be copied instead and the pointer being a member of some other class could be invalid at any time.

- **Default constructor:**
  For singleton class this will just be an empty function like this:

```cpp
singleton(){// do nothing}
```

We could have done something like:

```cpp
singleton() : value()
{

}
```

i.e. initialize value with an empty of a default value (e.g. int value to 0) by doing value().
But we don't want to do this because compiler will do it for you anyway.

- However, firm advice with respect to default constructor is that, you should only rely on default constructor to create something for you. But you should not rely on default constructor to initialize the members etc. to their default values. If you want members to be at their default values, then construct the class and then assign the values. This will also take care of the invalid pointer corner case that was discussed above.
- It is also very unsafe to rely on the presence of default constructor even though compiler synthesizes for you. But the moment you declare another signature for a constructor, compiler will not synthesize a default constructor for you.
- Some classes will not need any other constructors other than copy and default constructors -- these are the classes with no members (e.g. std::plus)
  - In order to understand this, let's inspect what other types of constructors there are:
    - Revisit this later
- What other constructors do I need for singleton other than copy and default?? Think about it

  - Revisit this also

- **Destructor:**
  This is as simple as:

```cpp
~singleton(){}
```

- Even though there is a templated class member T (which could be an object or even a pointer of any kind) in singleton class, we don't need to explicitly clean it up, because compiler does it for you.
- Also, if we didn't explicitly define the destructor, compiler will synthesize one for you.

- **Assignment operator**:
  Here we're talking about = operator, which will allow us to do somethig like this:

```cpp
singleton<T> a;
singleton<T> b;
singleton<T> c;

a = b = c;
```

As we know, a=b essentially translates to `a.operator=(b)`, meaning that user is calling operator= function on a with b as argument.
In case of singleton class, who has only one member called T value, the only logic that needs to be implemented is the copying of b.value to a.value. However, to support the chain assignment, the = operation should also return the result of operation, which is the assigned value itself. So, the operator= implementation would look like this:

```cpp
singleton& operator=(singleton x)
{
  value = x.value;
  return *this;
}
```

We return \*this here as a reference to the instance of this class. this means, in case of a=b=c, when b=c is done, a reference of a is assigned with b.

### Regular methods of singleton class

- To make singleton a regular class, we need to add the following methods:

1. Equality

- Here we want to implement == operator. == operator takes two arguments and returns true if they're "equal". The meaning of equal can get complicated when we're talking about complex datastructures.
- Also realize that in case of == operator, we're not really calling a member function on a class. Instead, what we're doing is, invoking a function in a global scope that takes two arguments and returns the equality status.
- This function however needs to have access to class's private data members. Therefore, it should be declared as a friend function within singleton class
- Where should this function be defined?

  - Being in global scope, it can be defined globally, but that complicates the syntax
  - Instead, you should define this function in the class itself

- So, here's what the function will look like:

```cpp
friend
bool operator==(const singleton& x, const singleton& y){
  return (x.value == y.value);
}
```

2.Inequality: Same as above. However, there are two ways to do it:

```cpp
// option1: Bad option because it's independent of equality and potentially will require more code to be changed in case code change is required
friend
bool operator!=(const singleton& x, const singleton& y){
  return (x.value != y.value);
}

// option2: This will always work as long as == is working
friend
bool operator!=(const singleton& x, const singleton& y){
  return !(x == y); // this is invoking == operator in turn
}
```

#### Some interesting discussion about Templated classes

- We know that compiler synthesizes a few things for user, if the user doesn't define them explicitly. e.g. copy constructor, default constructor etc.
- We also know that not all template types T can be "regular" classes. i.e. they probably don't support equality.
- In such a case, if the template parameter T does not _NEED_ a particular method, compiler will not synthesize it.
- In other words, if T is semiregular, Singleton<T> is also semiregular
- if T is regular (aka totally ordered), Singleton<T> is also regular
- Also note that compiler doesn't generate things until they're used

### Totally ordered methods of singleton class

- There are 4 methods that need to be defined to make the singleton class totally ordered.
- There are 4 methods because these methods always come in groups because we want to maintain the symmetry. i.e. if you define `<` operator, you should also define `>` operator. And if you define `<=` you should also define `>=`
- We saw that we used == operator as a baseline for !=. Same can be done here. i.e in case of comparison, we will select `<` operator as default operator. This choice is kind of arbitrary, but not really. Because, you can expect users to be wanting to sort a group of numbers etc. in an ascending order more often than in decending order. And in sorting algorithms that will be done by using `<` comparison. i.e. if a < b, put b before a. What we mean to say here is that because Singleton needs to be a "complete" class, an STL algorithm should also be able to sort a bunch of singletons. And thus, we want to, as a starting place, start by providing an implementation for `<` operator.

- So the implementation would looks like this:

```cpp
// this should work for x < y (i.e. arg1=x, arg2=y)
friend
bool operator<(const singleton& x, const singleton& y){
  return x.value < y.value;
}

// this should work for x > y (i.e. arg1=x, arg2=y)
// notice how we're reusing the < implementation
// this is because x > y implies y < x
friend
bool operator>(const singleton& x, const singleton& y){
  return y < x;
}

// this should work for x <= y
// x <=y implies y is NOT less than x
friend
bool operator<=(const singleton& x, const singleton& y){
  return !(y < x);
}

// this should work for x >= y
friend
bool operator>=(const singleton& x, const singleton& y){
  return !(x < y);
}
```

### Conversion methods of Singleton

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
  - This kind of conversion is achieve with a conversion operator, `()`
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

### Templatized class constructor

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
