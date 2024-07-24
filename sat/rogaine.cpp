# include <iostream>
# include "checkpoint.h"
# include "team.h"
# include "rogaineEvent.h"
# include "graphConstructor.h"
# include "../adts/traversals.h"
# include "../adts/shortPaths.h"
# include "../time/time.h"

int main () {
    
    graph<checkpoint> eventMap = initGraphCheckpoints();

    // prints nodes and coords and point reward
    listNode<node<checkpoint> >* walk = eventMap.allNodes().returnHead();
    for (int i = 0; i < eventMap.allNodes().size(); i++) {
        std::cout << *walk->data << ": " << *walk->data->attribute << '\n';
        if (walk->next) {
            walk = walk->next;
        }
    }

    rogaineEvent rEvent(60 * 6);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << rEvent.optimalRoute(team(1 + j * 0.1, i)) << '\n';
        }
    }
}
