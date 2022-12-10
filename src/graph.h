#include <utility>
#include <vector>
#include <queue>
# pragma once

class Graph {
    public:
        const double LINEAR_CONV_FACTOR = 69.0; // 69 miles per degree, set this to change units

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

                bool operator<(const Edge & other);
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
         * @brief appends an edge to the end of edge list without checking index to ID
         * 
         * @param edge - edge to copy and pushback
         */
        void push_backEdge(const Edge & edge);

        /**
         * @brief Get speed of an edge based on routeID + speed lookup
         * 
         * @param edgeID
         * @return double - speed of that edge
         */
        double getTravelSpeed(int edgeID) const;

        /**
         * @brief Get the travel time of an edge based on speed lookup table
         * 
         * @param edgeID
         * @return double - time it takes to travel that edge
         */
        double getTravelTime(int edgeID) const;

        // This iterator will only iterate through the start's connected component
        class Iterator : std::iterator<std::forward_iterator_tag, Node> {
            public:
                Iterator();
                Iterator(Node start, std::vector<Graph::Node> * nodes, std::vector<Graph::Edge> * edgeList);

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

        // Iterator access
        Iterator begin();
        Iterator end();
        Iterator iterAt(int startIdx);

        /**
         * @brief generates a MST of a graph using Kruskal's alg
         * 
         * @param const Graph & graph - reference to target graph, must be properly formatted
         * 
         * @returns Graph - graph object representing MST (new nodes to show MST adjacency lists)
         * 
         */

        Graph generateMST();
        /**
         * @brief converts distance in degrees (what's given in edge) to miles
         * 
         * @param degDistance - distance in degrees (given in edge obj)
         * 
         * @return distance in miles
         * 
         */
        double degToLinear(double degDistance) const;

        /**
         * @brief helper to get linear distance between two lat/long pairs
         * 
         * @param coord1
         * @param coord2
         * 
         * @return linear distance between them
         */

        double coordDistance(std::pair<double, double> coord1, std::pair<double, double> coord2) const;

        /**
         * @brief returns index of nearest node to a given loc
         * 
         * @param loc input location
         * @return int index to nearest match
         */
        int getNearestNode(std::pair<double, double> loc) const;

        // Getters and setters
        std::vector<Edge> & getEdgeList() {
            return edgeList;
        }

        std::vector<Node> & getNodes() {
            return nodes;
        }

        std::vector<double> & getSpeedLookup() {
            return speedLookup;
        }

        void setSpeedLookup(std::vector<double> & newSpeed) {
            speedLookup = newSpeed;
        }

    private:
        // Edge List
        std::vector<Edge> edgeList;

        // Node list, might need switch to map to get ID access
        std::vector<Node> nodes;

        // Speed (indexed by routeType, might need map), store as proj units (see LINEAR_CONV_FACTOR)
        std::vector<double> speedLookup;
};