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

    // map
    const graph<goal> eventMap;
    const linkedList<goal> goals;

    // register for teams
    linkedList<team> teamRegister;
    linkedList<team> bracketArr[6];

    //register of goals, maps to teams that visit them that visited goals
    dictionary<goal, linkedList<pair<team, timePlaceholder> > > goalRegister;

    public:
    // epic constructor
    rogaineEvent(graph<goal> mapIn, float startIn[2], float endIn[2], linkedList<goal> goalList) : eventMap(mapIn), goals(goalList) {
        // set start and end
        float start[2] = { startIn[0], startIn[1] };
        float end[2] = { endIn[0], endIn[1] };
        std::cout << "start at [" << start[0] << ", " << start[1] << "], end at [" << end[0] << ", " << end[1] << "]\n";
        std::cout << "map: " << eventMap << '\n';
    }

    void addTeamToBracket(team* t, int index);
    linkedList<goal> optimalRoute(int bracket);
    void addTeamToCheckpoint(goal* g, team* t, timePlaceholder time);
};

void rogaineEvent::addTeamToBracket(team* t, int index) {
    bracketArr[index].insertTail(t);
}

// algorithm shit
linkedList<goal> rogaineEvent::optimalRoute(int bracket) {
    linkedList<goal> route;
    return route;
}

void rogaineEvent::addTeamToCheckpoint(goal* g, team* t, timePlaceholder time) {
    pair<team, timePlaceholder> add;
    add.one = t;
    *add.two = time;
    goalRegister.getValue(g).insertTail(add);
}
