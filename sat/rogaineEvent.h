# pragma once

# include <iostream>
# include "../adts/graph.h"
# include "../adts/linkedlist.h"
# include "../adts/pair.h"
# include "../adts/traversals.h"
# include "../time/time.h"
# include "checkpoint.h"
# include "graphConstructor.h"
# include "team.h"


class rogaineEvent {

    // start and end can be represented as checkpoints with no reward 
    node<checkpoint>* startNode;
    node<checkpoint>* endNode;

    // time related vars
    const int timeLimit;

    // map
    const graph<checkpoint> eventMap;
    node<checkpoint>** nodeArray;
    node<checkpoint>*** neighbourArray;
    edge*** edgeArray;

    // register for teams
    linkedList<team> teamRegister;
    linkedList<team> bracketArr[6];

    //register of checkpoints, maps to teams that visit them that visited checkpoints
    dictionary<checkpoint, linkedList<pair<team, timePlaceholder> > > checkpointRegister;

    public:

    // epic constructor
    rogaineEvent(int timeIn) : eventMap(initEventCheckpoints()), timeLimit(timeIn) {

        graph<checkpoint> tempGraph = initTeamGraph(eventMap, 1);
        nodeArray = new node<checkpoint>* [eventMap.nodeCount()];
        neighbourArray = new node<checkpoint>** [eventMap.nodeCount()];
        edgeArray = new edge** [eventMap.nodeCount()];

        for (int i = 0; i < eventMap.nodeCount(); i++) {

            nodeArray[i] = eventMap.searchNodeID(i);
            neighbourArray[i] = new node<checkpoint>* [eventMap.nodeCount()];
            edgeArray[i] = new edge* [eventMap.nodeCount()];

            for (int j = 0; j < eventMap.nodeCount(); j++) {
                if (tempGraph.searchEdge(i, j)) {
                    neighbourArray[i][j] = tempGraph.searchNodeID(tempGraph.searchEdge(i, j)->end);
                }
                else {
                    neighbourArray[i][j] = nullptr;
                }
            }
        }

        startNode = nodeArray[0];
        endNode = nodeArray[0];
    }

    void addTeamToBracket(team& t, int index);
    void addTeamToCheckpoint(checkpoint& c, team* t, timePlaceholder time);
    float desirability(graph<checkpoint> g, node<checkpoint>* currentNode, int depth);
    bool pathBackInTimeExists(graph<checkpoint>& g, node<checkpoint>* sourceNode, node<checkpoint>* possibleNode, node<checkpoint>* goalNode, int timeRemaining);
    bool pathBackFromNeighbourExists(graph<checkpoint>& g, node<checkpoint>* currentNode, node<checkpoint>* goalNode, int timeRemaining);
    linkedList<node<checkpoint> > optimalRoute(team t);
    node<checkpoint>** dijkstras(graph<checkpoint> g, int sourceNodeID, int sinkNodeID);
    linkedList<node<checkpoint> > dijkstrasPath(graph<checkpoint> g, int sourceNodeID, int sinkNodeID);
    int dijkstrasCost(graph<checkpoint> g, int sourceNodeID, int sinkNodeID);
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
    float des = 0;

    // go through every node : check for if they are a neighbour
    for (int i = 0; i < g.nodeCount(); i++) {
        if (neighbourArray[currentNode->id][i]) {
            // base case
            if (depth == 1) { 
                //des += neighbourArray[currentNode->id][i]->attribute->points / g.searchEdge(currentNode->id, i)->weight;
                des += neighbourArray[currentNode->id][i]->attribute->points / edgeArray[currentNode->id][i]->weight;

            }
            // recursive case
            else {
                des += desirability(g, neighbourArray[currentNode->id][i], depth - 1) / depth;
            }
        }
    }

    return des;
}

node<checkpoint>** rogaineEvent::dijkstras(graph<checkpoint> g, int sourceNodeID, int sinkNodeID) {
    typedef node<checkpoint> node;

    // DFS check to see if there is a path at all to sink node, if not return linkedlist with one thing
    if (!DFS(g, sourceNodeID).contains(sinkNodeID)) {
        std::cout << "no path exists from node " << sourceNodeID << " to " << sinkNodeID << '\n';
        return nullptr;
    }
    
    g.getTraversedState();

    node* current = nodeArray[sourceNodeID];
    current->traversed = true;
    priorityQueue<node> pq(false);
    pq.enqueue(current, 0);
    //std::cout << "starting from node " << *current << " and searching for path to node " << *g.searchNodeID(sinkNodeID) << '\n';

    // array to store current minimal path costs, init all to -1 to represent infinite
    // can be used since dijkstras is not for negative weight values
    double minimalDist[g.nodeCount()];
    node** prevNodes = new node*[g.nodeCount()];
    for (int i = 0; i < g.nodeCount(); i++) {
        minimalDist[i] = -1;
        prevNodes[i] = nullptr;
    }
    // set init distance to 0 
    minimalDist[sourceNodeID] = 0;
    
    // main loop 
    while (pq.size() > 0) {
        //std::cout << *current << " is current node\n";
        for (int i = 0; i < eventMap.nodeCount(); i++) {

            // untraversed neighbours
            if (neighbourArray[current->id][i] && !neighbourArray[current->id][i]->traversed) {

                double costToNeighbour = minimalDist[current->id] + (double)edgeArray[current->id][i]->weight;
                if (minimalDist[current->id] == -1) {
                    costToNeighbour += 1;
                }

                // if this new path is minimal or the minimal distance is "infinity" update it
                if (costToNeighbour < minimalDist[i] || minimalDist[i] == -1) {
                    // set minimal distance of neighbour to new cost to neighbour
                    minimalDist[i] = costToNeighbour;
                    prevNodes[i] = current;
                    pq.enqueue(nodeArray[i], costToNeighbour);
                }
            }
        }

        current = pq.extractFront();
        current->traversed = true;
    }

    g.resetTraversed();
    return prevNodes;
}

// linked list of path back to node
linkedList<node<checkpoint> > rogaineEvent::dijkstrasPath(graph<checkpoint> g, int sourceNodeID, int sinkNodeID) {
    node<checkpoint>** prev = new node<checkpoint>*[g.nodeCount()];
    prev = dijkstras(g, sourceNodeID, sinkNodeID);

    linkedList<node<checkpoint> > shortestPath;
    node<checkpoint>* walk = g.searchNodeID(sinkNodeID);

    while (walk) {
        shortestPath.insertHead(*walk);
        walk = prev[walk->id];
    }

    return shortestPath;
}

int rogaineEvent::dijkstrasCost(graph<checkpoint> g, int sourceNodeID, int sinkNodeID) {
    node<checkpoint>** prev = new node<checkpoint>*[g.nodeCount()];
    prev = dijkstras(g, sourceNodeID, sinkNodeID);

    int cost = 0;
    node<checkpoint>* walk = g.searchNodeID(sinkNodeID);

    while (prev[walk->id]) {
        cost += edgeArray[prev[walk->id]->id][walk->id]->weight;
        walk = prev[walk->id];
    }

    return cost;
}

// determines if a path back from possible node to goal node will be within the time limit
bool rogaineEvent::pathBackInTimeExists(graph<checkpoint>& g, node<checkpoint>* sourceNode, node<checkpoint>* possibleNode, node<checkpoint>* goalNode, int timeLimit) {

    //std::cout << "checking for path from " << possibleNode->id << " to " << goalNode->id << '\n';
    timeLimit -= edgeArray[sourceNode->id][possibleNode->id]->weight;
    if (!possibleNode->traversed) {
        timeLimit -= 2;
    }

    g.getTraversedState();
    g.setAllNodesToUntraversed();

    // extra 2 minutes to find scanning point check
    int pathCost = dijkstrasCost(g, possibleNode->id, goalNode->id);
    linkedList<node<checkpoint> > path = dijkstrasPath(g, possibleNode->id, goalNode->id);
    //std::cout << "path is " << path << '\n';
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
    return timeLimit > pathCost;
}

// determines if any neighbours of a node will have a path back
bool rogaineEvent::pathBackFromNeighbourExists(graph<checkpoint>& g, node<checkpoint>* currentNode, node<checkpoint>* goalNode, int timeLimit) {

    for (int i = 0; i < eventMap.nodeCount(); i++) {
        if (neighbourArray[currentNode->id][i]) {
            if (pathBackInTimeExists(g, currentNode, neighbourArray[currentNode->id][i], goalNode, timeLimit)) {
                return true;
            }
        }
    }
    return false;
}

// algorithm
linkedList<node<checkpoint> > rogaineEvent::optimalRoute(team t) {
    // s = d / t therefore if t /= 0.973 then s = d / (t / 0.973) = s / 0.973
    float walkSpeed = t.speed;
    for (int i = t.bracket; i < 6; i++) {
        // same as walkSpeed /= 0.973
        walkSpeed *= 1.02775;
    }

    // initalise everything
    graph<checkpoint> teamMap = initTeamGraph(eventMap, walkSpeed);
    node<checkpoint>* currentNode = nodeArray[0];
    node<checkpoint>* endCheckpoint = nodeArray[0];
    linkedList<node<checkpoint> > path;
    int pointTotal = 0;
    int timeRemaining = timeLimit;
    int desirabilityArr[teamMap.nodeCount()];

    // initalise edge array for each team
    for (int i = 0; i < eventMap.nodeCount(); i++) {
        for (int j = 0; j < eventMap.nodeCount(); j++) {
            if (teamMap.searchEdge(i, j)) {
                edgeArray[i][j] = teamMap.searchEdge(i, j);
            }
            else {
                edgeArray[i][j] = nullptr;
            }
        }
    }

    // get desirability of everything
    for (int i = 0; i < teamMap.nodeCount(); i++) {
        desirabilityArr[i] = desirability(teamMap, nodeArray[i], 6);
    }

    path.insertTail(*currentNode);

    // go further if path back from that node that doesnt hit any traversed nodes is within time limit
    while (pathBackFromNeighbourExists(teamMap, currentNode, endCheckpoint, timeRemaining)) {

        // pick most desirable node that has not been traversed
        node<checkpoint>* bestNode = nullptr;

        for (int i = 0; i < eventMap.nodeCount(); i++) {
            if (neighbourArray[currentNode->id][i]) {
                if (!bestNode && pathBackInTimeExists(teamMap, currentNode, neighbourArray[currentNode->id][i], endCheckpoint, timeRemaining)) {
                    bestNode = neighbourArray[currentNode->id][i];
                }
                // if i dont have this it tries to dereference a null bestNode ptr in the next if sometimes and segfaults
                else if (!bestNode && !pathBackInTimeExists(teamMap, currentNode, neighbourArray[currentNode->id][i], endCheckpoint, timeRemaining)) {
                    continue;
                }
                else if (desirabilityArr[bestNode->id] < desirabilityArr[i] && pathBackInTimeExists(teamMap, currentNode, neighbourArray[currentNode->id][i], endCheckpoint, timeRemaining)) {
                    bestNode = neighbourArray[currentNode->id][i];
                }
            }
        }

        // decrement time and set the node to traversed
        timeRemaining -= edgeArray[currentNode->id][bestNode->id]->weight;
        desirabilityArr[currentNode->id] = 0;
        // if bestnode not traversed
        if (desirabilityArr[bestNode->id] != 0) {
            timeRemaining -= 2;
            pointTotal += bestNode->attribute->points;
        }

        // new current node things
        currentNode = bestNode;
        path.insertTail(*currentNode);
    } 

    // print just in case algorithm doesnt work, hasn't yet
    if (timeRemaining < 0) {
        std::cout << "time is less than 0, taking off " << -1 * timeRemaining * 10 << " points\n";
        pointTotal -= timeRemaining * 10;
    }

    std::cout << pointTotal << '\n';
    //std::cout << "total points: " << pointTotal << " and time remaining is " << timeRemaining << '\n';
    return path;
};
