#pragma once

#include <iostream>
#include "linkedlist.h"

template <typename T> struct node {
    int id;
    T*  attribute;
    bool traversed;
    
    node () {
        traversed = false;
    }

    node (int id) {
        this->id = id;
        traversed = false;
    }
};

template <typename T> std::ostream& operator << (std::ostream& os, const node<T>& node)
{
    //os << "node id is " << node.id << " node attribute is " << node.attribute;
    os << node.id;
    return os;
}

struct edge {
    int start;
    int end;
    int weight;

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
    protected:

    typedef node<T> node;
    linkedList<node> nodes;
    linkedList<edge> edges;

    int indexOfId (int idToCheck) {
        // returns head of the list
        listNode<node>* curNode = nodes.returnHead();
        // checks if id is equal at all
        for (int i = 0; i < nodes.size(); i++) {
            if (curNode->data->id == idToCheck) {
                //std::cout << "found identical id of " << idToCheck << " at index " << i << " of nodes list \n";
                return i;
            }
            else {
                if (i < nodes.size() - 1) {
                    curNode = curNode->next;
                }
            }
        }
        return -1;
    }

    bool idExistsInList(int id) {
        if (indexOfId(id) != -1) {
            return true;
        }
        else {
            return false;
        }
    }

    int start (const edge& edge) {
        return nodes.goToIndex(0)->data->id;
    }

    int end (const edge& edge) {
        return nodes.goToIndex(nodes.size() - 1)->data->id;
    }

    public:

    const bool directed;
    bool isCyclic;

    graph (bool isDirected) : directed(isDirected) {
        if (directed == true) {
            isCyclic = false;
        }
        else {
            isCyclic = true;
        }
    }

    // returns nodes and edges
    linkedList<node>& allNodes () {
        linkedList<node>& allNodes = nodes;
        return allNodes;
    }

    linkedList<edge>& allEdges () {
        linkedList<edge>& allEdges = edges;
        return allEdges;
    }

    int nodeCount() {
        return nodes.size();
    }

    int edgeCount() {
        return edges.size();
    }

    // add node using pointer
    void addNode (node* add) {

        // validating id
        if (add->id < 0) {
            std::cout << "id is < 0, therefore cannot add to node list \n";
        }
        if (idExistsInList(add->id)) {
            std::cout << "id of " << add->id << " is equal to id of another node, therefore cannot add to node list \n";
            return;
        }
                
        //std::cout << "adding node with id " << add.id << "\n";

        nodes.insertTail(add);
    }
    // static implementation
    void addNode (node add) {
        node* ptr = new node(add.id);
        addNode(ptr);
    }

    void addNode(int id) {
        node* add = new node(id);
        addNode(add);
    }
    // add n nodes
    void addNodes(int n) {
        int highestID = 0;
        listNode<node>* curListNode = nodes.returnHead();

        for (int i = 0; i < nodes.size(); i++) {
            if (highestID < curListNode->data->id) {
                highestID = curListNode->data->id;
            }
            if (i < nodes.size() - 1) {
                curListNode = curListNode->next;
            }
        }

        for (int i = 0; i < n; i++) {
            // need a way to delete nodes now
            addNode(i + highestID);
        }
    }

    // has O(n^3)
    void deleteNode(node* del) {
        if (idExistsInList(del->id)) {
            nodes.removeAtIndex(indexOfId(del->id));
        }
        else {
            std::cout << "node does not exist in list \n";
        }

        listNode<edge>* curListNode = edges.returnHead();
        for (int i = 0; i < edges.size(); i++) {
            if (curListNode->data->start == del->id || curListNode->data->end == del->id) {
                curListNode = curListNode->next;
                edges.removeAtIndex(i);
                i = i - 1;
            }
            else {
                curListNode = curListNode->next;
            }
        }
    }

    // add/ delete edges
    void addEdge (edge* add) {
        
        if (edgeExists(*add)) {
            std::cout << "edge already exists between these two edges, cannot add \n";
            return;
        }
        else if (!idExistsInList(add->start) || !idExistsInList(add->end)) {
            std::cout << "you are trying to add edges to nodes that do not exsist in this graph. maybe try to add the node first \n";
            return;
        }
        std::cout << "adding edge [" << add->start << ", " << add->end << "] to the edges list \n";
        edges.insertTail(add);
    }

    void addEdge(int start, int end) {
        edge* ptr = new edge(start, end);
        addEdge(ptr);
    }

    void addEdge(int start, int end, int weight) {
        edge* ptr = new edge(start, end, weight);
        addEdge(ptr);
    }

    // has O(n^2) -- should implement map or associative array
    void deleteEdge (edge* del) {
        if (edgeExists(*del)) {
            listNode<edge> *curListNode = edges.returnHead();
            for (int i = 0; i < edges.size(); i++) {
                if (curListNode->data->start == del->start && curListNode->data->end == del->end) {
                    edges.removeAtIndex(i);
                }
                else {
                    curListNode = curListNode->next;
                }
            }
        }
    }

    // adjacent funcs
    linkedList<node>* neighbours (node* center) {
        //return nodes on opposite ends of edges that connect to graph
        listNode<edge>* curEdge = edges.returnHead();
        linkedList<node>* neighbours = new linkedList<node>;

        for (int i = 0; i < edges.size(); i++) {
            if (curEdge->data->start == center->id) {
                neighbours->insertTail(nodes.goToIndex(indexOfId(curEdge->data->end))->data);
                //std::cout << "from " << curEdge->data << " adding " << curEdge->data->end << " to neighbours \n";
            }
            else if (this->directed == false && curEdge->data->end == center->id) {
                neighbours->insertTail(nodes.goToIndex(indexOfId(curEdge->data->start))->data);
                //std::cout << "from " << curEdge->data << " adding " << curEdge->data->start << " to neighbours \n";
            }
            if (i < edges.size() - 1) {
                curEdge = curEdge->next;
            }
        }

        return neighbours;
    }

    linkedList<node>* untraversedNeighbours (node* center) {
        //return nodes on opposite ends of edges that connect to graph
        listNode<edge>* curEdge = edges.returnTail();
        linkedList<node>* untNeighbours = new linkedList<node>;

        for (int i = 0; i < edges.size(); i++) {
            if (curEdge->data->start == center->id && !searchNodeID(curEdge->data->end)->traversed) {
                untNeighbours->insertTail(nodes.goToIndex(indexOfId(curEdge->data->end))->data);
                //std::cout << "from " << curEdge->data << " adding " << curEdge->data->end << " to neighbours \n";
            }
            else if (this->directed == false && curEdge->data->end == center->id && !searchNodeID(curEdge->data->start)->traversed) {
                untNeighbours->insertTail(nodes.goToIndex(indexOfId(curEdge->data->start))->data);
                //std::cout << "from " << curEdge->data << " adding " << curEdge->data->start << " to neighbours \n";
            }
            if (i < edges.size() - 1) {
                curEdge = curEdge->prev;
            }
        }

        return untNeighbours;
    }
    
    // list of edges that an edge shares a common vertex with
    linkedList<edge>* incident (edge* centerEdge) {
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
            if (i < edges.size() - 1) {
                curEdge = curEdge->next;
            }
        }

        return incidentEdges;
    }

    int degree (int id) {
        int degree = 0;
        listNode<edge>* curEdge = allEdges().returnHead();

        for (int i = 0; i < allEdges().size(); i++) {
            if (curEdge->data->start == id || curEdge->data->end == id) {
                degree++;
            }
            if (curEdge->next != nullptr) {
                curEdge = curEdge->next;
            }
        }

        return degree;
    }

    node* searchNodeID (int id) {
        listNode<node>* curNode = allNodes().returnHead();
        for (int i = 0; i < allNodes().size(); i++) {
            if (curNode->data->id == id) {
                return curNode->data;
            }
            else if (i < allNodes().size() - 1) {
                curNode = curNode->next;
            }
        }

        std::cout << "could not find node with id of " << id << " in allNodes()\n";
        return nullptr;
    }

    // misc
    bool edgeExists (edge edgeToCheck) {
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

    bool edgeExists (int start, int end) {
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

    // checks if each node id exists in at least one edge
    bool connected() {
        int nodeUsed[nodes.size()];
        listNode<edge>* curEdge = edges.returnHead();
        listNode<node>* curNode = nodes.returnHead();

        for (int i = 0; i < edges.size(); i++) {
            curNode = nodes.returnHead();

            for (int j = 0; j < nodes.size(); j++) {
                if ((curNode->data->id == curEdge->data->start || curNode->data->id == curEdge->data->end) && nodeUsed[nodes.getIndex(curNode->data)] != 1) {
                    nodeUsed[nodes.getIndex(curNode->data)] = 1;
                }
                if (j < nodes.size() - 1) {
                    curNode = curNode->next;
                }
            }
            if (i < edges.size() - 1) {
                curEdge = curEdge->next;
            }
        }

        for (int i = 0; i < sizeof(nodeUsed) / sizeof(nodeUsed[0]); i++) {
            if (nodeUsed[i] != 1){
                return false;
            }
        }

        return true;
    }

    // O(n^2)
    void makeComplete() {
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
                if (j < nodes.size() - 1) {
                    end = end->next;
                }
            }
            if (i < nodes.size() - 1) {
                start = start->next;
            }
            end = nodes.returnHead();
        }
    }

    void displayAttribute(listNode<node>* listNode) {
        std::cout << listNode->data->attribute;
    }

    void displayNodeAndAttributes(listNode<node>* nodeSelect) {
        for (int i = 0; i < allNodes().size(); i++) {
            std::cout << "node with id " << nodeSelect->data->id << " has attribute ";
            displayAttribute(nodeSelect);
        }
    }

    // outside funcs for trav algorithms
    //inkedList<node> DFS (const int source);
    //linkedList<node> BFS (const int source);
    //linkedList<node>* topologicalSort();

    // outside funcs for mst algorithms
    //graph prims();
    //graph prims(const int sourceNode);
    //graph kruskals(const int sourceNode);*/

    template<typename U> friend std::ostream& operator << (std::ostream& os, const graph<U>& graph);
};

template<typename T> std::ostream& operator << (std::ostream& os, const graph<T>& graph) {
    if (*graph.nodes.sptr == 0) {
        os << "nodes is empty \n";
    }
    else {
        os << "graph contains nodes: " << graph.nodes << '\n';
    }

    if (*graph.edges.sptr == 0) {
        os << "edges is empty \n";
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
            else if (curNode->next != nullptr) {
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
        if (searchBinNodeID(id) == nullptr && searchBinNodeID(keyIn) != nullptr) {
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
        else if (searchBinNodeID(id) != nullptr) {
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
