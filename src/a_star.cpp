#include "a_star.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>

std::vector<Graph::Edge> shortestPath(Graph& graph, std::pair<double, 
                                    double> start, std::pair<double, double> end) {
    //get starting and ending nodes using graph.getNearestNode
    auto nodes = graph.getNodes();
    auto edges = graph.getEdgeList();
    Graph::Node start_node = nodes[graph.getNearestNode(start)];
    Graph::Node end_node = nodes[graph.getNearestNode(end)];

    //initialize open and closed lists
    Cell* start_cell = new Cell{start_node, nullptr, 0};
    std::vector<Cell*> open_list{start_cell};
    std::vector<Cell*> closed_list;

    //A* algorithm
    while (!open_list.empty()) {
        //gets idx of min F Cell, get that Cell, and removes that Cell
        unsigned int smallestF_idx = getMinFCell(open_list); 
        Cell* smallestF = open_list[smallestF_idx];
        open_list.erase(open_list.begin() + smallestF_idx);

        //generating the successors of current node smallestF
        for (int i : smallestF->currnode.adjList) {

            //creates Node endpoint, a successor of smallestF
            Graph::Edge edge = edges[i];
            Graph::Node endpoint;
            if (edge.end1 == smallestF->currnode.ID) endpoint = nodes[edge.end2];
            else endpoint = nodes[edge.end1];

            //checking if endpoint is the desired end
            if (endpoint.ID == end_node.ID) {

                //creating the result vector path using our backwards linked list through cell->parent
                std::vector<Graph::Edge> path{graph.getEdge(endpoint.ID, smallestF->currnode.ID)};
                Cell* currcell = smallestF;
                while (currcell->parent != nullptr) {
                    path.insert(path.begin(), graph.getEdge(currcell->currnode.ID, currcell->parent->currnode.ID));
                    currcell = currcell->parent;
                }
                
                //going through open and closed lists to free up all cells on the heap
                for (Cell* ptr : open_list) {
                    delete ptr;
                    ptr = nullptr;
                }
                for (Cell* ptr : closed_list) {
                    delete ptr;
                    ptr = nullptr;
                }

                return path;
            }
            
            //Cell for smallestF successor (endpoint)
            Cell* endpoint_cell = new Cell{endpoint, smallestF, calculateF(graph, edge, endpoint, end_node)};

            //if cell with same currnode as endpoint exists on open list, check if it has lower F
            int open_list_idx = getCellIdx(open_list, endpoint_cell);
            if (open_list_idx != -1 && open_list[open_list_idx]->F < endpoint_cell->F) {
                delete endpoint_cell;
                continue;
            }

            //if cell with same currnode as endpoint exists on closed list, check if it has lower F
            int closed_list_idx = getCellIdx(closed_list, endpoint_cell);
            if (closed_list_idx != -1 && closed_list[closed_list_idx]->F < endpoint_cell->F) {
                delete endpoint_cell;
                continue;
            }

            //else push endpoint_cell onto open_list
            open_list.push_back(endpoint_cell);
        }

        //push smallestF cell onto closed list to show it has been processed
        closed_list.push_back(smallestF);
    }
    //this should never happen
    return std::vector<Graph::Edge>();
}

double calculateF(const Graph& graph, Graph::Edge edge, Graph::Node potential, Graph::Node dest) {
    double g = graph.getTravelTime(edge.ID);
    /* 
        Euclidian distance in miles, converting latitude (1 = 69 miles) and longitude
        (1 = 54.6 miles) and then dividing by the average speed limit in America (55 mph)
        to get an approximate estimate of time between the potential node and destination
    */
    double h = graph.coordDistance(potential.coords, dest.coords) / 55;
    return g + h;
}

unsigned int getMinFCell(std::vector<Cell*> cells) {
    if (cells.empty()) throw std::runtime_error("Unexpected empty vector as argument");
    Cell* min = cells[0];
    unsigned int idx = 0;
    for (unsigned i = 1; i < cells.size(); i++) {
        if (cells[i]->F < min->F) {
            min = cells[i];
            idx = i;
        }
    }
    return idx;
}

int getCellIdx(std::vector<Cell*> cells, Cell* cell) {
    for (int i = 0; i < (int)cells.size(); i++) {
        if (cells[i]->currnode.ID == cell->currnode.ID) return i;
    }
    return -1;
}
