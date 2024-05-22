# pragma once

# include <iostream>

template <typename T, typename U> struct pair {

protected :
    T* one;
    U* two;
    
public:
    pair () {};
    pair (T* oneIn, U* twoIn) {
        one = oneIn;
        two = twoIn;
    }

    pair (T oneIn, U twoIn) {
        one = new T;
        *one = oneIn;
        two = new U;
        *two = twoIn;
    }

    template <typename V, typename W> friend std::ostream& operator << (std::ostream& os, const pair<V, W> p);
};

template <typename V, typename W> std::ostream& operator << (std::ostream& os, const pair<V, W> p) {
    if (p.one && p.two) {
        os << "one: " << *p.one << ", two: " << *p.two;
    }
    else {
        os << "one or two is null!\n";
    }

    return os;
}




template <typename... types> struct tuple {

};
