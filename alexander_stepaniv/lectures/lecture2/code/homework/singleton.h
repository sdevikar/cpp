#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>

struct singleton
{
    T value;

    // semiregular

    // default constructor
    singleton() {}

    // destructor
    ~singleton() {}

    // copy constructor
    singleton(const singleton &x) : value(x.value) {}

    // assignment operator
    singleton &operator=(const singleton &x)
    {
        value = x.value;
        return *this;
    }

    // regular

    // equality
    friend bool operator==(const singleton &x, const singleton &y)
    {
        return x.value == y.value;
    }

    friend bool operator!=(const singleton &x, const singleton &y)
    {
        return !(x == y);
    }

    // totally ordered

    friend bool operator<(const singleton &x, const singleton &y)
    {
        return x.value < y.value;
    }

    friend bool operator>(const singleton &x, const singleton &y)
    {
        return (y < x);
    }

    friend bool operator<=(const singleton &x, const singleton &y)
    {
        return !(y < x);
    }

    friend bool operator>=(const singleton &x, const singleton &y)
    {
        return !(x < y);
    }

    // conversions (from T to singleton<T> and vice versa)

    // conversion from T to singleton<T>
    // we define this constructor to be explicit, because we want users to call the constructor explicitly
    // as opposed to it being implicitly called by the compiler
    // i.e. to prevent the following from working
    // singleton<int> x = 3;
    // instead, we want it to be called as singleton<int>(3)
    explicit singleton(const T &x) : value(x){}

    // conversion from singleton<T> to T
    // here operator T() is a special operator definition function which will allow for something like:
    // singleton<int> x{3}; int y = int(x);
    // note that, because the operator is defined as explicit, this doesn't work:
    // singleton<int> x{3}; int y = x;

    explicit operator T() const { return value;}

    // it is also possible to have an templated copy constructor
    // i.e. which takes a singleton templated on another type.
    template <typename U>
    singleton(const singleton<U> &x) : value(x.value) {}
    // of course, this requires U to be convertible to T
    
};
#endif // SINGLETON_H