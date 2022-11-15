#include "graph.h"
#include "fileParser.h"
#include "kdtree.h"
#include <iostream>
#include <fstream>
#include <string>

fullGraph::fullGraph(const std::string& transport1, const std::string& transport2, const std::string& travelEdge1, const std::string& travelEdge2 ){
    
    transport2_end = insertAllNodes(transport2, true); // inserts the two types of transport nodes and get what indexes they will end/start at
    transport1_start = transport2_end +1;
    int dummy = insertAllNodes(transport1, false);

    dummy = insertAllEdges(travelEdge1); // we know insert our two data sets of edges
    dummy = insertAllEdges(travelEdge2);

    connectGraphs(); // we will know take our two connected graphs and make one connected graph out of it

}

int fullGraph::insertAllNodes(const std::string& nodeFile, bool needMap) {

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

            if(tempWord.compare("0")!=0) { // if the data pulled is of the 1st travel type ie: airport, this will check if we have a name or not
            //talk to bm of how to implement this since Node only has ID/coords/adjList
            }

            Nodes_>>tempWord;
            double longitude,latitude;
            longitude = std::stod(tempWord); // use stod to convert string to double, we can get the data from the file and place it as a node 
            Nodes_>>tempWord;
            latitude = std::stod(tempWord);
            std::pair <double,double> coords (longitude, latitude); // then place that node int our coordinate pair
            
            if(needMap) { // if we denoted a need for a map, then add the coordiante/ID to the map
                coorToID[coords] = ID;
            }
            
            bool result = fullG_.insertNode(ID, coords); // insert the node into the graph and add it to our vector
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

}



int fullGraph::getTransport1Start() {
    return transport1_start;
}

int fullGraph::getTransport1End() {
    return allPoints.size()-1;
}

int fullGraph::getTransport2Start() {
    return 0;
}

int fullGraph::getTransport2End() {
    return transport1_start;
}