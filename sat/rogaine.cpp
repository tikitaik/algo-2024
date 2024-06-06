# include <iostream>
# include "sat/goal.h"
# include "sat/team.h"
# include "sat/rogaineEvent.h"

int main () {
    
    float start[2] = { 0.252f, 0.134f };
    float end[2] = { 0.234532f, 1.2525f }; 

    rogaineEvent rEvent(start, end);
    rEvent.addGoal(0.123f, 0.252f, 112);

    
}
