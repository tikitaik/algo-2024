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

        team() {}

        team(linkedList<pair<std::string, int> > mems) {
            members = mems;
        }

        int teamSize();
        linkedList<pair<std::string, int> > teamMembers();
        void setStartTime(timePlaceholder s);
        void setEndTime(timePlaceholder e);
        timePlaceholder getElapsedTime();
        void addCheckpointToArmband(goal* point);
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
    timePlaceholder t;
    t.time = getCurrentTime().time - startTime.time;
    return t;
}

void team::addCheckpointToArmband(goal* point) {
    timePlaceholder t = getCurrentTime();
    pair<goal, timePlaceholder> add;
    add.one = point;
    *add.two = getCurrentTime();
    std::cout << "adding " << add << "to armbandregister\n";
    goalHistory.insertTail(add);
}
