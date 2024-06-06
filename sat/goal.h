# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/pair.h"

struct goal {
    public:
        const float x;
        const float y;
        const int points;

        goal (float xCoord, float yCoord, int pointsReward)  : x(xCoord), y(yCoord), points(pointsReward)  {
            std::cout << "goal initialised: [" << x << ", " << y <<  "], reward: " << points << '\n';
        }
};

bool operator == (const goal g1, const goal g2) {
    if (g1.points == g2.points && g1.x == g2.x && g1.y == g2.y) {
        return true;
    }
    else {
        return false;
    }
}
