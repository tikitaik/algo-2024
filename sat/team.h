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
        timePlaceholder startTime;
        timePlaceholder endTime;
        // linkedList of goals recorded : armbandRegister
        linkedList<pair<goal, timePlaceholder> > goalHistory;

        public team() {}

        public team(linkedList<pair<std::string, int> > mems) {
            members = mems;
        }

        int teamSize();
        linkedlist<pair<std::string, int> > teamMembers();
        void setStartTime(timePlaceholder s);
        void setEndTime(timePlaceholder e);
        timePlaceholder getElapsedTime();
        void addCheckpointToArmband(goal point);
};

int team::teamSize() {
    return memberCount;
}

linkedList<pair<std::string, int> > team::teamMembers() {
    return members;
}

void team::setStartTime(timePlaceholder s) {
    startTime = s;
}

void team::setEndTime(timePlaceholder e) {
    endTime = e;
}

timePlaceholder team::getElapsedTime() {
    return getCurrentTime() - startTime;
}

void team::addCheckpointToArmband(goal point) {
    pair<goal, timePlaceholder> add(goal, getCurrentTime());
    std::cout << "adding " << add << "to armbandregister\n";
    goalHistory.insertTail(add);
}
