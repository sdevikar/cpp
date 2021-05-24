## Lecture 6 part 1

- [Lecture 6 part 1](#lecture-6-part-1)
  - [Finding min and a second min](#finding-min-and-a-second-min)
    - [Run time considerations](#run-time-considerations)
    - [Why can you find a second min with logarithmic number of comparisons but not the first min?](#why-can-you-find-a-second-min-with-logarithmic-number-of-comparisons-but-not-the-first-min)
    - [Space considerations](#space-considerations)
  - [Data structures](#data-structures)
    - [Second min code](#second-min-code)
      - [Combine operation (add_to_counter)](#combine-operation-add_to_counter)
        - [reduce_counter](#reduce_counter)

### Finding min and a second min

We will now discuss a problem where we want to find the first min as usual but we also want to find the second min.

#### Run time considerations

We know that in order to find min, we will need `n-1` comparisons (as discussed in previous lectures).

The idea of finding the second min stems from the player seedings in tennis tournaments. In order for tournament to be fair, it is important that the final game is played between the two strongest players.
At the same time, not everyone can play with everyone. So the games are arranged in a binary tree. See this example:

![Elimination Bracket](images/brackets.png)

Here, the winner had to win 4 matches. i.e. $\lceil ln(n) \rceil$ (ceiling on log base 2 n) matches and beat $\lceil ln(n) \rceil$ players, where n is 16 in this case.
It is also obvious that the seed#2 player had to win $\lceil ln(n)-1 \rceil$ matches and that seed#2 lost ONLY one match and that was against seed#1.

What this means is:

- the winner of the tournament (seed #1 and our min) will not have lost any matches
- the runner up (our second min) will have lost only one match (i.e. the final match) and only against the winner (our min)

So once the winner is decided, we want to find the second winner for the remaining subset i.e. `n-1`.
We know that the winner had to win $\lceil ln(n) \rceil$ matches for n players. So, the runner up will have to now win $\lceil ln(n)-1\rceil$ matches.

Putting all of this together, we need:
`n-1` comparisions to find the min + `ln(n) - 1` comparisons to find the second minimum = total of `n + ln(n) - 2` comparisons.

#### Why can you find a second min with logarithmic number of comparisons but not the first min?

This because we already know an important property that seed#2 loses only 1 game and only against the seed#1

- So, if seed#2 loses only and only 1 game, only seed#2 can make it to the rightmost but one position to matchup with seed#1 for finals
- And this is where the seed#2 will lose to seed#1.

#### Space considerations

There are two steps to this alorithms.

1. Finding the min and we already know how much space we need for it
2. Finding the second min in logarithmic time. As we discussed above, we need history for this. And this history is the part where we could potentially use lots of space. But, observe that we don't technically need to save a lot of history. In the tree above, when we're done comparing two seeds we're ready to go a level to the right and discard the history. In other words, we really only need to store players with the same seed at a time. So, if there's a player who is "knocked out", we don't need to keep him around in the memory.

If we can't do all the comparisons "in-place", a logarithmic storage is acceptable. In practise, the logarithmic storage would not exceed 64.

In order to find second minimum in logarithmic time, we need to transform a linear sequence into a binary tree. It's important to understand that we can do this rearrangement because this group of numbers is associative. i.e. you can regroup them as you wish, but at the end, the result will still be the same. e.g. you can find a min between (1,4) and (3,6) and then between (1,3). Or you can find a min between (1,3) and (4,6) and then between (1,4), the end result will still be the same, i.e. 1.

### Data structures

Let's first discuss what we're going to compare. This is where the concept of parities comes into picture. The idea is that, we want to be comparing (i.e. create a match-up of) numbers of the same level/weight.
The idea is this:

- take array of booleans of length 32 initialized to all 0s at all indexes. The 0 at index m represent that no one has won m number of games. (i.e. 0 at index 5 will mean, nobody has won 5 games)
- take the first number, it has won 0 games so far, so "combine" it with 0th index, propogate the carry, and leave it there for a while
- take the next number. This will have won 0 games as well, so "combine" it with the number at 0th index
- Whoever won the above matchup, will have won 1 game now. And now it should be carry propogated to index 1

In order to put those numbers there, we'd need to figure out how to "combine" these numbers. So, we will need a combine function.

For example, we'll take the sequence [11, 10, 19, 13, 18, 4, 15].
This is an array of size 7. So, we will need a counter of size $\lceil ln(7) \rceil$ = 3

| #   | Value | counter[0] | counter[1] | counter[2] | function returns | comment                             |
| --- | ----- | ---------- | ---------- | ---------- | ---------------- | ----------------------------------- |
| 1   | Init  | 0          | 0          | 0          | -                | counter = 0                         |
| 2   | 11    | 11         | 0          | 0          | 0                | counter = 001 i.e. 00`0+11`         |
| 3   | 10    | 0          | 21         | 0          | 21               | counter = 010 i.e. 0`11+10`0        |
| 4   | 19    | 19         | 21         | 0          | 0                | counter = 011 i.e. 0` 21``0+19 `    |
| 5   | 13    | 0          | 0          | 53         | 53               | counter = 100 i.e. `19+21+13`00     |
| 6   | 18    | 18         | 0          | 53         | 0                | counter = 101 i.e.`53`0`0+18`       |
| 7   | 4     | 0          | 22         | 53         | 22               | counter = 110 i.e. ` 53``18+4 `0    |
| 8   | 15    | 15         | 22         | 53         | 0                | counter = 111 i.e. ` 53``22``0+15 ` |

The above table shows how this counter is implemented using binary carry propogation style.
We have replicated counting up from 000 to 111. In each step, we're

- working in an element from the sequence
- and performing combine operation (for simplicity, we've shown addition) and this is done in such a way that the counter looks like a binary number. This will allow us to represent the number of elements in the sequence that the counter has combined. e.g. `0` `21` `0` looks like `010`, i.e. the second bit set and hence representing the fact that two numbers are combined.

In the above table, if we look at the non zero numbers in the counter[2..1] as 1's, then at each step, we have the number of elements inserted in the counter.
This is because we implemented the combine operation similar to binary addition. i.e. 0+1 =1, 1+1 = 1,0
So, in our case, all we've done is, 11 + 10 = 21,0

Notice that this "binary counter device" automatically makes sure that only the numbers of the same strength (players of the same seed) are combined.
We also don't need the combine operation to be commutitive. i.e. we expect the outcome of `combine(a,b)` to be the same as `combine(b,a)`

#### Second min code

Let's think about the data structure later. Let's start with something very basic i.e. the combine function. What we know about it so far is:

- it is a binary operation (i.e. it operates on two operands)
- it will operate on a data type of the elements in the array (let's call it T)
- it needs to continuously give the feedback to the caller as to whether we were able to put the number in a particular position or not. And we know that the datastructure to keep track of this contains either all 0s or the element of type T who has won x number of matches, where x = index. So return type will be T. To further explain:
  - if there was a zero where we're sticking the element in, we return zero
  - if there was another element where we're going to stick this element in, we return the carry. So, for example in the table above, at row#3, 10 got combined with 11 and the result was 0 with carry 21, so we will return the carry 21

So, below we have

- typename T: This is the datatype of the elements
- typename I: This is for the iterator that iterates over a collection of items of type T
- typename Op: This is the binary operator type itself

##### Combine operation (add_to_counter)

```cpp
// The combine operation

template <typename T, typename I, typename Op>

// requires Op is BinaryOperation(T)
// and Op is associative
// I is forward iterator and ValueType(I) = T

T add_to_counter(I first, I last, Op op, const T &zero, T carry)
{
  // precondition: carry != zero
  while (first != last)
  {
    if(*first == zero)
    {
      *first = carry;
      return zero;
    }
      carry = op(*first, carry);
      *first = zero;
      ++first;
  }

  return carry;
}
```

In the code above:

- the argument `zero` is just some marker of "emptiness". For example, NULL. So that, we can compare the value at a position with it and see if it's empty.
- notice that carry is pass by value - this is because we want to reuse it as an accumulator to same temporary result and therefore need to modify it within the loop. Especially if a variable is going to be modified within a loop, we should keep it as close (within the same stack frame) as possible. Hence, pass by value makes sense in this case. Passing it by reference would've meant that the loop modifies the accumulator which is sitting somewhere else in a different stack frame and thus it'll be slow.
- in the combining operation `op` \*first and carry arguments' order matters because `op` is not a commutitive operation. And we've chosen to pass first as the first argument because it was already to the left of carry (I didn't understand this part)
- we have done `*first=zero` at line 848. This is because in binary operations, 1+1 = 10, i.e. 0 with carry 1. We also want to keep this counter as clean as possible and keep the bit array balanced. Balancing is important because we're trying to fit n elements in log(n) size bit array.

###### reduce_counter

Now that we have an algorithm for adding things to counter, we can start thinking about the higher level algorithm to take things one by one and reduce the counter. The idea here is to be greedy and start reducing the smaller sub-trees into bigger sub trees and kind of merge them together.
Notice that in the table above, the elements that come last are to the left in the binary counter. So, left side is the

In algorithms that involve comparing / combining numbers, we always need to make sure that we combine/compare numbers of equal parity / weight. This is because of the limitations of computers. Smaller quantities tend to get ignored when added to huge numbers, leading to wrong results.
e.g. if we add 0.0000000001 to 10000000 and add 0.0000000002 to another 10000000 and then compare 10000000.0000000001 and 10000000.0000000002, the computer may see them as equal numbers.
Therefore, in reduction algorithms like these, we always want to combine (reduce) smaller numbers first and then work up to bigger numbers.

We also need to think about initializing the counter in a little more detail here. So far, we've called `zero` as a marker of emptiness. i.e. in `add_to_counter` we checked if the element at a particular index is `zero` and if yes, we concluded that that index was empty and we stuck `T` in there. This process assumed that the counter was already initialized. But what if we're dealing with `int` type `T` and our `zero` is same as int 0? Then we won't know the difference.
So, the idea is that we can't initialize our result (i.e. the couter) till we find the first non-zero

```cpp
template <typename T, typename I, typename Op>

// requires Op is BinaryOperation(T)
// and Op is associative
// I is forward iterator and ValueType(I) = T

T reduce_counter(I first, I last, Op op, const T &zero){
  // keep going until we find the first non zero element
  while(first != last && *first == zero){
    ++first;
  }
  //we may have exited the last loop because if first == last
  if(first == last){return zero;}

  // store the first non zero element
  T result = *first;

  // then iterate
  //(now we're iterating from the first non zero element to the end)
  while(++first != last){
    if(*first != zero){
      // update the result
      result = op(*first, result);
    }
  }

  return result;
}
```
