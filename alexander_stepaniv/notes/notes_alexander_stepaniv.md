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

## Lecture 4 part 1

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

### The swap program

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

### the min function

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

## Lecture 4 part 2

### Optimizing the min program

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

### More on the equality

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

## Lecture 5 part 1

### More on the min function

- In the previous lecture we passed a comparator parameter to the min function.
  However, for totally ordered types, which support `\<` parameter, it's not convenient to always pass comparator.
  It should be the default instead. So, we need to figure out a way to call `min` without the additional comparator parameter. Maybe we can use the specialized template function for this.

- In other words, we want to be able to do

```cpp
// invoke min with a comparator
min<int, std::less<int> >

// invoke min without comparator
min<int>
```

Here, `std::less<T>` is a functor. i.e. a function object for performing comparisons. Unless specialized, invokes operator< on type T.

- So lets write a specialized min function for totally ordered types that support < operator

```cpp
  template <typename T>
  // requires T to be totally ordered
  inline
  const T& min(const T&a, const T&b){
    return min(a,b,std::less<T>());
  }
```

- notice how we reused the original min function here. In general, it's a good idea to not rewrite the same logic. In this particular case, there is no overhead, because functions are inline

### Function call vs Functors

In the quest to make our code as fast as possible, we want to:

- a. avoid function calls
- b. make sure that the code gets inlined

Note the original (unspecialized) definition of min

```cpp
const T& min(const T&a, const T&b, Compare cmp)
```

Here, typename T is a type, like int, double etc. Compare is also a type i.e. a class of some sort, which will let us perform some sort of ordering on two arguments.
Notice that this Compare is not a function pointer but a class type. It could have been a function pointer that takes two arguments. But there are reasons why we chose a class type instead of a function pointer.
The point of this is to avoid an expensive function call.

Now, let's look at the second (specilized) definition on `min`. This is returning `min(a,b,std::less<T>());`.
Here, the last argument to unspecialized min is an object of `std::less`.

Let's try to write this `std::less` class.

```cpp
template<typename T>

// requires T to be totally ordered
struct less<T>{

  bool operator()(const T& a, const T& b) const{
    return a < b;
  }
}

// And then we can use it like this
// std::vector<int> my_data;
// ... fill in the my_data here

//std::sort(my_data.begin(), my_data.end(), std::less<int>())
```

There are several things to notice here:

1. This will work for totally ordered datatype because it supports < operator
2. we're overridding () operator, essentially making the class `less` a functor. i.e. operator () can be invoked on its instance
3. operator() accepts two const reference argumenets, because we don't intend to modify the arguments nor we want to copy them by passing by value instead
4. operator() override is a const function. i.e. it won't allow for any members of class `less`, which is obvious, because there are no members in the class. This class is purely a functor

In the call `std::sort(my_data.begin(), my_data.end(), std::less<int>())`, the `std::less<int>` is a type. And we're making an empty object of it using the `()` operator. i.e. `std::less<int>()` is an empty object.

Once again, it's not a function pointer. But a functor object. The advantage of doing things this way, is that it allows us to call templated algorithm functions, such as `std::sort` or the one we defined above: `const T& min(const T&a, const T&b, Compare cmp)`

The interesting thing here, is because for dataypes like `int`, the `min` function is just `<`. So the `std::less<int>` will get inlined.

This is a little different from passing a function pointer. If we had passed a function pointer, a function will be called (and not linlined). For the operator(), the () call will be inlined and the entire less that operator would be just calling `a < b`

### the max function

We could write the max function the same way as we wrote the min function. i.e. using the Comparator functor.
However, let's dig a little deeper. The idea is that the min, max and sort should work in harmony.
Let's explore how the we would write a sort function to sort two items. This sort function will simply swap the items if they're out of order, so a always has the min value and b has the "max" value

```cpp

template <typename T, typename Compare>
// T is StrictWeakOrdering
inline
void sort2(const T& a, const T& b, Compare cmp)
{
  // cmp can be std::less, for example
  // so the logic is, if b is less than a, swap a and b
  // otherwise, do nothing
  if(cmp(b,a)) // checking b < a will make sure that a and b don't get swapped when b == a
  {
    std::swap(a,b)
  }
}
```

After this sort is done, a will contain min and b will contain max.

In the above implementation, if a and b are equivalent, no swap will happen and the sort will have no effect. This is the right thing to do.
Now, let's say we write a max function now. If we implement the max function the same way as min and use `>` instead of `<`, for example and we call min and max on a and b that are equivalent, they both will have the same effect. i.e. the output of `min` and `max` will have the exact same output. Whereas, in principle, they should have the opposite output.
So, let's write the max function so that it has the opposite output of min.

```cpp
template <typename T, typename Compare>

// T is StrictWeakOrdering

const T& max(T& a, T&b, Compare cmp)
{
  if(cmp(b,a)){ //cmp(a,b) will mean that a is less than b (i.e. b is either equal or greater than a)
    return a;
  }
  return b;
}
```

We can then similarly write a specialized templated function for totally ordered types as we did for min

### Find minimum element from a range

So far we have written a min program that operates on two elements. Let's expand on this and write a min program that returns minimum element from a range. This range could be a vector, for example.
For reference, see the `std::min_element` function.

- What should this function take as an input?
  - It should take a "range". The range implies a begining and an end
  - Therefore, the function should take the begin and the end of an iterator

- What should this function return?
  - We could return the element itself. But if we do that, we will only know what the element is. That means
    - We can't delete that element from the range
    - We can't know what's after it or before it
    - There's a dilemma of what to return when the range is actually empty

Here's what the code should look like:

```cpp
template <typename I, typename Compare>

// requires I is ForwardIterator (reason in the explanation below)
// and Compare is StrictWeakOrdering on ValueType(I)
I min_element(I begin, I end, Compare cmp)
{
  if(first == last) return last; // or first (i.e. get rid of the empty range case)
  I min = first; // save first element as min temporarily

  // now iterate over the entire range and update min

  ++first; // since we already know that first is not last, we only have to iterate over n-1 elements

  while(first != last){
    if(cmp(*first, *min)){ // i.e. if the current first is less than min
        min = first;
    }
    ++first;
  }

  return min; // so basically we're incrementing the iterator and recording the position of min element then returning it
}
```

- In the above algorithm, we are saving the value of iterator `I min = first` and also returning the iterator. This means, the iterator should be "alive" at the time of usage. This requires the iterator to be **forward iterator** as against input iterator
- Input iterators are temporary iterators, which when iterated over, are invalid.

- How would we implement the max?
  - We can just do `!cmp(*first, *min)`

## Lecture 5 part 2

### minmax element algorithm

- In the above examples of minimum and maximum, the number of comparisons we had to make were (n-1)
- What if we needed to find min and max both at the same time? Turns out there is a more efficient algorithm for that
- The idea is that we take two elements into consideration and find the min and max between the two, then do the same for next two elements while keeping a running min and max.

```cpp
// let's say there are 6 elements
3,2,5,1,0,4
// step0: init_min, init_max
// step1: input = 3,2 => cur_min=2, cur_max=3. min=2, max=3. #of comparisons=3 (1 for cur_min with cur_max, 2 for cur_ with init_)
// step2: input = 5,1 => cur_min=1, cur_max=5. min=1, max=5. #of comparisons=3 (1 for cur_min with cur_max, 2 for cur_ with global min/max)
// step3: input = 0,4 => cur_min=0, cur_max=4. min=0, max=5. #of comparisons=3

// total # of comparisons = 9 (i.e. 3n/2)
```

Let's talk aboout the function now. Let's call it `minmax_element`.

- what are the arguments to it?
  - Same as min and max. i.e. a range represented by the being and end iterator. And also a comparison functor
- what are the prerequisites on the inputs to the function
  - Same as before. i.e. the iterator has to be Forward iterator and compare functor is required to have StrictWeakOrdering on Valuetype(I), where I is the iterator
- What is the return value of the function?
  - The function is supposed to return two iterators pointing to the positions of min and max elements
  - So, let's return a pair of iterators

```cpp
// Requires I is ForwardIterator
// Compare is a StrictWeakOrdering on ValueType(I)
template <typename I, typename Compare>
std::pair<I, I> minmax_element(I first, I last, Compare cmp)
{
  // corner case - empty range
  if(begin == end) return std::make_pair(last, last);

  // now we have at least one element
  I min_el = first;
  I max_el = ++first; // at this point, this could be end, so we need to check for that in the next line

  if(first == last) return std::make_pair(min_el, max_el); // i.e. this is a one element range and min and max are the same

  if(!(cmp(*min_el, *max_el))) std::swap(min_el, max_el);

  I global_min_el = min_el;
  I global_max_el = max_el;

  while(...)
  {  
    if(cmp(*min_el, *global_min_el)){
      global_min_el = min_el;
    }

    if(cmp(*max_el, *global_max_el)){
      global_max_el = max_el;
    }

    min_el += 2;
    max_el += 2;

  }

}
```

the above code is incomplete. It needs to deal with the situation when there is only one element left at the end

### Finding min and a second min

We will now discuss a problem where we want to find the first min as usual but we also want to find the second min.

#### Run time considerations

We want to find an optimal way to find the second min, preferably with a logarithmic order of comparisons.

- What we know
  - We know that no matter what, finding the min will require n-1 comparisons. That won't change
  - We also can easily see that the second min will be the guy who loses only against the min and no one else.

- Let's say we have 6 numbers and we want to find the min and next min. Let's represent the winners with W and losers with an L in the figure below:

```none
              W1
      W1              W3
  W1      W2      W3      W4
W1,L1   W2,L2   W3,L3   W4,L4
```

In the above tree, we're pairing two numbers. One of them "wins" the min comparison and advances to a level above. There are total 8 elements. And the depth of tree is 3. i.e. 2^3.
If there were 7 elements, the depth of the tree would still be 3. Hence, in general, the depth of the tree is ceiling of ln(n). i.e. log base 2 of n

- The idea is to find the minimum (ultimate winner) with n-1 comparisons and then arrange the elements in a binary tree, so that there are logarithmic number of comparisons. To be exact, `ceiling(ln(n)) - 1` comparisons.
- So, overall, we want to be able to do it in `(n - 1) + ceiling(ln n) - 1 = n + ceiling(ln n) - 2` comparisons

#### Space considerations

- Because we need to know the second minimum and we know that the second minimum could've only lost against the absolute minimum, we somehow need to store a history. (How we would do it is a different story altogether. Let's save that for later)
- Also, observe that we don't technically need to save a lot of history. In the tree above, when we're done comparing W1,L1, we're ready to go a level above and discard W1 and L1.
- If we can't do all the comparisons "in-place", a logarithmic storage is acceptable. In practise, the logarithmic storage would not exceed 64.

### Data structures

Let's first discuss what we're going to compare. This is where the concept of parities comes into picture. The idea is that, we want to be comparing (i.e. create a match-up of) numbers of the same level/weight.
So, let's say we took an array (of some data strucute) of length 32, at 0th index, we'd put all the numbers that won 0 time, at index 1, we'd put numbers that won 1 times and so on.
In order to put those numbers there, we'd need to figure out how to "combine" these numbers. So, we will need a combine function.

### 