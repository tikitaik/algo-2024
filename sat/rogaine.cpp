# include <iostream>
# include "checkpoint.h"
# include "team.h"
# include "rogaineEvent.h"
# include "graphConstructor.h"
# include "../adts/traversals.h"
# include "../time/time.h"

int main () {
    
    graph<checkpoint> eventMap = initEventCheckpoints();

    // prints nodes and coords and point reward
    listNode<node<checkpoint> >* walk = eventMap.allNodes().returnHead();
    /*while (walk) {
        std::cout << *walk->data << ": " << *walk->data->attribute << '\n';
        walk = walk->next;
    }*/

    rogaineEvent rEvent(60 * 6);
    int scores[6 * 10];

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 10; j++) {
            rEvent.optimalRoute(team(1 + j * 0.1, i));
        }
        std::cout << '\n';
    }
}
