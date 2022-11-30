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
    * It will return the amount of element that was inserted. If the return value is -1, then no items were inserted
    * 
    * @param nodefile the file name that holds the data for our nodes
    */
    int insertAllNodes(const std::string& nodefile);

    /*
    * @brief will be used by the constructor, it will take in a file with all the Edges and insert them all in the graph with the proper weidght.
    * It will return the amoutnt of element that was inserted. If the return value is -1, then no items were inserted
    * 
    * @param edgefile the file name that holds the data for our edges
    * @param needMap a boolean that keeps track if we need to map each longitude/latitude to an ID for later use in the kd tree
    */
    int insertAllEdges(const std::string& edgefile);

    /*
    getter fn that returns the private variable edgesInserted
    */
    int getEdgeCount() {
        return edgesInserted;
    }

    /*
    getter fn that returns the amount of nodes inserted
    */
    int getNodeCount() {
        return nodesInserted;
    }

    //getter fn to get the graph
    Graph getGraph() {
        return fullG_;
    }


    private:
        Graph fullG_;
        int nodesInserted;
        int edgesInserted;

       
};

