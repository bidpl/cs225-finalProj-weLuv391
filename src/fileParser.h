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
    * @param fullG_ the Graph to be used to insert all the nodes, edges
    */
    fullGraph(const std::vector<std::string> listofFiles, Graph& fullG_);

    /*
    * @brief will be used by the constructor, it will take in a file with all the Nodes and insert them all in the graph.
    * It will return the amount of element that was inserted. If the return value is -1, then no items were inserted
    * 
    * @param nodefile the file name that holds the data for our nodes
    * @param fullG_ the Graph to be used to insert all the nodes
    */
    int insertAllNodes(const std::string& nodefile, Graph& fullG_);

    /*
    * @brief will be used by the constructor, it will take in a file with all the Edges and insert them all in the graph with the proper weidht.
    * It will return the amoutnt of element that was inserted. If the return value is -1, then no items were inserted
    * 
    * @param edgefile the file name that holds the data for our edges
    * @param fullG_ the Graph to be used to insert all the edges
    */
    int insertAllEdges(const std::string& edgefile, Graph& fullG_);

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


    private:
        //private variables that hold the amount of nodes and edges that were inserted.
        int nodesInserted;
        int edgesInserted;

       
};

