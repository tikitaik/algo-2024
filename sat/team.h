# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/pair.h"
# include "time/time.h"
# include "sat/goal.h"

class team {
    public :
        int memberCount;
        linkedList<pair<std::string, int> > members;
        timePlaceholder arrivalTime;
        timePlaceholder finishTime;
        // linkedList of goals recorded : armbandRegister
        linkedList<pair<goal, timePlaceholder> > goalHistory;
};
