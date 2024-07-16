# include <iostream>
# include "../adts/linkedlist.h"
# include "../adts/pair.h"
# include "../adts/graph.h"
# include "../adts/traversals.h"
# include "../adts/shortPaths.h"
# include "../time/time.h"
# include "../recursion/recursion.h"
# include "../searchAndSortAlgorithms/search.h"
# include "../searchAndSortAlgorithms/sort.h"

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
    //std::cout << "recDFS: " << *recDFSStart(g, 0) << '\n';
    std::cout << "BFS: " << BFS(g, 0) << '\n';
    //std::cout << "topSort: " << *topologicalSort(g) << '\n';
    //std::cout << "recTopSort: " << *recTopSortStart(g) << '\n';

    std::cout << "prims: " << prims(g) << '\n';
    std::cout << "recPrims: " << recPrimsStart(g) << '\n';
    std::cout << "kruskals: " << kruskals(g) << '\n';

    g.setAllNodesToUntraversed();
    // unit test
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (!DFS(g, i).contains(*g.searchNodeID(j))) {
                continue;
            }
            std::cout << dijkstrasPath(g, i, j) << ": " << dijkstrasCost(g, i, j) << '\n';
            std::cout << dijkstrasPathPQ(g, i, j, true) << ": " << dijkstrasCostPQ(g, i, j) << '\n';
        }
    }

    //std::cout << dijkstrasPath(g, 0, 9) << ": " << dijkstrasCost(g, 0, 9) << '\n';
    //std::cout << dijkstrasPathPQ(g, 0, 9, true) << ": " << dijkstrasCostPQ(g, 0, 9) << '\n';
}
