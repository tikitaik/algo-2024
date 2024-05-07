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

        std::cout << "smallest crossing edge is " << *toAdd << " with weight of " << toAdd->weight << '\n';
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
template<typename T> graph<T> prims(graph<T>& g) {
    return prims(g, g.allNodes().returnHead()->data->id);
}

template<typename U> graph<U> kruskals(graph<U>& g) {
    typedef node<U> node;
    // find lowest weight edge in A which doesnt form a cycle
    // add to T until T is connected
    
    // works on undirected graphs best
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
        listNode<edge>* curEdge = g.allEdges().returnHead();
        edge* minEdge;
        int minWeight = 0;

        for (int i = 0; i < sourceEdgeCount; i++) {
            if ((curEdge->data->weight < minWeight || minWeight == 0) && !T.allEdges().contains(*curEdge->data)) {

                T.addEdge(curEdge->data);

                if (!T.cyclic()) {
                    minEdge = curEdge->data;
                    minWeight = minEdge->weight;
                }
                T.deleteEdge(curEdge->data);
            }
            if (curEdge->next != nullptr) {
                curEdge = curEdge->next;
            }
        }

        T.addEdge(minEdge);


        std::cout << "minEdge is " << *minEdge << " with weight " << minEdge->weight << '\n';
        // add edge and nodes it connects to T
    }

    return T;
}
