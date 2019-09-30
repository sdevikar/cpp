
#include <cstddef>

class instrumented_base
{

public:
  enum operations {
    n, copy, assignment, destructor, default_constructor, equality, comparison, construction
  };
  static const size_t number_ops = 8;
  static double counts[number_ops];
  static const char* counter_names[number_ops];
  static void initialize(size_t);
};



template <typename T>
class instrumented : public instrumented_base
{
private:
    /* data */
public:
  typedef T value_type;
  T value;

  // operation = copy
  // notice that a copy constructor will only take a value of type instrumented
  // as its argument
  // notice that we have also used initializer here instead of assignment
  // i.e. we did value(x.value) instead of doing value = x.value
  instrumented(const instrumented& x): value(x.value){
    // increment counter here
    counts[++operations::copy];
  }
  
  // operation = assignment
  // this is an assignment operation. So, the value of x has to be 
  // actually assigned to value
  instrumented& operator=(const instrumented& x){
    // increment counter here
    value = x.value;
    counts[++operations::assignment];
    return *this;
  }

  // operation = destructor
  ~instrumented(){
    // increment counter here
    counts[++operations::destructor];

  }

  // operation = default_constructor
  instrumented(){
    // increment counter here
    counts[++operations::default_constructor];
  }


  // the following are binary operations, so there are going to be two arguments
  // these functions also have to be a friend function - 
  // because it requires comparing the private members of the class
   
  // operation = equality
  bool operator==(const instrumented& x, const instrumented& y){
    // increment counter here
    counts[++operations::equality];
    return x.value == y.value;
  }

  bool operator!=(const instrumented&){
  // increment counter here
  // x!=y is same as !(x==y)
  return !(x==y);
}

  // operation = comparison
  friend
  bool operator<(const instrumented& x, const instrumented& y){
    // increment counter here
    counts[++operations::comparison];
    return x.value < y.value;
  }

  friend
  bool operator>(onst instrumented& x, const instrumented& y){
    // increment counter here
    // x > y can also be interpreted as y < x
    return y < x; // avoided increment operation here by using 
  }
  
  friend
  bool operator<=(onst instrumented& x, const instrumented& y){
    // increment counter here 
    // x<=y means !y>x
    return !(y > x)
  }

  friend
  bool operator>=(const instrumented& x, const instrumented& y){
    // increment counter here
    // x >= y means !(x < y)
    return !(x < y);
  }  

  // operation = construction
  // this is defined as explicit to prevent anyone from implicitly invoking this
  // meaning, you can't invoke this constructor using assignment operator or something like that
  explicit instrumented(const T& x) : value(x) { ++counts[construction]; }


  //
};