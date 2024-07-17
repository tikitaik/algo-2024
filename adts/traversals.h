# pragma once

# include <iostream>
# include "linkedlist.h"
# include "graph.h"

// add untraversed neighbours of current vertex to unvisited list
template <typename T, typename U> void addUntraversedNeighbours(graph<T>& g, U& list, node<T>* current) {
    typedef node<T> node;
    linkedList<node>* untNeighbours = g.untraversedNeighbours(current, g.directed);
    listNode<node>* neighbourListNode = untNeighbours->returnHead();
    // loops through each neighbour and adds it
    for (int i = 0; i < untNeighbours->size(); i++) {
        list.insertTail(neighbourListNode->data);
        if (neighbourListNode->next) {
            neighbourListNode = neighbourListNode->next;
        }
    }
}

// returns an adjacency matrix in a 1D array, given a graph
// but is printed as 2D by the displayMatrix2D function
template <typename T> int* adjMatrix2D(graph<T>& g) {
    typedef node<T> node;
    const int nodeCount = g.allNodes().size();
    const int edgeCount = g.allEdges().size();
    int* matrixArr = new int [nodeCount * nodeCount + 1];

    // cheeky extra cell is used for storing the count in an extra element, not very useful though
    matrixArr[nodeCount * nodeCount] = nodeCount;
    listNode<edge>* curEdge = g.allEdges().returnHead();

    // O(n^2) sets all values to 0
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            matrixArr[i * nodeCount + j] = 0;
        }
    }

    // actually sets the values
    for (int i = 0; i < edgeCount; i++) {
        matrixArr[(curEdge->data->start) * nodeCount + (curEdge->data->end)] = curEdge->data->weight;

        if (!g.directed) {
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

void displayMatrix2D(int** arr, int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            std::cout << arr[i][j] << ' ';
        }
        std::cout << '\n';
    }
}


// depth first search on an adjacency matrix
template <typename T> stack<T> adjDFS(int* matrix, const int nodeCount, const int source) {
    stack<T> traversed;
    stack<T> unvisited;
    T* traversedArr = new T[nodeCount];
    T cur;
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
                T* toPush = new T;
                *toPush = j;
                unvisited.push(toPush);
            }
        }
        
        // sets cur to top of stack if there is an element in the stack and pushes the top
        // if it isnt in there already
        if (unvisited.top()) {
            T* ref = unvisited.pop()->data;
            if (!traversed.contains(*ref)) {
                traversed.push(*ref);
            }
            delete ref;
        }
    }

    return traversed;
}

// returns linkedList of order of nodes being searched with DFS
template <typename T> linkedList<node<T> > DFS (graph<T>& g, const int source) {
    typedef node<T> node;
    linkedList<node> visited;
    stack<node> unvisited;

    node* current = g.searchNodeID(source);

    g.getTraversedState();

    // preliminary node stuff
    current->traversed = true;
    visited.insertTail(current);
    
    // icy condition that means it'll terminate when theres no unvisited nodes or it has nowhere else to go
    while ((g.untraversedNeighbours(current, g.directed)->size() > 0 || unvisited.size() > 0 || visited.size() < 1) && !g.allNodesAreTraversed()) {
        // add neighbouring nodes to unvisited stack if they have not been traversed
        linkedList<node>* untNeighbours = g.untraversedNeighbours(current, g.directed);
        listNode<node>* curNode = untNeighbours->returnHead();

        for (int i = 0; i < untNeighbours->size(); i++) {
            unvisited.push(curNode->data);
            if (curNode->next) {
                curNode = curNode->next;
            }
        }

        // set current node to stack pop, set it to traversed, and add to visited stack
        // if visited stack doesnt contain it already
        if (unvisited.size() > 0) {
            current = unvisited.pop()->data;
            current->traversed = true;
            if (!visited.contains(*current)) {
                visited.insertTail(*current);
            }
            unvisited.removeKey(*current);
        }
    }
    g.resetTraversed();
    return visited;
}

// returns linkedList of order of nodes being searched with BFS (using queue not stack)
template <typename T> linkedList<node<T> > BFS (graph<T>& g, const int source) {
    typedef node<T> node;
    linkedList<node> visited;
    queue<node> unvisited;

    node* current = g.searchNodeID(source);

    g.getTraversedState();

    // preliminary node stuff
    current->traversed = true;
    visited.insertTail(current);
    
    // icy condition that means it'll terminate when theres no unvisited nodes or it has nowhere else to go
    while ((g.neighbours(current, g.directed)->size() > 0 || unvisited.size() > 0 || visited.size() < 1) && !g.allNodesAreTraversed()) {
        // add neighbouring nodes to unvisited stack if they have not been traversed
        linkedList<node>* untNeighbours = g.untraversedNeighbours(current, g.directed);
        listNode<node>* curNode = untNeighbours->returnHead();

        for (int i = 0; i < untNeighbours->size(); i++) {
            unvisited.enqueue(curNode->data);
            if (curNode->next) {
                curNode = curNode->next;
            }
        }

        // set current node to top of queue, remove it from the queue, set it to traversed,
        // and add to visited stack if visited doesnt contain it already
        if (unvisited.size() > 0) {
            current = unvisited.peek()->data;
            unvisited.removeFront();
            current->traversed = true;
            if (!visited.contains(*current)) {
                visited.insertTail(*current);
            }
            unvisited.removeKey(*current);
        }
    }
    g.resetTraversed();
    return visited;
}

template <typename U> int** FWTC(graph<U>& g) { 
    //let T be |V|x|V| matrix of transitive closure initialized to run on a directed graph G={V,E}
    const int nodeCount = g.nodeCount();
    int** T = new int*[nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        T[i] = new int[nodeCount];
    }

    // row
    for (int i = 0; i < nodeCount; i++) {
        // column
        for(int j = 0; j < nodeCount; j++) {
            if ((i == j) || (g.edgeExists(i, j))) {
                T[i][j] = 1; //there is a path
            }
            else {
                T[i][j] = 0; //path not yet found
            }
        }
    }
        
    // actual algorithm
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            for (int k = 0; k < nodeCount; k++) {
                //Check for path from k to j via i
                T[k][j] = T[k][j] || (T[k][i] && T[i][j]);
            } 
        }
    }

    return T;
}

template <typename U> int** FWSP(graph<U>& g) { 
    const int INF = -1;

    //let T be |V|x|V| matrix of transitive closure initialized to run on a directed graph G={V,E}
    const int nodeCount = g.nodeCount();
    int** T = new int*[nodeCount];
    for (int i = 0; i < nodeCount; i++) {
        T[i] = new int[nodeCount];
    }

    // row
    for (int i = 0; i < nodeCount; i++) {
        // column
        for(int j = 0; j < nodeCount; j++) {
            if (i == j) {
                T[i][j] = 0;
            }
            else if (g.edgeExists(i, j)) {
                T[i][j] = g.searchEdge(i, j)->weight; //there is a path
            }
            else {
                T[i][j] = INF; //path not yet found
            }
        }
    }
        
    // actual algorithm
    for (int i = 0; i < nodeCount; i++) {
        for (int j = 0; j < nodeCount; j++) {
            for (int k = 0; k < nodeCount; k++) {
                //Check for path from k to j via i
                if ((T[k][j] > T[k][i] + T[i][j] || T[k][j] == INF) && T[k][i] != INF && T[i][j] != INF) {
                    T[k][j] = T[k][i] + T[i][j];
                }
            } 
        }
    }

    return T;
}

// returns topological sort if the graph is acyclic and directed
template <typename T> linkedList<node<T> >* topologicalSort(graph<T>& g) {
    typedef node<T> node;
    if (g.directed == false) {
        std::cout << "this g is not directed\n";
        return nullptr;
    }
    else if (g.cyclic()) {
        std::cout << "this g is cyclic\n";
        return nullptr;
    }
    else if (!g.connected()) {
        std::cout << "this g is disconnected\n";
        return nullptr;
    }
    // top sort vars
    stack<node> visited;
    stack<node> unvisited;
    node* current;

    g.getTraversedState();

    // do a dfs from each node, and add node to visited stack if it has no untraversed descendants and it is not in topSort
    for (int i = 0; i < g.nodeCount(); i++) {

        // find node not in visited and set it to that to ensure every node is explored
        listNode<node>* curNode = g.allNodes().returnHead();
        for (int j = 0; j < g.nodeCount(); j++) {
            if (!visited.contains(*curNode->data)) {
                //std::cout << "visited does not contain node with id " << curNode->data->id << '\n';
                current = curNode->data;
                break;
            }
            else if (curNode->next) {
                curNode = curNode->next;
            }
        }
        unvisited.push(*current);

        // this is the DFS starting from each node on the directed g
        for (int j = 0; j < g.nodeCount(); j++) {
            if (!g.allNodesAreTraversed()) {

                // add neighbouring nodes to unvisited stack if they have not been traversed
                addUntraversedNeighbours(g, unvisited, current);

                // if node has no untraversed neighbours and isnt already in the visited stack add it to the topSort stack
                // repeat for every node going back until it has an untraversed child
                if (unvisited.top() && g.untraversedNeighbours(unvisited.top()->data, g.directed)->size() <= 0 && !visited.contains(*unvisited.top()->data)) {
                    while (g.untraversedNeighbours(unvisited.top()->data, g.directed)->size() <= 0 && !visited.contains(*unvisited.top()->data)) {
                        //std::cout << "pushing: " << *unvisited.top()->data << " to visited\n";
                        current = unvisited.pop()->data;
                        current->traversed = true;
                        visited.push(*current);
                        unvisited.removeKey(*current);
                        if (unvisited.size() == 0) { break; }
                    }
                }
                else if (unvisited.top()) {
                    current = unvisited.top()->data;
                }
            }
            else { break; }
        }
    }

    linkedList<node>* sortOrdered = new linkedList<node>;

    for (int i = 0; i < g.nodeCount(); i++) {
        sortOrdered->insertTail(*visited.pop()->data);
        visited.removeKey(*sortOrdered->returnTail()->data);
    }
    
    g.resetTraversed();
    return sortOrdered;
}
