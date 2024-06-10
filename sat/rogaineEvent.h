# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/graph.h"
# include "adts/pair.h"
# include "time/time.h"
# include "sat/goal.h"
# include "sat/team.h"
# include "sat/bestRoute.h"
# include "sat/mapToGraph.h"


class rogaineEvent {

    // start and end can be represented as checkpoints with no reward 
    const node<goal>* startNode;
    const node<goal>* endNode;

    // time related vars
    const timePlaceholder timeLimit;
    const float walkSpeed;

    // map
    const graph<goal> eventMap;
    const linkedList<node<goal> > goals;

    // register for teams
    linkedList<team> teamRegister;
    linkedList<team> bracketArr[6];

    //register of goals, maps to teams that visit them that visited goals
    dictionary<goal, linkedList<pair<team, timePlaceholder> > > goalRegister;

    public:
    // epic constructor
    rogaineEvent(graph<goal> mapIn, linkedList<node<goal> > goalList, node<goal>* start, node<goal>* end, timePlaceholder timeIn, float speed) : eventMap(mapIn), goals(goalList), startNode(start), endNode(end), timeLimit(timeIn), walkSpeed(speed) {

    }

    void addTeamToBracket(team* t, int index);
    linkedList<node<goal> > optimalRoute(int bracket);
    void addTeamToCheckpoint(goal* g, team* t, timePlaceholder time);
};

void rogaineEvent::addTeamToBracket(team* t, int index) {
    bracketArr[index].insertTail(t);
}

// algorithm shit
linkedList<node<goal> > rogaineEvent::optimalRoute(int bracket) {
    // if 2.7% is linear: time will eventually reach 0
    //return bestRoute(eventMap, startNode, endNode, timeLimit * (1 + 0.27 * (5 - bracket), walkSpeed);
    // if 2.7% is 2.7% of the previous bracket: doesnt ever get to 0
    return bestRoute(eventMap, startNode, endNode, timeLimit.time * pow(1.027, 5 - bracket), walkSpeed);
}

void rogaineEvent::addTeamToCheckpoint(goal* g, team* t, timePlaceholder time) {
    pair<team, timePlaceholder> add;
    add.one = t;
    *add.two = time;
    goalRegister.getValue(g).insertTail(add);
}
