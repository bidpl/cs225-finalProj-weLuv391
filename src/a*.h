#pragma once
#include <vector>
#include <utility>

#include "graph.h"

/**
 * @brief Data structure used to store nodes, their parents, and their F-values.
 * Useful for retrieving the final path using backtracking.
 */
struct Cell {
    Graph::Node currnode;
    Cell* parent;
    double F;
};

/**
 * @brief Given a pair of any starting lat/long coords and the desired end coords, 
 * function uses A* algorithm on the given graph in order to find the shortest path 
 * between these coords.
 * 
 * @param graph Graph representation of coords as Nodes and routes as edges, see 
 * "graph.h" for more details.
 * @param start Pair of lat/long coords representing starting coordinates.
 * @param end Pair of lat/long coords representing desired ending coordinates.
 * @return Vector containing the edges(routes) to take in order.
 */
std::vector<Graph::Edge> shortestPath(const Graph& graph, std::pair<double, 
                                    double> start, std::pair<double, double> end);

/**
 * @brief Helper function for shortestPath. Given a pair of lat/long coords, function 
 * uses a KD-Tree to find the nearest Graph node to those coords.
 * 
 * @param kd 2-dimensional KD-Tree that contains the nodes from the graph used in shortestPath.
 * @param coords Pair of lat/long coords that we want to find the closest node for.
 * @return Nearest graph node to our coords.
 */
// Graph::Node nearestNode(KDTree<2> kd, std::pair<double, double> coords);

/**
 * @brief Helper function for shortestPath. Given a graph, the edge between the current 
 * node and a potential next node, the potential node, and the target destination, computes 
 * the F-score of the potential next node. F-score is defined as the sum of G and H, where 
 * G is the cost of of moving from the current node to the next which is known, and H is 
 * an estimate of the cost of moving from the potential next node to the destination, 
 * which will be approximated using the Euclidean distance in miles between the nodes. 
 *
 * @param edge Graph edge between current node and potential next
 * @param potential Graph node currently being processed that could potentially be a 
 * part of the path.
 * @param dest Graph node that we're trying to reach.
 * @return F-score for potential next node.
 */
double calculateF(const Graph& graph, Graph::Edge edge, Graph::Node potential, Graph::Node dest);

/**
 * @brief Helper function for shortestPath. Given a vector of Cells find the index of cell
 * of the lowest F value in the vector.
 *
 * @param cells Vector containing Cells.
 * @return Index of cell with lowest F.
 */
unsigned int getMinFCell(std::vector<Cell> cells);


/**
 * @brief Helper function for shortestPath. Given a vector of cells and a cell with certain node,
 * finds the index of cell with same node as currnode or -1 if the node doesn't exist in the vector.
 *
 * @param cells Vector containing cells to search through
 * @param cell Cell to find in cells
 * @return Index of cell to find or -1 if cell doesn't exist 
 */
int getCellIdx(std::vector<Graph::Node> cells, Graph::Node cell);
