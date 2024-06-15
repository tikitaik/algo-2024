# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/graph.h"
# include "adts/pair.h"
# include "time/time.h"
# include "sat/checkpoint.h"
# include "sat/team.h"
# include "sat/bestRoute.h"
# include "sat/mapToGraph.h"


class rogaineEvent {

    // start and end can be represented as checkpoints with no reward 
    const node<checkpoint>* startNode;
    const node<checkpoint>* endNode;

    // time related vars
    const timePlaceholder timeLimit;
    const float walkSpeed;

    // map
    const graph<checkpoint> eventMap;
    const linkedList<node<checkpoint> > checkpoints;

    // register for teams
    linkedList<team> teamRegister;
    linkedList<team> bracketArr[6];

    //register of checkpoints, maps to teams that visit them that visited checkpoints
    dictionary<checkpoint, linkedList<pair<team, timePlaceholder> > > checkpointRegister;

    public:
    // epic constructor
    rogaineEvent(graph<checkpoint> mapIn, linkedList<node<checkpoint> > checkpointList, node<checkpoint>* start, node<checkpoint>* end, timePlaceholder timeIn, float speed) : eventMap(mapIn), checkpoints(checkpointList), startNode(start), endNode(end), timeLimit(timeIn), walkSpeed(speed) {

    }

    void addTeamToBracket(team* t, int index);
    linkedList<node<checkpoint> > optimalRoute(int bracket);
    void addTeamToCheckpoint(checkpoint* g, team* t, timePlaceholder time);
};

void rogaineEvent::addTeamToBracket(team* t, int index) {
    bracketArr[index].insertTail(t);
}

// algorithm shit
linkedList<node<checkpoint> > rogaineEvent::optimalRoute(int bracket) {
    // if 2.7% is linear: time will eventually reach 0
    //return bestRoute(eventMap, startNode, endNode, timeLimit * (1 + 0.27 * (5 - bracket), walkSpeed);
    // if 2.7% is 2.7% of the previous bracket: doesnt ever get to 0
}

void rogaineEvent::addTeamToCheckpoint(checkpoint* g, team* t, timePlaceholder time) {
    pair<team, timePlaceholder> add;
    add.one = t;
    *add.two = time;
    checkpointRegister.getValue(g).insertTail(add);
}
