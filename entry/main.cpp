#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include "graph.h"
#include "getCleanedData.h"
#include "fileParser.h"
#include "a_star.h"

// <command name> <road nodes/intersections> <road edges> <airport filename> 
int main(int argc, char *argv[]) {
    if(argc < 4) {
        std::cout << "Missing arguments" << std::endl;
        return 1;
    }

    // Clean up data into edges and nodes file
    Sanitizer files;
    files.getCleanedData(std::string(argv[1]), std::string(argv[3]), std::string(argv[2]));
    
    // Build graph from edges and nodes file
    Graph network;
    fullGraph fileParser = fullGraph(std::vector<string>{"../src/nodes.txt", "../src/edges.txt"}, network);

    std::vector<double> speeds = {60, 500}; // 60mph average highway, 500 mph cruising speed of 737
    network.setSpeedLookup(speeds);

    // Get start/end
    std::pair<double,double> startLoc;
    std::pair<double,double> endLoc;

    std::string inBuff;
    std::cout << "Start (\"lat,long\"): ";
    std::getline(std::cin, inBuff);
    inBuff.erase(std::remove_if(inBuff.begin(), inBuff.end(), ::isspace), inBuff.end());
    unsigned cut = inBuff.find(',');
    startLoc.second = std::stod(inBuff.substr(0, cut));
    startLoc.first = std::stod(inBuff.substr(cut + 1));

    std::cout << "Destination (\"lat\",\"long\"): ";
    std::getline(std::cin, inBuff);
    inBuff.erase(std::remove_if(inBuff.begin(), inBuff.end(), ::isspace), inBuff.end());
    cut = inBuff.find(',');
    endLoc.second = std::stod(inBuff.substr(0, cut));
    endLoc.first = std::stod(inBuff.substr(cut + 1));

    // run a*
    std::vector<Graph::Edge> pathEdges = shortestPath(network, startLoc, endLoc);

    // some function to print edges out
    // function to print nodes in path in visited order
    std::cout << "A* traversal includes: " << pathEdges.size() << " steps:"<< std::endl;
    Graph::Node prevNode = network.getNodes()[network.getNearestNode(startLoc)];
    std::cout << prevNode.coords.second << ',' << prevNode.coords.first << std::endl;
    for(unsigned i = 0; i < pathEdges.size(); ++i) {
        prevNode = network.getNodes()[(pathEdges[i].end1 == prevNode.ID) ? pathEdges[i].end2 : pathEdges[i].end1];

        std::cout << prevNode.coords.second << ',' << prevNode.coords.first << std::endl;
    }
 
    return 0;
}