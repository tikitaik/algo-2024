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
    std::cout << eventMap.allNodes().size() << '\n';
    std::cout << eventMap.allEdges().size() << '\n';
}
