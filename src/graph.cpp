#include "graph.h"
#include <stdexcept>

bool Graph::Node::operator!=(const Node & other) {
    return ID = other.ID;
}

Graph::Node Graph::Node::operator=(const Node & other) {
    ID = other.ID;
    coords = other.coords;
    adjList = other.adjList;
}

std::vector<Graph::Edge*> & Graph::getAdj(int ID) {
    for (Node & n : nodes) {
        if (n.ID == ID) return n.adjList;
    }
    throw std::runtime_error("node with ID doesn't exist");
    return nodes[0].adjList; // fudge fix, need better way of doing this, could seg fault 
}

Graph::Node::Node() : 
    ID(-1) {}

Graph::Node::Node(int ID_, std::pair<double, double> coords_) :
    ID(ID_),
    coords(coords_) {}

Graph::Node::Node(const Node & other) :
    ID(other.ID),
    coords(other.coords),
    adjList(other.adjList) {}

Graph::Edge* Graph::getEdge(int IDa, int IDb) {
    Node* a;
    Node* b;
    std::vector<Edge*> adjListA;
    std::vector<Edge*> adjListB;
    for (Node & n : nodes) {
        if (n.ID == IDa) {
            a = &n;
            adjListA = n.adjList;
        } else if (n.ID == IDb) {
            b = &n;
            adjListB = n.adjList;
        }
    }
    if (a == NULL || b == NULL) throw std::runtime_error("either nodeA or nodeB doesn't exist");
    bool found = false;
    Edge* result;
    bool foundA = false;
    bool foundB = false;
    for (Edge* edge : edgeList) {
         if (edge->end1 == b && edge->end2 == a) {
            found = true;
            result = edge;
        }
    }
    for (Edge* edge : adjListA) {
        if (edge->end1 == a && edge->end2 == b) {
            foundA = true;
            // resultA = edge;  // What's this for?
        }
    }
    for (Edge* edge : adjListB) {
        if (edge->end1 == a && edge->end2 == b) {
            foundB = true;
            // resultB = edge;  // What's this for?
        }
    }
    if (found && foundA && foundB) return result;
    if (found || foundA || foundB) throw std::runtime_error(
        "edge was found but not present in all lists (edgeList, adjListA, adjListB");
    return NULL;
}

bool Graph::insertNode(int ID, std::pair<double, double> coords) {
    for (Node & n : nodes) {
        if (n.ID == ID) {
            n.coords = coords;
            return false;
        }
    }
    Node newnode;
    newnode.ID = ID;
    newnode.coords = coords;
    nodes.push_back(newnode);
    return true;
}

bool Graph::insertEdge(int routeID, int IDa, int IDb, double distance, int routeType) {
    Node* a = NULL;
    Node* b = NULL;
    for (Node & n : nodes) {
        if (n.ID == IDa) a = &n;
        else if (n.ID == IDb) b = &n;
    }
    if (a == NULL || b == NULL) throw std::runtime_error("either nodeA or nodeB doesn't exist");
    return insertEdge(routeID, a, b, distance, routeType);
}

bool Graph::insertEdge(int routeID, Node * node1, Node * node2, double distance, int routeType) {
    Edge newedge;
    newedge.ID = routeID;
    newedge.end1 = node1;
    newedge.end2 = node2;
    newedge.distance = distance;
    newedge.routeType = routeType;

    edgeList.push_back(&newedge);
    node1->adjList.push_back(&newedge);
    node2->adjList.push_back(&newedge);

    // @todo add checking to see if this is overwrite (will have to edit above code)
    return true; // Change this
}

//do we need this as a parameter as it's already Graph's private variable?
double Graph::getTravelTime(Edge * edge, std::vector<double> speedLookup) {
    int type = edge->routeType;
    if (type < 0 || type >= speedLookup.size()) throw std::runtime_error("route type doesn't exist");
    return speedLookup[type];
}

Graph::Iterator::Iterator() {
    current_ = Node(); // Might need to change this default
}

Graph::Iterator::Iterator(Node start, unsigned numNodes) :
    current_(start),
    visited_(std::vector<bool>(numNodes, false)) {}

Graph::Iterator & Graph::Iterator::operator++() {
    // @TODO
    // If at end, don't increment
    if(current_.ID == -1) {
        return *this;
    }

    // Continue this
    for(Edge * neigh : current_.adjList) {
        Node neighNode = (neigh->end1->ID == current_.ID) ? neigh->end2 : neigh->end1;

        if(!visited_[neighNode.ID]) {
            q_.push(neighNode);
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

