# include <iostream>
# include "checkpoint.h"
# include "team.h"
# include "rogaineEvent.h"
# include "graphConstructor.h"
# include "../adts/traversals.h"
# include "../adts/shortPaths.h"
# include "../time/time.h"

int main () {
    team t[10][6];
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 6; j++) {
            t[i][j] = team(1 + i * 0.1, j);
        }
    }
    
    graph<checkpoint> eventMap = initGraphCheckpoints();

    // prints nodes and coords and point reward
    listNode<node<checkpoint> >* walk = eventMap.allNodes().returnHead();
    for (int i = 0; i < eventMap.allNodes().size(); i++) {
        std::cout << *walk->data << ": " << *walk->data->attribute << '\n';
        if (walk->next) {
            walk = walk->next;
        }
    }

    rogaineEvent rEvent(eventMap, eventMap.allNodes(), eventMap.searchNodeID(0), eventMap.searchNodeID(0), 60 * 6);

    int scores[10][6];
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << rEvent.optimalRoute(t[j][i]) << '\n';
        }
    }
    //std::cout << rEvent.optimalRoute(t[9][0]) << '\n';
    //std::cout << rEvent.optimalRoute(t[0][0]) << '\n';
    //std::cout << rEvent.optimalRoute(team(1.8, 0)) << '\n';
    //std::cout << rEvent.optimalRoute(team(1.8, 1)) << '\n';
    std::cout << rEvent.desirabilityCount << '\n';
}
