# Move semantics

## lvalues and rvalues

- anything that can appear to the left side of the expression is lvalue. e.g. in `x = 10` `x` is lvalue
- anything that can only appear to the right side of the expression is rvalue. e.g. in the above case, `10` is rvalue
- A function in C++ can return by value or reference. The function that returns by value is returning an rvalue and the function that returns by reference is returning an lvalue. So, that function can appear on the left hand side of the expression
- C++11 introduced rvalue references. These are the references to rvalues. Following are some examples of how rvalue reference works:
-

```cpp

// quick recap of "lvalue" reference


int l1 = 10; // l1 is lvalue
int& rl1 = l1; // rl1 is reference to lvalue that is l1

// doubleit function doubles the x and returns its reference
int& doubleit(int x){
   x = 2*x;
   return x;
}

// lr2 is a reference that is currently holding
// the reference to return value of doubleit
int& lr2 = doubleit(l1);

// an lvalue reference can NOT bind to a rvalue
// the following WILL RESULT IN AN ERROR
int& lr3 = 3; //ERROR

// HOWEVER, a const lvalue reference can bind to an rvalue
// i.e. the following is legal
const int& lr4 = 4;


// Rvalue reference examples

// r1 is a reference to 10, which is an rvalue
int&& r1 = 10;

// r2 is a reference to a return value of a function
// this function returns by value, hence its return value is rvalue
int&& r2 = add(5,3);

```

- The purpose of rvalues is to detect temporary values in expressions. For example, we can write functions that overload based on lvale or rvalue arg. See examples below:

```cpp
// function with lvalue reference as argument
print(int& x) { std::cout << "#1 called print(int& x)" }

// function with a const lvalue reference as argument
print(const int& x) { std::cout << "#2 called print(const int& x)" }

// function with an rvalue reference as argument
print(int&& x) { std::cout << "#3 called print(int&& x)" }

int main(void){
    int x = 4;

    // we called this function with lvalue reference
    // so output will be: #1 called print(int& x)
    print(x);

    // we called this function with const lvalue reference
    // so in theory the output coult either be:
    // #2 called print(const int& x) or #3 called print(const int&& x)
    // in this case, function with rvalue reference argument is available,
    // so print binds to print(int&& x) and #3...is printed
    // if the the function print(int&& x) wasn't available,
    // this print call will bind to print(const int& x) and #2 will be printed
    print(7);

}
```

## Copy vs Move and move constructor

There are two ways to copy one object to the other:

- copy: this is done using copy constructor for example, where the binary footprint on one object is copied byte by byte to the other object. This "deep copy" can be expensive.
- move: when we know that the result of an expression is temporary or intermediate there's no real reason to copy that result when someone outside the scope of the expression is consuming it. e.g. let's say we have a function that returns a vector by value. At the calling location of this function, this vector will ve entirely copied, while the vector returned by the function is destroyed. It would be much more efficient if we could reuse i.e. move this temporary vector that's returned by a function. Move semantics allows for exactly this.
  In order to distinguish between when copy should be used vs when move should be used, compiler needs some way to figure out what is temporary value from an expression and what's lvalue. The overloading that is allowed based on lvalue and r value is exactly what we need to achieve that sort of detection.

- rvalue binding allows for a constructor to detect rvalue arguments and does the right thing behind the scenes. e.g. Let's say we have two object of type T, `obj1` and `obj2`, that can be constructed with an rvalue. e.g. `Integer(3)`. Let's say `obj1` has a pointer that's pointing to some rvalue in memory. When we do `T obj2(obj1)` we call the copy constructor and a shallow copy happens, where pointer in `obj2` might now be left dangling if `obj1` is destroyed behind the scenes.

But with move semantics, we have the possibility of binding based on rvalue or lvale. So we define another copy constructor that accepts rvalue reference. This constructor is called move constructor and the signature is the folowing:

```cpp
// move constructor
T(const T&& x)
```

In this constructor:

- we shallow copy obj1's pointer, so it points to the same value in the memory
- we set obj1's pointer to null pointer

When obj1's destroyed, it's destructor will call delete on null pointer and thus nothing happens to the value at the pointer and we have essentially stolen resource from obj1 and moved to obj2.

The move assignment operator should also do the same.

## Rule of 5 and 0

Some classes own a resource like sockets, file handlers, pointers, etc. that must be deleted, released, etc. when the class is destroyed to prevent leaks. We also need to decide what should happen when such a resource is copied or moved.
To ensure this, when you implement such a class, you should provide the following 5 implementations:

- Destructor
- copy constructor
- copy assignment operator
- move constructor
- move assignment operator ()

When a class does not hold a resource that must be dealt with, compiler generated functions are good enough.

When we provide an implementation for some, but not all of the above functions, we need to be mindful about the fact that providing a custom implementation for a particular function might result in deleting the other. e.g. providing custom copy constructor implementation will delete the compiler provided implementation for move constructor and move assignment operator.

In some cases, we may be able to order a compiler to still go ahead and provide default implementation even though you've provided custom implementation for other function, using `=default` keyword. e.g. Let's say we have a Number class for which we wrote custom copy constructor and that resulted in deletion of compiler provided move assignment operator.

By placing =default qualifier next to the operator overload function below, we're asking compiler to stil generate for us.

```cpp
Number& operator=(Number&& n) = default;
```

Note that the above is still ordered by user and thus considered user defined.

See code/move_semantics for implementation.

## Copy elision

Elision stands for omission. The idea behind copy elision is that the compiler will avoid copy of temporary objects as and when possible.
See code for example.

## std::move function

As we've seen before, when we construct an object of a type from the object of the same type, copy constructor is invoked. i.e.

```cpp
int main(void){
    Integer a(1);
    Integer b{a}; // this will invoke a copy constructor in Integer class
}
```

Copy constructor can get expensive and especially in cases like above, if we have no use of object `a`, it's better to just "move" the data, using move constructor. But because `a` in the above case is an `lvalue`, the call `b(a)` will always bind to copy constructor and not move constructor, even if we provide the move constructor.
So, in such a case, how do we invoke move constructor instea?

One way to invoke move constructor is to cast a to rvalue as such:

```cpp
Integer b{static_cast<Integer&&>(a)}
```
But in the above code, it's not really clear what's going on.

To do the same thing, C++ provides `std::move` function. So, we can write the same thing as below:
```cpp
Integer b{std::move(a)}
```

Note that once the object is moved, we should not read from it, because it's in unspecified state. Maybe because it's probably been manipulated, modified, destroyed and so on by the object to which it was moved.
However, it is possible to reinitialize it. As such the internal implementation of the object itself will have to support reinitialization, by let's say allocating new memory and so on.

std::move is also useful for moving non copyable objects. For example, thred, unique pointer, filestream, etc. 

Also note that std::move doesn't do anything for primitive data types since they do not have any underlying resources.
