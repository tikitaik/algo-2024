# include <iostream>
# include "sat/goal.h"
# include "sat/team.h"
# include "sat/rogaineEvent.h"

int main () {
    
    float start[2] = { 0.252f, 0.134f };
    float end[2] = { 0.234532f, 1.2525f }; 

    linkedList<goal> points;
    
    goal g(1.2, 52.232, 1212);

    graph<goal> eventMap(true);
    linkedList<goal> goals;
    goals.insertTail(&g);

    rogaineEvent rEvent(eventMap, start, end, goals);

    team t;
    rEvent.addTeamToBracket(&t, 0); 
}
