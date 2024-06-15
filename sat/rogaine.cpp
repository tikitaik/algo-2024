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

    graph<checkpoint> eventMap = constructGraph();
    std::cout << eventMap << '\n';

    rogaineEvent rEvent(eventMap, eventMap.allNodes(), eventMap.allNodes().returnHead()->data, eventMap.allNodes().returnHead()->data, timeLimit, walkSpeed);
    std::cout << getPathTime(eventMap.searchNodeID(0), eventMap.searchNodeID(39), walkSpeed, -1, 1, 0) << '\n';
}
