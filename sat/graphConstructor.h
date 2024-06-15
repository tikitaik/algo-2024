# pragma once

# include <iostream>
# include "adts/graph.h"
# include "adts/pair.h"

# define METER 1 / 0.190 // one km is 190 pixels

graph<checkpoint> initGraphCheckpoints() {
    graph<checkpoint> g(true);

    // every goal - coordinates are in pixels
    g.addNode(0, checkpoint(891, 863, 0));
    g.addNode(1, checkpoint(220, 964, 32));
    g.addNode(2, checkpoint(365, 1193, 83));
    g.addNode(3, checkpoint(336, 1035, 57));
    g.addNode(4, checkpoint(478, 878, 63));
    g.addNode(5, checkpoint(344, 859, 56));
    g.addNode(6, checkpoint(518, 122, 58));
    g.addNode(7, checkpoint(648, 1112, 46));
    g.addNode(8, checkpoint(643, 815, 51));
    g.addNode(9, checkpoint(571, 738, 70));
    g.addNode(10, checkpoint(716, 567, 50));
    g.addNode(11, checkpoint(778, 1152, 22));
    g.addNode(12, checkpoint(838, 1088, 61));
    g.addNode(13, checkpoint(822, 954, 30));
    g.addNode(14, checkpoint(723, 878, 31));
    g.addNode(15, checkpoint(871, 753, 40));
    g.addNode(16, checkpoint(736, 690, 41));
    g.addNode(17, checkpoint(840, 490, 60));
    g.addNode(18, checkpoint(1005, 1143, 54));
    g.addNode(19, checkpoint(917, 968, 21));
    g.addNode(20, checkpoint(969, 844, 20));
    g.addNode(21, checkpoint(1025, 677, 42));
    g.addNode(22, checkpoint(1180, 1246, 47));
    g.addNode(23, checkpoint(1103, 990, 45));
    g.addNode(24, checkpoint(1244, 967, 43));
    g.addNode(25, checkpoint(1168, 767, 34));
    g.addNode(26, checkpoint(1122, 613, 55));
    g.addNode(27, checkpoint(1250, 490, 33));
    g.addNode(28, checkpoint(1392, 1252, 91));
    g.addNode(29, checkpoint(1310, 1070, 80));
    g.addNode(30, checkpoint(1288, 812, 82));
    g.addNode(31, checkpoint(1300, 672, 62));
    g.addNode(32, checkpoint(1487, 447, 53));
    g.addNode(33, checkpoint(1380, 350, 44));
    g.addNode(34, checkpoint(1494, 181, 81));
    g.addNode(35, checkpoint(1472, 1240, 64));
    g.addNode(36, checkpoint(1535, 696, 71));
    g.addNode(37, checkpoint(1555, 569, 52));
    g.addNode(38, checkpoint(1550, 350, 90));
    g.addNode(39, checkpoint(1620, 175, 92));

    return g;
}

// time in minutes
float getPathTime(const node<checkpoint>* startNode, const node<checkpoint>* endNode, int uphill, float roadCoefficient, float obstacleDifficultyCoefficient) {
    if (roadCoefficient > 1 || roadCoefficient < 0) {
        std::cout << "incorrect road coefficient!\n";
        return -1;
    }
    else if (obstacleDifficultyCoefficient >= 1 || obstacleDifficultyCoefficient < 0) {
        std::cout << "incorrect obstacle difficulty coefficient!\n";
        return -1;
    }
    // ewwwwww
    float distance = sqrt((*startNode->attribute->coords.one - *endNode->attribute->coords.one) *
        (*startNode->attribute->coords.one - *endNode->attribute->coords.one)
        + (*startNode->attribute->coords.two - *endNode->attribute->coords.two)
        * (*startNode->attribute->coords.two - *endNode->attribute->coords.two)) 
        * METER;
    std::cout << "distance in meters: " <<  distance << '\n';

    distance = distance * roadCoefficient + (1 - roadCoefficient) * distance * 1.429; // slows down according to road coefficient
    distance /= 1 - obstacleDifficultyCoefficient;

    if (uphill > 0) {
        distance *= 1.25;
    }
    else if (uphill < 0) {
        distance *= 0.8333;
    }

    return distance / 60;
}

graph<checkpoint> constructGraph() {
    graph<checkpoint> g = initGraphCheckpoints();
    return g;
}
