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
        /*
        * simple contstructor for Sanitizer
        */
        Sanitizer();
        /*
        * @brief main function that takes in 3 files with relevant transportation and 
        * location data and returns two csv files of nodes and edges with data correction 
        * 
        * @param intersectionFile - space seperated file that holds the data for all the intersections in California
        * @param airportFile - csv file that holds all the data for airports
        * @param roadEdgeFile - space seperated file that holds all the data for all the road edges connecting the interscections
        */
        void getCleanedData(std::string intersectionFile, std::string airportFile, std::string roadEdgeFile);


        /*
        * @brief helper function to getCleandData() takes in the index of the last edge created and using a Kd-tree creates 
        * edges connecting all the airports to the closest intersection
        * 
        * @param currIdx - index of the last edge created
        */
        vector<string> connectGraphs(int currIdx);

        /*
        * @brief getter function to return the amount of nodes created of a given data type
        *  returns -1 if the index is past the size of the vector
        * @param index - identitfier to either the amount of intersections or airports should be returned
        */
        int getNodeCount(int index) {
            if((unsigned long)index>=nodeCountIND.size()) 
                return -1;
            return nodeCountIND[index];
        }

         /*
        * @brief getter function to return the amount of edges created of a given data type
        *  returns -1 if the index is past the size of the vector
        * @param index - identitfier to either the amount of road edges, airport edges, intersection to airport edges should be returned
        */
        int getEdgeCount(int index) {
            if((unsigned long)index>=edgeCountIND.size()) 
                return -1;
            return edgeCountIND[index];
        }
    private:
        std::vector<std::pair<double,double>> allPoints; // A vector to hold our nodes 
        std::vector<int> nodeCountIND; // a vector that holds the count of nodes/edges of each transport type
        std::vector<int> edgeCountIND; 
        std::vector<std::pair<int,int>> nodeIndex; // a vector to hold the start/end position of each Node in our vector of allPoints
        std::map<std::pair<double,double>, int> coorToID; // a map that relates our coordinate of long/lat to its unique id
        int edgeCount; // variable to count total edges
        int nodeCount; // varaible to count total nodes
};
