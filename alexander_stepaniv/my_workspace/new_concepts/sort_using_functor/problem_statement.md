# Problem statement

## Problem

We have a list of a non standard datatype, let's call it `Complex`.
We want to sort this list.
We intend to use the `std::sort` for sorting in this case.

## Analysis

Since `Complex` is a custom datatype, the sort algorithm needs some help in determining how to compare the two `Complex` objects.

There are two possible signatures of `std::sort` that we could be using:

1. `void sort(RandomIt first, RandomIt last)`
2. `void sort( RandomIt first, RandomIt last, Compare comp )`

The first signature assumes that the object that is being sorted defines `std::less`
For the second signature, we actually have to pass an **object** that does the comparison.

## Solution

Let's use the second approach in this case, to reinforce the learning in lecture 5 part 1.
Also note that, since the Complex class may very well be templated, second approach is better than the first one.
Because for a templated class, you can't really define less than operator for every possible datatype.
