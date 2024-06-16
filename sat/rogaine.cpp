# include <iostream>
# include "time/time.h"
# include "sat/checkpoint.h"
# include "sat/team.h"
# include "sat/rogaineEvent.h"
# include "sat/graphConstructor.h"

int main () {
    const float walkSpeed = 1.5f;
    
    timePlaceholder timeLimit;
    timeLimit.time = 10 * 60 * 60;

    graph<checkpoint> eventMap = constructGraph(walkSpeed);
    std::cout << eventMap << '\n';

    rogaineEvent rEvent(eventMap, eventMap.allNodes(), eventMap.allNodes().returnHead()->data, eventMap.allNodes().returnHead()->data, timeLimit, walkSpeed);

    listNode<node<checkpoint> >* walk = eventMap.allNodes().returnHead();
    for (int i = 0; i < eventMap.allNodes().size(); i++) {
        std::cout << *walk->data << '\n';
        if (walk->next) {
            walk = walk->next;
        }
    }
    listNode<edge>* edgeWalk = eventMap.allEdges().returnHead();
    for (int i = 0; i < eventMap.allEdges().size(); i++) {
        std::cout << *edgeWalk->data << ": "<< edgeWalk->data->weight << '\n';
        if (edgeWalk->next) {
            edgeWalk = edgeWalk->next;
        }
    }
}
