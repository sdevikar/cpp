# Lecture 5 part 1

- [Lecture 5 part 1](#lecture-5-part-1)
  - [More on the min function](#more-on-the-min-function)
  - [Function call vs Functors](#function-call-vs-functors)
  - [the max function](#the-max-function)
  - [Find minimum element from a range](#find-minimum-element-from-a-range)
- [Lecture 5 part 2](#lecture-5-part-2)
  - [minmax element algorithm](#minmax-element-algorithm)


## More on the min function

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

## Function call vs Functors

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

## the max function

We could write the max function the same way as we wrote the min function. i.e. using the Comparator functor.
However, let's dig a little deeper. The idea is that the min, max and sort should work in harmony.
Let's explore how we would write a sort function to sort two items. This sort function will simply swap the items if they're out of order, so `a` always has the min value and `b` has the "max" value

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

## Find minimum element from a range

So far we have written a min program that operates on two elements. Let's expand on this and write a min program that returns minimum element from a range. This range could be a vector, for example.
For reference, see the `std::min_element` function.

- What should this function take as an input?

  - It should take a "range". The range implies a begining and an end
  - Therefore, the function should take the begin and the end of an iterator

- What should this function return?
  - We could return the element itself. But if we do that, we will only know what the element is. That means:
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

# Lecture 5 part 2

## minmax element algorithm

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
