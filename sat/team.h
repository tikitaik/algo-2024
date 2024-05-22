# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/tuple.h"
# include "sat/goal.h"

class team {
    public :
        int memberCount;
        linkedList<pair<std::string, int> > members;
        uint arrivalTime;
        uint finishTime;
        // linkedList of goals recorded : armbandRegister
        linkedList<pair<goal, int> > goalHistory;
};
