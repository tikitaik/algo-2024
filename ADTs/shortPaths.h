# pragma once

#include "adts/linkedlist.h"
#include "adts/graph.h"
#include "adts/traversals.h"

// given a connected inGraph returns an MST using prims algorithm
template<typename U> graph<U> prims(graph<U>& inGraph, const int sourceNode) {
    typedef node<U> node;
    // prelim setup
    graph<U> T(inGraph.directed);
    T.addNode(*inGraph.searchNodeID(sourceNode));
    const int sourceNodeCount = inGraph.allNodes().size();
    const int sourceEdgeCount = inGraph.allEdges().size();
    
    // main loop
    while (T.nodeCount() != sourceNodeCount)
    {
        // boilerplatetetetatatet
        listNode<edge>* curEdge = inGraph.allEdges().returnHead();
        linkedList<edge> crossingEdges;

        // find crossing edges for T and G - T
        for(int i = 0; i < sourceEdgeCount; i++) {
            // i wish it looked better than this
            if ((T.allNodes().contains(*inGraph.searchNodeID(curEdge->data->start)) && !T.allNodes().contains(*inGraph.searchNodeID(curEdge->data->end))) || (T.allNodes().contains(*inGraph.searchNodeID(curEdge->data->end)) && !T.allNodes().contains(*inGraph.searchNodeID(curEdge->data->start)))) {
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

        std::cout << "smallest crossing edge is " << *toAdd << " with weight of " << toAdd->weight << '\n';
        // add node before edge otherwise inGraph class wont let me add the edge
        if (T.allNodes().contains(*inGraph.searchNodeID(toAdd->start)) && !T.allNodes().contains(*inGraph.searchNodeID(toAdd->end))) {
            T.addNode(inGraph.searchNodeID(toAdd->end));
        }
        else {
            T.addNode(inGraph.searchNodeID(toAdd->start));
        }
        T.addEdge(toAdd);
    }

    return T;
}

// for when you dont want to define source node
template<typename T> graph<T> prims(graph<T>& inGraph) {
    return prims(inGraph, inGraph.allNodes().returnHead()->data->id);
}

template<typename U> graph<U> kruskals(graph<U>& inGraph, const int sourceNode) {
    // find lowest weight edge in A which doesnt form a cycle
    // add to T until T is connected

    // prelim setup
    graph<U> T(inGraph.directed);
    const int sourceNodeCount = inGraph.allNodes().size();
    const int sourceEdgeCount = inGraph.allEdges().size();

    // main loop
    while (!T.connected()) {

    }

    return T;
}

int fastExp(int base, int power) {
    return -1;
}
