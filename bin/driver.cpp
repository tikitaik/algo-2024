# include "adts/linkedlist.h"
# include "adts/pair.h"
# include "adts/graph.h"
# include "adts/traversals.h"
# include "adts/shortPaths.h"
# include "time/time.h"
# include "recursion/recursion.h"

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
    int startId = 8;
    int endId = 2;
    std::cout << djikstrasPath(g, startId, endId) << '\n';
    std::cout << djikstrasCost(g, startId, endId) << '\n';

    displayMatrix2D(FWSP(g), g.nodeCount());

    /*
    // pair testing
    pair<int, int> p(4, 6);
    std::cout << p << '\n';
    linkedList<pair<int, std::string> > l;
    l.insertTail(pair<int, std::string>(5, "hi"));
    std::cout << l << '\n';

    // time testing
    timePlaceholder t;
    t.time = 864000;
    std::cout << t << '\n';

    // dictionary testing
    dictionary<int, char> d;
    d.insert(4, 'g');
    d.insert(6, 'w');
    std::cout << d << '\n';
    std::cout << d.getValue(6) << '\n';

    graph<int> h(false);
    h.addNodes(5);
    h.addEdge(0, 1, 2);
    h.addEdge(0, 3, 8);
    h.addEdge(1, 2, 3);
    h.addEdge(1, 4, 7);
    h.addEdge(2, 3, 1);
    h.addEdge(2, 4, 5);
    h.addEdge(3, 4, 4);

    int** f = FWTC(h);
    int** s = FWSP(h);

    displayMatrix2D(f, 5);
    displayMatrix2D(s, 5);
    std::cout << djikstrasPath(h, 0, 4) << '\n';*/
}
