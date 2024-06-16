# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/graph.h"
# include "adts/shortPaths.h"
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
    bool pathBackInTimeExists(node<checkpoint>* sourceNode, node<checkpoint>* possibleNode, node<checkpoint>* goalNode, int timeRemaining);
    bool pathBackFromNeighbourExists(node<checkpoint>* currentNode, node<checkpoint>* goalNode, int timeRemaining);
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
            des += desirability(walk->data, depth - 1);

            if (walk->next) {
                walk = walk->next;
            }
        }

        return des * 1 / depth;
    }
}

// determines if a path back from possible node to goal node will be within the time limit
bool rogaineEvent::pathBackInTimeExists(node<checkpoint>* sourceNode, node<checkpoint>* possibleNode, node<checkpoint>* goalNode, int timeLimit) {
    //std::cout << *sourceNode << " " << *possibleNode << '\n';
    timeLimit -= eventMap.searchEdge(sourceNode->id, possibleNode->id)->weight;

    //std::cout << djikstrasCost(eventMap, possibleNode->id, goalNode->id) << '\n';
    //std::cout << djikstrasPath(eventMap, possibleNode->id, goalNode->id) << '\n';
    if (djikstrasCost(eventMap, possibleNode->id, goalNode->id) > timeLimit) {
        return false;
    }
    else { 
        //std::cout << "hypothetical path back is " << djikstrasPath(eventMap, possibleNode->id, goalNode->id) << " with cost " 
        //<< djikstrasCost(eventMap, possibleNode->id, goalNode->id) << " and timeRemaining is " << timeLimit << '\n';
        return true;
    }
}

// determines if any neighbours of a node will have a path back
bool rogaineEvent::pathBackFromNeighbourExists(node<checkpoint>* currentNode, node<checkpoint>* goalNode, int timeLimit) {
    linkedList<node<checkpoint> >* neighbours = eventMap.neighbours(currentNode, true);
    listNode<node<checkpoint> >* neighbourWalk = neighbours->returnHead();
    for (int i = 0; i < neighbours->size(); i++) {
        if (pathBackInTimeExists(currentNode, neighbourWalk->data, goalNode, timeLimit)) {
            return true;
        }
        if (neighbourWalk->next) {
            neighbourWalk = neighbourWalk->next;
        }
    }
    return false;
}

// algorithm
linkedList<node<checkpoint> > rogaineEvent::optimalRoute(int bracket) {
    // if 2.7% is linear: time will eventually reach 0
    // int timeLimit *= 1 + 0.27 * (5 - bracket)
    // if 2.7% is 2.7% of the previous bracket: doesnt ever get to 0
    int timeRemaining = timeLimit * pow(1.027, 5 - bracket);
    node<checkpoint>* currentNode = eventMap.searchNodeID(0);
    node<checkpoint>* endCheckpoint = eventMap.searchNodeID(0);

    linkedList<node<checkpoint> > path;
    int pointTotal;

    int desirabilityArr[eventMap.nodeCount()];
    for (int i = 0; i < eventMap.nodeCount(); i++) {
        desirabilityArr[i] = desirability(eventMap.searchNodeID(i), 6);
    }
    /*for (int i = 0; i < eventMap.nodeCount(); i++) {
        std::cout << desirabilityArr[i] << ", ";
    }
    std::cout << '\n';*/
    path.insertTail(*currentNode);
    // go further if path back from that node that doesnt hit any traversed nodes is within time limit
    while (pathBackFromNeighbourExists(currentNode, endCheckpoint, timeRemaining) || (djikstrasCost(eventMap, currentNode->id, endCheckpoint->id) < timeRemaining && currentNode != endCheckpoint)) {
       // std::cout << "current node " << *currentNode << '\n';

        // pick most desirable node that has not been traversed
        node<checkpoint>* bestNode = nullptr;
        linkedList<node<checkpoint> >* n = eventMap.neighbours(currentNode, true);
        listNode<node<checkpoint> >* bestWalk = n->returnHead();

        //std::cout << "neighbours: " << *n << '\n';

        for (int i = 0; i < n->size(); i++) {
            if (!bestNode && pathBackInTimeExists(currentNode, bestWalk->data, endCheckpoint, timeRemaining)) {
                bestNode = bestWalk->data;
            }
            // if i dont have this it tries to dereference a null bestNode ptr in the next if sometimes and segfaults
            else if (!bestNode && !pathBackInTimeExists(currentNode, bestWalk->data, endCheckpoint, timeRemaining)) {
                if (bestWalk->next) {
                    bestWalk = bestWalk->next;
                }
                continue;
            }
            else if (desirabilityArr[bestNode->id] < desirabilityArr[bestWalk->data->id] && pathBackInTimeExists(currentNode, bestWalk->data, endCheckpoint, timeRemaining)) {
                bestNode = bestWalk->data;
            }

            if (bestWalk->next) {
                bestWalk = bestWalk->next;
            }
        }
        // debug pray
        /*std::cout << "most desirable node from " << *currentNode << " is " << *bestNode << " with a desirability of " << desirabilityArr[bestNode->id] 
        << " and hypothetical path back of " << djikstrasPath(eventMap, bestNode->id, endCheckpoint->id)<< " with cost " 
        << djikstrasCost(eventMap, bestNode->id, endCheckpoint->id) << " and time remaining is " << timeRemaining << '\n';*/
        // decrement time
        timeRemaining -= eventMap.searchEdge(currentNode->id, bestNode->id)->weight;
        desirabilityArr[currentNode->id] = 0;

        currentNode = bestNode;
        path.insertTail(*currentNode);
        if (desirabilityArr[currentNode->id] != 0) {
            pointTotal += currentNode->attribute->points;
        }
    } 
    std::cout << "total points is: " << pointTotal << " and time remaining is " << timeRemaining << '\n';
    return path;
};
