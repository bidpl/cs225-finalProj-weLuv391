#include "graph.h"
#include "fileParser.h"
#include "cs225/kdtree.h"
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
fullGraph::fullGraph(const vector< string> listofFiles){
    
    vector<string> copyList = listofFiles;
    int total = 0; // a way to count current index of how many have been inserted
    int start, end;
    std::pair<int, int> nodeIndexStartEnd; //a temp pair to index our start/end

    for(vector<string>::iterator it = copyList.begin(); it!=copyList.end(); it++) {

        if(it== copyList.begin()) { // if we are at the first node type then our start is 0 and the end is the amount of ndes inserted -1;
            start = 0;
        } else{ // else we are at the previous end + 1 which is equivalent to the the amount of Nodes inserted so far
            start = total;
        }
        total += insertAllNodes(*it); //increases our counter by the amount of nodes inserted
        end = total-1; //our ending index and add it to our vector as a pair
        nodeIndexStartEnd.first = start;
        nodeIndexStartEnd.second = end;
        nodeIndex.push_back(nodeIndexStartEnd);//the end index of the current vertices
        it++;
        int edges = insertAllEdges(*it);  // add all of the edges
    }
    connectGraphs(); // we will know take our two connected graphs and make one connected graph out of it

}

int fullGraph::insertAllNodes(const std::string& nodeFile) {

    string tempWord; // a temp string that holds the data from our files
    int i = 0; // a counter variable that will keep track of how many nodes have been added
    std::fstream Nodes_ (nodeFile, std::fstream::out);// opens our 2nd file for reading
    if(!Nodes_.is_open()) { // if the file was unsuccesfully read then cancel the fn
        return -1;
    } else {
        while(Nodes_ >> tempWord){ // we will loop through the entire file
        //however we will pull the word 3 more times within the loop in order to create our Node as the data has already been placed in the necesarry format
        
            int ID = std::stoi(tempWord); // using stoi to convert string to int 
            Nodes_>>tempWord;

            int nodeType =  std::stoi(tempWord);
            Nodes_>>tempWord;

            Nodes_>>tempWord;
            double longitude,latitude;
            longitude = std::stod(tempWord); // use stod to convert string to double, we can get the data from the file and place it as a node 
            Nodes_>>tempWord;
            latitude = std::stod(tempWord);
            std::pair <double,double> coords (longitude, latitude); // then place that node int our coordinate pair
            coorToID[coords] = ID; // make the coords to an ID in our map
        
            
            bool result = fullG_.insertNode(ID, /*nodeType,*/coords); // insert the node into the graph and add it to our vector
            allPoints.push_back(coords);
            i++; 
        }
    }
    Nodes_.close(); // close the current file at reading
    return i-1; // this returns the last index of our Nodes, if it is negative one then no nodes were added
}


int fullGraph::insertAllEdges(const std::string& edgefile) {

    string tempWord; // a temp string that holds the data from our files
    int sourceNode; // these two string are temp vars that will hold the source and destination node for our edges
    int destinationNode;
    int i = 0; // a counter variable that will keep track of how many edges have been added
    std::fstream Edges_ (edgefile, std::fstream::out);// opens our 2nd file for reading

    if(!Edges_.is_open()) { // if the file was unsuccesfully read then cancel the fn
        return -1;
    } else {
         while(Edges_ >> tempWord){ 
            int ID = std::stoi(tempWord); // using stoi to convert string to int 

            Edges_>>tempWord; //get our start/end nodes and store them
            sourceNode = std::stoi(tempWord);
            Edges_>>tempWord;
            destinationNode = std::stoi(tempWord);

            Edges_>>tempWord;
            double distanceWeight = std::stod(tempWord); //using stod to convert string to double for our edge weight

            Edges_>>tempWord;
            int type = std::stoi(tempWord); // using stoi to convert string to int to get our routeType
            
            fullG_.insertEdge(ID, sourceNode, destinationNode, distanceWeight, type); //inserts our edge with the given data
            i++;
         }
    }

    Edges_.close(); // close the current file at reading
    return i-1; // this returns the last index of our edge, if it is negative one then no edges were added
}

void fullGraph::connectGraphs() {

    std::vector<Point<2>> coordinateVector; // a vector of points that match to our coordinates but in 
    for(int i = (nodeIndex[0].first); i<(nodeIndex[0].second); i++) { // loop through the amount of Nodes in our 1st data type
        coordinateVector.push_back(Point<2>(allPoints[i].first, allPoints[i].second)); // converts our pair vector to that of Points  to use in the KD tree
    }
    KDTree<2> coordsTree (coordinateVector); // creates a KDTree out of the coordinates of our first 

    for(std::vector<std::pair<int,int>>::iterator it = nodeIndex.begin()+2; it!= nodeIndex.end(); it++) { //loop through all the start/ends of the different transportation types
        int start = (*it).first;
        int end = (*it).second;
        for(int i = start; i<=end; i++) { //loop through the amount of transportation nodes
            Point<2> closestCoordinate2 = coordsTree.findNearestNeighbor(Point<2>(allPoints[i].first, allPoints[i].second)); //get the closest node from dataset2 to that of dataset 1
            std::pair <double, double> mapLookup (closestCoordinate2[0],closestCoordinate2[1]); //creates a pair of the coordinates to use in the map lookup
            int startNode = coorToID[mapLookup]; //get the ID of the corresponding coordinates
            int destinationNode = coorToID[allPoints[i]];
            //need to figure out what we call our airport to interescction edges
            fullG_.insertEdge(0, startNode, destinationNode, 0, 0); // create an edge between the two Nodes
        }
    }


}
