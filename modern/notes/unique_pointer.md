# Unique Pointer

Refresher:

A smart pointer is a class that manages a dynamically allocated object. Although smart pointers can offer other features, the defining characteristic of a smart pointer is that it manages a dynamically allocated resource, and ensures the dynamically allocated object is properly cleaned up at the appropriate time (usually when the smart pointer goes out of scope).
Since smart pointers in turn manage dynamically allocated objects, we always want to make sure that the smart pointers aren't dynamically allocated themselves, so that they themselves don't run the risk of not being deleted and thus also not deleting the resources they hold

## std::unique_ptr

std::unique_ptr is the C++11 replacement for std::auto_ptr. It should be used to manage any dynamically allocated object that is not shared by multiple objects. That is, std::unique_ptr should completely own the object it manages, not share that ownership with other classes. std::unique_ptr lives in the <memory> header.
The difference between std::auto_ptr and std::unique_ptr is that the unique pointer implements move semantics properly, as opposed to auto pointer. Because std::unique_ptr is designed with move semantics in mind, copy initialization and copy assignment are disabled. So, the following code works as expected

```cpp

#include <iostream>
#include <memory> // for std::unique_ptr
#include <utility> // for std::move

class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
    std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
    std::unique_ptr<Resource> res2{}; // Start as nullptr

    std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n"); // this will print not null
    std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n"); // this will print null

    // res2 = res1; // Won't compile: copy assignment is disabled
    res2 = std::move(res1); // res2 assumes ownership, res1 is set to null

    std::cout << "Ownership transferred\n";

    std::cout << "res1 is " << (static_cast<bool>(res1) ? "not null\n" : "null\n"); // this will print null
    std::cout << "res2 is " << (static_cast<bool>(res2) ? "not null\n" : "null\n"); // this will print not null

    return 0;
} // Resource destroyed here when res2 goes out of scope
```

As we can see in the above code, `std::move` is now required to move res1 to res2. This eliminates the possibility of the shallow copy of underlying resource that was possible with auto pointer.

## Empty unique_ptr

As in the above code, we could do `std::unique_ptr<Resource> res2{};` i.e. we created a unique pointer without an underlying resource to manage. The invocation like this calls the default constructor, which sets the shared resource to `nullptr`.
We can check if the unique pointer is managing any resource simply by if statement. This is possible because unique pointer has an implicit cast to `bool` implemented.

```cpp

std::unique_ptr<Resource> res1{ new Resource{} }; // Resource created here
std::unique_ptr<Resource> res2{}; // Start as nullptr

if(res1){
    // this will be printed
    std::cout << "I am holding a resource" << std::endl;
}
if(res2){
    // this will NOT be printed
    std::cout << "I am holding a resource" << std::endl;
}
```

## Accessing the managed resource

`std::unique_ptr` has implementation for the `->` and `*` operators. As you'd expect:

- `*` returns the the reference to the shared resource
- `->` returns the pointer to shared resource

```cpp
std::unique_ptr<Resource> res{ new Resource{} };

if (res) // use implicit cast to bool to ensure res contains a Resource
    std::cout << *res << '\n'; // print the Resource that res is owning

```
