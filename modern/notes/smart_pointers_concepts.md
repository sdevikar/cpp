# Smart pointers

Notes from [learncpp.com tutorial](https://www.learncpp.com/cpp-tutorial/intro-to-smart-pointers-move-semantics/)

## Introduction

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

The classes have a destructor that gets called automatically when they go out of scope. This is the idea behind smart pointers. We can wrap a pointer inside a class and when the class goes out of scope, delete the pointer. This is also known as the _RAII (Resource Acquisition is Initialization)_

## First attempt

The code for the smart pointer discussed above could look like this:

```cpp

#include <iostream>

template<class T>
class Auto_ptr1
{
	T* m_ptr;
public:
	// Pass in a pointer to "own" via the constructor
	Auto_ptr1(T* ptr=nullptr)
		:m_ptr(ptr)
	{
	}

	// The destructor will make sure it gets deallocated
	~Auto_ptr1()
	{
		delete m_ptr;
	}

	// Overload dereference and operator-> so we can use Auto_ptr1 like m_ptr.
	T& operator*() const { return *m_ptr; }
	T* operator->() const { return m_ptr; }
};

// A sample class to prove the above works
class Resource
{
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource destroyed\n"; }
};

int main()
{
	Auto_ptr1<Resource> res(new Resource()); // Note the allocation of memory here

        // ... but no explicit delete needed

	// Also note that the Resource in angled braces doesn't need a * symbol, since that's supplied by the template

	return 0;
} // res goes out of scope here, and destroys the allocated Resource for us

```

Here, the `Auto_ptr1` is the smart pointer that wraps the `Resource`. Notice above that:

- `m_ptr` points to the instance of `Resource`
- `m_ptr` is deleted when the destructor of `Auto_ptr1` is called
- `dereference` and `->` operators are overloaded to operate of the `m_ptr`

This should work because no matter what, the destructor of `m_ptr` will always be called and there's no way for others to access the instance of resource that was passed to the `Auto_ptr1`, so nobody can invalidate it.

## Problems with the first attempt

At the end of the day, the `Auto_ptr1` holds something that points to something. And we know that the compiler generated copy and assign constructors only do a shallow copy of things. That means, if we made `Auto_ptr2 = Auto_ptr1`, it'll also hold a pointer to `Resource` and we no longer have a single owner of the `Resource`.

Consider the following program:

```cpp
int main()
{
	Auto_ptr1<Resource> res1(new Resource());
	Auto_ptr1<Resource> res2(res1); // Alternatively, don't initialize res2 and then assign res2 = res1;

	return 0;
}
```

Here, the sequence of operation is: 1. constructor of `Auto_ptr1` is called 2. copy constructor of `Auto_ptr2` is called - at this point, a shallow copy will happen 3. destructor of `Auto_ptr2` and `Auto_ptr1` is called.
Since both destructors call the delete on the same pointer, the program will crash.

We could mark the assignment operator and copy constructor for deletion, that way compiler won't generate them and `Auto_ptr1<Resource> res2(res1)` won't work unless explicitly defined. Just deleting and preventing assignment and copy is not a good idea because we won't be able to return the `Auto_ptr1` from a function, for example. i.e. the following won't work.

```cpp

<typename T>
Auto_ptr1& make_ptr()
{
     T* r{ new T() };
     return Auto_ptr1(r);
}

// this won't work because we'd have told compiler to not generate assignment operator code
Auto_ptr1 smartptr = make_ptr<Resource>(); // notice the assignment here
```

As mentioned earlier, we can always define the assignment and copy operators and do a deep copy of `Resource` but it's a bad idea for two reasons:

- copying can be expensive and may not be desirable or even possible (e.g. how would you deep copy an arbitrary type T)
- assigning or initializing a dumb pointer doesn’t copy the object being pointed to and there's no reason smart pointer should do that either.

## Using move semantics instead of copy semantics

The core idea behind smart pointers is the single ownership of a resource. So, in reality assignment and copy operations discussed above should actually transfer ownership as opposed to inadvertently sharing it. This is where the move semantics will help. Here's how we will implement copy and assignment operator using move semantics instead.

```cpp
// A copy constructor that implements move semantics
Auto_ptr2(Auto_ptr2& a) // note: not const
{
    m_ptr = a.m_ptr; // transfer our dumb pointer from the source to our local object
    a.m_ptr = nullptr; // make sure the source no longer owns the pointer
}

// An assignment operator that implements move semantics
Auto_ptr2& operator=(Auto_ptr2& a) // note: not const
{
    if (&a == this)
        return *this;

    delete m_ptr; // make sure we deallocate any pointer the destination is already holding first
    m_ptr = a.m_ptr; // then transfer our dumb pointer from the source to the local object
    a.m_ptr = nullptr; // make sure the source no longer owns the pointer
    return *this;
}
```

In the above code, the takeway is that the pointer to the resource owned by the input arg `a` gets invalidated after the pointer itself got copied to the new owner.

## c++ auto_ptr

The above move semantics implementation is what the C++ std::auto_ptr (in C++98, 11 & 14) once did, until it got discontinued in C++17. The above implementation has a number of problems on its own. e.g.

- notice we passed `Auto_ptr2& a` to both copy constructor and =operator. This `a` got modified within those functions and `a.m_ptr` was set to null. Now, if you try to access the argument you passed at the calling location, there would be a crash because `a.m_ptr` is now null.
- auto_ptr also does a simple delete in its destructor. If the `Resource` is an array type, that deletion won't work.
- auto_ptr will also not work for a lot of standard library containers and algorithms, because those standard library classes assume that when they copy an item, it actually makes a copy, not a move

C++11 standard library ships with 4 smart pointer classes:

- std::auto_ptr (as discussed above, you shouldn’t use it and it’s being removed in C++17)
- std::unique_ptr
- std::shared_ptr, and
- std::weak_ptr

Let's see [Unique Pointer](unique_pointer.md) next, which is the most widely used smart pointer.
