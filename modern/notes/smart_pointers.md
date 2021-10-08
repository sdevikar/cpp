# Smart pointers

In C++, we need to explicitly free the dynamically allocated memory. i.e. anything assigned with `new`, must be explicitly `free`d. But sometimes because of exceptions, early returns, etc. the memory may not be freed and we end up with a memory leak.

Consider the following example:

```cpp
#include <iostream>

void someFunction()
{
    Resource *ptr = new Resource();

    int x;
    std::cout << "Enter an integer: ";
    std::cin >> x;

    if (x == 0)
        return; // the function returns early, and ptr won’t be deleted!

    // do stuff with ptr here

    delete ptr;
}
```

Here, the delete will not execute if x = 0 and there will be a memory leak.

The classes have a destructor that gets called automatically when they go out of scope. This is the idea behind smart pointers. We can wrap a pointer inside a class and when the class goes out of scope, delete the pointer. This is also known as the RAII (Resource Acquisition is Initialization)
