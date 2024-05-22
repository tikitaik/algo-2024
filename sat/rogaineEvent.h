# include <iostream>
# include "adts/linkedlist.h"
# include "adts/graph.h"
# include "adts/traversals.h"
# include "sat/goal.h"
# include "sat/team.h"


class rogaineEvent {

    // start and end have and x coordinate and a y coordinate
    float start[2];
    float end[2];

    // linkedList to keep track of all of the goals, can update the linkedList lib later
    linkedList<goal> goals;    

    // register
    linkedList<teamData> teamRegister;


    public:

    rogaineEvent(float start[2], float end[2]) {
        // set start and end
    }

    void addGoal(float points, float x, float y);
};

void rogaineEvent::addGoal(float points, float x, float y) {
    goal* newGoal = new goal(points, x, y);
    goals.insertTail(newGoal);
}
        // array of tuples of goals;
