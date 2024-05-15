#include "adts/linkedlist.h"
#include "adts/graph.h"
#include "adts/traversals.h"
#include "adts/shortPaths.h"
#include "recursion/recursion.h"

int main() {
    graph<int> g(false);
    
    g.addNodes(10);

    g.addEdge(0, 3, 4);
    g.addEdge(0, 1, 10);
    g.addEdge(1, 2, 11);
    g.addEdge(1, 3, 3);
    g.addEdge(1, 4, 17);
    g.addEdge(2, 4, 10);
    g.addEdge(2, 5, 16);
    g.addEdge(3, 4, 13);
    g.addEdge(3, 6, 19);
    g.addEdge(3, 7, 20);
    g.addEdge(4, 7, 9);
    g.addEdge(4, 5, 1);
    g.addEdge(5, 7, 11);
    g.addEdge(5, 8, 18);
    g.addEdge(6, 7, 6);
    g.addEdge(6, 9, 12);
    g.addEdge(7, 9, 15);
    g.addEdge(8, 9, 5);

    std::cout << "DFS: " << DFS(g, 0) << '\n';
    std::cout << "BFS: " << BFS(g, 0) << '\n';
    //std::cout << "topSort: " << *topologicalSort(g) << '\n';
    //std::cout << "topSort: " << *recTopSortStart(g) << '\n';
    
    // bad boy deletes everything
    std::cout << kruskals(g) << '\n';

    std::cout << prims(g) << '\n';
    std::cout << djikstras(g, 8, 0) << '\n';

}
