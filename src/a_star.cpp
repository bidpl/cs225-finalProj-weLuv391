#include "a_star.h"
#include <cmath>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <queue>

std::vector<Graph::Edge> shortestPath(Graph& graph, std::pair<double, 
                                    double> start, std::pair<double, double> end) {
    //get starting and ending nodes using graph.getNearestNode
    auto nodes = graph.getNodes();
    auto edges = graph.getEdgeList();
    Graph::Node start_node = nodes[graph.getNearestNode(start)];
    Graph::Node end_node = nodes[graph.getNearestNode(end)];

    //initialize open and closed lists
    Cell* start_cell = new Cell{start_node, nullptr, 0};
    std::priority_queue<Cell*, std::vector<Cell*>, CompareF> open_list;
    open_list.push(start_cell);
    std::vector<bool> visited(nodes.size(), false); // Init visited markers

    //A* algorithm
    while (!open_list.empty()) {
        //gets idx of min F Cell, get that Cell, and removes that Cell
        Cell* smallestF = open_list.top();
        open_list.pop();
        visited[smallestF->currnode.ID] = true; 

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
                
                //going through open list to free up all cells on the heap
                while (!open_list.empty()) {
                    Cell* ptr = open_list.top();
                    open_list.pop();
                    delete ptr;
                    ptr = nullptr;
                }

                //function is finished, returning the answer
                return path;
            }
            
            // If cell already visited (on final path), skip this cell
            if(visited[endpoint.ID]) {
                continue;
            }

            //Cell for smallestF successor (endpoint)
            Cell* endpoint_cell = new Cell{endpoint, smallestF, calculateF(graph, edge, endpoint, end_node)};

            //if cell with same currnode as endpoint exists on open list, check if it has lower F
            if (onOpenListWithLowerF(open_list, endpoint_cell)) {
                delete endpoint_cell;
                continue;
            } 

            //else push endpoint_cell onto open_list
            open_list.push(endpoint_cell);
        }
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


bool onOpenListWithLowerF(std::priority_queue<Cell*, std::vector<Cell*>, CompareF> cells, Cell* cell) {
    while (!cells.empty()) {
        Cell* top = cells.top();
        cells.pop();
        if (top->currnode.ID == cell->currnode.ID) {
            if (top->F <= cell->F) return true;
            return false;
        }
    }
    return false;
}
