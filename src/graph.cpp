#include "graph.h"
#include <stdexcept>
#include <iostream>
#include <cmath>

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
    return ID != other.ID;
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

bool Graph::Edge::operator<(const Edge & other) {
    return distance < other.distance;
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
        std::cerr << "Graph::insertNode: tried to overwrite " << ID << std::endl; 
        return false;
    }

    if(ID > (int) nodes.size()) {
        std::cerr << "Graph::insertNode: unexpected ID " << ID << " expected " << nodes.size() << std::endl; 
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
        std::cerr << "Graph::insertEdge: tried to overwrite" << routeID << " Expected " << edgeList.size() << std::endl;
        return false;
    }

    if(routeID > (int) edgeList.size()) {
        std::cerr << "Graph::insertEdge: unexpected ID " << routeID << " Expected " << edgeList.size() << std::endl;
    }

    edgeList.push_back(Edge(routeID, IDa, IDb, distance, routeType));
    nodes[IDa].adjList.push_back(routeID);
    nodes[IDb].adjList.push_back(routeID);

    return true;
}

double Graph::getTravelSpeed(int edgeID) const {
    if(edgeID < 0 || edgeID >= (int) edgeList.size()) {
        throw std::out_of_range("Graph::getTravelTime: invalid edgeID " + std::to_string(edgeID));
    }
    
    const double DEFAULT_SPEED = 1.0;

    if(edgeList[edgeID].routeType == -1) {
        std::cerr << "Graph::getTravelTime: got routeType -1" << std::endl;
        return DEFAULT_SPEED;
    }

    const int routeType = edgeList[edgeID].routeType;

    if(routeType < -1 || routeType >= (int) speedLookup.size()) {
        throw std::runtime_error("Graph::getTravelTime:: route type doesn't exist");
    }

    return speedLookup[routeType];
}

double Graph::getTravelTime(int edgeID) const {
    if(edgeID < 0 || edgeID >= (int) edgeList.size()) {
        throw std::out_of_range("Graph::getTravelTime: invalid edgeID " + std::to_string(edgeID));
    }

    return degToLinear(edgeList[edgeID].distance)/getTravelSpeed(edgeID);
}

double Graph::degToLinear(double degDistance) const {
    return degDistance * LINEAR_CONV_FACTOR;
}

double Graph::coordDistance(std::pair<double, double> coord1, std::pair<double, double> coord2) const {
    return degToLinear(sqrt( pow(coord1.first - coord2.first, 2) + pow(coord1.second - coord2.second, 2) ));
}

Graph::Iterator::Iterator() : current_(Node()) {}

Graph::Iterator::Iterator(Graph::Node start, std::vector<Graph::Node> * nodes, std::vector<Graph::Edge> * edgeList) :
    current_(start),
    visited_(std::vector<bool>(nodes->size(), false)),
    nodes_(nodes),
    edgeList_(edgeList) {
        if(start.ID >= 0 && start.ID < (int) visited_.size()) {
            visited_[start.ID] = true;
        }
    }

Graph::Iterator Graph::begin() {
    return iterAt(0);
}

Graph::Iterator Graph::end() {
    return Iterator();
}

Graph::Iterator Graph::iterAt(int startIdx) {
    if(startIdx < 0 || startIdx >= (int) nodes.size()) return end();

    Iterator it(nodes[startIdx], &nodes, &edgeList);

    return it;
}

Graph::Iterator & Graph::Iterator::operator++() {
    // @TODO
    // If at end, don't increment
    if(current_.ID == -1) {
        return *this;
    }

    // Add neighbors to queue if not already visited
    for(int edgeID : current_.adjList) {
        Edge & neigh = edgeList_->at(edgeID);
        int neighID = (neigh.end1 == current_.ID) ? neigh.end2 : neigh.end1;

        if(!visited_[neighID]) {
            q_.push(nodes_->at(neighID));
            visited_[neighID] = true;
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