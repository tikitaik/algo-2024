# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/pair.h"

class checkpoint {
    public:
        pair<int, int> coords;
        int points;

        checkpoint () {};
        checkpoint (int xCoord, int yCoord, int pointsReward)  : coords(pair<int, int>(xCoord, yCoord)), points(pointsReward)  {

            //std::cout << coords << ", " << points << '\n';
        }

        pair<int, int> getCoordinates();
        int getPoints();
};

pair<int, int> checkpoint::getCoordinates() {
    return coords;
}

int checkpoint::getPoints() {
    return points;
}

bool operator == (const checkpoint g1, const checkpoint g2) {
    if (g1.points == g2.points && g1.coords == g2.coords) {
        return true;
    }
    else {
        return false;
    }
}

std::ostream& operator << (std::ostream& os, const checkpoint g) {
    os << g.coords << ", " << g.points;
    return os;
}
