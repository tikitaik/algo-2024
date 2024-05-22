# pragma once

# include <iostream>
# include "adts/linkedlist.h"

class teamData {
    public :
        int memberCount;
        dictionary<std::string, int> members;
        uint arrivalTime;
        uint finishTime;
        linkedList<teamData> bracket;
        // linkedList of goals recorded : armbandRegister
};
