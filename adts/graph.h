# pragma once

# include <iostream>
# include "linkedlist.h"

template <typename T> struct node {
    int id;
    T*  attribute;
    bool traversed;
    
    node () {
        attribute = nullptr;
        traversed = false;
    }

    node (int id) {
        this->id = id;
        attribute = nullptr;
        traversed = false;
    }

    node (int id, T* attributeIn) {
        this->id = id;
        this->attribute = attributeIn;
        traversed = false;
    }

    node (int id, T attributeIn) {
        this->id = id;
        T* att = new T;
        *att = attributeIn;
        this->attribute = att;
        traversed = false;
    }
};

template <typename T> std::ostream& operator << (std::ostream& os, const node<T>& node)
{
    //os << "node id is " << node.id << " node attribute is " << node.attribute;
    os << node.id;
    /*if (node.attribute) {
        os << ": " << *node.attribute;
    }*/
    return os;
}

struct edge {
    int start;
    int end;
    int weight;
    
    edge () {}

    edge (int start, int end) {
        this->start = start;
        this->end = end;
        weight = 1;
    }
    
    edge (int start, int end, int weight) {
        this->start = start;
        this->end = end;
        this->weight = weight;
    }
};

std::ostream& operator << (std::ostream& os, const edge& edge)
{
    os << "[" << edge.start << ", " << edge.end <<  "]";
    return os;
}

template <typename T> class graph {
    typedef node<T> node;

    protected:

    linkedList<node> nodes;
    linkedList<edge> edges;

    bool* traversedStates;

    int indexOfId(int id) const;
    bool idExistsInList(int id) const;
    bool idIsConsecutive(int id) const;

    // dangerous sigma
    void addNode (node* add);
    void addNode (node add);

    public:

    const bool directed;
    bool isCyclic;

    graph (bool isDirected) : directed(isDirected) {}

    linkedList<node> allNodes() const;
    linkedList<edge> allEdges() const;

    int nodeCount() const;
    int edgeCount() const;

    void addNode(T attributeIn);
    void addNode(T* attributeIn);
    void addNodes(int n);
    void deleteNode(node* del);

    void addEdge (edge* add);
    void addEdge (edge add);
    void addEdge(int start, int end);
    void addEdge(int start, int end, int weight);
    void deleteEdge (edge* del);

    linkedList<node>* neighbours (node* center, bool directed) const;
    linkedList<node>* untraversedNeighbours (node* center, bool directed) const;
    linkedList<edge>* incident (edge* centerEdge) const;
    int degree(int id) const;

    node* searchNodeID(int id) const;
    int getIndexInAllNodes(int id) const;
    edge* searchEdge(int start, int end) const;
    bool edgeExists(edge edgeToCheck) const;
    bool edgeExists(int start, int end) const;

    void setAllNodesToUntraversed();
    void getTraversedState();
    void resetTraversed();

    bool allNodesAreTraversed() const;
    linkedList<node> traversedNodes() const;
    linkedList<node> untraversedNodes() const;
    void displayTraversedNodes() const;

    bool connected();
    bool cycleCheck(node* current, stack<node>& curStack, linkedList<node>& visited) const;
    bool cyclic() const;

    void makeComplete();

    void displayAttribute(listNode<node>* listNode) const;
    void displayNodeAndAttributes(listNode<node>* nodeSelect) const;
    void printGraphAndAttributes() const;
    bool hasAttribute(T att) const;
    node* searchAttribute(T att) const;

    template<typename U> friend std::ostream& operator << (std::ostream& os, const graph<U>& graph);
};

template<typename T> bool graph<T>::idIsConsecutive(int id) const {
    if (nodes.size() != id) {
        return false;
    }
    else {
        return true;
    }
}

template<typename T> int graph<T>::indexOfId (int idToCheck) const {
    // returns head of the list
    listNode<node>* curNode = nodes.returnHead();
    // checks if id is equal at all
    for (int i = 0; i < nodes.size(); i++) {
        if (curNode->data->id == idToCheck) {
            //std::cout << "found identical id of " << idToCheck << " at index " << i << " of nodes list \n";
            return i;
        }
        else {
            if (curNode->next) {
                curNode = curNode->next;
            }
        }
    }
    return -1;
}

template<typename T> bool graph<T>::idExistsInList(int id) const {
    if (indexOfId(id) != -1) {
        return true;
    }
    else {
        return false;
    }
}

// returns nodes and edges
template<typename T> linkedList<node<T> > graph<T>::allNodes() const {
    return nodes;
}

template<typename T> linkedList<edge> graph<T>::allEdges() const {
    return edges;
}

template<typename T> int graph<T>::nodeCount() const {
    return nodes.size();
}

template<typename T> int graph<T>::edgeCount() const {
    return edges.size();
}

// add node using pointer
template<typename T> void graph<T>::addNode (node* add) {
    // validating id
    if (!idIsConsecutive(add->id)) {
        std::cout << "id is nonconsecutive, therefore cannot add to node list \n";
    }
    if (idExistsInList(add->id)) {
        std::cout << "id of " << add->id << " is equal to id of another node, therefore cannot add to node list \n";
        return;
    }

    //std::cout << "adding node with id " << add->id << "\n";

    nodes.insertTail(add);
}
    
// static implementation
template<typename T> void graph<T>::addNode (node add) {
    node* ptr = new node(add.id, add.attribute);
    addNode(ptr);
}

template<typename T> void graph<T>::addNode(T attributeIn) {
    node* add = new node(nodes.size(), attributeIn);
    addNode(add);
}

template<typename T> void graph<T>::addNode(T* attributeIn) {
    node* add = new node(nodes.size(), attributeIn);
    addNode(add);
}

// add n nodes
template<typename T> void graph<T>::addNodes(int n) {
    int highestID = 0;
    listNode<node>* walk = nodes.returnHead();

    for (int i = 0; i < nodes.size(); i++) {
        if (highestID < walk->data->id) {
            highestID = walk->data->id;
        }
        if (walk->next) {
            walk = walk->next;
        }
    }

    for (int i = 0; i < n; i++) {
        // need a way to delete nodes now
        addNode(node(i + highestID));
    }
}

// has O(n^3)
template<typename T> void graph<T>::deleteNode(node* del) {
    if (idExistsInList(del->id)) {
        nodes.removeAtIndex(indexOfId(del->id));
    }
    else {
        std::cout << "node does not exist in list \n";
    }

    listNode<edge>* walk = edges.returnHead();
    for (int i = 0; i < edges.size(); i++) {
        if (walk->data->start == del->id || walk->data->end == del->id) {
            walk = walk->next;
            edges.removeAtIndex(i);
            i = i - 1;
        }
        else {
            walk = walk->next;
        }
    }
}

// add/ delete edges
template<typename T> void graph<T>::addEdge (edge* add) {

    if (edgeExists(*add)) {
        std::cout << "edge already exists between these two edges, cannot add \n";
        return;
    }
    else if (!idExistsInList(add->start) || !idExistsInList(add->end)) {
        std::cout << "you are trying to add edges to nodes that do not exist in this graph. maybe try to add the node first \n";
        return;
    }
    //std::cout << "adding edge [" << add->start << ", " << add->end << "] to the edges list \n";
    edges.insertTail(add);
}

template<typename T> void graph<T>::addEdge (edge add) {
    edge* toAdd = new edge;
    *toAdd = add;
    addEdge(toAdd);
}

template<typename T> void graph<T>::addEdge(int start, int end) {
    edge* ptr = new edge(start, end);
    addEdge(ptr);
}

template<typename T> void graph<T>::addEdge(int start, int end, int weight) {
    edge* ptr = new edge(start, end, weight);
    addEdge(ptr);
}

// has O(n^2) -- should implement map or associative array
template<typename T> void graph<T>::deleteEdge (edge* del) {
    if (edgeExists(*del)) {
        listNode<edge> *walk = edges.returnHead();
        for (int i = 0; i < edges.size(); i++) {
            if (walk->data->start == del->start && walk->data->end == del->end) {
                edges.removeAtIndex(i);
            }
            else {
                walk = walk->next;
            }
        }
    }
}

// adjacent funcs
template<typename T> linkedList<node<T> >* graph<T>::neighbours (node* center, bool directed) const {
    //return nodes on opposite ends of edges that connect to graph
    listNode<edge>* curEdge = edges.returnHead();
    linkedList<node>* neighbours = new linkedList<node>;

    for (int i = 0; i < edges.size(); i++) {
        if (curEdge->data->start == center->id) {
            neighbours->insertTail(searchNodeID(curEdge->data->end));
            //std::cout << "from " << curEdge->data << " adding " << curEdge->data->end << " to neighbours \n";
        }
        else if (!directed && curEdge->data->end == center->id) {
            neighbours->insertTail(searchNodeID(curEdge->data->start));
            //std::cout << "from " << curEdge->data << " adding " << curEdge->data->start << " to neighbours \n";
        }
        if (curEdge->next) {
            curEdge = curEdge->next;
        }
    }

    return neighbours;
}

template<typename T> linkedList<node<T> >* graph<T>::untraversedNeighbours (node* center, bool directed) const {
    //return nodes on opposite ends of edges that connect to graph
    listNode<edge>* curEdge = edges.returnHead();
    linkedList<node>* untNeighbours = new linkedList<node>;

    for (int i = 0; i < edges.size(); i++) {
        if (curEdge->data->start == center->id && !searchNodeID(curEdge->data->end)->traversed) {
            untNeighbours->insertTail(searchNodeID(curEdge->data->end));
            //std::cout << "from " << curEdge->data << " adding " << curEdge->data->end << " to neighbours \n";
        }
        else if (!directed && curEdge->data->end == center->id && !searchNodeID(curEdge->data->start)->traversed) {
            untNeighbours->insertTail(searchNodeID(curEdge->data->start));
            //std::cout << "from " << curEdge->data << " adding " << curEdge->data->start << " to neighbours \n";
        }

        if (curEdge->next) {
            curEdge = curEdge->next;
        }
    }

    return untNeighbours;
}

// list of edges that an edge shares a common vertex with
template <typename T> linkedList<edge>* graph<T>::incident (edge* centerEdge) const {
    //return nodes on opposite ends of edges that connect to graph
    listNode<edge>* curEdge = edges.returnHead();
    linkedList<edge>* incidentEdges = new linkedList<edge>;

    for (int i = 0; i < edges.size(); i++) {
        if (curEdge->data->start == centerEdge->start || curEdge->data->start == centerEdge->end || curEdge->data->end == centerEdge->start || curEdge->data->end  == centerEdge->end) {
            if (curEdge->data->start != centerEdge->start || curEdge->data->end != centerEdge->end) {
                incidentEdges->insertTail(curEdge->data);
            }
        }
        // dont want to go out of the bounds of the list
        if (curEdge->next) {
            curEdge = curEdge->next;
        }
    }

    return incidentEdges;
}

template<typename T> int graph<T>::degree (int id) const {
    int degree = 0;
    listNode<edge>* curEdge = allEdges().returnHead();

    for (int i = 0; i < allEdges().size(); i++) {
        if (curEdge->data->start == id || curEdge->data->end == id) {
            degree++;
        }
        if (curEdge->next) {
            curEdge = curEdge->next;
        }
    }

    return degree;
}

// misc
template<typename T> node<T>* graph<T>::searchNodeID (int id) const {
    listNode<node>* curNode = allNodes().returnHead();
    for (int i = 0; i < allNodes().size(); i++) {
        if (curNode->data->id == id) {
            return curNode->data;
        }
        //else if (i < allNodes().size() - 1)
        else if (curNode->next) {
            curNode = curNode->next;
        }
    }

    std::cout << "could not find node with id of " << id << " in allNodes()\n";
    return nullptr;
}

template<typename T> int graph<T>::getIndexInAllNodes(int id) const {
    return nodes.getIndex(searchNodeID(id));
}

template<typename T> edge* graph<T>::searchEdge (int start, int end) const {
    listNode<edge>* curEdge = edges.returnHead();
    // O(n)
    for (int i = 0; i < edges.size(); i++) {
        if (curEdge->data->start == start && curEdge->data->end == end) {
            return curEdge->data;
        }
        else if (!directed && curEdge->data->start == end && curEdge->data->end == start) {
            return curEdge->data;
        }
        else if (curEdge->next){
            curEdge = curEdge->next;
        }
    }
    return nullptr;
}

template<typename T> bool graph<T>::edgeExists (edge edgeToCheck) const {
    listNode<edge>* curEdge = edges.returnHead();
    // O(n)
    for (int i = 0; i < edges.size(); i++) {
        if (curEdge->data->start == edgeToCheck.start && curEdge->data->end == edgeToCheck.end) {
            return true;
        }
        else if (this->directed == false && curEdge->data->start == edgeToCheck.end && curEdge->data->end == edgeToCheck.start) {
            return true;
        }
        else {
            curEdge = curEdge->next;
        }
    }
    return false;
}

template<typename T> bool graph<T>::edgeExists (int start, int end) const {
    listNode<edge>* curEdge = edges.returnHead();
    // O(n)
    for (int i = 0; i < edges.size(); i++) {
        if (curEdge->data->start == start && curEdge->data->end == end) {
            return true;
        }
        else if (this->directed == false && curEdge->data->start == end && curEdge->data->end == start) {
            return true;
        }
        else {
            curEdge = curEdge->next;
        }
    }
    return false;
}

// sets every node in graph to untraversed
template<typename T> void graph<T>::setAllNodesToUntraversed() {
    listNode<node>* curNode = allNodes().returnHead();

    // loop and enum again
    for (int i = 0; i < nodeCount(); i++) {
        curNode->data->traversed = false;
        if (curNode->next) {
            curNode = curNode->next;
        }
    }
}

template<typename T> void graph<T>::getTraversedState() {
    bool* state = new bool[nodes.size()];
    listNode<node>* walk = allNodes().returnHead();

    for (int i = 0; i < nodeCount(); i++) {
        state[i] = walk->data->traversed;
        if (walk->next) {
            walk = walk->next;
        }
    }

    traversedStates = state;
}

template<typename T> void graph<T>::resetTraversed() {
    listNode<node>* walk = allNodes().returnHead();

    for (int i = 0; i < nodeCount(); i++) {
        walk->data->traversed = traversedStates[i];

        if (walk->next) {
            walk = walk->next;
        }
    }
}

// check if every node in graph's traversed attribute == true
template<typename T> bool graph<T>::allNodesAreTraversed() const {
    listNode<node>* walk = allNodes().returnHead();

    // for loop and enum
    for (int i = 0; i < nodeCount(); i++) {
        if (!walk->data->traversed) {
            return false;
        }
        if (walk->next) {
            walk = walk->next;
        }
    }
    // otherwise return true
    return true;
}

// returns all traversed nodes
template<typename T> linkedList<node<T> > graph<T>::traversedNodes() const {
    listNode<node>* walk = allNodes().returnHead();
    linkedList<node> traversed;

    for (int i = 0; i < nodeCount(); i++) {
        if (walk->data->traversed) {
            traversed.insertTail(walk->data);
        }
        if (walk->next) {
            walk = walk->next;
        }
    }

    return traversed;
}

// returns all untraversed nodes
template<typename T> linkedList<node<T> > graph<T>::untraversedNodes() const {
    listNode<node>* walk = allNodes().returnHead();

    linkedList<node> untraversed;
    for (int i = 0; i < nodeCount(); i++) {
        if (!walk->data->traversed) {
            untraversed.insertTail(walk->data);
        }
        if (walk->next) {
            walk = walk->next;
        }
    }

    return untraversed;
}

// writes the traversed and untraversed nodes to console, quite useless
template<typename T> void graph<T>::displayTraversedNodes() const {
    std::cout << "traversed: " << traversedNodes() << '\n';
    std::cout << "untraversed: " << untraversedNodes() << '\n';
}

// does a DFS and returns if each node was traversed
template<typename T> bool graph<T>::connected() {
    getTraversedState();
    // DFS aay
    linkedList<node> visited;
    stack<node> unvisited;
    node* current = allNodes().returnHead()->data;

    current->traversed = true;
    visited.insertTail(*current);

    while ((untraversedNeighbours(current, false)->size() > 0 || unvisited.size() > 0 || visited.size() < 1) && !allNodesAreTraversed()) {
        linkedList<node>* untNeighbours = untraversedNeighbours(current, false);
        listNode<node>* curNode = untNeighbours->returnHead();

        for (int i = 0; i < untNeighbours->size(); i++) {
            unvisited.push(curNode->data);
            if (curNode->next) {
                curNode = curNode->next;
            }
        }

        if (unvisited.size() > 0) {
            current = unvisited.pop()->data;
            current->traversed = true;
            if (!visited.contains(*current)) {
                visited.insertTail(*current);
            }
            unvisited.removeKey(*current);
        }
    }

    // nicer than what was here before
    bool allTrav = allNodesAreTraversed();
    resetTraversed();
    return allTrav;
}

// util for cyclic bool praise be to the internet
template<typename T> bool graph<T>::cycleCheck(node* current, stack<node>& curStack, linkedList<node>& visited) const {
    // return cyclic if already in recursion stack
    if (curStack.contains(*current)) {
        //std::cout << "curStack: " << curStack << '\n';
        //std::cout << *current << " is in curStack\n";
        return true;
    }
    // return acyclic if node is visited but not in recursion stack im not actaully sure why this should return false
    if (visited.contains(*current)) {
        return false;
    }

    // add all neighbours to list to check except the node we just came from
    linkedList<node> neighboursToCheck = *neighbours(current, directed);
    // get rid of previous node so we dont go backwards and shit ourselves
    if (curStack.size() > 0) {
        neighboursToCheck.removeKey(*curStack.top()->data);
    }

    curStack.push(current);
    visited.insertTail(current);

    listNode<node>* curNode = neighboursToCheck.returnHead();

    for (int i = 0; i < neighboursToCheck.size(); i++) {
        // loop to check each subtree from each node neighbouring this one
        if (cycleCheck(curNode->data, curStack, visited)) {
            return true;
        }
        if (curNode->next) {
            curNode = curNode->next;
        }
    }
    // get rid of every instance of this node from curstack cos we're going backwards
    curStack.removeKey(*current);
    return false;
}

// DFS return true and needs to set things back to untraversed afterwards
template<typename T> bool graph<T>::cyclic() const {
    stack<node> curStack;
    linkedList<node> visited;
    listNode<node>* curNode = allNodes().returnHead();

    for (int i = 0; i < nodeCount(); i++) {
        if (cycleCheck(curNode->data, curStack, visited)) {
            return true;
        }
        if (curNode->next) {
            curNode = curNode->next;
        }
    }
    return false;
}

template<typename T> void graph<T>::makeComplete() {
    if (this->directed == true) {
        std::cout << "complete graph is directed, returning \n";
        return;
    }
    listNode<node>* start = nodes.returnHead();
    listNode<node>* end = nodes.returnHead();

    for (int i = 0; i < nodes.size(); i++) {
        for (int j = 0; j < nodes.size(); j++) {
            if (i == j) {
                end = end->next;
                continue;
            }
            edge edge(start->data->id, end->data->id);

            if (!edgeExists(edge)) {
                addEdge(start->data->id, end->data->id);
            }
            if (end->next) {
                end = end->next;
            }
        }
        if (start->next) {
            start = start->next;
        }
        end = nodes.returnHead();
    }
}

template<typename T> void graph<T>::displayAttribute(listNode<node>* listNode) const {
    std::cout << *listNode->data->attribute << '\n';
}

template<typename T> void graph<T>::displayNodeAndAttributes(listNode<node>* nodeSelect) const {
    for (int i = 0; i < allNodes().size(); i++) {
        std::cout << "node with id " << nodeSelect->data->id << " has attribute ";
        displayAttribute(nodeSelect);
    }
}

template<typename T> void graph<T>::printGraphAndAttributes() const {
    listNode<node>* walk = allNodes().returnHead();
    std::cout << "graph attributes are: ";
    for (int i = 0; i < nodeCount() - 1; i++) {
        if (walk->data->attribute) {
            std::cout << *walk->data->attribute << ", ";
        }
        else {
            std::cout << "null, ";
        }
        if (walk->next) {
            walk = walk->next;
        }
    }
    if (walk->data->attribute) {
        std::cout << *walk->data->attribute << '\n';
    }
    else {
        std::cout << "null\n";
    }
    std::cout << *this << '\n';
}

template<typename T> bool graph<T>::hasAttribute(T att) const {

    listNode<node>* walk = allNodes().returnHead();

    for (int i = 0; i < nodeCount(); i++) {
        if (*walk->data->attribute == att) {
            return true;
        }

        if (walk->next) {
            walk = walk->next;
        }
    }

    return false;
}

template<typename T> node<T>* graph<T>::searchAttribute(T att) const {

    listNode<node>* walk = allNodes().returnHead();

    for (int i = 0; i < nodeCount(); i++) {
        if (*walk->data->attribute == att) {
            return walk->data;
        }

        if (walk->next) {
            walk = walk->next;
        }
    }

    return nullptr;
}

template<typename T> std::ostream& operator << (std::ostream& os, const graph<T>& graph) {
    if (graph.nodes.size() == 0) {
        os << "nodes is empty \n";
    }
    else {
        os << "graph contains nodes: " << graph.nodes << '\n';
    }

    if (graph.edges.size() == 0) {
        os << "edges is empty";
    }
    else {
        os << "and graph contains edges: " << graph.edges;
    }

    return os;
}

template <typename T> class tree : graph<T> {
    typedef node<T> node;
    node* srcNode;

    public:
    
    tree() : graph<T>(false) {}

    // only add edge if graph isnt cyclic
};

template <typename T> struct binNode {
    typedef binNode<T> node;
    const int id;
    // need to make ref
    T data;
    node* in;
    node* left;
    node* right;

    binNode (int setID) : id(setID) {
        in = nullptr;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T> class binaryTree {
    
    typedef binNode<T> binNode;

    linkedList<binNode> binaryTree;

    // returns mem address of the first node found from head with equal key
    binNode* searchBinNodeID (int id) {
        listNode<binNode>* curNode = binaryTree.returnHead();
        for (int i = 0; i < binaryTree.size(); i++) {
            if (curNode->data->id == id) {
                return &curNode->data;
            }
            else if (curNode->next) {
                curNode = curNode->next;
            }
        }

        std::cout << "could not find node with id of " << id << " in allNodes()\n";
        return nullptr;
    }

    public:

    // thing to add a node
    void addNode(int id, int keyIn, bool isALeftNode) {
        // if there is no node with same id and parent node is in the binary tree add
        if (searchBinNodeID(id) == nullptr && searchBinNodeID(keyIn)) {
            binNode* toAdd = new binNode(id);
            binNode& ref = *toAdd;
            
            // makes sure to not change left or right of parent node if it already points to something
            if (isALeftNode && searchBinNodeID(keyIn)->left == nullptr) {
                searchBinNodeID(keyIn)->left = toAdd;
                ref.in = searchBinNodeID(keyIn);
                binaryTree.insertTail(ref);
                std::cout << "adding node with id " << ref.id << '\n';
            }
            else if (!isALeftNode && searchBinNodeID(keyIn)->right == nullptr){
                searchBinNodeID(keyIn)->right = toAdd;
                ref.in = searchBinNodeID(keyIn);
                binaryTree.insertTail(ref);
                std::cout << "adding node with id " << ref.id << '\n';
            }
            else {
                std::cout << "parent node already has left/right child\n";
            }
        }
        else if (searchBinNodeID(id)) {
            std::cout << "id already exists in binary tree\n";
        }
        else if (searchBinNodeID(keyIn) == nullptr) {
            std::cout << "parent doesn't exist in binary tree\n";
        }
    }

    // case where the node being added is a first node
    void addNode(int id) {
        if (binaryTree.size() != 0) {
            std::cout << "this is not the first node in the binary tree\n";
            return;
        }
        binNode* toAdd = new binNode(id);
        binNode& ref = *toAdd;
        binaryTree.insertTail(ref);
        std::cout << "adding node with id " << ref.id << '\n';
    }   
};
