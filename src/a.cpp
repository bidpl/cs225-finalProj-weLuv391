#include "a*.h"
#include <cmath>

std::vector<Graph::Edge> shortestPath(const Graph& graph, std::pair<double, 
                                    double> start, std::pair<double, double> end) {
    //TODO
    return std::vector<Graph::Edge>();
}

Graph::Node nearestNode(KDTree<2> kd, std::pair<double, double> coords) {
    //TODO
    return Graph::Node();
}

double calculateF(const Graph& graph, Graph::Edge edge, Graph::Node potential, Graph::Node dest); {
    /* confused abt 2 things here
     1. why does getTravelTime need to take speedLookup as a parameter if it's already the
        graph's private variable?
     2. does getTravelTime return the speed limit of the route or the time it takes to travel
        that route?
    */
    double g = edge.distance / graph.getTravelTime(edge.ID, speedLookup);
    /* 
        Euclidian distance in miles, converting latitude (1 = 69 miles) and longitude
        (1 = 54.6 miles) and then dividing by the average speed limit in America (55 mph)
        to get an approximate estimate of time between the potential node and destination
    */
    double h = sqrt(((potential.coords[0] - dest.coords[0]) * 69) * ((potential.coords[0] 
        - dest.coords[0]) * 69) + ((potential.coords[1] - dest.coords[1]) * 54.6) * 
        ((potential.coords[1] - dest.coords[1]) * 54.6)) / 55;
    return g + h;
}
