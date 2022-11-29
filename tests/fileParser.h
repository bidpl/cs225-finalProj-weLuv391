# pragma once
#include <utility>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <utility>      // std::pair, std::make_pair
#include <map>

class fullGraph{
    public:

    /*
    * @brief a constructor for the fileParser
    * This will take in a file with the given data type and create two connected graphs from it
    * It will also construct a KD-tree of the longitude/latitude points to be used in connectGraphs();
    * 
    * @param transport1 - the file name that holds the data for our nodes that represent our first travel type
    * @param transport2 - the file name that holds the data for our nodes that represent our second travel type
    * @param travelEdge1 - the file name that holds the data for our edges that connect our 1st travel type together
    * @param travelEdge2 - the file name that holds the data for our edges of the 2nd data type
    */
    fullGraph(const std::string& transport1, const std::string& transport2, const std::string& travelEdge1, const std::string& travelEdge2 );

    /*
    * @brief will be used by the constructor, it will take in a file with all the Nodes and insert them all in the graph.
    * It will return an integer value of the index of the last element that was inserted. If the return value is -1, then no items were inserted
    * 
    * @param nodefile the file name that holds the data for our nodes
    */
    int insertAllNodes(const std::string& nodefile);

    /*
    * @brief will be used by the constructor, it will take in a file with all the Edges and insert them all in the graph with the proper weidght.
    * It will return an integer value of the index of the last element that was inserted. If the return value is -1, then no items were inserted
    * 
    * @param edgefile the file name that holds the data for our edges
    * @param needMap a boolean that keeps track if we need to map each longitude/latitude to an ID for later use in the kd tree
    */
    int insertAllEdges(const std::string& edgefile);

    /*
    * These set of four fns give the start/end index of their respective node type 
    * This can be used to get the longitude/lattiude from the allPoints
    */

    int getTransport1Start();

    int getTransport1End();

    int getTransport2Start();

    int getTransport2End();


    /*
    * @brief Using our graph and a KD Tree of longitude/latitude coordinates of our second transport type, 
    * we will connect transport1 vertex to that of the second vertex making one whole connected graph 
    *
    */
    void connectGraphs();

    private:
        Graph fullG_;
        std::vector<std::pair<double,double>> allPoints; // A vector to hold our nodes 
        int transport1_start;
        int transport2_end;
        std::map<std::pair<double,double>, int> coorToID; // a map that relates our coordinate of long/lat to its unique id
       // KDTree lat_longTree_; // currently commented out untill kdTree.h/hpp is implemented
};

