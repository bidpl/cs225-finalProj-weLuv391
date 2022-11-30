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
    nodesInserted = 0;
    edgesInserted = 0;

    for(vector<string>::iterator it = copyList.begin(); it!=copyList.end(); it++) {
        nodesInserted += insertAllNodes(*it); //increases our counter by the amount of nodes inserted
        it++;
        edgesInserted = insertAllEdges(*it);  // add all of the edges
    }

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
        
            bool result = fullG_.insertNode(ID, /*nodeType,*/coords); // insert the node into the graph and add it to our vector
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

