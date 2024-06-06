# include <iostream>
# include "adts/linkedlist.h"
# include "adts/pair.h"
# include "adts/graph.h"
# include "adts/traversals.h"
# include "adts/shortPaths.h"
# include "time/time.h"
# include "recursion/recursion.h"
# include "searchAndSortAlgorithms/search.h"
# include "searchAndSortAlgorithms/sort.h"

void test(int n, int** arr) {
    std::cout << "hi!" << '\n';
}

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
    std::cout << "recDFS: " << *recDFSStart(g, 0) << '\n';
    std::cout << "BFS: " << BFS(g, 0) << '\n';
    //std::cout << "topSort: " << *topologicalSort(g) << '\n';
    //std::cout << "recTopSort: " << *recTopSortStart(g) << '\n';

    std::cout << "prims: " << prims(g) << '\n';
    std::cout << "recPrims: " << recPrimsStart(g) << '\n';
    std::cout << "kruskals: " << kruskals(g) << '\n';
    std::cout << djikstras(g, 9, 1) << '\n';

    int test[10] = {677, 1424, 5, 1241, -1, 73, 13, 568, 8, -124 };
    binarySearch(test, 10, 9);
    int* sorted = insertionSort(test, 10);
    for (int i = 0; i < 9; i++) {
        std::cout << sorted[i] << ", ";
    }
    std::cout << sorted[9] << '\n';
}
