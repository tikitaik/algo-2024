# pragma once

# include <iostream>
# include <fstream>
# include <sstream>
# include "../adts/graph.h"
# include "../adts/pair.h"

# define METER 1 / 0.190 // one m is 0.190 pixels

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

    float edgeTime = distance / walkSpeed;

    edgeTime = edgeTime * (roadCoefficient + (1 - roadCoefficient) * 1.429); // slows down according to road coefficient
    edgeTime /= 1 - obstacleCoefficient;

    //std::cout << "distance after road and obstacle calcs: " << distance << '\n';

    if (uphill > 0) {
        edgeTime *= 1.25;
    }
    else if (uphill < 0) {
        edgeTime *= 0.8333;
    }

    //std::cout << "distance after uphill/downhill " << distance << '\n';

    // year 7 physics finally applying to the real world
    // speed in m/s
    // convert to minutes
    edgeTime /= 60;
    edgeTime = std::round(edgeTime);
    //std::cout << "edgeTime: " << edgeTime << '\n';
    return edgeTime;
}

graph<checkpoint> initEventCheckpoints() {

    std::ifstream checkpointData("../sat/map-data/checkpoint-data.csv");
    if (!checkpointData.is_open()) {
        std::cout << "checkpoint data couldn't be opened\n";
    }

    graph<checkpoint> g(true);
    
    std::string line;

    while (getline(checkpointData, line)) {

        std::stringstream ss(line);
        std::string idStr;
        std::string xStr;
        std::string yStr;
        std::string rewardStr;

        getline(ss, idStr, ',');
        getline(ss, xStr, ',');
        getline(ss, yStr, ',');
        getline(ss, rewardStr, ',');

        //std::cout << idStr << " ";
        //std::cout << xStr << " ";
        //std::cout << yStr << " ";
        //std::cout << rewardStr << '\n';

        if (xStr == "x") {
            continue;
        }

        int x = stoi(xStr);
        int y = stoi(yStr);
        int reward = stoi(rewardStr);
        g.addNode(checkpoint(x, y, reward - (reward % 10)));
    }

    return g;
}

graph<checkpoint> initTeamGraph(graph<checkpoint> g, const float walkSpeed) {

    std::ifstream edgeData("../sat/map-data/edge-data.csv");
    if (!edgeData.is_open()) {
        std::cout << "edge data couldn't be opened\n";
    }
        
    std::string line;

    while (getline(edgeData, line)) {

        std::stringstream ss(line);
        std::string startIdStr;
        std::string endIdStr;
        std::string uphillStr;
        std::string roadCoefficientStr;
        std::string obstacleCoefficientStr;

        getline(ss, startIdStr, ',');
        getline(ss, endIdStr, ',');
        getline(ss, uphillStr, ',');
        getline(ss, roadCoefficientStr, ',');
        getline(ss, obstacleCoefficientStr, ',');

        //std::cout << startIdStr << " ";
        //std::cout << endIdStr << " ";
        //std::cout << uphillStr << " ";
        //std::cout << roadCoefficientStr << " ";
        //std::cout << obstacleCoefficientStr << '\n';

        if (uphillStr == "uphill") {
            continue;
        }

        int start = stoi(startIdStr);
        int end = stoi(endIdStr);
        int uphill = stoi(uphillStr);
        float roadCoefficient = stof(roadCoefficientStr);
        float obstacleCoefficient = stof(obstacleCoefficientStr);

        g.addEdge(start, end, getPathTime(g.searchNodeID(start), g.searchNodeID(end), walkSpeed, uphill, roadCoefficient, obstacleCoefficient));
        g.addEdge(end, start, getPathTime(g.searchNodeID(end), g.searchNodeID(start), walkSpeed, uphill * -1, roadCoefficient, obstacleCoefficient));
    }

    return g;
}

