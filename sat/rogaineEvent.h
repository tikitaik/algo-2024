# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/graph.h"
# include "adts/pair.h"
# include "time/time.h"
# include "sat/checkpoint.h"
# include "sat/team.h"
# include "sat/graphConstructor.h"


class rogaineEvent {

    // start and end can be represented as checkpoints with no reward 
    const node<checkpoint>* startNode;
    const node<checkpoint>* endNode;

    // time related vars
    const int timeLimit;
    const float walkSpeed;

    // map
    graph<checkpoint> eventMap;
    const linkedList<node<checkpoint> > checkpoints;

    // register for teams
    linkedList<team> teamRegister;
    linkedList<team> bracketArr[6];

    //register of checkpoints, maps to teams that visit them that visited checkpoints
    dictionary<checkpoint, linkedList<pair<team, timePlaceholder> > > checkpointRegister;

    public:
    // epic constructor
    rogaineEvent(graph<checkpoint> mapIn, linkedList<node<checkpoint> > checkpointList, node<checkpoint>* start, node<checkpoint>* end, int timeIn, float speed) : eventMap(mapIn), checkpoints(checkpointList), startNode(start), endNode(end), timeLimit(timeIn), walkSpeed(speed) {}

    void addTeamToBracket(team& t, int index);
    void addTeamToCheckpoint(checkpoint* g, team* t, timePlaceholder time);
    float desirability(node<checkpoint>* currentNode, int depth);
    linkedList<node<checkpoint> > optimalRoute(int bracket);
};

void rogaineEvent::addTeamToBracket(team& t, int index) {
    bracketArr[index].insertTail(t);
}

void rogaineEvent::addTeamToCheckpoint(checkpoint* check, team* t, timePlaceholder time) {
    pair<team, timePlaceholder> add;
    add.one = t;
    *add.two = time;
    checkpointRegister.getValue(check).insertTail(add);
}

float rogaineEvent::desirability(node<checkpoint>* currentNode, int depth) {
    // base case
    if (depth == 1) {
        float des = 0;
        linkedList<node<checkpoint> >* nodeNeighbours = eventMap.neighbours(currentNode, true);
        listNode<node<checkpoint> >* walk = nodeNeighbours->returnHead();

        for (int i = 0 ; i < nodeNeighbours->size(); i++) {
            des += walk->data->attribute->points / eventMap.searchEdge(currentNode->id, walk->data->id)->weight;
            
            if (walk->next) {
                walk = walk->next;
            }
        }

        return des;
    }
    else {
        float des = 0;
        linkedList<node<checkpoint> >* nodeNeighbours = eventMap.neighbours(currentNode, true);
        listNode<node<checkpoint> >* walk = nodeNeighbours->returnHead();

        for (int i = 0 ; i < nodeNeighbours->size(); i++) {
            des += desirability( walk->data, depth - 1);

            if (walk->next) {
                walk = walk->next;
            }
        }

        return des * 1 / depth;
    }
}

// algorithm
linkedList<node<checkpoint> > rogaineEvent::optimalRoute(int bracket) {
    // if 2.7% is linear: time will eventually reach 0
    // int timeLimit *= 1 + 0.27 * (5 - bracket)
    // if 2.7% is 2.7% of the previous bracket: doesnt ever get to 0
    int timeRemaining = timeLimit * pow(1.027, 5 - bracket);

    // go further if path back from that node that doesnt hit any traversed nodes is within time limit
    while (djikstrasCost(eventMap, currentNode, eventMap.searchNodeID(0)) < timeRemaining) {

    } 

    // else start going back
};
