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
    * @param listofFiles a vector that holds all of ur files where its stored as the nodes1, edges1, nodes2, edges2, ....
    */
    fullGraph(const std::vector<std::string> listofFiles);

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

    // int getTransport1Start();

    // int getTransport1End();

    // int getTransport2Start();

    // int getTransport2End();


    /*
    * @brief Using our graph and a KD Tree of longitude/latitude coordinates of our second transport type, 
    * we will connect transport1 vertex to that of the second vertex making one whole connected graph 
    *
    */
    void connectGraphs();

    private:
        Graph fullG_;
        // std::vector<std::pair<double,double>> allPoints; // A vector to hold our nodes 
        // int transport1_start;
        // int transport2_end;
        // std::map<std::pair<double,double>, int> coorToID; // a map that relates our coordinate of long/lat to its unique id
       // KDTree lat_longTree_; // currently commented out untill kdTree.h/hpp is implemented
};

