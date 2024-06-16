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

bool rogaineEvent::pathBackInTimeExists(node<checkpoint>* sourceNode, node<checkpoint>* possibleNode, node<checkpoint>* goalNode, int timeLimit) {
    std::cout << "possible node is " << *possibleNode << ": ";
    /*possibleNode->traversed = true;
    if (eventMap.untraversedNeighbours(goalNode, true)->size() <= 0) {
        std::cout << "this would mean no unt neighbours next to goal node\n";
        possibleNode-> traversed = false;
        return false;
    }
    possibleNode-> traversed = false;*/
    timeLimit -= eventMap.searchEdge(sourceNode->id, possibleNode->id)->weight;
    if (djikstrasCost(eventMap, possibleNode->id, goalNode->id) > timeLimit) {
        std::cout << "too much time to get back\n";
        return false;
    }
    else {
        std::cout << "hypothetical path back is " << djikstrasPath(eventMap, possibleNode->id, goalNode->id) << " with cost " << djikstrasCost(eventMap, possibleNode->id, goalNode->id)
            << " and timeRemaining is " << timeLimit << '\n';
        return true;
    }
}

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
    for (int i = 0; i < eventMap.nodeCount(); i++) {
        std::cout << desirabilityArr[i] << ", ";
    }
    std::cout << '\n';

    // go further if path back from that node that doesnt hit any traversed nodes is within time limit
    while (pathBackFromNeighbourExists(currentNode, endCheckpoint, timeRemaining)) {
        std::cout << "current node " << *currentNode << '\n';
        path.insertTail(*currentNode);

        // so that the end checkpoint is still untraversed for djikstras and stuff
        if (currentNode != endCheckpoint) {
            //currentNode->traversed = true;
        }

        // pick most desirable node that has not been traversed
        node<checkpoint>* bestNode = nullptr;
        linkedList<node<checkpoint> >* n = eventMap.untraversedNeighbours(currentNode, true);
        listNode<node<checkpoint> >* bestWalk = n->returnHead();

        std::cout << *n << "\n" << *bestWalk->data << '\n';

        for (int i = 0; i < n->size(); i++) {
            if (!bestNode && pathBackInTimeExists(currentNode, bestWalk->data, endCheckpoint, timeRemaining)) {
                bestNode = bestWalk->data;
            }
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
        if (!pathBackFromNeighbourExists(currentNode, endCheckpoint, timeRemaining)) {
            std::cout << "this is breaking earlly\n";
            break;
        }
        // debug pray
        std::cout << "most desirable node from " << *currentNode << " is " << *bestNode << " with a desirability of " << desirabilityArr[bestNode->id] << '\n';
        // decrement time
        timeRemaining -= eventMap.searchEdge(currentNode->id, bestNode->id)->weight;
        desirabilityArr[currentNode->id] = 0;

        currentNode = bestNode;
        if (desirabilityArr[currentNode->id] != 0) {
            pointTotal += currentNode->attribute->points;
        }


        if (!pathBackFromNeighbourExists(currentNode, endCheckpoint, timeRemaining)) {
            std::cout << "this is breaking\n";
            break;
        }
    } 

    std::cout << "test: " << djikstrasCost(eventMap, 6, 0) << '\n';
    // else start going back
    std::cout << "time to get back is " << djikstrasCost(eventMap, currentNode->id, endCheckpoint->id) << ". Time remaining is " << timeRemaining << '\n';

    linkedList<node<checkpoint> > pathBack = djikstrasPath(eventMap, currentNode->id, endCheckpoint->id);
    listNode<node<checkpoint > >* pathBackWalk = pathBack.returnHead();

    for (int i = 0; i < pathBack.size(); i++) {
        path.insertTail(pathBackWalk->data);
        pointTotal += pathBackWalk->data->attribute->points;

        if (pathBackWalk->next) {
            timeRemaining -= eventMap.searchEdge(pathBackWalk->data->id, pathBackWalk->next->data->id)->weight;
            pathBackWalk = pathBackWalk->next;
        }

    }

    std::cout << "time remaining is " << timeRemaining << '\n';
    std::cout << "total points is: " << pointTotal << '\n';
    return path;
};
