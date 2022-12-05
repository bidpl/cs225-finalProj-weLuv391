#include "a*.h"
#include <cmath>
#include <vector>
#include <algorithm>

std::vector<Graph::Edge> shortestPath(const Graph& graph, std::pair<double, 
                                    double> start, std::pair<double, double> end) {
    //build kd tree here-- for Shiv <3
    KDTree kd;

    //get starting and ending nodes using nearestNode
    Graph::Node start_node = nearestNode(kd, start);
    Graph::Node end_node = nearestNode(kd, end);

    //initialize open and closed lists
    Cell start_cell = {start_node, nullptr, 0};
    std::vector<Cell> open_list{start_cell};
    std::vector<Cell> closed_list;

    //A* algorithm
    while (!open_list.empty()) {

        //gets idx of min F Cell, get that Cell, and removes that Cell
        unsigned int smallestF_idx = getMinFIdx(open_list); 
        Cell smallestF = open_list[smallestF_idx];
        open_list.erase(open_list.begin() + smallestF_idx);

        //generating the successors of current node smallestF
        for (int i : smallestF.currnode->adjList) {

            //creates Node endpoint, a successor of smallestF
            Graph::Edge edge = graph.getEdgeList[i];
            Graph::Node endpoint;
            if (edge.end1 == smallestF.ID) endpoint = graph.getNodes[edge.end2];
            else endpoint = graph.getNodes[edge.end1];

            //checking if endpoint is the desired end
            if (endpoint.ID == end_node.ID) {
                std::vector<Graph::Edge> path{graph.getEdge(endpoint.ID, smallestF.currnode.ID)};
                Cell currcell = smallestF;
                while (currcell.parent != nullptr) {
                    path.insert(0, graph.getEdge(currcell.currnode.ID, (currcell.parent)->currnode.ID));
                    currcell = *(currcell.parent);
                }
                return path;
            }
            
            //Cell for smallestF successor (endpoint)
            Cell endpoint_cell = {endpoint, &smallestF, calculateF(graph, edge, endpoint, end_node)};

            //if cell with same currnode as endpoint exists on open list, check if it has lower F
            int open_list_idx = getCellIdx(open_list, endpoint_cell);
            if (open_list_idx != -1 && open_list[open_list_idx].F < endpoint_cell.F) continue;

            //if cell with same currnode as endpoint exists on closed list, check if it has lower F
            int closed_list_idx = getCellIdx(closed_list, endpoint_cell);
            if (closed_list_idx != -1 && closed_list[closed_list_idx].F < endpoint_cell.F) continue;

            //else push endpoint_cell onto open_list
            open_list.push_back(endpoint_cell);
        }

        //push smallestF cell onto closed list to show it has been processed
        closed_list.push_back(smallestF);
    }
    //this should never happen
    return std::vector<Graph::Edge>();
}

Graph::Node nearestNode(KDTree<2> kd, std::pair<double, double> coords) {
    //TODO-- for Shiv <3
    return Graph::Node();
}

double calculateF(const Graph& graph, Graph::Edge edge, Graph::Node potential, Graph::Node dest); {
    double g = edge.distance / graph.getTravelTime(edge.ID, speedLookup);
    /* 
        Euclidian distance in miles, converting latitude (1 = 69 miles) and longitude
        (1 = 54.6 miles) and then dividing by the average speed limit in America (55 mph)
        to get an approximate estimate of time between the potential node and destination
    */
    double h = coordDistance(potential.coords, dest.coords) / 55;
    return g + h;
}

unsigned int getMinFCell(std::vector<Cell> cells); {
    if (cells.empty()) throw std::runtime_error("Unexpected empty vector as argument");
    Cell min = cells[0];
    unsigned int idx = 0;
    for (unsigned i = 1; i < cells.size(); i++) {
        if (cells[i].F < min.F) {
            min = cells[i];
            idx = i;
        }
    }
    return idx;
}

int getCellIdx(std::vector<Graph::Node> cells, Graph::Node cell); {
    for (int i = 0; i < cells.size(); i++) {
        if (cells[i].currnode.ID == cell.currnode.ID) return i;
    }
    return -1;
}
