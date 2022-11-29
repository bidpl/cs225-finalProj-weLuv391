#pragma once

#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <iterator>
#include <fstream>
#include <cmath>
#include <sstream>
#include <utility>      // std::pair, std::make_pair
#include <map>
using namespace std;

class Sanitizer{
    public:
        Sanitizer();
        void getCleanedData();
        //currIdx refers to the last edge inserted
        //returns a vector of strings that contian our edges
        vector<string> connectGraphs(int currIdx);

        int getNodeCount(int index) {
            if((unsigned long)index>nodeCountIND.size()) 
                return -1;
            return nodeCountIND[index];
        }

        int getEdgeCount(int index) {
            if((unsigned long)index>edgeCountIND.size()) 
                return -1;
            return edgeCountIND[index];
        }
    private:
        std::vector<std::pair<double,double>> allPoints; // A vector to hold our nodes 
        std::vector<int> nodeCountIND; // a vector that holds the count of nodes/edges of each transport type
        std::vector<int> edgeCountIND; 
        std::vector<std::pair<int,int>> nodeIndex; // a vector to hold the start/end position of each Node in our vector of allPoints
        std::map<std::pair<double,double>, int> coorToID; // a map that relates our coordinate of long/lat to its unique id
        int edgeCount;
        int nodeCount;
};