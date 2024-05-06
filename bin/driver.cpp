#include "adts/linkedlist.h"
#include "adts/graph.h"
#include "adts/traversals.h"
#include "adts/shortPaths.h"
#include "recursion/recursion.h"

int main() {
    /*graph<int> graphTest(true);
    
    graphTest.addNodes(10);

    graphTest.addEdge(0, 3, 4);
    graphTest.addEdge(0, 1, 10);
    graphTest.addEdge(1, 2, 11);
    graphTest.addEdge(1, 3, 3);
    graphTest.addEdge(1, 4, 17);
    graphTest.addEdge(2, 4, 10);
    graphTest.addEdge(2, 5, 16);
    graphTest.addEdge(3, 4, 13);
    graphTest.addEdge(3, 6, 19);
    graphTest.addEdge(3, 7, 20);
    graphTest.addEdge(4, 7, 9);
    graphTest.addEdge(4, 5, 1);
    graphTest.addEdge(5, 7, 11);
    graphTest.addEdge(5, 8, 18);
    graphTest.addEdge(6, 7, 6);
    graphTest.addEdge(6, 9, 12);
    graphTest.addEdge(7, 9, 15);
    graphTest.addEdge(8, 9, 5);

    std::cout << graphTest << '\n';
    displayTraversed(graphTest);
    std::cout << "DFS: " << DFS(graphTest, 0) << '\n';
    std::cout << "BFS: " << BFS(graphTest, 0) << '\n';
    std::cout << "topSort: " << *topologicalSort(graphTest) << '\n';
    std::cout << "topSort: " << *recTopSortStart(graphTest) << '\n';
    std::cout << prims(graphTest) << '\n';
    std::cout << recPrimsStart(graphTest) << '\n';
    //displayMatrix2D(adjMatrix2D(graphTest), graph.nodeCount());
    //std::cout << adjDFS(adjMatrix2D(graphTest), graph.nodeCount(), 0) << '\n';
    //displayMatrix2D(FWTC(graphTest), graph.nodeCount());*/

    graph<int> graphTopSort(true);

    graphTopSort.addNodes(5);

    graphTopSort.addEdge(0, 1);
    graphTopSort.addEdge(0, 2);
    graphTopSort.addEdge(0, 4);
    graphTopSort.addEdge(1, 3);
    graphTopSort.addEdge(1, 4);
    graphTopSort.addEdge(2, 3);
    graphTopSort.addEdge(2, 4);
    graphTopSort.addEdge(3, 4);

    
    std::cout << "recTopSort:\n" << *recTopSortStart(graphTopSort) << '\n';
    std::cout << "topSortNormal:\n" << *topologicalSort(graphTopSort) << '\n';

    //std::cout << fastExp(15, 5) << '\n';
    
}
