# pragma once

# include "linkedlist.h"
# include "graph.h"
# include "traversals.h"

template<typename U> linkedList<edge> findCrossingEdges (graph<U> g, graph<U> T) {
    
    listNode<edge>* curEdge = g.allEdges().returnHead();
    linkedList<edge> crossingEdges;

    // find crossing edges for T and G - T
    for (int i = 0; i < g.edgeCount(); i++) {
        // i wish it looked better than this
        // seg faults on this if statement
        if ((T.allNodes().contains(*g.searchNodeID(curEdge->data->start)) && !T.allNodes().contains(*g.searchNodeID(curEdge->data->end))) || (T.allNodes().contains(*g.searchNodeID(curEdge->data->end)) && !T.allNodes().contains(*g.searchNodeID(curEdge->data->start)))) {
            crossingEdges.insertTail(curEdge->data);
            //std::cout << "adding edge " << *curEdge->data << " to crossingEdges\n";
        } // enumerate yuhh
        if (curEdge->next) {
            curEdge = curEdge->next;
        }
    }

    return crossingEdges;
}

edge* findMinimalCrossingEdge(linkedList<edge>& crossingEdges) {
   // only works for positive integer weight 
    int smallestWeight = 0;
    listNode<edge>* curCrossingEdge = crossingEdges.returnHead();
    edge* minimalEdge = crossingEdges.returnHead()->data;

    for (int i = 0; i < crossingEdges.size(); i++) {
        if (smallestWeight == 0 || curCrossingEdge->data->weight < smallestWeight) {
            smallestWeight = curCrossingEdge->data->weight;
            minimalEdge = curCrossingEdge->data;
        }

        if (curCrossingEdge->next) {
            curCrossingEdge = curCrossingEdge->next;
        }
    }
    // deletes everything in crossingEdges for clean up
    for (int i = crossingEdges.size(); i > 0; i--) {
        crossingEdges.removeAtIndex(i - 1);
    }

    return minimalEdge;
}

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
        linkedList<edge> crossingEdges = findCrossingEdges(g, T);

        // find minimal edge from crossingEdges
        edge* minimalEdge = findMinimalCrossingEdge(crossingEdges);
        //std::cout << "minimal crossing edge is " << *minimalEdge << " with weight of " << minimalEdge->weight << '\n';

        // add node before edge otherwise g class wont let me add the edge
        if (T.allNodes().contains(*g.searchNodeID(minimalEdge->start)) && !T.allNodes().contains(*g.searchNodeID(minimalEdge->end))) {
            T.addNode(g.searchNodeID(minimalEdge->end));
        }
        else {
            T.addNode(g.searchNodeID(minimalEdge->start));
        }
        T.addEdge(*minimalEdge);
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

            T.addEdge(*curEdge->data);
            // this was a fucking pain to implement
            if (!T.cyclic()) {
                minEdge = curEdge->data;
                minWeight = minEdge->weight;
            }
            // im so glad that this works like no way
            T.deleteEdge(curEdge->data);
        } // enumerate
        if (curEdge->next) {
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
        // need to add instances so that when they are removed they dont change the pointers in the og graph
        T.addNode(*curNode->data);
        if (curNode->next) {
            curNode = curNode->next;
        }
    }

    // main loop
    while (!T.connected()) {
        // find minimal edge that doesn't make the graph cyclic
        edge* minEdge = findMinEdgeThatIsntCyclic(g, T);

        // add edge and nodes that it connects to T
        T.addEdge(*minEdge);
        //std::cout << "minimal edge is " << *minEdge << " with weight " << minEdge->weight << '\n';
    }

    return T;
}

template <typename T> node<T>** dijkstras(graph<T> g, int sourceNodeID, int sinkNodeID) {
    typedef node<T> node;

    // DFS check to see if there is a path at all to sink node, if not return linkedlist with one thing
    if (!DFS(g, sourceNodeID).contains(sinkNodeID)) {
        std::cout << "no path exists from node " << sourceNodeID << " to " << sinkNodeID << '\n';
        return nullptr;
    }
    
    g.getTraversedState();
    node* current = g.searchNodeID(sourceNodeID);
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
    minimalDist[g.getIndexInAllNodes(sourceNodeID)] = 0;
    
    // main loop 
    while (pq.size() > 0) {
        //std::cout << *current << " is current node\n";

        linkedList<node> untNeighbours = *g.untraversedNeighbours(current, g.directed); 
        listNode<node>* curNeighbour = untNeighbours.returnHead();

        for (int i = 0; i < untNeighbours.size(); i++) {

            const int indexOfNeighbour = g.getIndexInAllNodes(curNeighbour->data->id);
            double costToNeighbour = minimalDist[g.getIndexInAllNodes(current->id)] + (double)g.searchEdge(current->id, curNeighbour->data->id)->weight;
            if(minimalDist[g.getIndexInAllNodes(current->id)] == -1) {
                costToNeighbour += 1;
            }

            // if this new path is minimal or the minimal distance is "infinity" update it
            if (costToNeighbour < minimalDist[indexOfNeighbour] || minimalDist[indexOfNeighbour] == -1) {
                // set minimal distance of neighbour to new cost to neighbour
                minimalDist[indexOfNeighbour] = costToNeighbour;
                prevNodes[indexOfNeighbour] = current;
                pq.enqueue(curNeighbour->data, costToNeighbour);
            }
            if (curNeighbour->next) {
                curNeighbour = curNeighbour->next;
            }
        }

        current = pq.extractFront();
        current->traversed = true;
    }
    g.resetTraversed();
    return prevNodes;
}

// linked list of path back to node
template<typename T> linkedList<node<T> > dijkstrasPath(graph<T> g, int sourceNodeID, int sinkNodeID) {
    node<T>** prev = new node<T>*[g.nodeCount()];
    prev = dijkstras(g, sourceNodeID, sinkNodeID);

    linkedList<node<T> > shortestPath;
    node<T>* walk = g.searchNodeID(sinkNodeID);

    while (walk) {
        shortestPath.insertHead(*walk);
        walk = prev[g.getIndexInAllNodes(walk->id)];
    }

    return shortestPath;
}

template<typename T> int dijkstrasCost(graph<T> g, int sourceNodeID, int sinkNodeID) {
    node<T>** prev = new node<T>*[g.nodeCount()];
    prev = dijkstras(g, sourceNodeID, sinkNodeID);

    int cost = 0;
    node<T>* walk = g.searchNodeID(sinkNodeID);

    while (prev[g.getIndexInAllNodes(walk->id)]) {
        cost += g.searchEdge(prev[g.getIndexInAllNodes(walk->id)]->id, walk->id)->weight;
        walk = prev[g.getIndexInAllNodes(walk->id)];
    }

    return cost;
}
