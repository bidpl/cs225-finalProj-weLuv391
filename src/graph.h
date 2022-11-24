#include <utility>
#include <vector>
#include <iostream>
//#include "edge.h"
# pragma once


class Graph {
    public:
        class Node;
        class Edge;

        class Edge {
            int ID;
            Node * end1;
            Node * end2;
            double distance;
            int routeType;
        };

        class Node {
            public:
                int ID;
                std::pair<double, double> coords;
                std::vector<Edge *> adjList;
        };


        /**
         * @brief given a node ID, return a reference to it's adjacency list
         * 
         * @param ID - of node
         * @return std::vector<Edge *>& - reference to it's adjacency list (vector of ptr to edge objs)
         */
        std::vector<Edge *> & getAdj(int ID);

        /**
         * @brief given two Node IDs, returns the edge obj connecting them (if exists)
         * 
         * @param IDa 
         * @param IDb 
         * @return Edge* - NULL if no edge connects them
         */
        Edge * getEdge(int IDa, int IDb);

        /**
         * @brief inserts node with ID and coordinates, overwrites if Node with that ID already exists
         * 
         * @param ID 
         * @param coords pair of lat/long coordinates
         * @return false if node with that ID already existed
         */
        bool insertNode(int ID, std::pair<double, double> coords);

        /**
         * @brief inserts edge with ID and refers to vertices by ID
         * 
         * @param routeID 
         * @param IDa 
         * @param IDb 
         * @param distance 
         * @param routeType 
         * @return false if node with that ID already existed 
         */
        bool insertEdge(int routeID, int IDa, int IDb, double distance, int routeType);

        /**
         * @brief inserts edge with ID and refers to vertices by pointer
         * 
         * @param routeID 
         * @param IDa 
         * @param IDb 
         * @param distance 
         * @param routeType 
         * @return false if node with that ID already existed 
         */
        bool insertEdge(int routeID, Node * node1, Node * node2, double distance, int routeType);

        /**
         * @brief Get the travel time of an edge based on speed lookup table
         * 
         * @param edge 
         * @param speedLookup 
         * @return double - time it takes to travel that edge
         */
        double getTravelTime(Edge * edge, std::vector<double> speedLookup);

    private:
        // Edge List
        std::vector<Edge *> edgeList;

        // Node list, might need switch to map to get ID access
        std::vector<Node> nodes;

        // Speed (indexed by routeType, might need map)
        std::vector<double> speedLookup;
};