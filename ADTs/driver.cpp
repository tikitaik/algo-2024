#include "linkedlist.h"
#include "graph.h"
#include "traversals.h"
#include "shortPaths.h"

int main() {
    graph graph(true);
    
    graph.addNodes(10);

    graph.addEdge(0, 3, 4);
    graph.addEdge(0, 1, 10);
    graph.addEdge(1, 2, 11);
    graph.addEdge(1, 3, 3);
    graph.addEdge(1, 4, 17);
    graph.addEdge(2, 4, 10);
    graph.addEdge(2, 5, 16);
    graph.addEdge(3, 4, 13);
    graph.addEdge(3, 6, 19);
    graph.addEdge(3, 7, 20);
    graph.addEdge(4, 7, 9);
    graph.addEdge(4, 5, 1);
    graph.addEdge(5, 7, 11);
    graph.addEdge(5, 8, 18);
    graph.addEdge(6, 7, 6);
    graph.addEdge(6, 9, 12);
    graph.addEdge(7, 9, 15);
    graph.addEdge(8, 9, 5);

    std::cout << graph << '\n';
    std::cout << "DFS: " << graph.DFS(0) << '\n';
    std::cout << "topSort: " << *graph.topologicalSort() << '\n';
    std::cout << graph.prims() << '\n';
    graph.displayMatrix2D(graph.FWTC(), graph.allNodes().size());
}
