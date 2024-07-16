# pragma once

# include <iostream>
# include "../adts/graph.h"
# include "../adts/pair.h"

# define METER 1 / 0.190 // one m is 0.190 pixels

graph<checkpoint> initGraphCheckpoints() {
    graph<checkpoint> g(true);

    // every goal - coordinates are in pixels
    g.addNode(0, checkpoint(891, 863, 0));
    g.addNode(1, checkpoint(220, 964, 30));
    g.addNode(2, checkpoint(365, 1193, 80));
    g.addNode(3, checkpoint(336, 1035, 50));
    g.addNode(4, checkpoint(478, 878, 60));
    g.addNode(5, checkpoint(344, 859, 50));
    g.addNode(6, checkpoint(518, 1260, 50));
    g.addNode(7, checkpoint(648, 1112, 40));
    g.addNode(8, checkpoint(643, 815, 50));
    g.addNode(9, checkpoint(571, 738, 70));
    g.addNode(10, checkpoint(716, 567, 50));
    g.addNode(11, checkpoint(778, 1152, 20));
    g.addNode(12, checkpoint(838, 1088, 60));
    g.addNode(13, checkpoint(822, 954, 30));
    g.addNode(14, checkpoint(723, 878, 30));
    g.addNode(15, checkpoint(871, 753, 40));
    g.addNode(16, checkpoint(736, 690, 40));
    g.addNode(17, checkpoint(840, 490, 60));
    g.addNode(18, checkpoint(1005, 1143, 50));
    g.addNode(19, checkpoint(917, 968, 20));
    g.addNode(20, checkpoint(969, 844, 20));
    g.addNode(21, checkpoint(1025, 677, 40));
    g.addNode(22, checkpoint(1180, 1246, 40));
    g.addNode(23, checkpoint(1103, 990, 40));
    g.addNode(24, checkpoint(1244, 967, 40));
    g.addNode(25, checkpoint(1168, 767, 30));
    g.addNode(26, checkpoint(1122, 613, 50));
    g.addNode(27, checkpoint(1250, 490, 30));
    g.addNode(28, checkpoint(1392, 1252, 90));
    g.addNode(29, checkpoint(1310, 1070, 80));
    g.addNode(30, checkpoint(1288, 812, 80));
    g.addNode(31, checkpoint(1300, 672, 60));
    g.addNode(32, checkpoint(1487, 447, 50));
    g.addNode(33, checkpoint(1380, 350, 40));
    g.addNode(34, checkpoint(1494, 181, 80));
    g.addNode(35, checkpoint(1472, 1240, 60));
    g.addNode(36, checkpoint(1535, 696, 70));
    g.addNode(37, checkpoint(1555, 569, 50));
    g.addNode(38, checkpoint(1550, 350, 90));
    g.addNode(39, checkpoint(1620, 175, 90));

    return g;
}

// time in minutes
float getPathTime(const node<checkpoint>* startNode, const node<checkpoint>* endNode, const float walkSpeed, const float uphill, const float roadCoefficient, const float obstacleCoefficient) {
    if (roadCoefficient > 1 || roadCoefficient < 0) {
        std::cout << "incorrect road coefficient!\n";
        return -1;
    }
    else if (obstacleCoefficient >= 1 || obstacleCoefficient < 0) {
        std::cout << "incorrect obstacle difficulty coefficient!\n";
        return -1;
    }
    // ewwwwww
    // gets 2d distance
    float distance = sqrt((*startNode->attribute->coords.one - *endNode->attribute->coords.one)
        * (*startNode->attribute->coords.one - *endNode->attribute->coords.one)
        + (*startNode->attribute->coords.two - *endNode->attribute->coords.two)
        * (*startNode->attribute->coords.two - *endNode->attribute->coords.two)) 
        * METER;
    //std::cout << "distance in meters: " <<  distance << '\n';

    distance = distance * (roadCoefficient + (1 - roadCoefficient) * 1.429); // slows down according to road coefficient
    distance /= 1 - obstacleCoefficient;

    //std::cout << "distance after road and obstacle calcs: " << distance << '\n';

    if (uphill > 0) {
        distance *= 1.25;
    }
    else if (uphill < 0) {
        distance *= 0.8333;
    }

    //std::cout << "distance after uphill/downhill " << distance << '\n';

    // year 7 physics finally applying to the real world
    // speed in m/s
    float edgeTime = distance / walkSpeed;
    // convert to minutes
    edgeTime /= 60;
    edgeTime = std::round(edgeTime);
    //std::cout << "edgeTime: " << edgeTime << '\n';
    return edgeTime;
}

graph<checkpoint> constructGraph(const float walkSpeed) {
    graph<checkpoint> g = initGraphCheckpoints();

    // id array that has ids of edges that will be implemented 
    const int ids[96][2] = {
        { 0, 13 },
        { 0, 14 },
        { 0, 15 },
        { 0, 19 },
        { 0, 20 },
        { 1, 2 },
        { 1, 3 },
        { 1, 4 },
        { 2, 3 },
        { 2, 5 },
        { 2, 6 },
        { 3, 4 },
        { 3, 5 },
        { 3, 7 },
        { 4, 5 },
        { 4, 8 },
        { 4, 9 },
        { 6, 7 },
        { 6, 11 },
        { 7, 11 },
        { 7, 12 },
        { 7, 13 },
        { 7, 14 },
        { 8, 9 },
        { 8, 14 },
        { 8, 16 },
        { 9, 10 },
        { 9, 16 },
        { 10, 15 },
        { 10, 16 },
        { 10, 17 },
        { 11, 12 },
        { 11, 13 },
        { 12, 13 },
        { 12, 18 },
        { 12, 19 },
        { 13, 14 },
        { 13, 19 },
        { 13, 20 },
        { 14, 15 },
        { 14, 16 },
        { 15, 16 },
        { 15, 17 },
        { 15, 20 },
        { 15, 21 },
        { 16, 17 },
        { 17, 21 },
        { 18, 19 },
        { 18, 20 },
        { 18, 23 },
        { 19, 20 },
        { 19, 23 },
        { 20, 21 },
        { 20, 23 },
        { 20, 25 },
        { 21, 25 },
        { 21, 26 },
        { 22, 23 },
        { 22, 24 },
        { 22, 28 },
        { 22, 29 },
        { 23, 24 },
        { 23, 25 },
        { 23, 30 },
        { 24, 25 },
        { 24, 29 },
        { 24, 30 },
        { 25, 26 },
        { 25, 30 },
        { 25, 31 },
        { 25, 27 },
        { 26, 27 },
        { 26, 31 },
        { 26, 32 },
        { 27, 31 },
        { 27, 32 },
        { 27, 33 },
        { 28, 35 },
        { 28, 29 },
        { 29, 30 },
        { 29, 35 },
        { 30, 31 },
        { 30, 36 },
        { 31, 36 },
        { 31, 37 },
        { 31, 32 },
        { 32, 33 },
        { 32, 36 },
        { 32, 37 },
        { 32, 38 },
        { 33, 34 },
        { 33, 38 },
        { 34, 39 },
        { 36, 37 },
        { 37, 38 },
        { 38, 39 }
    };
    // is/isnt uphill, roadCoefficient, obstacleCoefficient
    const float edgeData [96][3] = {
        {-1, 0.40, 0.35 }, 
        {-1, 0.50, 0.10 }, 
        { 1, 0.40, 0.30 }, 
        {-1, 0.90, 0.10 }, 
        { 0, 0.95, 0.10 }, 
        { 0, 0.15, 0.20 }, 
        { 0, 0.10, 0.10 }, 
        {-1, 0.40, 0.20 }, 
        { 1, 0.30, 0.15 }, 
        { 1, 0.65, 0.20 }, 
        {-1, 0.30, 0.30 }, 
        {-1, 0.10, 0.30 }, 
        { 0, 0.60, 0.35 }, 
        {-1, 0.20, 0.30 }, 
        { 1, 0.30, 0.40 }, 
        { 0, 0.20, 0.30 }, 
        { 0, 0.20, 0.15 }, 
        { 1, 0.40, 0.15 }, 
        { 0, 0.00, 0.10 }, 
        {-1, 0.50, 0.10 }, 
        { 0, 0.05, 0.12 }, 
        { 1, 0.40, 0.30 }, 
        { 1, 0.70, 0.30 }, 
        { 0, 0.10, 0.15 }, 
        {-1, 0.30, 0.25 }, 
        { 1, 0.80, 0.30 }, 
        {-1, 0.80, 0.20 }, 
        { 0, 0.65, 0.17 }, 
        {-1, 0.70, 0.40 }, 
        { 0, 0.85, 0.10 }, 
        { 1, 0.50, 0.30 }, 
        { 1, 0.00, 0.60 }, 
        { 1, 0.40, 0.40 }, 
        { 1, 0.10, 0.40 }, 
        {-1, 0.40, 0.40 }, 
        { 1, 0.10, 0.25 }, 
        { 0, 0.95, 0.10 }, 
        {-1, 0.90, 0.20 }, 
        { 0, 0.30, 0.60 }, 
        { 0, 0.80, 0.15 }, 
        { 0, 0.50, 0.30 }, 
        { 0, 0.05, 0.50 }, 
        { 1, 0.20, 0.40 }, 
        {-1, 0.30, 0.20 }, 
        { 0, 0.60, 0.40 }, 
        { 1, 0.70, 0.30 }, 
        {-1, 0.80, 0.30 }, 
        { 1, 0.50, 0.20 }, 
        { 1, 0.70, 0.10 }, 
        { 1, 0.40, 0.10 }, 
        { 0, 0.70, 0.05 }, 
        {-1, 0.50, 0.10 }, 
        {-1, 0.60, 0.10 }, 
        {-1, 0.70, 0.20 }, 
        {-1, 0.95, 0.10 }, 
        { 1, 0.40, 0.20 }, 
        { 1, 0.05, 0.10 }, 
        { 1, 0.60, 0.25 }, 
        { 1, 0.40, 0.25 }, 
        { 0, 0.90, 0.30 }, 
        { 0, 0.50, 0.20 }, 
        { 0, 0.70, 0.20 }, 
        { 0, 0.80, 0.20 }, 
        { 0, 0.70, 0.25 }, 
        {-1, 0.60, 0.15 }, 
        {-1, 0.90, 0.15 }, 
        {-1, 0.80, 0.40 }, 
        {-1, 0.80, 0.10 }, 
        { 1, 0.50, 0.20 }, 
        { 1, 0.60, 0.10 }, 
        { 1, 1.00, 0.15 }, 
        { 1, 0.80, 0.10 }, 
        { 1, 0.20, 0.20 }, 
        { 1, 0.80, 0.30 }, 
        {-1, 0.65, 0.30 }, 
        { 0, 0.40, 0.25 }, 
        { 1, 0.70, 0.20 }, 
        { 0, 0.10, 0.20 }, 
        { 1, 0.70, 0.15 }, 
        { 1, 0.40, 0.45 }, 
        {-1, 0.20, 0.50 }, 
        { 0, 0.50, 0.50 }, 
        { 1, 0.70, 0.20 }, 
        { 1, 1.00, 0.15 }, 
        { 1, 1.00, 0.20 }, 
        { 1, 1.00, 0.15 }, 
        { 1, 0.60, 0.20 }, 
        { 0, 0.85, 0.15 }, 
        { 0, 0.90, 0.20 }, 
        { 1, 0.90, 0.10 }, 
        { 1, 0.50, 0.15 }, 
        { 1, 0.30, 0.30 }, 
        { 0, 1.00, 0.30 }, 
        {-1, 0.95, 0.20 }, 
        { 1, 0.85, 0.10 }, 
        { 0, 0.95, 0.40 }
    };

    for (int i = 0; i < 96; i++) {
        g.addEdge(ids[i][0], ids[i][1], getPathTime(g.searchNodeID(ids[i][0]), g.searchNodeID(ids[i][1]), walkSpeed, edgeData[i][0], edgeData[i][1], edgeData[i][2]));
        g.addEdge(ids[i][1], ids[i][0], getPathTime(g.searchNodeID(ids[i][1]), g.searchNodeID(ids[i][0]), walkSpeed, edgeData[i][0] * -1, edgeData[i][1], edgeData[i][2]));
    }

    return g;
}

