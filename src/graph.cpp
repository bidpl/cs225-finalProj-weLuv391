#include "graph.h"
#include <stdexcept>
using namespace std;
vector<Graph::Edge *>& Graph::getAdj(int ID) {
    for (Node n : nodes) {
        if (n.ID == ID) return n.adjList;
    }
    throw runtime_error("node with ID doesn't exist");
    return vector<Edge*>();
}

Graph::Edge* Graph::getEdge(int IDa, int IDb) {
    Node* a;
    Node* b;
    std::vector<Edge*> adjListA;
    std::vector<Edge*> adjListB;
    for (const Node n : nodes) {
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
            resultA = edge;
        }
    }
    for (Edge* edge : adjListB) {
        if (edge->end1 == a && edge->end2 == b) {
            foundB = true;
            resultB = edge;
        }
    }
    if (found && foundA && foundB) return result;
    if (found || foundA || foundB) throw std::runtime_error(
        "edge was found but not present in all lists (edgeList, adjListA, adjListB");
    return NULL;
}

bool Graph::insertNode(int ID, std::pair<double, double> coords) {
    for (Node n : nodes) {
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
    for (const Node n : nodes) {
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
}

//do we need this as a parameter as it's already Graph's private variable?
double Graph::getTravelTime(Edge * edge, std::vector<double> speedLookup) {
    int type = edge->routeType;
    if (type < 0 || type >= speedLookup) throw std::runtime_error("route type doesn't exist");
    return speedLookup[type];
}