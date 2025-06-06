# pragma once

# include <iostream>
# include "../adts/linkedlist.h"
# include "../adts/graph.h"
# include "../adts/traversals.h"

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

// this shit suckcs dick
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
        if (curNode->next) {
            curNode = curNode->next;
        }
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
            if (curWordNode->next) {
                curWordNode = curWordNode->next;
            }
        }
        return wordCheck(words, wordToCheck.erase(0, 1));
    }
}

template <typename T> linkedList<node<T> >* recDFSStart(graph<T>& g, const int sourceNodeID) {
    if (!g.connected() || g.directed) {
        std::cout << "wont run because might seg fault\n";
        return nullptr;
    }
    linkedList<node<T> > visited;
    stack<node<T> > unvisited;
    g.getTraversedState();
    linkedList<node<T> >* returnList = new linkedList<node<T> >;
    *returnList = recursiveDFS(g, g.searchNodeID(sourceNodeID), visited, unvisited);
    return returnList; 
}

template <typename T> linkedList<node<T> > recursiveDFS(graph<T>& g, node<T>* current, linkedList<node<T> >& visited, stack<node<T> >& unvisited) {
    // add one node to list each time?
    // delete nodes from g?
    if (visited.size() == g.nodeCount()) {
        g.resetTraversed();
        return visited;
    }
    else {
        // do stuff
        current->traversed = true;

        if (!visited.contains(*current)) {
            visited.insertTail(*current);
        }

        addUntraversedNeighbours(g, unvisited, current);

        if (unvisited.size() > 0) {
            current = unvisited.pop()->data;
        }
        return recursiveDFS(g, current, visited, unvisited);
    }
}

template <typename T> linkedList<node<T> >* recTopSortStart(graph<T>& g) {
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

    g.getTraversedState();
    stack<node> visited;
    stack<node> unvisited;
    unvisited.push(g.allNodes().returnHead()->data);
    return recTopSort(g, g.allNodes().returnHead()->data , visited, unvisited);
}

template <typename T> linkedList<node<T> >* recTopSort(graph<T>& g, node<T>* current, stack<node<T> >& visited, stack<node<T> >& unvisited) {
    typedef node<T> node;
    // if top sort is done return opp order topsort push thing
    if (visited.size() == g.nodeCount()) {
        // reverse it
        linkedList<node>* orderedTopSort = new linkedList<node>;
        for (int i = 0; i < g.nodeCount(); i++) {
            node* add = visited.pop()->data;
            orderedTopSort->insertTail(*add);
            delete add;
        }

        g.resetTraversed();
        return orderedTopSort;
    }
    // do more topsorting otherwise
    else {
        // need to call one iteration if it has nodes it can keep traversing
        // only add vertex once all children are explored or it has no children
        if (g.untraversedNeighbours(current, g.directed)->size() == 0) {
            current->traversed = true;
            if (!visited.contains(*current)) {
                //std::cout << "pushing " << *current << " to visited\n";
                visited.push(*current);
            } 
            if (unvisited.size() > 0) {
                return recTopSort(g, unvisited.pop()->data, visited, unvisited);
            }
            // find node not in visited and set it to that to ensure every node is explored
            listNode<node>* curNode = g.allNodes().returnHead();
            for (int i = 0; i < g.nodeCount(); i++) {
                if (!visited.contains(*curNode->data)) {
                    //std::cout << "visited does not contain node with id " << curNode->data->id << '\n';
                    return recTopSort(g, curNode->data, visited, unvisited);
                }
                else if (curNode->next) {
                    curNode = curNode->next;
                }
            }
            // prints if all ndoes are in g after pushing last node to visited
            //std::cout << "i dont think this should be printing\n";
            return recTopSort(g, current, visited, unvisited);
        }
        // continute DFS if not fully explored 
        else {
            addUntraversedNeighbours(g, unvisited, current);
            if (unvisited.size() > 0) {
                current = unvisited.top()->data;
            }

            return recTopSort(g, current, visited, unvisited);
        }
    }
}
// prims but recursive
template <typename T> graph<node<T> > recPrimsStart(graph<T>& g) {
    if (g.directed) {
        std::cout << "theres a good chance this wont be right g\n";
    }
    graph<node<T> > MST(false);
    MST.addNode(g.allNodes().returnHead()->data);
    return recPrims(g, MST);
}

// add one edge and node and return MST if the node count is the same 
template <typename T> graph<node<T> > recPrims(graph<T>& g, graph<node<T> >& MST) {
    // must be an MST if it has all of the nodes
    if (MST.nodeCount() == g.nodeCount()) {
        return MST;
    } // add one node and one edge
    else {

        // find crossing edges
        linkedList<edge> crossingEdges;
        listNode<edge>* curEdge = g.allEdges().returnHead();
        for(int i = 0; i < g.allEdges().size(); i++) {
            // i wish it looked better than this
            if ((MST.hasAttribute(*g.searchNodeID(curEdge->data->start)) && !MST.hasAttribute(*g.searchNodeID(curEdge->data->end))) || (MST.hasAttribute(*g.searchNodeID(curEdge->data->end)) && !MST.hasAttribute(*g.searchNodeID(curEdge->data->start)))) {
                crossingEdges.insertTail(curEdge->data);
                //std::cout << "adding edge " << *curEdge->data << " to crossingEdges\n";
            }

            if(curEdge->next) {
                curEdge = curEdge->next;
            }
        }

        // find minimal edge from crossingEdges
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
        const int crossingEdgesSize = crossingEdges.size();
        for (int i = crossingEdges.size(); i > 0; i--) {
            crossingEdges.removeAtIndex(i - 1);
        }

        //std::cout << "smallest crossing edge is " << *minimalEdge << " with weight of " << minimalEdge->weight << '\n';
        // add edge and node it leads to to graph
        if (MST.hasAttribute(*g.searchNodeID(minimalEdge->start)) && !MST.hasAttribute(*g.searchNodeID(minimalEdge->end))) {
            MST.addNode(g.searchNodeID(minimalEdge->end));
        }
        else {
            MST.addNode(g.searchNodeID(minimalEdge->start));
        }
        
        MST.addEdge(edge(MST.searchAttribute(*g.searchNodeID(minimalEdge->start))->id, MST.searchAttribute(*g.searchNodeID(minimalEdge->end))->id));

        // call thing again
        return recPrims(g, MST);
        // easy
    }
}

bool isPowerOfTwo (int n) {
    if (n == 1) {
        return false;
    }
    while (n % 2 == 0 && n != 1) {
        n = n / 2;
    }

    if (n == 1) {
        return true;
    }
    else return false;
}

void printProductMatrix(int** product, int len) {
    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            std::cout << product[i][j] << ' ';
        }
        std::cout << '\n';
    }
}

int** recSquareMatrixMultiplication(int** matA, int** matB, int** product, int len) {
    // do the multiplication
    // repeat len times
    static int i = 0, j = 0, k = 0;

    if (i >= len)
        return product;

    // If i < row1
    if (j < len) {
        if (k < len) {
            product[i][j] += matA[i][k] * matB[k][j];
            k++;

            recSquareMatrixMultiplication(matA, matB, product, len);
        }

        k = 0;
        j++;
        recSquareMatrixMultiplication(matA, matB, product, len);
    }

    j = 0;
    i++;
    recSquareMatrixMultiplication(matA, matB, product, len);
    
    return product;
}

// only works for square arrays of size 2^n
int** recSquareMatrixMultiplication(int** matA, int** matB, int len) {
    // check that len is a power of two
    if (!isPowerOfTwo(len)) {
        std::cout << "len is not a power of 2 therefore cannot multiply!\n";
        return nullptr;
    }

    // init product array
    int** product =  new int* [len];
    for (int i = 0; i < len; i++) {

        product[i] = new int [len];

        for (int j = 0; j < len; j++) {
            product[i][j] = 0;
        }
    }

    // go along row for matA and down column for matB
    return recSquareMatrixMultiplication(matA, matB, product, len);
}
