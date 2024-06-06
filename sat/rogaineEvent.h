# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/pair.h"
# include "adts/graph.h"
# include "adts/traversals.h"
# include "time/time.h"
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
    dictionary<goal, linkedList<pair<team, timePlaceholder> > > goalRegister;

    public:
    // epic constructor
    rogaineEvent(float startIn[2], float endIn[2]) {
        // set start and end
        float start[2] = { startIn[0], startIn[1] };
        float end[2] = { endIn[0], endIn[1] };
        std::cout << "start at [" << start[0] << ", " << start[1] << "], end at [" << end[0] << ", " << end[1] << "]\n";
    }

    void addGoal(float x, float y, int points);
};

void rogaineEvent::addGoal(float x, float y, int points) {
    goal* newGoal = new goal(x, y, points);
    linkedList<pair<team, timePlaceholder> >* visitedTeams = new linkedList<pair<team, timePlaceholder> >;
    goalRegister.insert(newGoal, visitedTeams);
}
