# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/pair.h"

class checkpoint {
    public:
        const pair<float, float> coords;
        const int points;

        checkpoint (float xCoord, float yCoord, int pointsReward)  : coords(pair<float, float>(xCoord, yCoord)), points(pointsReward)  {

            std::cout << coords << ", " << points << '\n';
        }

        pair<float, float> getCoordinates();
        int getPoints();
};

pair<float, float> checkpoint::getCoordinates() {
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
