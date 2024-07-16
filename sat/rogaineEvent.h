# pragma once

# include <iostream>
# include "../adts/linkedlist.h"
# include "../adts/graph.h"
# include "../adts/shortPaths.h"
# include "../adts/pair.h"
# include "../time/time.h"
# include "checkpoint.h"
# include "team.h"
# include "graphConstructor.h"


class rogaineEvent {

    // start and end can be represented as checkpoints with no reward 
    const node<checkpoint>* startNode;
    const node<checkpoint>* endNode;

    // time related vars
    const int timeLimit;

    // map
    const graph<checkpoint> eventMap;
    const linkedList<node<checkpoint> > checkpoints;

    // register for teams
    linkedList<team> teamRegister;
    linkedList<team> bracketArr[6];

    //register of checkpoints, maps to teams that visit them that visited checkpoints
    dictionary<checkpoint, linkedList<pair<team, timePlaceholder> > > checkpointRegister;

    public:

    int desirabilityCount;
    // epic constructor
    rogaineEvent(graph<checkpoint> mapIn, linkedList<node<checkpoint> > checkpointList, node<checkpoint>* start, node<checkpoint>* end, int timeIn) : eventMap(mapIn), checkpoints(checkpointList), startNode(start), endNode(end), timeLimit(timeIn) {
        desirabilityCount = 0;
    }

    void addTeamToBracket(team& t, int index);
    void addTeamToCheckpoint(checkpoint& c, team* t, timePlaceholder time);
    float desirability(graph<checkpoint> g, node<checkpoint>* currentNode, int depth);
    bool pathBackInTimeExists(graph<checkpoint>& g, node<checkpoint>* sourceNode, node<checkpoint>* possibleNode, node<checkpoint>* goalNode, int timeRemaining);
    bool pathBackFromNeighbourExists(graph<checkpoint>& g, node<checkpoint>* currentNode, node<checkpoint>* goalNode, int timeRemaining);
    linkedList<node<checkpoint> > optimalRoute(team t);
};

void rogaineEvent::addTeamToBracket(team& t, int index) {
    bracketArr[index].insertTail(t);
}

void rogaineEvent::addTeamToCheckpoint(checkpoint& check, team* t, timePlaceholder time) {
    pair<team, timePlaceholder> add;
    add.one = t;
    *add.two = time;
    checkpointRegister.getValue(check).insertTail(add);
}

float rogaineEvent::desirability(graph<checkpoint> g, node<checkpoint>* currentNode, int depth) {
    desirabilityCount++;
    // base case
    if (depth == 1) {
        float des = 0;
        linkedList<node<checkpoint> >* nodeNeighbours = g.neighbours(currentNode, true);
        listNode<node<checkpoint> >* walk = nodeNeighbours->returnHead();

        for (int i = 0 ; i < nodeNeighbours->size(); i++) {
            des += walk->data->attribute->points / g.searchEdge(currentNode->id, walk->data->id)->weight;
            
            if (walk->next) {
                walk = walk->next;
            }
        }

        return des;
    }
    else {
        float des = 0;
        linkedList<node<checkpoint> >* nodeNeighbours = g.neighbours(currentNode, true);
        listNode<node<checkpoint> >* walk = nodeNeighbours->returnHead();

        for (int i = 0 ; i < nodeNeighbours->size(); i++) {
            des += desirability(g, walk->data, depth - 1);

            if (walk->next) {
                walk = walk->next;
            }
        }

        return des / depth;
    }
}

// determines if a path back from possible node to goal node will be within the time limit
bool rogaineEvent::pathBackInTimeExists(graph<checkpoint>& g, node<checkpoint>* sourceNode, node<checkpoint>* possibleNode, node<checkpoint>* goalNode, int timeLimit) {

    timeLimit -= g.searchEdge(sourceNode->id, possibleNode->id)->weight;
    if (!possibleNode->traversed) {
        timeLimit -= 2;
    }

    g.getTraversedState();
    g.setAllNodesToUntraversed();

    // extra 2 minutes to find scanning point check
    int pathCost = dijkstrasCost(g, possibleNode->id, goalNode->id);
    linkedList<node<checkpoint> > path = dijkstrasPath(g, possibleNode->id, goalNode->id);
    listNode<node<checkpoint> >* walk = path.returnHead();
    for (int i = 0; i < path.size(); i++) {
        if (!walk->data->traversed) {
            pathCost += 2;
        }
        if (walk->next) {
            walk = walk->next;
        }
    }

    g.resetTraversed();

    if (pathCost > timeLimit) {
        return false;
    }
    else { 
        //std::cout << "hypothetical path back is " << dijkstrasPath(g, possibleNode->id, goalNode->id) << " with cost " 
        //<< dijkstrasCost(g, possibleNode->id, goalNode->id) << " and timeRemaining is " << timeLimit << '\n';
        return true;
    }
}

// determines if any neighbours of a node will have a path back
bool rogaineEvent::pathBackFromNeighbourExists(graph<checkpoint>& g, node<checkpoint>* currentNode, node<checkpoint>* goalNode, int timeLimit) {
    linkedList<node<checkpoint> >* neighbours = g.neighbours(currentNode, true);
    listNode<node<checkpoint> >* neighbourWalk = neighbours->returnHead();
    for (int i = 0; i < neighbours->size(); i++) {
        if (pathBackInTimeExists(g, currentNode, neighbourWalk->data, goalNode, timeLimit)) {
            return true;
        }
        if (neighbourWalk->next) {
            neighbourWalk = neighbourWalk->next;
        }
    }
    return false;
}

// algorithm
linkedList<node<checkpoint> > rogaineEvent::optimalRoute(team t) {
    // s = d / t therefore if t /= 0.973 then s = d / (t / 0.973) = s / 0.973
    float walkSpeed = t.speed;
    int bracket = t.bracket;
    for (int i = t.bracket; i < 6; i++) {
        // same as walkSpeed /= 0.973
        walkSpeed *= 1.02775;
    }
    //std::cout << "inital team speed was " << t.speed << " but because they are in bracket " << t.bracket << " and so team walkSpeed is now " << walkSpeed << '\n';

    // initalise everything
    graph<checkpoint> teamMap = constructGraph(walkSpeed);
    node<checkpoint>* currentNode = teamMap.searchNodeID(0);
    node<checkpoint>* endCheckpoint = teamMap.searchNodeID(0);
    linkedList<node<checkpoint> > path;
    int pointTotal = 0;
    int timeRemaining = timeLimit;
    int desirabilityArr[teamMap.nodeCount()];

    // get desirability of everything
    for (int i = 0; i < teamMap.nodeCount(); i++) {
        desirabilityArr[i] = desirability(teamMap, teamMap.searchNodeID(i), 6);
    }

    /*for (int i = 0; i < teamMap.nodeCount(); i++) {
        std::cout << desirabilityArr[i] << ", ";
    }
    std::cout << '\n';*/

    path.insertTail(*currentNode);

    // go further if path back from that node that doesnt hit any traversed nodes is within time limit
    while (pathBackFromNeighbourExists(teamMap, currentNode, endCheckpoint, timeRemaining)) {
        //std::cout << "current node " << *currentNode << '\n';
        currentNode->traversed = true;
        // pick most desirable node that has not been traversed
        node<checkpoint>* bestNode = nullptr;
        linkedList<node<checkpoint> >* n = teamMap.neighbours(currentNode, true);
        listNode<node<checkpoint> >* bestWalk = n->returnHead();

        //std::cout << "neighbours: " << *n << '\n';

        for (int i = 0; i < n->size(); i++) {
            if (!bestNode && pathBackInTimeExists(teamMap, currentNode, bestWalk->data, endCheckpoint, timeRemaining)) {
                bestNode = bestWalk->data;
            }
            // if i dont have this it tries to dereference a null bestNode ptr in the next if sometimes and segfaults
            else if (!bestNode && !pathBackInTimeExists(teamMap, currentNode, bestWalk->data, endCheckpoint, timeRemaining)) {
                if (bestWalk->next) {
                    bestWalk = bestWalk->next;
                }
                continue;
            }
            else if (desirabilityArr[bestNode->id] < desirabilityArr[bestWalk->data->id] && pathBackInTimeExists(teamMap, currentNode, bestWalk->data, endCheckpoint, timeRemaining)) {
                bestNode = bestWalk->data;
            }

            if (bestWalk->next) {
                bestWalk = bestWalk->next;
            }
        }
        // debug pray
        /*teamMap.getTraversedState();
        teamMap.setAllNodesToUntraversed();
        std::cout << "most desirable node from " << *currentNode << " is " << *bestNode << " with a desirability of " << desirabilityArr[bestNode->id] 
        << " and hypothetical path back of " << dijkstrasPath(teamMap, bestNode->id, endCheckpoint->id)<< " with cost " 
        << dijkstrasCost(teamMap, bestNode->id, endCheckpoint->id) << " and time remaining is " << timeRemaining << '\n';
        teamMap.resetTraversed();*/
        // decrement time
        timeRemaining -= teamMap.searchEdge(currentNode->id, bestNode->id)->weight;
        if (!bestNode->traversed) {
            timeRemaining = timeRemaining - 2;
        }
        desirabilityArr[currentNode->id] = 0;
        // new current node things
        currentNode = bestNode;
        path.insertTail(*currentNode);
        if (desirabilityArr[currentNode->id] != 0) {
            pointTotal += currentNode->attribute->points;
        }
    } 
    // check just to be sure
    if (timeRemaining < 0) {
        std::cout << "time is less than 0, taking off " << -1 * timeRemaining * 10 << " points\n";
        pointTotal += timeRemaining * 10;
    }

    std::cout << "total points is: " << pointTotal << " and time remaining is " << timeRemaining << '\n';
    //std::cout << pointTotal;
    return path;
};
