# Efficient Programming in C++
These notes are written with reference to video lectures here:
[YouTube](https://www.youtube.com/watch?v=aIHAEYyoTUc&list=PLHxtyCq_WDLXryyw91lahwdtpZsmo4BGD)

## Introduction lecture Part1:
- Always use the simplest data structure possible. In C++, **USE VECTORS!** if you can. If you can't use vectors, figure out a way to **USE VECTORS**
- An example discussed in the class discusses why using a combination of ```std::sort``` and ```std::unique``` for finding number of unique elements in an array is better than using a ```set```. (The reason is that set is designed to efficiently handle the constant growing and shrinking i.e. insertions and removals. And if you have a big list of elements, constructing a set itself will take a lot of time and we will never be able to reap the benefits of using a set, because we're not really going to insert and remove from the set multiple times)


## Introduction lecture Part2:
- When we write some code, it is essential to determine how efficient it is. There is no need to ALWAYS go into big O analysis. Instead, there are some things we can do to benchmark the code performance, WITHOUT modifying the original code at all.
- Semiregular types: These are the datatypes that provide only constructor, destructor and assignment.
- Totally ordered types: Like Semiregular, but also supports equality and maybe non-equality too (i.e. == and !=)
- So, what kind of operations do we really need to count? The answer is - whatever operations a regular datatype may reasonably support. Regular datatype being, a datatype that is expected to behave like a built-in datatype, like ```int``` for example. For instance, when you construct a vector of ```int```s, the vector itself can be expected to support reasonable operations that ```int``` may support. So, these operations are:
  - copy: For example, copy constructor, stuff like vector a = b  
  - assign: For example, we have T a, and T b, and we do a = b (i.e. assigning one already constructed object to other)
  - default: Default constructor  for example, T a;
  - destruct: as the name says, destructor
  - equal: For example, a == b. Note that the measure of equality is different for different types.
  - compare



## Lecture 2
Intro lecture ended on a note that the goal for the entire class is to write identical code for the same problem. Subtle conventions are necessary to achieve this. For example, when to capitalize something, when to use what alternative, even though the two alternatives are synonyms etc. Following are the examples discussed at the beginning of lecture:
- when we use template and do something like ```template<typename T>``` or ```template<class T>```, although the two declarations mean the same, one is indicative that the template parameter is an actual class, vs probably a primitive datatype. Also, pay attention to capitalized T. Capitalization is convention here.
- Use of struct vs class: We know that the difference between two in cpp is just the default scope of class members. i.e. in struct, class members are public by default. But there is a deeper reason behind when to use what.
- Public vs Private: Discussed that the common understanding that class properties should ALWAYS be private is BS. Private is only requires when "invariance" is important. Meaning that, you actively want to prevent someone or something from writing anything to that class property.  
