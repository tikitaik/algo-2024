#pragma once

#include <iostream>
#include "adts/linkedlist.h"
#include "adts/graph.h"

// add untraversed neighbours of current vertex to unvisited list
template <typename T, typename U> void addUntraversedNeighbours(graph<T>& graph, U& list, node<T>* current) {
    typedef node<T> node;
    linkedList<node>* untNeighbours = graph.untraversedNeighbours(current);
    listNode<node>* neighbourListNode = untNeighbours->returnHead();
    // loops through each neighbour and adds it
    for (int i = 0; i < untNeighbours->size(); i++) {
        list.insertTail(neighbourListNode->data);
        if (neighbourListNode->next != nullptr) {
            neighbourListNode = neighbourListNode->next;
        }
    }
}

// check if every node in graph's traversed attribute == true
template <typename T> bool allNodesAreTraversed(graph<T>& graph) {
    typedef node<T> node;
    listNode<node>* curListNode = graph.allNodes().returnHead();
    // for loop and enum
    for (int i = 0; i < graph.allNodes().size(); i++) {
        if (!curListNode->data->traversed) {
            return false;
        }
        if (i < graph.allNodes().size() - 1) {
            curListNode = curListNode->next;
        }
    }
    // otherwise return true
    return true;
}

// writes the traversed and untraversed nodes to console, very useless
template <typename T> void displayTraversed(graph<T>& graph) {
    typedef node<T> node;
    listNode<node>* curListNode = graph.allNodes().returnHead();

    linkedList<int> traversed;
    linkedList<int> untraversed;
    for (int i = 0; i < graph.allNodes().size(); i++) {
        if (curListNode->data->traversed) {
            traversed.insertTail(curListNode->data->id);
        }
        else {
            untraversed.insertTail(curListNode->data->id);
        }
        if (curListNode->next != nullptr) {
            curListNode = curListNode->next;
        }
    }
    std::cout << "traversed: " << traversed << '\n';
    std::cout << "untraversed: " << untraversed << '\n';
}


// returns an adjacency matrix in a 1D array, given a graph
// but is printed as 2D by the displayMatrix2D function
template <typename T> int* adjMatrix2D(graph<T>& graph) {
    typedef node<T> node;
    const int nodeCount = graph.allNodes().size();
    const int edgeCount = graph.allEdges().size();
    int* matrixArr = new int [nodeCount * nodeCount + 1];

    // cheeky extra cell is used for storing the count in an extra element, not very useful though
    matrixArr[nodeCount * nodeCount] = nodeCount;
    listNode<edge>* curEdge = graph.allEdges().returnHead();

    // O(n^2) sets all values to 0
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            matrixArr[i * nodeCount + j] = 0;
        }
    }

    // actually sets the values
    for (int i = 0; i < edgeCount; i++) {
        matrixArr[(curEdge->data->start) * nodeCount + (curEdge->data->end)] = curEdge->data->weight;

        if (!graph.directed) {
            matrixArr[(curEdge->data->end) * nodeCount + (curEdge->data->start)] = curEdge->data->weight;
        }
        curEdge = curEdge->next;
    }

    return matrixArr;
}

// displays 1D matrix as if it was 2D, sadly need second param for size as pointers fucking suck
// and dont have good sizeof functionality
void displayMatrix2D(const int* matrix, const int nodeCount) {
    // beautiful if else statement
    if (nodeCount < 10) {
        std::cout << "outputting matrix:\n   ";
    }
    else {
        std::cout << "outputting matrix:\n    ";
    }
    // top legened
    for (int i = 0; i < nodeCount; i++) {
        std::cout << "  " << i << " ";
    }
    // only works for graphs with < 100 nodes, which should be fine
    if (nodeCount >= 10) {
        std::cout << "\n0  [ ";
    }
    else if (nodeCount < 10) {
        std::cout << "\n0 [ ";
    }
    // mwah chefs kiss
    for (int i = 0; i < nodeCount * nodeCount; i++) {
        if (matrix[i] < 10) {
            std::cout << ' ';
        }
        std::cout << matrix[i];
        // end of row and start of new row for less than ten nodes total
        if (i + 1 == nodeCount * nodeCount) {
            continue;
        }
        else if ((i + 1) % nodeCount == 0 && nodeCount < 10) {
            std::cout << " ]\n" << (i + nodeCount) / nodeCount << " [ ";
        }
        // end of row and start of new row for row thats single digit when there's double digit nodes
        else if ((i + 1) % nodeCount == 0 && ((i + nodeCount) / nodeCount) < 10) {
            std::cout << " ]\n" << (i + nodeCount) / nodeCount << "  [ ";
        }
        // end of row and start of new row for row thats double digit when there's double digit nodes
        else if ((i + 1) % nodeCount == 0 && ((i + nodeCount) / nodeCount) >= 10) {
            std::cout << " ]\n" << (i + nodeCount) / nodeCount << " [ ";
        }
        // commas in rows with column number higher than or equal to 10
        else if ((i % nodeCount) >= 9) {
            std::cout << ",  ";
        }
        // commas in rows with column number higher than or equal to 10
        else {
            std::cout << ", ";
        }
    }
    std::cout << " ]\n";
}


// depth first search on an adjaency matrix
stack<int> adjDFS(int* matrix, const int nodeCount, const int source) {
    stack<int> traversed;
    stack<int> unvisited;
    int* traversedArr = new int[nodeCount];
    int cur;
    int sourcePush = source;
    traversedArr[source] = 1;
    traversed.push(sourcePush);

    // big ugly for loop that goes through each row and adds coordinates of 1s to the unvisited stack
    // and then goes to those rows and adds all of the ones from there
    // it returns same thing as the other DFS
    for (int i = 0; i < nodeCount; i++) {
        cur = *traversed.top()->data;
        traversedArr[cur] = 1;
        for (int j = nodeCount - 1; j > -1; j--) {
            // if an edge between node with id cur and nodeCount + j exists and it is not a
            // traversed node then add it to the unvisited stack
            if (matrix[cur * nodeCount + j] != 0 && traversedArr[j] == 0) {
                int* toPush = new int;
                *toPush = j;
                unvisited.push(toPush);
            }
        }
        
        // sets cur to top of stack if there is an element in the stack and pushes the top
        // if it isnt in there already
        if (unvisited.top() != nullptr) {
            int* ref = unvisited.pop()->data;
            if (!traversed.contains(*ref)) {
                traversed.push(ref);
            }
        }
    }

    return traversed;
}

// returns linkedList of order of nodes being searched with DFS
template <typename T> linkedList<node<T> > DFS (graph<T>& graph, const int source) {
    typedef node<T> node;
    linkedList<node> visited;
    stack<node> unvisited;
    node sourceNode = *graph.searchNodeID(source);

    node* current = graph.searchNodeID(source);

    // guess what this does
    graph.setAllNodesToUntraversed();

    // preliminary node stuff
    current->traversed = true;
    visited.insertTail(current);
    
    // repeat while not every node has been traversed
    while (!allNodesAreTraversed(graph)) {

        // add neighbouring nodes to unvisited stack if they have not been traversed
        // works in numerical order of node ID
        addUntraversedNeighbours(graph, unvisited, current);

        // set current node to stack pop, set it to traversed, and add to visited stack
        // if visited stack doesnt contain it already
        if (unvisited.size() > 0) {
            current = unvisited.pop()->data;
            current->traversed = true;
            if (!visited.contains(*current)) {
                visited.insertTail(current);
            }
        }
    }
    return visited;
}

// returns linkedList of order of nodes being searched with BFS (using queue not stack)
template <typename T> linkedList<node<T> > BFS (graph<T>& graph, const int source) {
    typedef node<T> node;
    linkedList<node> visited;
    queue<node> unvisited;

    node* current = graph.searchNodeID(source);

    graph.setAllNodesToUntraversed();

    // preliminary node stuff
    current->traversed = true;
    visited.insertTail(current);
    
    // repeat while not every node has been traversed
    while (!allNodesAreTraversed(graph)) {

        // add neighbouring nodes to unvisited stack if they have not been traversed
        // this works in alphabetical order in DFS but not for BFS
        addUntraversedNeighbours(graph, unvisited, current);

        // set current node to top of queue, remove it from the queue, set it to traversed,
        // and add to visited stack if visited doesnt contain it already
        if (unvisited.size() > 0) {
            current = unvisited.peek()->data;
            unvisited.removeFront();
            current->traversed = true;
            if (!visited.contains(*current)) {
                visited.insertTail(current);
            }
        }
    }
    return visited;
}

template <typename U> int* FWTC(graph<U>& graph) { 
    //let T be |V|x|V| matrix of transitive closure initialized to run on a directed graph G={V,E}
    const int nodeCount = graph.nodeCount();
    int* T = new int[nodeCount * nodeCount];

    // row
    for (int i = 0; i < nodeCount; i++) {
        // column
        for(int j = 0; j < nodeCount; j++) {
            if ((i == j) || (graph.edgeExists(i, j))) {
                T[nodeCount * i + j] = 1; //there is a path
            }
            else {
                T[nodeCount * i + j] = 0; //path not yet found
            }
        }
    }
        
    //construct T
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            for (int k = 0; k < nodeCount; k++) {
                //Check for path from k to j via i
                T[nodeCount * k + j] = T[nodeCount * k + j] || (T[nodeCount * k + i] && T[nodeCount * i + j]);
            } 
        }
    }

    return T;
}

// returns topological sort if the graph is acyclic and directed
template <typename T> linkedList<node<T> >* topologicalSort(graph<T>& graph) {
    typedef node<T> node;
    if (graph.directed == false) {
        std::cout << "this graph is not directed\n";
        return nullptr;
    }
    else if (graph.cyclic()) {
        std::cout << "this graph is cyclic\n";
        return nullptr;
    }
    else if (!graph.connected()) {
        std::cout << "this graph is disconnected\n";
        return nullptr;
    }
    // top sort vars
    stack<node> visited;
    stack<node> unvisited;
    node* current;
    // the one and only functionnnnnn
    graph.setAllNodesToUntraversed();

    // do a dfs from each node, and add node to visited stack if it has no untraversed descendants and it is not in topSort
    for (int i = 0; i < graph.nodeCount(); i++) {

        // find node not in visited and set it to that to ensure every node is explored
        listNode<node>* curNode = graph.allNodes().returnHead();
        for (int j = 0; j < graph.nodeCount(); j++) {
            if (!visited.contains(*curNode->data)) {
                std::cout << "visited does not contain node with id " << curNode->data->id << '\n';
                current = curNode->data;
                break;
            }
            else if (curNode->next != nullptr) {
                curNode = curNode->next;
            }
        }
        unvisited.push(*current);

        // this is the DFS starting from each node on the directed graph
        for (int j = 0; j < graph.nodeCount(); j++) {
            if (!allNodesAreTraversed(graph)) {

                // add neighbouring nodes to unvisited stack if they have not been traversed
                addUntraversedNeighbours(graph, unvisited, current);

                // if node has no untraversed neighbours and isnt already in the visited stack add it to the topSort stack
                // repeat for every node going back until it has an untraversed child
                if (unvisited.top() != nullptr && graph.untraversedNeighbours(unvisited.top()->data)->size() <= 0 && !visited.contains(*unvisited.top()->data)) {
                    while (graph.untraversedNeighbours(unvisited.top()->data)->size() <= 0 && !visited.contains(*unvisited.top()->data)) {
                        std::cout << "pushing: " << *unvisited.top()->data << " to visited\n";
                        current = unvisited.pop()->data;
                        current->traversed = true;
                        visited.push(current);
                        if (unvisited.size() == 0) { break; }
                    }
                }
                else if (unvisited.top() != nullptr) {
                    current = unvisited.top()->data;
                }
            }
            else { break; }
        }
    }

    linkedList<node>* sortOrdered = new linkedList<node>;

    for (int i = 0; i < graph.nodeCount(); i++) {
        sortOrdered->insertTail(visited.pop()->data);
    }
    
    return sortOrdered;
}
