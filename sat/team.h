# pragma once

# include <iostream>
# include "adts/linkedlist.h"
# include "adts/pair.h"
# include "time/time.h"
# include "sat/checkpoint.h"

class team {
    public :
        int memberCount;
        linkedList<pair<std::string, int> > members;
        timePlaceholder startTime;
        timePlaceholder endTime;
        // linkedList of checkpoints recorded : armbandRegister
        linkedList<pair<checkpoint, timePlaceholder> > checkpointHistory;
        float speed;
        int bracket;

        team () {}

        team(float speedIn, int bracketIndex) : speed(speedIn), bracket(bracketIndex) {}

        team(linkedList<pair<std::string, int> > mems, float speedIn, int bracketIndex) : speed(speedIn), bracket(bracketIndex) {
            members = mems;
        }

        int teamSize();
        linkedList<pair<std::string, int> > teamMembers();
        void setStartTime(timePlaceholder s);
        void setEndTime(timePlaceholder e);
        timePlaceholder getElapsedTime();
        void addCheckpointToArmband(checkpoint* point);
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

void team::addCheckpointToArmband(checkpoint* point) {
    timePlaceholder t = getCurrentTime();
    pair<checkpoint, timePlaceholder> add;
    add.one = point;
    *add.two = getCurrentTime();
    std::cout << "adding " << add << "to armbandregister\n";
    checkpointHistory.insertTail(add);
}
