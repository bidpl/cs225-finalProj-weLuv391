# pragma once
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>      // std::pair, std::make_pair

class fullGraph{
    public:

    /*
    * @brief aconstructor for the fileParser
    * This will take in a file with the given data type and create two connected graphs from it
    * It will also construct a KD-tree of the longitude/latitude points in radians to be used in connectGraphs();
    * 
    * @param transport1 - the file name that holds the data for our vertices that represent our first travel type
    * @param transport2 - the file name that holds the data for our vertices that represent our second travel type
    * @param travelEdge - the file name that holds the data for our edges that connect our 2nd travel type together
    */
    fullGraph(const std::string& transport1, const std::string& transport2, const std::string& travelEdge );


    /*
    * @brief Using our graph and a KD Tree of longitude/latitude coordinates of our second transport type, 
    * we will connect transport1 vertex to that of the second vertex making one whole connected graph 
    *
    */
    void connectGraphs();

    private:
        Graph fullGraph_;
       // KDTree lat_longTree_; // currently commented out untill kdTree.h/hpp is implemented
};


