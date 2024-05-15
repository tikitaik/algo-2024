# pragma once

#include "adts/linkedlist.h"
#include "adts/graph.h"
#include "adts/traversals.h"

// given a connected g returns an MST using prims algorithm
template<typename U> graph<U> prims(graph<U>& g, const int sourceNode) {
    typedef node<U> node;

    // works on undirected graphs best
    if (g.directed) {
        std::cout << "this may not work as prim's doesnt always work on directed graphs\n";
    }

    // prelim setup
    graph<U> T(g.directed);
    T.addNode(*g.searchNodeID(sourceNode));
    const int sourceNodeCount = g.allNodes().size();
    const int sourceEdgeCount = g.allEdges().size();
    
    // main loop
    while (T.nodeCount() != sourceNodeCount)
    {
        // boilerplatetetetatatet
        listNode<edge>* curEdge = g.allEdges().returnHead();
        linkedList<edge> crossingEdges;

        // find crossing edges for T and G - T
        for(int i = 0; i < sourceEdgeCount; i++) {
            // i wish it looked better than this
            if ((T.allNodes().contains(*g.searchNodeID(curEdge->data->start)) && !T.allNodes().contains(*g.searchNodeID(curEdge->data->end))) || (T.allNodes().contains(*g.searchNodeID(curEdge->data->end)) && !T.allNodes().contains(*g.searchNodeID(curEdge->data->start)))) {
                crossingEdges.insertTail(curEdge->data);
                //std::cout << "adding edge " << *curEdge->data << " to crossingEdges\n";
            }

            if(curEdge->next != nullptr) {
                curEdge = curEdge->next;
            }
        }

        // find minimal edge from crossingEdges
        int smallestWeight = 0;
        listNode<edge>* curCrossingEdge = crossingEdges.returnHead();
        edge* toAdd = crossingEdges.returnHead()->data;

        for (int i = 0; i < crossingEdges.size(); i++) {
            if (smallestWeight == 0 || curCrossingEdge->data->weight < smallestWeight) {
                smallestWeight = curCrossingEdge->data->weight;
                toAdd = curCrossingEdge->data;
            }

            if (i < crossingEdges.size() - 1) {
                curCrossingEdge = curCrossingEdge->next;
            }
        }
        // deletes everything in crossingEdges for clean up
        for (int i = crossingEdges.size(); i > 0; i--) {
            crossingEdges.removeAtIndex(i - 1);
        }

        std::cout << "minimal crossing edge is " << *toAdd << " with weight of " << toAdd->weight << '\n';
        // add node before edge otherwise g class wont let me add the edge
        if (T.allNodes().contains(*g.searchNodeID(toAdd->start)) && !T.allNodes().contains(*g.searchNodeID(toAdd->end))) {
            T.addNode(g.searchNodeID(toAdd->end));
        }
        else {
            T.addNode(g.searchNodeID(toAdd->start));
        }
        T.addEdge(toAdd);
    }

    return T;
}

// for when you dont want to define source node
template<typename T> graph<T> prims(graph<T> g) {
    return prims(g, g.allNodes().returnHead()->data->id);
}

// kruskals util
template<typename U> edge* findMinEdgeThatIsntCyclic (graph<U> g, graph<U> T) {
    listNode<edge>* curEdge = g.allEdges().returnHead();
    edge* minEdge;
    int minWeight = 0;

    for (int i = 0; i < g.edgeCount(); i++) {
        // test each edge
        if ((curEdge->data->weight < minWeight || minWeight == 0) && !T.allEdges().contains(*curEdge->data)) {

            T.addEdge(curEdge->data);
            // this was a fucking pain to implement
            if (!T.cyclic()) {
                minEdge = curEdge->data;
                minWeight = minEdge->weight;
            }
            // im so glad that this works like no way
            T.deleteEdge(curEdge->data);
        } // enumerate
        if (curEdge->next != nullptr) {
            curEdge = curEdge->next;
        }
    }

    return minEdge;
}

// add the minimal node that doesnt make the graph cyclic until it is connected
template<typename U> graph<U> kruskals(graph<U> g) {
    typedef node<U> node;
    // warning
    if (g.directed) {
        std::cout << "this may not work as kruskals doesnt always work on directed graphs\n";
    }

    // prelim setup
    graph<U> T(g.directed);
    const int sourceNodeCount = g.allNodes().size();
    const int sourceEdgeCount = g.allEdges().size();

    // add all nodes from g to T
    listNode<node>* curNode = g.allNodes().returnHead();
    for (int i = 0; i < sourceNodeCount; i++) {
        T.addNode(curNode->data);
        curNode->increment();
    }

    // main loop
    while (!T.connected()) {
        // find minimal edge that doesn't make the graph cyclic
        edge* minEdge = findMinEdgeThatIsntCyclic(g, T);

        // add edge and nodes that it connects to T
        T.addEdge(minEdge);
        std::cout << "minimal edge is " << *minEdge << " with weight " << minEdge->weight << '\n';
    }

    std::cout << "1";
    return T;
}

template <typename T> void updateAdjacents(graph<T> g, node<T>* current, double minimalDist[], node<T>* prevNode[]) {
    typedef node<T> node;

    linkedList<node>* untNeighbours = g.untraversedNeighbours(current, g.directed); 
    listNode<node>* curNeighbour = untNeighbours->returnHead();
    
    for (int i = 0; i < untNeighbours->size(); i++) {

        const int indexOfNeighbour = g.getIndexInAllNodes(curNeighbour->data->id);
        const double costToNeighbour = minimalDist[g.getIndexInAllNodes(current->id)] + (double)g.searchEdge(current->id, curNeighbour->data->id)->weight;
        // if this new path is minimal or the minimal distance is "infinity" update it
        if (costToNeighbour < minimalDist[indexOfNeighbour] || minimalDist[indexOfNeighbour] == -1) {
            // set minimal distance of neighbour to new cost to neighbour
            minimalDist[indexOfNeighbour] = costToNeighbour;
            prevNode[indexOfNeighbour] = current;
        } // enumerate
        if (curNeighbour->next != nullptr) {
            curNeighbour = curNeighbour->next;
        }
    }
}

template <typename T> node<T>* findMinNode(graph<T> g, const double minimalDist[]) {
    typedef node<T> node;

    linkedList<node> untraversed = g.untraversedNodes(); 
    listNode<node>* curNode = untraversed.returnHead();
    node* minNode;
    int minDistance = -1;

    for (int i = 0; i < untraversed.size(); i++) {
        int distOfCur = minimalDist[g.getIndexInAllNodes(curNode->data->id)];

        if (distOfCur != -1 && (distOfCur < minDistance || minDistance == -1)) {
            minDistance = distOfCur;
            minNode = curNode->data;
        } // enumerate
        if (curNode->next != nullptr) {
            curNode = curNode->next;
        }
    }

    minNode->traversed = true;

    return minNode;
}

// makes linkedlist of path back to sourcenode 
template <typename T> linkedList<node<T> > buildPath (graph<T> g, int sourceNodeID, int sinkNodeID, node<T>* prevNode[]) {
    linkedList<node<T> > shortestPath;
    node<T>* toAdd = g.searchNodeID(sinkNodeID);

    while (toAdd != nullptr) {
        shortestPath.insertHead(toAdd);
        toAdd = prevNode[g.getIndexInAllNodes(toAdd->id)];
    }
    return shortestPath;
}

template <typename T> linkedList<node<T> > djikstras(graph<T> g, int sourceNodeID, int sinkNodeID) {
    typedef node<T> node;

    g.setAllNodesToUntraversed();
    node* current = g.searchNodeID(sourceNodeID);
    current->traversed = true;
    std::cout << "current is starting at node " << *current << " and searching for path to node " << *g.searchNodeID(sinkNodeID) << '\n';

    // array to store current minimal path costs, init all to -1 to represent infinite
    // can be used since djikstras is not for negative weight values
    double minimalDist[g.nodeCount()];
    node* prevNode[g.nodeCount()];
    for (int i = 0; i < g.nodeCount(); i++) {
        minimalDist[i] = -1;
        prevNode[i] = nullptr;
    }
    // set init distance to 0 
    minimalDist[g.getIndexInAllNodes(sourceNodeID)] = 0;
    
    // main loop
    while (current != g.searchNodeID(sinkNodeID)) {
        updateAdjacents(g, current, minimalDist, prevNode);

        // choose current
        current = findMinNode(g, minimalDist);
    }

    // go back and make path
    return buildPath(g, sourceNodeID, sinkNodeID, prevNode);
}
