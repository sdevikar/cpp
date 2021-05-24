# Lecture 2

- [Lecture 2](#lecture-2)
  - [Semiregular methods of singleton classs](#semiregular-methods-of-singleton-classs)
  - [Regular methods of singleton class](#regular-methods-of-singleton-class)
  - [Some interesting discussion about Templated classes](#some-interesting-discussion-about-templated-classes)
  - [Totally ordered methods of singleton class](#totally-ordered-methods-of-singleton-class)

Intro lecture ended on a note that the goal for the entire class is to write identical code for the same problem. Subtle conventions are necessary to achieve this. For example, when to capitalize something, when to use what alternative, even though the two alternatives are synonyms etc. Following are the examples discussed at the beginning of lecture:

- when we use template and do something like `template<typename T>` or `template<class T>`, although the two declarations mean the same, one is indicative that the template parameter is an actual class, vs probably a primitive datatype. Also, pay attention to capitalized T. Capitalization is convention here.
- Use of struct vs class: We know that the difference between two in cpp is just the default scope of class members. i.e. in struct, class members are public by default. But there is a deeper reason behind when to use what.
- Public vs Private: Discussed that the common understanding that class properties should ALWAYS be private is BS. Private is only requires when "invariance" is important. Meaning that, you actively want to prevent someone or something from writing anything to that class property.
- Writing a complete class:

  - To make things as simple as possible, we will write a class called Singleton class.
  - Singleton class is not the same as singleton design pattern. It is a class that only has one thing. Let's call that thing as some value. This value can be any datatype like int, float, double, a pointer. So, we will make it a template class
  - Our goal is to take a type T and make it into another type. Which, in this case, will be a singleton wrapped around T.

## Semiregular methods of singleton classs

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

## Regular methods of singleton class

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

## Some interesting discussion about Templated classes

- We know that compiler synthesizes a few things for user, if the user doesn't define them explicitly. e.g. copy constructor, default constructor etc.
- We also know that not all template types T can be "regular" classes. i.e. they probably don't support equality.
- In such a case, if the template parameter T does not _NEED_ a particular method, compiler will not synthesize it.
- In other words, if T is semiregular, Singleton<T> is also semiregular
- if T is regular (aka totally ordered), Singleton<T> is also regular
- Also note that compiler doesn't generate things until they're used

## Totally ordered methods of singleton class

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