# pragma once

# include <iostream>

template <typename T, typename U> struct pair {

public:
    T* one;
    U* two;
    
    pair () {};
    pair (T* oneIn, U* twoIn) {
        one = oneIn;
        two = twoIn;
    }
    pair (T* oneIn, U twoIn) {
        one = oneIn;
        two = new U;
        *two = twoIn;
    }

    pair (T oneIn, U twoIn) {
        one = new T;
        *one = oneIn;
        two = new U;
        *two = twoIn;
    }

    template <typename V, typename W> friend std::ostream& operator << (std::ostream& os, const pair<V, W> p);
};

template <typename T, typename U> bool operator == (const pair<T, U> p1, const pair<T, U> p2) {
    if (p1.one == p2.one && p2.two == p2.two) {
        return true;
    }
    else {
        return false;
    }
}

template <typename V, typename W> std::ostream& operator << (std::ostream& os, const pair<V, W> p) {
    if (p.one && p.two) {
        os << "[" << *p.one << ", " << *p.two << "]";
    }
    else {
        os << "one of the elements is null!\n";
    }

    return os;
}
