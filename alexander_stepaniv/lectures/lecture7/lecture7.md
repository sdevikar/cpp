## Lecture 7

- [Lecture 7](#lecture-7)
  - [The binary_counter class](#the-binary_counter-class)
  - [Using the binary_counter class to find the min element](#using-the-binary_counter-class-to-find-the-min-element)

In lecture 6 part 1 and 2, we wrote two algorithms to add values of type T to a special counter and reduce the counter.
We're going to put these two algorithms into an object now.

### The binary_counter class

- In `alexander_stepaniv/homework/balanced_reduction/test_binary_counter.cpp`, in order to execute `add_to_counter`, we had to iterate over all the values in a for loop and pass the value as an argument to `add_to_counter`. That is, we outsourced the need for maintaining the "state". In order to move this algorithm within an object, we can maintain an internal state.
- The other thing that is not going to change throughout the execution, is the value of zero. So, it can also be "fixed" and internalized
- The operation is also the same throughout the execution, so, that could be fixed as well

We have a choice to use a class or a struct to embed the algorithm into an object. But in this case, since the class should actually have a private state (to iterate over the values), we will use class instead of a struct

```cpp

template <typename T, typename Op>
class binary_counter
{
  private:
    std::vector<T> counter;
    Op op;
    T zero;

  public:
  // contructor
  // order of arguments to the constructor is important
  // because we could potentially "default" the zero to 0 or something
  // e.g. zero is 0 for plus, zero is 1 for multiplication and so on
  binary_counter(const Op& op, const T& zero): op(op), zero(zero){
    counter.reserve(32)
  }

  // no need to return anything
  // return type is void because:
  // return carry was only supposed to happen when the counter runs out of space
  // also no need to pass iterators or op and zero, since they're internal to the class

  void add(T x){
      add_to_counter(counter.begin(), counter.end(), zero, x);
      if(x!=0)  counter.push_back(x);
  }

  T reduce(){
      return reduce_counter(counter.begin(), counter.end(), op, zero);
    }
```

- In passing the arguments to the constructor, there are two conflicting conventions. The standard convention says, that the arguments should be passed by const reference. And the second convention says, the functors (function objects) throughout STL are passed by value (because they're very cheap). In case of such a conflict, always use the more standard and general convention. Hence, the arguments to the constructor are pass by const reference. The reason for general convention of passing by reference is that we do not want to construct before constructing. (because if you pass by value, copy constructor would be invoked.)
- We also used the initializer list for initialization of `op` and `zero`. Doing `op(op)` is better than `op=x` in the constructor code, because `op=x` is equivalent to `op(); op=x;`. So, we're going to save an operation with initializer list.
- We "reserved" memory equivanent to 32 units of type T for counter. We know that the upper bound on the counter size is 64, so we could've reserved just 64 units. But in practise, 32 is enough since 2^64 is a very large number (18.4 exabytes) that we'll probably never go over. Note that `reserve` only allocates memory. But the vector is still size 0

### Using the binary_counter class to find the min element

Now we're going to use the binary_couter class to find the min element. Note that we've already written `min_element` in [this section] (###-find-minimum-element-from-a-range), where the `min_element` function took two iterators to the collection (i.e. begin and end) and returned an iterator pointing to the minimum element in that collection. We want to do the same thing with the `binary_counter`.
So, let's see what we know so far:
- We'd have a collection, let's say an array.
- Our goal is to define a function that accepts the beginning (first) and the end (last) of this collection and returns the position of the min element. 
  - So, we know that this function will take the iterator pointers (first, last). 
  - Since this function will use `binary_counter` class, it needs to know for sure, how to construct `binary_counter`. Which means it needs to know what `op` is and what `zero` is. Note that since we're reusing `min_element` signature here, `Operation` is called `Compare` instead. But it is a combine operation regardless.
  - a good `zero` is just last, because it's just a marker of emptiness. So, we don't really need to pass `zero` to this function explicitly. So, the function signature would look like this:
```cpp
template <typename I, typename Compare>
// requires I is a ForwardIterator
// and Compare is a StrictWeakOrdering on ValueType(I)
I min_element_binary(I first, I last, Compare cmp) 
```
- We'll construct the `binary_counter` class with begin and end iterator and find min element in "binary way". What do we need to know to construct the class?
  - The class is templatized. So, we need to know the type T and the typename op.
  - Notice that typename `op` is a type. i.e. not a function pointer or something like that. So, we'd have to create and specify an actual type or an object for template substitution. And since the class constructor needs an `op` argument, we'll also have to construct it. Let's call that type as `min_op`
- What should `min_op` do? It should look at two positions in a collection (using iterator) and return an iterator position that's minimum of the two. The reason why we're only dealing with the iterators and not values is because this way 
  - we don't need to pass around the entire collection
  - when the function returns, we'll know where in the collection the element is and do whatever we want with it
- Also notice that when we call `min_element_binary`, we already pass `Compare cmp`. But this is a standard compare functor like `std::less`. We need to write a wrapper around it because we want to wotk with the collection and compare the elements pointed to by iterators. `std::less` can only be templatized on the datatype `T`. We need to be able to templatize on iterator type `I` as well. `min_op` will eventually call `std::less` after it dereferences the stuff pointed to by iterators.

```cpp
// - compares two iterators and returns the one
//   pointing to the smallest element
template <typename Compare>
class min_op 
{
private:
  Compare cmp;
public:
  min_op(const Compare& cmp) : cmp(cmp) {}
  template <typename I>
  I operator()(const I& x, const I& y) {
    return cmp(*y, *x) ? y : x;
  }
};

```

In the above code:
- notice that the `min_op` class is parameterized for `Compare` type only and within the class `()` operator is templatized with iterator type `I`. This allows us to do something like `min_op<Compare>`, without worrying about iterator type just yet. Later when its time to use min_op `()` operator, we do `carry = op(*first, carry);` (see `add_to_counter` function) and the code is generated for `min_op` based on the type `I` passed to `add_to_counter`
    
