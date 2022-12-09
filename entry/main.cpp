#include <iostream>
#include "graph.h"
#include "getCleanedData.h"
#include "fileParser.h"
// #include "a*.h"

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

    std::cout << "Num nodes: " << network.getNodes().size() << std::endl;
    std::cout << "Num edges: " << network.getEdgeList().size() << std::endl;

    std::vector<int> visitOrder;
    for(Graph::Iterator it = network.begin(); it != network.end(); ++it) {
        visitOrder.push_back((*it).ID);
    }

    std::cout << "BFS iterator visits " << visitOrder.size() << " nodes" << std::endl;

    std::cout << "First 20 items in BFS iteration: " <<std::endl;
    for(unsigned i = 0; i < 20; ++i) {
        std::cout << network.getNodes()[visitOrder[i]].coords.second << "," << network.getNodes()[visitOrder[i]].coords.first << std::endl;
    }

    // Golden Gate S Vista Point to Santa Monica Pier
    // std::vector<Graph::Edge> pathEdges = shortestPath(network, std::pair<double, double>{37.807680, -122.474735}, std::pair<double, double>{37.807680, -122.474735});

    // some function to print edges out
    // function to print nodes in path in visited order

    return 0;
}