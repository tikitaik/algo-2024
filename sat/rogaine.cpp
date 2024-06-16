# include <iostream>
# include "time/time.h"
# include "sat/checkpoint.h"
# include "sat/team.h"
# include "sat/rogaineEvent.h"
# include "sat/graphConstructor.h"

# include "adts/traversals.h"
# include "adts/shortPaths.h"

int main () {
    const float walkSpeed = 1.5f;
    
    graph<checkpoint> eventMap = constructGraph(walkSpeed);
    std::cout << eventMap << '\n';

    rogaineEvent rEvent(eventMap, eventMap.allNodes(), eventMap.searchNodeID(0), eventMap.searchNodeID(0), 60 * 6, walkSpeed);

    // prints nodes and coords and point reward
    listNode<node<checkpoint> >* walk = eventMap.allNodes().returnHead();
    for (int i = 0; i < eventMap.allNodes().size(); i++) {
        std::cout << *walk->data << ": " << *walk->data->attribute << '\n';
        if (walk->next) {
            walk = walk->next;
        }
    }
    // prints the edges and their weights
    listNode<edge>* edgeWalk = eventMap.allEdges().returnHead();
    for (int i = 0; i < eventMap.allEdges().size(); i++) {
        std::cout << *edgeWalk->data << ": "<< edgeWalk->data->weight << '\n';
        if (edgeWalk->next) {
            edgeWalk = edgeWalk->next;
        }
    }
    
    listNode<node<checkpoint> >* desWalk = eventMap.allNodes().returnHead();
    for (int i = 0; i < eventMap.allNodes().size(); i++) {
        std::cout << "desirability of " << *desWalk->data << " is " << rEvent.desirability(desWalk->data, 6) << '\n';
        if (desWalk->next) {
            desWalk = desWalk->next;
        }
    }

    std::cout << rEvent.optimalRoute(0) << '\n';
    std::cout << rEvent.optimalRoute(1) << '\n';
    std::cout << rEvent.optimalRoute(2) << '\n';
    std::cout << rEvent.optimalRoute(3) << '\n';
    std::cout << rEvent.optimalRoute(4) << '\n';
    std::cout << rEvent.optimalRoute(5) << '\n';
    std::cout << rEvent.optimalRoute(6) << '\n';
}
