# include <iostream>
# include "adts/linkedlist.h"
# include "adts/graph.h"
# include "adts/traversals.h"

class goal {
    public:
        const int points;
        const float x;
        const float y;
        // linkeList of teams that visited this goal

        goal (int points, float xCoord, float yCoord) : points(pointReward), x(xCoord), y(yCoord) {
            std::cout << "goal initialised !\n";
        }
};

class rogaineEvent {

    // start and end have and x coordinate and a y coordinate
    float start[2];
    float end[2];

    // linkedList to keep track of all of the goals, can update the linkedList lib later
    linkedList<linkedList<float> > goals;    

    // register
    linkedList<teamData>
    public:

    rogaineEvent(float start[2], float end[2]) {
        // set start and end
    }

    void addGoal(float points, float x, float y);
};

void rogaineEvent::addGoal(float points, float x, float y) {
    linkedList<float> goal;
    goal.insertTail(points);
    goal.insertTail(x);
    goal.insertTail(y);

    goals.insertTail(goal);
}
