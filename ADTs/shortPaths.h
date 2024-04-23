# pragma once

#include "linkedlist.h"
#include "graph.h"
#include "traversals.h"

// given a connected graph returns an MST using prims algorithm
template<typename U> graph<U> prims(graph<U>& graph, const int sourceNode) {
    typedef node<U> node;
    // prelim setup
    class graph<U> T(graph.directed);
    T.addNode(*graph.searchNodeID(sourceNode));
    const int sourceNodeCount = graph.allNodes().size();
    const int sourceEdgeCount = graph.allEdges().size();
    
    // main loop
    while (T.nodeCount() != sourceNodeCount)
    {
        // boilerplatetetetatatet
        listNode<edge>* curEdge = graph.allEdges().returnHead();
        linkedList<edge> crossingEdges;

        // find crossing edges for T and G - T
        for(int i = 0; i < sourceEdgeCount; i++) {
            // i wish it looked better than this
            if ((T.allNodes().contains(*graph.searchNodeID(curEdge->data->start)) && !T.allNodes().contains(*graph.searchNodeID(curEdge->data->end))) || (T.allNodes().contains(*graph.searchNodeID(curEdge->data->end)) && !T.allNodes().contains(*graph.searchNodeID(curEdge->data->start)))) {
                crossingEdges.insertTail(curEdge->data);
                std::cout << "adding edge " << curEdge->data << " to crossingEdges\n";
            }
            else {
                std::cout << "not adding edge\n";
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
        int crossingEdgesSize = crossingEdges.size();
        for (int i = 0; i < crossingEdgesSize; i++) {
            crossingEdges.removeAtIndex(0);
        }

        std::cout << "smallest crossing edge is " << toAdd << " with weight of " << toAdd->weight << '\n';
        // add node before edge otherwise graph class wont let me add the edge
        if (T.allNodes().contains(*graph.searchNodeID(toAdd->start)) && !T.allNodes().contains(*graph.searchNodeID(toAdd->end))) {
            T.addNode(*graph.searchNodeID(toAdd->end));
        }
        else {
            T.addNode(*graph.searchNodeID(toAdd->start));
        }
        T.addEdge(toAdd);
    }

    return T;
}

// for when you dont want to define source node
template<typename T> graph<T> prims(graph<T>& graph) {
    return prims(graph, graph.allNodes().returnHead()->data->id);
}

template<typename T> graph<T> kruskals(graph<T>& graph, const int sourceNode) {
    // find lowest weight edge in A which doesnt form a cycle
    // add to T until T is connected

    // prelim setup
    class graph<T> T(graph.directed);
    const int sourceNodeCount = graph.allNodes().size();
    const int sourceEdgeCount = graph.allEdges().size();

    // main loop
    while (!T.connected()) {

    }

    return T;
}
