# pragma once

# include <iostream>
# include "linkedlist.h"

class goal {
    public:
        const int points;
        const float x;
        const float y;
        // linkedList of teams that visited this goal

        goal (int points, float xCoord, float yCoord) : points(pointReward), x(xCoord), y(yCoord) {
            std::cout << "goal initialised !\n";
        }
};
