# pragma once

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

    // register for teams
    linkedList<team> teamRegister;
    linkedList<team> bracketArr[6];

    //register of goals, maps to teams that visit them that visited goals
    dictionary<goal, linkedList<pair<team, int> > > goalRegister;

    public:

    rogaineEvent(float start[2], float end[2]) {
        // set start and end
    }

    void addGoal(float x, float y, int points);
};

void rogaineEvent::addGoal(float x, float y, int points) {
    goal* newGoal = new goal(points, x, y);
    linkedList<pair<team, int> >* visitedTeams = new linkedList<pair<team, int> >;
    goalRegister.insert(newGoal, visitedTeams);
}
