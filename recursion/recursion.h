#pragma once

#include <iostream>
#include "adts/linkedlist.h"
#include "adts/graph.h"
#include "adts/traversals.h"

int factorial(unsigned long long int n)
{
    if (n == 0)
    {
        return 1;
    }
    else
    {
        return n * factorial (n - 1);
    }
}

int fib (int n) {
    if (n <= 1) {
        return n;
    }
    else {
        return fib(n - 1) + fib(n - 2);
    }
}

// i hate snakeCase 🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬🤬
int arithSeries (int start, int diff, int n) {
    if (n == 0) {
        return start;
    }
    else {
        return arithSeries(start + diff * (n - 1), diff, n - 1);
    }
}

int geoSeries (int a, float r, int n) {
    if (n <= 1) {
        return a;
    }
    else {
        return a + geoSeries(r * a, r, n - 1);
    }
}

// f(n) = a^n, a > 0 e R
float powIntExponent(float a, int n) {
    if (n == 1) {
        return a;
    }
    else {
        return powIntExponent(a, n - 1) * a;
    }
}

// this shiz suckcs dick
int fastExp(int base, int n) {
    // x^n = {x(x^2)^((n - 1)/2) for odd}
    //     = {x(x^2)^(n / 2) for even }
    if (n == 0) {
        return 1;
    }
    else if (n % 2 == 1) {
        return base * fastExp(base * base, (n - 1) / 2);
    }
    else {
        return fastExp(base * base, n / 2);
    }
}

int**  multiplySquareMatricies(const int n, int a[][n], int b[][n], int c[][n]) {
    // base case is 1 x 1 matrix
    // do sum of rows recursively
    // for each int in column[0] sum it into the rows
    int** product = new int*[n];

    for (int i = 0; i < n; i++) {
        product[i] = new int[n];
        for (int j = 0; j < n; j++) {
            product[i][j] = 0;
        }
    }
    std::cout << "init\n";
    // row
    for (int i = 0; i < n; i++) {
        // column
        for (int j = 0; j < n; j++) {
            // iterate through
            for (int k = 0; k < n; k++) {
                product[i][j] = product[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << product[i][j] << ", ";
        }
        std::cout << '\n';
    }

    // recursion come to me
    // base case of 1x1 matrix
    //

    if ()
    return product;
}

// recursive binary search for an array
template <typename T> int recBinSearch(T arr[], int left, int right, T target) {
    int mid = (left + right) / 2;
    
    // yayyyy
    if (arr[mid] == target) {
        return mid;
    }
    // uh oh
    else if (left > right) {
        return -1;
    }
    // get the left side outta here
    else if (arr[mid] < target) {
        return recBinSearch(arr, mid + 1, right, target);
    }
    // get the right side outta here
    else  {
        return recBinSearch(arr, left, mid - 1, target);
    }
}

//checks if any strings in a linked list have one character and are equal to input char
bool oneCharAndEqual (linkedList<std::string> words, std::string wordToCheck) {
    if (wordToCheck.length() != 1) {
        return false;
    }
    // commence the search
    listNode<std::string>* curNode = words.returnHead();

    // returns true if any strings in words has size of 1 and is equal to wordToCheck (which would be a 1 length string)
    for (int i = 0; i < words.size(); i++) {
        if (curNode->data->length() == 1 && (*curNode->data)[0] == wordToCheck[0]) {
            std::cout << "returning true" << '\n';
            return true;
        }
        curNode->inc();
    }

    return false;
}

// recursive check for if wordToCheck is a string in words
bool wordCheck (linkedList<std::string> words, std::string wordToCheck) {
    std::cout << "wordToCheck: " << wordToCheck << '\n';
    if (oneCharAndEqual(words, wordToCheck) == true) {
        return true;
    }
    else if (wordToCheck.length() == 1) {
        return false;
    }
    else {
        char charCheck = wordToCheck[0];
        listNode<std::string>* curWordNode = words.returnHead();

        // check each word in list to see if the first character in remaining string is same as the first
        // in the wordCheck string, which also gets whittled down
        int size = words.size();
        for (int i = 0; i < size; i++) {
            if ((*curWordNode->data)[0] != charCheck) {
                std::cout << "removing word " << *curWordNode->data << '\n';
                words.removeNode(curWordNode);
            }
            else {
                // get rid of first letter in each string, shortens words until one will be equal
                words.searchKey(*curWordNode->data)->data->erase(0, 1);
            }
            curWordNode->inc();
        }
        return wordCheck(words, wordToCheck.erase(0, 1));
    }
}

template <typename T> linkedList<node<T> >* recursiveDFSStart(graph<T>& graph, const int sourceNodeID) {
    if (!graph.connected() || graph.directed) {
        std::cout << "wont run because might seg fault\n";
        return nullptr;
    }
    linkedList<node<T> > visited;
    stack<node<T> > unvisited;
    setAllNodesToUntraversed(graph);
    linkedList<node<T> >* returnList = new linkedList<node<T> >;
    *returnList = recursiveDFS(graph, graph.searchNodeID(sourceNodeID), visited, unvisited);
    return returnList; 
}

template <typename T> linkedList<node<T> > recursiveDFS(graph<T>& graph, node<T>* current, linkedList<node<T> >& visited, stack<node<T> >& unvisited) {
    // add one node to list each time?
    // delete nodes from graph?
    if (visited.size() == graph.nodeCount()) {
        return visited;
    }
    else {
        // do stuff
        current->traversed = true;

        if (!visited.contains(*current)) {
            visited.insertTail(current);
        }

        addUntraversedNeighbours(graph, unvisited, current);

        if (unvisited.size() > 0) {
            current = unvisited.pop()->data;
        }
        return recursiveDFS(graph, current, visited, unvisited);
    }
}

template <typename T> linkedList<node<T> >* recTopSortStart(graph<T>& graph) {
    typedef node<T> node;
    if (graph.directed == false) {
        std::cout << "this graph is not directed\n";
        return nullptr;
    }
    else if (cyclic(graph)) {
        std::cout << "this graph is cyclic\n";
        return nullptr;
    }
    else if (!graph.connected()) {
        std::cout << "this graph is disconnected\n";
        return nullptr;
    }

    setAllNodesToUntraversed(graph);
    stack<node> visited;
    stack<node> unvisited;
    unvisited.push(graph.allNodes().returnHead()->data);
    return recTopSort(graph, graph.allNodes().returnHead()->data , visited, unvisited);
}

template <typename T> linkedList<node<T> >* recTopSort(graph<T>& graph, node<T>* current, stack<node<T> >& visited, stack<node<T> >& unvisited) {
    typedef node<T> node;
    // if top sort is done return opp order topsort push thing
    if (visited.size() == graph.nodeCount()) {
        // reverse it
        linkedList<node>* orderedTopSort = new linkedList<node>;
        for (int i = 0; i < graph.nodeCount(); i++) {
            orderedTopSort->insertTail(visited.pop()->data);
        }

        return orderedTopSort;
    }
    // do more topsorting otherwise
    else {
        // need to call one iteration if it has nodes it can keep traversing
        // only add vertex once all children are explored or it has no children
        if (graph.untraversedNeighbours(current)->size() == 0) {
            current->traversed = true;
            if (!visited.contains(*current)) {
                std::cout << "pushing " << *current << " to visited\n";
                visited.push(current);
            } 
            if (unvisited.size() > 0) {
                return recTopSort(graph, unvisited.pop()->data, visited, unvisited);
            }
            // find node not in visited and set it to that to ensure every node is explored
            listNode<node>* curNode = graph.allNodes().returnHead();
            for (int i = 0; i < graph.nodeCount(); i++) {
                if (!visited.contains(*curNode->data)) {
                    std::cout << "visited does not contain node with id " << curNode->data->id << '\n';
                    return recTopSort(graph, curNode->data, visited, unvisited);
                }
                else if (curNode->next != nullptr) {
                    curNode = curNode->next;
                }
            }
            // prints if all ndoes are in graph after pushing last node to visited
            std::cout << "i dont think this should be printing\n";
            return recTopSort(graph, current, visited, unvisited);
        }
        // continute DFS if not fully explored 
        else {
            addUntraversedNeighbours(graph, unvisited, current);
            if (unvisited.size() > 0) {
                current = unvisited.top()->data;
            }

            return recTopSort(graph, current, visited, unvisited);
        }
    }
}
// prims but recursive
template <typename T> graph<T> recPrimsStart(graph<T>& sourceGraph) {
    if (sourceGraph.directed) {
        std::cout << "theres a good chance this wont be right g\n";
    }
    graph<T> MST(false);
    MST.addNode(sourceGraph.allNodes().returnHead()->data);
    return recPrims(sourceGraph, MST);
}

// add one edge and node and return MST if the node count is the same 
template <typename T> graph<T> recPrims(graph<T>& sourceGraph, graph<T>& MST) {
    // must be an MST if it has all of the nodes
    if (MST.nodeCount() == sourceGraph.nodeCount()) {
        return MST;
    } // add one node and one edge
    else {

        // find crossing edges
        linkedList<edge> crossingEdges;
        listNode<edge>* curEdge = sourceGraph.allEdges().returnHead();
        for(int i = 0; i < sourceGraph.allEdges().size(); i++) {
            // i wish it looked better than this
            if ((MST.allNodes().contains(*sourceGraph.searchNodeID(curEdge->data->start)) && !MST.allNodes().contains(*sourceGraph.searchNodeID(curEdge->data->end))) || (MST.allNodes().contains(*sourceGraph.searchNodeID(curEdge->data->end)) && !MST.allNodes().contains(*sourceGraph.searchNodeID(curEdge->data->start)))) {
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

            if (curCrossingEdge->next != nullptr) {
                curCrossingEdge = curCrossingEdge->next;
            }
        }
        // deletes everything in crossingEdges for clean up
        const int crossingEdgesSize = crossingEdges.size();
        for (int i = crossingEdges.size(); i > 0; i--) {
            crossingEdges.removeAtIndex(i - 1);
        }

        std::cout << "smallest crossing edge is " << *toAdd << " with weight of " << toAdd->weight << '\n';
        // add edge and node it leads to to graph
        if (MST.allNodes().contains(*sourceGraph.searchNodeID(toAdd->start)) && !MST.allNodes().contains(*sourceGraph.searchNodeID(toAdd->end))) {
            MST.addNode(sourceGraph.searchNodeID(toAdd->end));
        }
        else {
            MST.addNode(sourceGraph.searchNodeID(toAdd->start));
        }
        MST.addEdge(toAdd);

        // call thing again
        return recPrims(sourceGraph, MST);
        // easy
    }
}
