# include <iostream>
# include "time/time.h"
# include "sat/checkpoint.h"
# include "sat/team.h"
# include "sat/rogaineEvent.h"

int main () {
    
    checkpoint g(1.2, 52.232, 0);
    timePlaceholder timeLimit;
    timeLimit.time = 10 * 60 * 60;

    graph<checkpoint> eventMap(true);
    node<checkpoint> n;
    n.attribute = &g;
    eventMap.addNode(&n);

    rogaineEvent rEvent(eventMap, eventMap.allNodes(), eventMap.allNodes().returnHead()->data, eventMap.allNodes().returnHead()->data, timeLimit, 1.5f);

    team t;
    rEvent.addTeamToBracket(&t, 0); 
}
