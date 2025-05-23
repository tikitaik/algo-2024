// this will have to do for now
# pragma once

# include <iostream>

class timePlaceholder {
    public:
        // time in deciseconds (uint has enough for 4971 days of saving)
        unsigned int time;

    public:
        
    friend std::ostream& operator << (std::ostream& os, const timePlaceholder tm); 
};

std::ostream& operator << (std::ostream& os, const timePlaceholder tm) {
    unsigned int t = tm.time;
    // deciseconds
    os << "deciseconds: " << t % 10 << ", ";
    t = t - (t % 10);
    t = t / 10;
    os << "seconds: " << t % 60 << ", ";
    t = t - (t % 60);
    t = t / 60;
    os << "minutes: " << t % 60 << ", ";
    t = t - (t % 60);
    t = t / 60;
    os << "hours: " << t;

    return os;
}

timePlaceholder getCurrentTime() {
    timePlaceholder t;
    t.time = 69696969;
    return t;
}
