#include <utility>
#include <vector>
#include <queue>
# pragma once

class Graph {
    public:
        class Node;
        class Edge;

        class Edge {
            public:
                Edge();
                Edge(int ID_, int end1_, int end2_, double distance_, int routeType_);

                int ID;
                int end1;
                int end2;
                double distance;
                int routeType;

                bool operator<=(const Edge & other);
        };

        class Node {
            public:
                Node();
                Node(int ID_, std::pair<double, double> coords_, int type_);
                Node(const Node & other);

                int ID;
                std::pair<double, double> coords;
                std::vector<int> adjList;
                int type;

                bool operator!=(const Node & other);
                Node & operator=(const Node & other);
        };


        /**
         * @brief given a node ID, return a reference to it's adjacency list
         * 
         * @param ID - of node
         * @return std::vector<Edge *>& - reference to it's adjacency list (vector of ptr to edge objs)
         */
        std::vector<int> & getAdj(int ID);

        /**
         * @brief given two Node IDs, returns the edge obj connecting them (if exists)
         * 
         * @param IDa 
         * @param IDb 
         * @return Edge* - NULL if no edge connects them
         */
        Edge getEdge(int IDa, int IDb);

        /**
         * @brief inserts node with ID and coordinates, overwrites if Node with that ID already exists
         * 
         * @param ID 
         * @param coords pair of lat/long coordinates
         * @return false if node with that ID already existed
         */
        bool insertNode(int ID, std::pair<double, double> coords);

        /**
         * @brief inserts node with ID and coordinates, overwrites if Node with that ID already exists
         * 
         * @param ID 
         * @param coords pair of lat/long coordinates
         * @param type of node (intersection, airport, etc)
         * @return false if node with that ID already existed
         */
        bool insertNode(int ID, std::pair<double, double> coords, int type);

        /**
         * @brief inserts edge with ID and refers to vertices by ID, does nothing if ID already exists
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
         * @brief Get the travel time of an edge based on speed lookup table
         * 
         * @param edgeID
         * @param speedLookup 
         * @return double - time it takes to travel that edge
         */
        double getTravelTime(int edgeID, const std::vector<double> & speedLookup);

        class Iterator : std::iterator<std::forward_iterator_tag, Node> {
            public:
                Iterator();
                Iterator(Node start, unsigned numNodes, std::vector<Graph::Node> * nodes, std::vector<Graph::Edge> * edgeList);

                Iterator & operator++();
                Node operator*();
                bool operator!=(const Iterator &other);

            private:
                Node current_;
                std::queue<Node> q_;
                std::vector<bool> visited_; // Requires continunous IDs that match with index

                std::vector<Node> * nodes_;
                std::vector<Edge> * edgeList_;
        };

    private:
        // Edge List
        std::vector<Edge> edgeList;

        // Node list, might need switch to map to get ID access
        std::vector<Node> nodes;

        // Speed (indexed by routeType, might need map)
        std::vector<double> speedLookup;
};