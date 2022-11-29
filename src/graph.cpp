#include "graph.h"
#include <stdexcept>
#include <iostream>

Graph::Node::Node() : 
    ID(-1) {}

Graph::Node::Node(int ID_, std::pair<double, double> coords_, int type_) :
    ID(ID_),
    coords(coords_),
    type(type_) {}

Graph::Node::Node(const Node & other) :
    ID(other.ID),
    coords(other.coords),
    adjList(other.adjList) {}

bool Graph::Node::operator!=(const Node & other) {
    return ID = other.ID;
}

Graph::Node & Graph::Node::operator=(const Node & other) {
    ID = other.ID;
    coords = other.coords;
    adjList = other.adjList;

    return *this;
}

Graph::Edge::Edge() : 
    ID(-1),
    end1(-1),
    end2(-1),
    distance(-1),
    routeType(-1) {}

Graph::Edge::Edge(int ID_, int end1_, int end2_, double distance_, int routeType_) :
    ID(ID_),
    end1(end1_),
    end2(end2_),
    distance(distance_),
    routeType(routeType_) {}

bool Graph::Edge::operator<=(const Edge & other) {
    return distance <= other.distance;
}

std::vector<int> & Graph::getAdj(int ID) {
    // valid ID check
    if(ID < 0 || ID >= (int) nodes.size()) {
        throw std::runtime_error("Graph::getAdj: Invalid ID " + std::to_string(ID));
    }    

    return nodes[ID].adjList;
}

Graph::Edge Graph::getEdge(int IDa, int IDb) {
    // Check for valid indexes
    if(IDa < 0 || IDa >= (int) nodes.size()) {
        throw std::runtime_error("Graph::getEdge: Invalid IDa: " + std::to_string(IDa));
    } else if (IDb < 0 || IDb >= (int) nodes.size()) {
        throw std::runtime_error("Graph::getEdge: Invalid IDb: " + std::to_string(IDb));
    }

    // Find edge in a's adjList
    for(const int edgeID : nodes[IDa].adjList) {
        if(edgeList[edgeID].end1 == IDb || edgeList[edgeID].end2 == IDb) {
            return edgeList[edgeID];
        }
    }

    // If not found, return defualt edge
    return Edge();
}

bool Graph::insertNode(int ID, std::pair<double, double> coords) {
    return insertNode(ID, coords, -1);
}

bool Graph::insertNode(int ID, std::pair<double, double> coords, int type) {
    if(ID < 0) {
        throw std::runtime_error("Graph::insertNode: invalid ID " + std::to_string(ID));
    }

    if(ID < (int) nodes.size()) {
        std::cout << "Graph::insertNode: tried to overwrite " << ID << std::endl; 
        return false;
    }

    if(ID > (int) nodes.size()) {
        std::cout << "Graph::insertNode: unexpected ID " << ID << " expected " << nodes.size() << std::endl; 
    }

    nodes.push_back(Node(ID, coords, type));
    return true;
}

bool Graph::insertEdge(int routeID, int IDa, int IDb, double distance, int routeType) {
    // Check for valid indexes
    if(IDa < 0 || IDa >= (int) nodes.size()) {
        throw std::runtime_error("Graph::insertEdge: Invalid IDa: " + std::to_string(IDa));
    } else if (IDb < 0 || IDb >= (int) nodes.size()) {
        throw std::runtime_error("Graph::insertEdge: Invalid IDb: " + std::to_string(IDb));
    } else if (routeID < 0 || routeID > (int) edgeList.size()) {
        throw std::runtime_error("Graph::insertEdge: Invalid routeID: " + std::to_string(routeID));
    }

    // Check if edge already exists, if so return
    if(routeID < (int) edgeList.size()) {
        std::cout << "Graph::insertEdge: tried to overwrite" << routeID << " Expected " << edgeList.size() << std::endl;
        return false;
    }

    if(routeID > (int) edgeList.size()) {
        std::cout << "Graph::insertEdge: unexpected ID " << routeID << " Expected " << edgeList.size() << std::endl;
    }

    edgeList.push_back(Edge(routeID, IDa, IDb, distance, routeType));
    return true;
}

//do we need this as a parameter as it's already Graph's private variable?
double Graph::getTravelTime(int edgeID, const std::vector<double> & speedLookup) {
    if(edgeID < 0 || edgeID > (int) edgeList.size()) {
        throw std::runtime_error("Graph::getTravelTime: invalid edgeID " + std::to_string(edgeID));
    }
    
    const double DEFAULT_SPEED = 1.0;

    if(edgeList[edgeID].routeType == -1) {
        std::cout << "Graph::getTravelTime: got routeType -1" << std::endl;
        return DEFAULT_SPEED;
    }

    const int routeType = edgeList[edgeID].routeType;

    if(routeType < -1 || routeType >= (int) speedLookup.size()) {
        throw std::runtime_error("Graph::getTravelTime:: route type doesn't exist");
    }

    return speedLookup[routeType];
}

Graph::Iterator::Iterator() {
    current_ = Node(); // Might need to change this default
}

Graph::Iterator::Iterator(Graph::Node start, unsigned numNodes, std::vector<Graph::Node> * nodes, std::vector<Graph::Edge> * edgeList) :
    current_(start),
    visited_(std::vector<bool>(numNodes, false)),
    nodes_(nodes),
    edgeList_(edgeList) {}

Graph::Iterator & Graph::Iterator::operator++() {
    // @TODO
    // If at end, don't increment
    if(current_.ID == -1) {
        return *this;
    }

    // Continue this
    for(int edgeID : current_.adjList) {
        Edge & neigh = edgeList_->at(edgeID);
        int neighID = (neigh.end1 == current_.ID) ? neigh.end2 : neigh.end1;

        if(!visited_[neighID]) {
            q_.push(nodes_->at(neighID));
        }
    }

    if(q_.empty()) {
        current_ = Node();
    } else {
        current_ = q_.front();
        q_.pop();
    }
    
    return *this;
}

Graph::Node Graph::Iterator::operator*() {
    return current_;
}

bool Graph::Iterator::operator!=(const Iterator &other) {
    return current_ != other.current_;
}

