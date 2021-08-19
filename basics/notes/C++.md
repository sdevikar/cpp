# C++ basic concepts:

## Prefer const over #define

- Type safety: Because const variable is an actual variable, compiler knows the
  datatype of the variable
- We can define const anywhere in the program versus a #define which has to be
  defined at the top of the file

# inline functions

- We can use #defines for defining simple operations and calculations. e.g.

```cpp
#define SQUARE(x) x * x
```

But the above is dangerous because `SQUARE(a+1)` will expand as follows:

```
a + 1 * a + 1
```

The above will follow the rules of precedence and the result will be not as expected.

- In contrast to above #define, if we use `inline` keyword, the above syntactic pitfall is removed. Inline function will behave the same way as any normal C++ function
- The call to inline function is replaced by it's definition. This is NOT true in debug build. In debug build, inline function is not inlined
- Inline is also a directive -- meaning that it's a suggestion to the compiler. Compiler may not inline code if it deems that the function is too big or something like that
- Inline functions can not be recursive either
- For inline function, the body also needs to be in the header

# Pointer vs Reference

- Reference is simply a synonym/alias for an existing variable. e.g.

```cpp
int i = 15;
int &j = i; //here, j is reference to i. i.e. i's alias

```

- Reference is denoted by an & sign followed by the reference name (j in above case)
- Reference and pointer are only similar to the extent that they both refer to an address. But other than that they're completely different
- Since pointer is basically pointing to an address and a reference is nothing but an alias of something that already exists, reference cannot be NULL. The pointer can be NULL, meaning that it's pointing to nothing
- Since pointer is again a special variable that points to something, the "something" that pointer points to can change. But since reference was CREATED based on the fact that it's an alias for something, the reference cannot refer to a different variable. e.g.

```cpp
int a, b, *ptr;
ptr = &a; // this is ok
ptr = &b; // this is ok too

int x, y;
int &z = x; // this is ok
int &z = y; //ERROR - this is not allowed

```

- One advantage of pointers is that it comes with a facility of operations that can be performed on it. e.g. on a 32 bit machine, incrementing a pointer by 1 will make it point to the current address + 4. Whereas for references, these operators like ++, -- etc are meaningless. Because these operators are interpreted as operations being performed on the original referent. i.e in above example, &z is interpreted as alias of x.

# Function overloading:

- Allows for reuse of function name but with a different number or different types of parameters
- Binding happens at compile time. i.e. the decision regarding which function to call among the functions with the same name, happens at compile time
- It should be noted that the binding happens based on the number and types of the parameters but NOT the return values. So, function overloading cannot be used when the arguments of two functions are the same but they have a different return type
- Compiler follows the rules below to bind the function call to the function. These rules are to be followed in the order of priorities as listed below:
  - match the name of the function
  - match the number of parameters
  - match the datatype of parameters
    e.g. if we had the following function signatures available:

```cpp
void myfunc(int a); //function1
void myfunc(double a, double b=3.3); //function2
```

And then we go ahead and call the function as below:

```
myfunc(5.6);
```

Here, both function1 and function2 are viable functions because:

- they match by name
- they match by number of parameters as well, because the function2's second
  formal argument is defaulted to 3.3
- actual argument 5.6 can be truncated as int

In the above case, function2 will be called because as per the last rule of binding, datatype must match.
5.6 is rather a double than int.
If instead the function was called as below:

```cpp
myfunc((int)5.6);
```

In the above case, function1 will be called.

Following is an example of compiler not able to bind because of ambiguity:

```cpp
int myfunc(double a, double b =5.0);
int myfunc(double a, double b);

int x = myfunc(5.5, 6.5);
```

Here, both formal arguments are double datatype. And actual arguments are also double.
It doesn't matter that one of the functions has the second argument defaulted. The
argument type is still double. Therefore, compiler gets confused.

- Here's another example that puts emphasis on overloading and defaulting function parameters

```cpp
int f();
int f(int x = 0); // it is important to know here that this function is really 2 declarations
                  // declaration 1: int f(int x); the only special thing here is x=10
                  // declaration 2: int f();
// Now we try to call the function f
int z = f(); // this will result in an error because of function 2 can be interpreted as declaration 2
```

# Operator overloading:

- Has to do with assigning new behavior to the operators like +, -, = and so on
- If we think about it, operators are pretty similar to functions. In the sense
  that they both work on inputs (we call them arguments) and produce an output.
- There are certain differences though, such as follows:
  - operators are mostly written in "infix" notation i.e. they sit in between the two operands
  - functions are written in "prefix" notation. i.e. they sit before operands
  - operators operate on 1 or more (upto 3) operands and functions operate on 0 or more arguments
  - operator will always produce a result, function doesn't have to (void return type)
  - order of operation using operators is decided by rules of precedence. For functions, usually we don't need to worry about precedence. However, for example, when we pass an expression (e.g. a function call) as an argument to a function, arguments will be evaluated based on how they're nested
  - operator operation is pre-defined. Function definitions can be modified as needed
- C++ provides a way to associate a function with a particular operator. This is facilitated by keyword `operator`
- The syntax for this is `operator<operator_name>(arguments)`

## Operator overloading rules:

- You cannot invent your own operators. e.g. you cannot define \*\* as an operator and define it's operation logic
- You cannot change intrinsic properties of an operator. Intrinsic properties include:
  - Number of operand the operator operates on (arity). e.g. + operates on 2 operands.
  - Precedence remains the same. You cannot change precedence
  - Associativity cannot be changed
- Almost all operators can be overloaded
- In some cases same operand can be used as prefix and postfix. e.g ++a and int a++. So, how do we override this?

  - In the above case, prefix operator gets to keep the normal syntax. i.e. ++a can be overridden as follows:

  ```cpp
  int& operator++(int &a){
    // do something here
  }
  ```

  - In the postfix case, we need to provide an additional int argument. i.e. a++ in int a++ can be overridden as:

  ```cpp
  int& operator++(int &a, int){
    //do something here
  }
  ```

  Note that, when we call ++ operator on anything, we don't need to pass this additional int argument

  - Some operators like scope resolution (::), member access (.), sizeof, and ternary operator cannot be overloaded
  - You're allowed to override operators like &&, || etc. But we need to understand that these operators will lose their special properties after we override them. The special properties being - short circuit evaluation. e.g. in false && expression, expression will never get evaluated because no matter what the output of the expression is, result of && is going to be false. This is called short circuit evaluation
  - operator -> can be overloaded, but must return a raw pointer or return an object (by value or reference)

# Memory management

- C++ provides a shortcut alternative to malloc, calloc etc. It's called the operator `new`
- With operator new, you can dynamically allocate memory to a datatype and initialize as below:

```cpp
int *a = new int(5); //this goes on a heap
```

- There is another similar operator `new[]` that can be used to dynamically allocate memory to an array

```cpp
int *b = new int[10]; // array of 10 integers on the heap
```

- There is a way to tell new, where to allocate the memory from. This is called _placement new_ operator. This is how you can do it:

```cpp
char *buf = new char[50];
int *a = new(buf) int(2); // an integer pointer with init value = 2 that's allocated at the beginning of buf address
```

- To delete/deallocate the memory allocated this way, we can use the delete and delete[] operator

```cpp
delete a;
delete [] b;
```

- In placement new, there is no need for explicitly calling delete. i.e. in example above, we will not need to call delete a. But delete buf will be required.

- Since new and delete are operators, we can override them or call them using their full names

```
int *p3 = (int *) operator new(sizeof(int));
```

In summary, new operator takes 3 forms. new, new[] and new(). First two forms must be paired with corresponding delete and delete[] and last form doesn't require a delete
| Allocator | De-Allocator|
| :-------------------| :-----------|
| malloc | free |
| operator new | delete |
| operator new[] | delete[] |
| operator new() | No delete |

# C++ classes

- Two _main_ types of access specifiers
- Public and private (we'll talk about protected later)
- Members are private if there is no explicit access specifier
- In general, properties (i.e. data members) of the class are associated with its state. So we prefer to keep the properties private
- The methods of the class are usually associated with changing these properties. So we sometimes need to keep the methods public

## Constructor:

- A special function, that bears the same name as the class name
- Can be overridden
- Default constructor is a constructor with no parameters: This is automatically provided by C++ compiler
- Default constructor is automatically called when the object of class is created

## Destructor:

- Counterpart of Constructor
- Only one type of destructor - i.e. destructor with no parameters and no return value
- Destructor is automatically called when the class object goes out of scope. We'll demonstrate this with an example

## Initializer lists:

- This is a way to initialize class properties with the help of values or expressions
- Same as assigning values to individual properties inside the constructor, but with a slight difference (discussed later)
- Initializations done using initializer lists are invoked in an order in which the class members are defined in the class definition and not by the order in which initializations appear in initializer list.

## Destructor

- Special function that gets called on the object, when that object goes out of scope
- Has no return value
- Cannot be overridden
- Starts with ~
- In some rare cases, destructor can be called using delete keyword
- Destructors are called in the reverse order of constructors. e.g.

```cpp
int main(void){
  ClassA obj1;
  ClassB obj2;

  return 0;
}
```

In the above case,

- Constructor of ClassA will be called first
- Constructor of ClassB will be called next
- Destructor of ClassB will be called first
- Destructor of ClassA will be called next

## Copy Constructor

- We have instantiated Complex class object the following ways:

```cpp
//case1: simplest case:
Complex comp(2,3);

//case2: somewhat different way:
Complex comp = {2,3};
```

- We can also do something like this:

```cpp
//case3: pass another object to the constructor of complex class
Complex comp2(comp);

//case4: Or using assignment:
Complex comp2 = comp;
```

- Case 3 and 4 above invoke a constructor that is known as a _copy constructor_.
  This constructor looks like this:

```cpp
Complex::Complex(const Complex &);
```

Note here that even if we're doing assignment in case4 using `=` operator, we're constructing a new object here, hence the copy constructor is invoked. This is different from copying one existing object to another existing object. i.e. if we do something like the following, `=operator` will be invoked

```cpp
// invocation of = operator
Complex c1(2,3);
Complex c2(4,5);

// = operator is invoked here instead of copy constructor
// because we're not constructing anything
c2=c1
```

- Apart from case#3 and case#4, copy constructors are invoked whenever there is
  copying of object involved. This includes passing object by value to a function

```cpp
// case5: Here compformal will make a copy of compactual
// therefore a copy constructor will be invoked
void DoSomething(Complex compformal){

}

int main(){
  Complex compactual(2,3);
  DoSomething(compactual);
}

```

- Copy constructor can have multiple signatures. Following signatures will be
  recognized as copy constructor by C++:

```cpp
// signature with constant reference. Formal argument can't be modified
MyClass(const MyClass& myclass);

// signature with a non const reference. Formal argument can be modified
// this is important for certain designs
MyClass(MyClass& myclass);

// signature with volatile const reference. Formal argument can't be modified
MyClass(volatile const MyClass& myclass);

// signature with volatile reference. Formal argument can be modified
MyClass(volatile MyClass& myclass);

```

- Following signatures will NOT be recognized as copy constructors by cpp

```cpp
MyClass(MyClass* myclass);
MyClass(const MyClass* myclass);

//here, by specifying the pass by value mechanism, the prerequisite is that
// the actual parameter needs to get copied to formal parameter
// this renders this kind of constructor useless, because the act of copying
// is a prerequisite for this copy constructor to work
MyClass(MyClass myclass);

```

- As with the normal constructor, if user doesn't write a copy constructor,
  compiler will provide one
- However, since compiler doesn't know how to do deep copy for user defined objects,
  it will provide bit by bit copy. (similar to memcopy). This approach doesn't always work though.
  More on this later.
- The most important point to remember is that the default copy constructor does a _shallow copy_

## Copy assignment operator:

- Consider the following lines of code:

```cpp
Complex c1(2,3); // constructed complex object c1 from scratch
Complex c2(c1); // constructed a complex object c2 from c1. Copy constructor will Be called here

c1 = c2; // c1 already existed. We're copying c2 into c1. This requires =operator to be overloaded
```

- The assignment copy operator is nothing but overloaded = operator.

```cpp
Complex& operator=(const Complex& c){
  // do deep copy here. e.g. this->real = c.real;
}
```

- Notice that we're returning Complex& i.e. reference to same type as of the class. This is to support expressions like:

```cpp
Complex c1,c2,c3;
c1 = c2 = c3; // chain assignment
```

- The above is equivalent to `c1 = (c2=c3)`. Unless the expression `c2=c3` doesn't return Complex& type, `c1 = <expression>` will not work.
- There is a caveat in copy assignment operator. The caveat being, we always want to check if the object being copied is the same as current object. This is to make sure that we're not trying to write freed memory, that we may have freed, before executing the logic inside copy operator to avoid memory leak

## Const objects:

- You can create const objects for classes like so:

```cpp
const MyClass obj;
```

- This basically means, the instance is read only and you cannot do ANY operations on it.
- Any operations include calling getter and setter methods or directly modifying public members of the class.
- Obviously, this isn't helpful to do anything at all. To perform any operations on the class, we need constant member functions
- Concept: When a method is invoked on an object, `this` gets passed as a default argument to the function (i.e. a method needs a pointer to class object). (In python, this is explicitly done manually using `self`)
- In C++, the object of class gets passed to the method implicitly as below:

```cpp
MyClass * const this
```

- In case of a constant object, we need to be able to pass the following to the method as an implicit parameter

```cpp
const MyClass * const this
```

- We achieve this by doing the following modification to the function definition:

```cpp
void MyMethod() const { // notice the use of const before curly brace
  // some logic here
}
```

- The method above is saying that it can be invoked on a constant object
- In a constant member function like above, we cannot modify any data members of the class, UNLESS the data member is declared as _mutable_
- A non constant object can invoke a constant function above
- In summary, a constant object can only invoke a constant function. A non constant object can invoke both kinds of methods

### Mutable data members:

- We learned earlier that:
  - We cannot modify const data members no matter what
  - We cannot modify data members inside const functions
- There is one exception in const object though. It is called the mutable data member
- Mutable is applicable only to data member of a class and not to local variables etc.
- Reference data members cannot be declared as mutable
- static data members cannot be declared as mutable either
- const data members obviously can't be declared as mutable

# Static data members

- Associated with class and not the member
- Shared by all objects of the class
- Need to be _defined_ outside the class scope and initialized in the source file (more on this later). Can be declared within the class scope
- Can be public or private
- Virtually eliminates the need for global variables

## Static data member initialization:

The initialization of static data member doesn't happen the same way as a normal instance data member.
When we create an instance of a class, the memory for all the instance (non-static) data members get allocated.
However, since static data member is a class data member, rather than an instance member, the declaration of static data member in the class definition doesn't automatically mean that the memory will be allocated for that member. In other words, static data member has to be separately and manually _defined_.

As discussed earlier, in the application, initializations of global variables happen BEFORE main is executed. As such, class static variable initialization will happen before main, if it is initialized in global scope within the file.

Example:

```cpp
class MyClass{

public:
  static int mydatamember; // this is just a declaration

private:
  static int myprivatedatamember; // this is just a declaration
};

MyClass::mydatamember = 0; // this is actual definition
MyClass::myprivatedatamember = 0; // this is actual definition. You can still do this even if the member is private because this is *definition*

int main void(){
  MyClass::mydatamember += 1;
}

```

# Static function

- Similar to static data members, these are per-class functions
- Since they are per-class, they do not have _this_ pointer
- As a result of not having this pointer, they cannot access instance data members (i.e. cannot access non-static data members)
- Why do we need static member functions?
  - To manipulate private static data member functions. i.e. public static functions will be used to access or modify private static member function
- Static member function cannot share a name with non static member function
- Static member function can't be a const function either - this is because const function need const this pointer and as said earlier, static functions don't have a this pointer

## The linker error issue:

- If the private static data member is not initialized in the application globally, we will get the linker error
- This is because, up to the point the static data member is _defined_, the space was never allocated for it by the compiler, during the object creation

# Friend function

- A function that can access private and protected members of a class
- The function is defined outside the class scope and only _declared_ as a "friend" function within the class scope
- By _outside the class scope_ we mean a function that is defined outside in global scope, or within a _different class_, or it could be a function template (more on this later)

## Why not just provide public APIs in a class?

- It may seem that friend function is a loophole in encapsulation but...
- Using friend function, we have the ability to control who has access to private members of the class.
- Some typical use cases for friend function is:
  - operator overloading: _Defining_ a friend function within class scope doesn't make it a _member_ function. So, it's not visible to the application. This makes it useful for operator overloading
  - test code
- See the answers to this question: https://stackoverflow.com/questions/17434/when-should-you-use-friend-in-c#
- As per the video lecture, there are some operators (like streaming operators), that are very hard to overload. In this case, the friend concept is useful

# Friend Class

- Same as friend function, but for a class. A class (A) declared to be the friend of class (B), will have access to the private and protected functions of class B.
- This means, all functions in class A, will be able to access private and protected members of class B
- A friend class can be a simple class (like class A) or a template class (more on this later)

## Some properties of friend class:

- A is a friend of B doesn't mean B is a friend of A - i.e. this relationship is non-associative

# Operator overloading for User Defined Datatypes:

- We have seen already that operator overloading is simply a special type of function, with the operator as the invoking function name and the operands being its arguments. e.g.

```cpp
a+b;
// the above is same as
a.operator+(b);
```

- Now, we can overload the operator in different scopes.
  - Class scope: We can define a public function inside the class. In this case, since the first argument to the function is implicitly `*this`, we don't need to explicitly pass that argument.
  - Global space or friend function: We can overload the operator in global space and/or declare it as a friend function. In this case, instances of both the classes will be required to be passed to the function (assuming the operator is binary)
- We also need to be careful about overriding = operator for user defined datatypes and realize that it will be required wherever allocation of memory using `new` operator is involved. Because if we don't, compiler provides a default = operator that does only shallow copy and this could result in unexpected behavior. In general, if constructor uses operator `new`, = operator should be overloaded
- Study specific case of pre and post increment operator and how it's implemented in the examples

## Doing more with operator overloading:

- We studied a simple example of Complex class where we overrode the `+` operator to add two complex numbers. We also studied that we can override the operator in global space or in class scope as a member function. When we use global scope though, we're basically violating the encapsulation of private data members and thus this approach is not always practical.
- Another thing worth noticing is that, the overriding that we did for `+` operator was not flexible. e.g. if we were to add a complex number and a real number like so: `(3 + i4) + 5` what we defined is not sufficient and we'll have to define additional overloaded methods for `+` operator. e.g.

```cpp
Complex operator+(const Complex& comp1, int r); // global override that says, first argument is complex number and second is double. This will take care of (3 + i4) + 5
Complex operator+(int r, const Complex& comp); // this will take care of 5+(3 + i4)
```

- Note above that operator+ takes two arguments. Which means, the only option we have is to either have operator+ be overridden and as a friend function or do a global override. Particularly in the second case above, if we do `5+(3 + i4)`, for a member operator+ function within class scope, it'll be translated to 5.(complex_number_instance_for_3+i4) and this is invalid
- The solution to the above is still using a global function for operator overload, but then define it as a friend function, so it can access private data members of the class.

## IO operations:

- IO operations are the operations that you do when e.g. you're reading/writing from/to a stream/file etc. e.g. we want to be able to do something like:

```cpp
Complex c1(1,2);
Complex c2(3,4);
std::cout << c1 << c2; // this means (std::cout << c1) << c2;
```

- The cout operator above is a binary operator that has left to right precedence. The cout << c1 is interpreted as follows:

```cpp
// the following is the same as:
std::cout << c1;
// the following overloaded operator function
ostream& operator<<(ostream &os, const Complex& c1){
// some logic here
}
```

- Notice above that operator returns ostream reference. This is required to implement chaining.
- Here, for overloading `<<` operator, we have following options:
  - Override in global space and pass it two arguments as shown above
  - Override in ostream class with signature `ostream& operator<<(const Complex& c)`
    - Can't do this because we can't modify ostream class, which is a part of standard library
  - Override in Complex class with signature `ostream& operator<<(ostream &os)`
    - this is equivalent to doing `complex.operator<<(ostream& os)`
    - and that is equivalent to `complexobj << cout` i.e the order is reversed.
    - this breaks the syntax, therefore **IT IS NOT possible to use member functions for overloading of io operators**
    - **Instead, use friend function**
- Other observations:
  - ostream/istream argument is not const in any signature, because it is ostream that we're modifying
  - in overriding both, ostream and istream, we'd return reference to original ostream and istream to achieve chaining of << and/or >>

## When to use what kind of operator overloading:

- Use global overloading when encapsulation is not a concern. e.g. if you're simply trying to override an operator for a structure that wraps some primitive datatypes, pointers etc.
- Use member function when left operand (first argument) is guaranteed to be a class within which, the operator is overloaded. e.g. complexobj + realnumber. This translates to `complexobj.operator+(int realnumber)` and thus, to the operator+, the left operand is always the class object.
- In majority of cases, use friend function for overloading the operators.

## Some other considerations:

- Consider effect of casting (more on this later)
- Do it only when necessary

# Namespaces

- Namespaces are open. i.e. if you have defined a namespace before and added few things to it, you can later define some more elements to that namespace somewhere else.
  e.g.

```cpp

// file1
namspace mynamespace {
  int x;
};

//file2
namespace mynamespace{
  int y;
};

// following is valid
mynamespace::x = 5;
mynamespace::y = 10;

```

- There can be unnamed namespaces, just to segregate certain symbols. This is just another encapsulation technique, where only the symbols within the same namespace can see each other and interact with each other.
- Just as a sidenote, global scope symbols can be identified using '::' operator. e.g. ::var means var is in global scope

# Inheritance

- Has to do with IS A relationship. e.g. Civic is a car
- As such IS A relationship has to do with specialization/generalization. Civic is specialization and car is a generalization.
- Inheritance syntax is as follows:

```cpp
// Single inheritance example:
class Employee; // base class
class Engineer : public Employee; // Engineer is a 'public-ly' derived class. Engineer IS AN Employee

//Multiple inheritance example:
class Vehicle; // base class
class TwoWheeler : public Vehicle; // child1 of vehicle
class FourWheeler : public Vehicle; // child2 of vehicle

// there can also be multi-level inheritance
class SoftwareEngineer : public Engineer; // Engineer is a base class here, which is in turn a child class of Employee

// more on usage of 'public' keyword later

```

## Some properties of IS A relationship

- Derived class _inherits_ all data members of base class
- Derived class may add its own data Members
- Derived class _inherits_ all member functions of base class
- Derived class may override the base class member function (WITHOUT changing signature) -- this is NOT the same as overloading
- Derived class may overload the base class member function (BY changing signature, but keeping the name)
- Derived class can NOT access the private members of base class
- Derived class can access the protected members of the base class
- Constructor of derived class must first call the constructor of base class to construct the base class instance of the derived class. i.e. derived class first constructs base class and then itself.
- Destructor of derived class calls destructor of the base class instance of the derived class. i.e. derived class constructs and owns base class instance, keeps it and then destroys it, when it is destroying itself

## Access specification:

- Derived class can't access _private_ member of the base class.
- However, derived class can access the _protected_ members of the base class.
  - Keep in mind that protected members can ONLY be accessed using base class instance. For example:

```
class Base{
protected:
  int m_BaseX;
};

class Child : public Base{
public:
  void Print(){
    //This is OK
    cout << "Base class protected member is: " << m_BaseX << endl;
  }
};

int main(void){
  Child c;
  // This is NOT ok
  c.m_BaseX = 5;
  return 0;
}
```

## Friend functions and automatic casting:

- Suppose you have a public friend function declared and defined in the base class:
  - This friend function will have access to the private members of the base class
- Now suppose you write a child class that inherits from base class
  - By definition, child class will have access to the public base class member functions
  - When we call this friend function on child class object and assuming child class hasn't overridden this function, this will be deemed as a simple case of inherited function and base class friend function will be called.
  - The point to be noted here, is that, even though, the function call is on child instance, the call goes on base class instance. This is possible because the instance of the base class is included in the child class. And the child class is automatically casted to base class. This is known as **implicit casting**

## Constructor and destructor:

- As we discussed before, the child class has an instance of base class. So, naturally the child class will need access to the constructor and destructor of the base class. So, child class INHERITS the constructor and destructor of the base class. HOWEVER, the **inheritance semantics are different.**
- In particular, child class cannot override the base class constructor and destructors.

## Private inheritance

- Private inheritance has nothing to do with IS A relationship. i.e. it is not used to create base and child class relationship. But rather, it is used to achieve something similar to composition design pattern, where one class is composed of one or more other classes.
- As a result, private inheritance has no meaning in the design phase
- Since there is no IS A relationship, there is NO implicit casting. i.e. in the example discussed before, if the child class had privately inherited the base class, calling the friend function with overloaded operator << will result in error, because when the << operator in base class is called, the child class object won't be implicitly casted to base class

## Protected inheritance

- Also doesn't mean IS A relationship
- No real design use case for implementing protected inheritance

## Private inheritance for composition

The fact that every class object with IS A relationship with base class holds an instance of its base class implicitly, it is necessary to create base class object first.
This is true for private inheritance as well, BUT, in private inheritance, THERE IS NO IS A RELATIONSHIP
So, in effect, with private inheritance. we're creating an effect of composition

## Inheritance and visibility:

- This has to do with what happens to the visibility of a member of a base class when it is inherited by the child class
- The simple answer is, two of the more restrictive visibility will be applied.
  - e.g.#1 child class publicly inherits base class. In this case, base class's private members will remain private, public will remain public in child class.
  - e.g.#2 child class privately inherits base class. In this case, public member of base class will become private in child class (i.e. child class cannot access the public members of base class directly using . operator)

# Casting

- Implicit casting occurs when compiler knows how to convert one datatype to the other. Conversions that lead to data loss are done with compiler warning

```cpp
double numerator = 5.0;
int denominator = 4;

// here the denominator will be implicitly upcasted to double datatype
double answer = numerator / denominator;
```

- You cannot explicitly cast unrelated classes from one type to other. You can make the arbitrary class pointer point to other class object, but there is no point doing this because the class pointer will point to a memory that has some other class's data in it

```cpp
class A { /*blah blah*/};
class UnrelatedClassB { /*blah blah*/};

A a;
UnrelatedClassB b;

// following will result in a compiler error because the classes are not related.
a = b; //ERROR

A* pa;
UnrelatedClassB* pb;

pa = &b; // possible but wrong
```

- You can cast child class to base class (upcast) safely. The reason for this is that the child class has an object of base class and compiler knows how to refer to base class object in the child class.

```cpp
class A { /*blah blah*/};
class B : public A{ /*blah blah*/};

A a;
B b;

// This is OK
a = b;

// BUT this is not OK
b = a;

```

## Static and Dynamic Binding

- Refers to the process of compiler binding the function calls to the corresponding object either at compile time (static) or run time (dynamic)
- The implication here is that compiler will bind a function call to the object based on the "type" of the object and not the content of the object
- So, if we have a pointer to a parent class that holds the address of its child class, calling any function on that object will still call the function defined in the base class. This is counterintuitive, because the actual object that the object pointer holds is the child class object. This happens due to the compiler binding the function calls to the object statically i.e. at compile time. So, it doesn't know what object parent class object pointer will hold
- To achieve dynamic binding, i.e. to call the function on based on the actual object content and not the object type, we need to declare a function as `virtual`.
- See dynamic_binding example code for more details

### Properties of virtual

- The class with a virtual function is called a polymorphic class
- When a child class inherits parent class, the corresponding function is by default virtual in the child class as well
- This means, if there is a grand-child class down the line, it will also see the corresponding function as virtual function
- In the class hierarchy, function can be made virtual at any stage in the hierarchy and then it becomes virtual for all the classes downstream

### Virtual destructor

- A destructor is nothing but a member function in a class.
- So, if you have created a class pointer using a reference to its base class, static binding will happen
- Finally when you delete the class object using `delete` call, the destructor of base class will be called
- Always make the base class virtual, if you're going to derive from it

### Pure Virtual Function

- Sometimes the classes are made for the sole purpose of having other classes inherit them and implement the specific functionality. e.g. an interface
- In these kind of classes, providing the implementation for that particular function in the base class should not be possible
- This can be accomplished by defining that function as pure virtual
- Pure virtual function maybe defined or inherited
- Pure virtual function is just a declaration. There is no body

#### Abstract class and implications of pure virtual function

- When one or more function in the class is declared pure virtual, the class is called Abstract Class.
  - This means, no instance of this class can be created
- In an abstract class, there can be data members, other non-pure virtual or even non virtual functions.
- Data members in this abstract base class should be protected (i.e. it makes sense for the data members to be only accessed by derived members)
- Whereas the functions in abstract class should be public
- One thing to note is that, even though it is common for virtual functions to not have any implementation body, it is possible for them to have a body. This is useful when one wants to write some common code that a derived class will call before executing its own logic.
- The parent class pure virtual function can be called simply by calling it on parent class scope.

```cpp
Parent::Function();
```

### Virtual Function Table

- Virtual function tables come into play when dynamic binding is involved. i.e. for a function that was defined virtual.
- Every class with a virtual function defined in it has a virtual function table. Remember that virtual function remains virtual in child classes too. i.e. if we have two classes like this:

```cpp
class B {
  int i;
public:
  void f(){};
  virtual void g(int x){}; // this is a virtual function
};

class D : public B{
  int j;
public:
  void f(){};
  void g(int x){}; // this is a virtual function too
};

```

Both classes B and D above will have their own virtual function table

- Some things to notice/remind:
  - daughter class D is overriding the f() function in the base class
  - Daughter class holds the object of parent class
  - `this` pointer is always passed to a function call when the function is called on class object
- Now, in case of static binding, this is how the calls are compiled:

```cpp
// static binding happens because f() is non virtual
B b;
D d;

B *p = &b;
b.f(); // this translates to B::f(&b) i.e. copy constructor invoked
p->f(); // this translates to B::f(p) i.e. f gets pointer to b

B *p = &d;
d.f(); // this translates to D::f(&d)
p->f(); // this translates to B::f(p), since pointer was constructed using B (static binding)

```

- When dynamic binding is involved though, the following occurs:
  - Each class has a virtual function table with pointers to functions

| Class | VFT entry for g |
| :---- | :-------------- |
| B     | B::g(B \*const) |
| D     | D::g(D \*const) |

However, for f() table looks like this, f being non-virtual. i.e. both classes get the base class pointer for a non virtual function

| Class | VFT entry for f      |
| :---- | :------------------- |
| B     | B::f(B \*const, int) |
| D     | D::f(B \*const, int) |

```cpp
B b;
D d;

b.g(5); // this translates to B::f(&b, int) as usual
p->g(5); //this translates to p->vft[0](); i.e.
        //0th function pointer from virtual function table is called
        // in this case, the 0th fptr is function pointer to B::g()

B *p = &d;
d.g(5); // this translates to D::f(&d, int)
p->g(5); //this translates to p->vft[0](); i.e.
        //0th function pointer from virtual function table is called
        // in this case, the 0th fptr is function pointer to D::g()
        // i.e. the virtual function  table's 0th entry is overwritten
```

- The virtual functions are added in the VFT in the order in which they're defined

## Casting in C++

- We already know that upcasting is safe and downcasting is not. i.e. casting from daughter class to base class will not lead to loss of information. But the vice versa will lead to loss of information.
- Implicit typecasting is taken care by the language itself. e.g. an integer will be automatically upcasted to a double when referenced as a double:

```cpp
int x = 5;
double y;
int z = 3;

y = x; // implicit upcasting with no loss of information

y = 4.5;
x = y; // implicit down-casting with loss of information / precision

double w = (double) x / z; // x is explicitly converted to double and z is implicitly converted to a double
```

- Casting usually requires compiler to allocate a different temporary storage for the cast value and initializes the temporary storage with value being cast. This means, the compiler most likely will do the following, except in few cases, where it doesn't need to do that:

```cpp

int num = 5;
int den = 2;

// this is explicit casting for num
double result = (double)num/den;

// and it is equivalent to:
double temp_num = num;
double temp_den = den;
double result = temp_num / temp_den;

```

- C++ takes a significantly different approach towards casting. In C++ casting is done using cast operators.
  Cast operator is a binary operator with following syntax:

```
cast<T2>(T1)
```

Where,

- T2: Type to which casting needs to be done
- T1: expression or a variable in certain existing type e.g. int, double, class type etc.
- cast: keyword specifying what type of casting is being done
- This kind of casting can be done statically or dynamically in C++

### Types of cast operators:

- const-cast: To change the const-ness/volatility of variable or expression. Either make a non-const expression const or vice versa. No computational change. `const_cast<type>(expression)`
- static-cast: Performs a non-polymorphic cast. i.e. it can be performed when you're in a non-polymorphic hierarchy (more on this later). Usually performs computational change. `static_cast<type>(expression)`
- reinterprete_cast: Almost similar to C style casting. Used to do typecastings between two unrelated types. e.g. pointer to class object and so on. Very risky and should be very sparingly used. `reinterpret_cast<type>(expression)`
- dynamic_cast: For runtime casting.

#### const_cast:

- This casting type reinterprets the const-ness of an expression. Here's a simple example:

```cpp
// function that accepts non const char pointer
void print(char* str){ // print str};

// in main
const char * str = "Hello!";

// this will result in error, because we're passing a const argument to a function that expects a non-const parameter:
print(str); // error

// so instead, we can do this:
print(const_cast<char *>(str)); // this is going to typecast str to a non-const char pointer and pass to function

```

- This const_cast is also applicable to class objects. We know that if a class object is const, only const functions can be called on that object.

```cpp

class A {

  void get() const{
    // get something
  }

  void set(int arg) {
    // set something
  }
};

int main(void){
  const A obj; // this is a const object, thus only const functions can be called on it
}

obj.get(); // this is ok

obj.set(5); // NOT OK.

const_cast<A&>(obj).set(5); // OK now. BEcause we created a non-const reference (A&) to const object

const_cast<A>(obj).set(5); // Still not OK. You can't change the object from const to non const. You can only reference the object as non-const
```

- You can do the same thing using c style casting. But it's not readable and reader won't be able to understand why you casted
- Also, illegality (e.g. converting from const class object to non const object) is prevented using const_cast
- const-ness cannot be removed from function pointers or pointers in general. For example:

```cpp
const int j = 5; // this is a constant
int *ptr = const_cast<int *>(&j); // this will result in undefined behavior

```

#### static_cast:

- cast that can be decided at static (compile) time
  - Allows for all conversions that are allowed implicitly. e.g. int, floats, void pointers to specific types etc.
  - Allows for pointers to related class (upcast or downcast). But in case of downcast, no checks are performed at runtime
  - Allows for conversion between user defined types. This is possible because static_cast can call single argument constructor or a conversion operator
  - It can also convert:
    - to rvalue references
    - enum class value to integers
    - convert any type of void

## Placeholder for rest of the casting types

## Placeholder for exceptions

## Templates

C++ is a strongly typed language. Templates are a way to reuse the existing code by parameterizing the datatypes themselves.
Templates is an implementation of meta-programming concept, where some code is generated from some other code.

### Function templates:

- Data types of the parameters to the function can be parameterized. For example, let's say we have a function called max that compares two variables and returns the greater of the two:

```cpp
// function for int comparison
int max(int a, int b){ a > b ? a:b};

//override max for double comparison
double max(double a, double b){ a > b ? a:b};

// Using templates, we can represent both these functions by parameterizing the parameter DATATYPE to let's say, T
template<class T>
T max(T a, T b){ a > b ? a:b};

// The above function can then be called as:
int maxval = max<int>(5, 4);
int maxval = max<double>(5.5, 4.3);
```

There are a few of things to notice here:

1. the keyword `template`
2. Placeholder datatype represented by `<class T>`
3. Passing of parameter datatype at the calling location like `max<double>(...)`

### Template specialization:

- One of the reasons for using templates is code reuse. But in some cases, even though the algorithm is same, the implementation details have to slightly change. For example, the max function above will not work for comparing C style strings represented by char\*. i.e. if we had a C style string comparison function like so:

```cpp
// this will mean we're comparing two pointers (i.e. memory addresses) which does not make any sense and will give unpredictable results
char* max(char* a, char *b){ a > b ? a:b};
```

The solution to something like this is **Template Specialization**.

- Template specialization essentially says that use the template function as usual, EXCEPT when the parameter is so and so. e.g.:

```cpp
template<>
char* max<char*>(char* a, char *b){ return strcmp(a,b) > 0 ? a: b};

```

There are a couple of things to notice here:

1. empty `template<>` declaration
2. new implementation (definition) of max function
3. the new implementation signature above is exactly same as what it would have been, if it was generated by compiler. But we manually and explicitly wrote it out, so the compiler doesn't generate it.

### Explicit and implicit instantiation of Template function:

- So far above we have been calling the template function with a parameter like so: `int maxval = max<int>(5, 4);`
- However, it is possible to not explicitly provide <int>, <double>, <char\*> ... etc. as parameters, as long as they can be inferred from the arguments themselves. e.g.

```cpp
int a = 5;
int b = 4;
double c = 1.5;
double d = 1.3;

// these are valid invocation, since data type of a,b,c and d can be implicitly understood
int maxval = max(a, b);
double maxval = max(c, d);

// this is also valid because int a can always be up-casted to a double
double maxval = max(a, c);
```

- As far as the conversions are concerned, following conversions are allowed:
  - L-value transformations. e.g. array to pointer etc.
  - Qualification coversions. e.g. using non-const value in place of a const value etc.
  - Conversion to base class instantiation

### User defined data types in templates:

Templates work the same way for user defined classes / datatypes. The only requirements is that the datatype must support the requirements of the "algorithm" that the template function is implementing. e.g. in our max function, the algorithm is to compare two parameters and return the greater of the two. For this comparison, an operator `>` is used.

Unless this parameter is defined for comparison of the two datatypes being compares, the max function will not compile. e.g.

```cpp

class Complex {
  // constructor destructor etc.

  friend bool operator>(const Complex& c1, const Complex&c2){
    //algorithm to compare two complex classes.
    // also recall that this needs to be a friend function because
    // comparison algorithm requires access to private data members of the c1 and c2 instances
  }
};
```

### Overloading a template function:

- Template functions can in turn be overloaded with other template functions. e.g. with different number of parameters:

```cpp

template<class T, int size>
T max(T a[size]){
  //do something with the array a
}

// we can call this as:
int arr[] = {....}; // initialize this with ints
max<int, 7>(arr);

double arr2[] = {....}; // initialize this with doubles
max<double, 7>(arr2);
```

- Notice here that the template has two parameters instead of one. `<param1, param2>`. The param2 here is not a template datatype but a primitive datatype. This kind of parameter is called a **"non-type" template parameter**.
  - **only the `int` type of non type template parameter is allowed**
- Note that the specialized template was also an example of template function overriding

### `typename` keyword

So far we've been using the syntax `template<class T>`. The keyword typename is a synonym for the keyword class in this case in almost all cases. And can be used interchangeably. Although, it's a good practise to use `typename` and `class` appropriately, so as to make our intent clear. e.g. if you are intending the template parameter to be an object vs a premitive datatype, it'll be justified to use `class` instead of `typename`
There is only one exception to this.

_typename_ keyword is basically used to tell the compiler that an expression is a type expression.
Let's consider this case:

```cpp
template <class T>
func(T x){
  T::name * p;
}
```

The above can mean two things:

1. T::name is a datatype and p is a pointer to it
2. T::name is some variable in T scope (like a class member) and the expression T::name p becomes a multiplication.

This confusion can be avoided by using the keyword `typename` like so:

```cpp
template <class T>
func(T x){
  typename T::name * p; // the use of typename here says that T::name is a datatype and not some member within T scope
}
```

## Class templates:

- Exact same concept as function template. i.e. we can parameterize the construction of the class. In case of function templates, we specified the data types of the function arguments at the function call location. In case of class templates we'd do the same, but for the datatype used internally by the class.
- The syntax remains the same. e.g.

```cpp

template <class T>
// or we can use template <typename T>

class Stack{

private:
  T data[100];
  int top; //maintains index of the stack top

public:
  push(const T &){// logic to push};
  void pop(){// logic to pop};
  const T& top(){//logic to return top of stack};
}

```

We can create instances of the class from this template:

```cpp
Stack<int> s; // stack of integers
Stack<char> s; // stack of chars
```

- It is important to note that in case of class templates, the instantiation has to be done explicitly. i.e. the template parameters will not be interpreted for you automatically.
- Also remember that classes can be forward declared. i.e. we can just say something like

```cpp
template <class T>
class Stack; // forward declaration
```

And then refer to this class:

```cpp
Stack<char> *char_stack_p; // this is ok, since its a pointer

// but this is not OK, since this thing needs to call constructor etc
Stack<char> char_stack; // this is NOT ok

void MyFunction(Stack<int> stackx&); // this declaration is also OK.

```

### Default class templates:

- We can have default datatypes for the template class. For example:

```cpp

// IMPLEMENTATION - 1

template <class T1 = int, class T2=string >

class Records{
  //implementation.
};

//We can create the instance to the above class as:
Records rs1;
Records <double, string>rs2;
Records <float>rs3;
//etc.
```

## Class template specialization:

- Remember the char* specialization of template function from before. It's the same concept here. i.e. if we want to provide explicit implementation for some datatype for a template class, we can. e.g. let's specialize the above class Records for char*.

```cpp

// IMPLEMENTATION - 2

template <class T>
class Records<T, char*>{
  // implementation
};

```

- **Note** here that the Records class is now redefined with ONE template parameter declared above it. This is the parameter we're willing to templatize. And we have **specialized the second parameter only.**

- Notice that during all of this, the template class Records, remains a class that has two template parameters. It is just that in the second definition, we have hard-coded the second template datatype to char\* datatype

- This kind of class is called partially specialized template class.

In summary, these are the different ways you can create an instance of `Records`:

```cpp
Records<int, string> r1(5, "swapnil"); //both template parameters specified
Records<int> r2(11, "devikar"); //one template parameter specified, second is interpreted as string as default
Records<> r3(12, "nnnn"); // no parameter is specified so by default int and string will be interpreted
Records<string> r3("some_name", "some other name"); // only first template parameter is specified, AND overridden as string. so, <string, string> is the final type

// following is an important one.
// here, the second template datatype is char*, which is specialized above.
// So, // IMPLEMENTATION - 2 is called

Records<int, char*> r1(5, "swapnil");
```

- Note that even though we are specifying only one parameter in case of calls like Records<int>, Records<string>, it does not mean that IMPLEMENTATION-2 will be invoked. IMPLEMENTATION-2 is merely there to prevent compiler from autogenerating the code for <T, char\*> case.

## Templates with class inheritance

- The syntax for this is as below:

```cpp
template <class T>
class Base{
  T someproperty;

  // other implemenations
}

template <class T>
class Child : public Base<T>{
  T somechildproperty;
  T someotherchildproperty;

  // some implementation
}

// if we later define some function in cpp class, this is how we will do it:

template<class T>
Child::SomeFunction<T>(int foo, int bar, T whatever){
  // do something awesome
}

```

- The important and only point to note here is that the templatization trickles down the entire hierarchy. This is to say that:
  - both child and base classes are parameterized for datatype. i.e. not only does the child but also the parent class code will be generated with whatever template datatype the child class is instantiated
  - i.e. in the above case, if Child class was instantiated with let's say string, then Child class properties will be string datatype (`somechildproperty` and `somechildproperty` will be string). And also the `someproperty` type in base class will also be string
