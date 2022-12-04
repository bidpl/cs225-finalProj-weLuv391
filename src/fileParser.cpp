#include "graph.h"
#include "fileParser.h"
#include <fstream>
#include <string>
using namespace std;
fullGraph::fullGraph(const vector< string> listofFiles, Graph& fullG_){
    
    vector<string> copyList = listofFiles;
    nodesInserted = 0;
    edgesInserted = 0;

    for(vector<string>::iterator it = copyList.begin(); it!=copyList.end(); it++) {
        nodesInserted += insertAllNodes(*it, fullG_); //increases our counter by the amount of nodes inserted
        it++;
        edgesInserted = insertAllEdges(*it, fullG_);  // add all of the edges
    }

}

int fullGraph::insertAllNodes(const std::string& nodeFile, Graph& fullG_) {

    string tempWord; // a temp string that holds the data from our files
    int i = 0; // a counter variable that will keep track of how many nodes have been added
    std::ifstream Nodes_ (nodeFile);// opens our 2nd file for reading
    if(!Nodes_.is_open()) { // if the file was unsuccesfully read then cancel the fn
        return -1;
    } else {
        while(Nodes_ >> tempWord){ // we will loop through the entire file
        //however we will pull the word 3 more times within the loop in order to create our Node as the data has already been placed in the necesarry format
        
            int ID = std::stoi(tempWord); // using stoi to convert string to int 
            Nodes_>>tempWord;

            int nodeType =  std::stoi(tempWord); // get the node type
            Nodes_>>tempWord;

            std::string airportName = tempWord; // gets the airport name if there is one
            airportName.pop_back(); // trims the space and comma
            Nodes_>>tempWord;

            double longitude,latitude;
            longitude = std::stod(tempWord); // use stod to convert string to double, we can get the data from the file and place it as a node 
            Nodes_>>tempWord;
            latitude = std::stod(tempWord);
            std::pair <double,double> coords (longitude, latitude); // then place that node int our coordinate pair
        
            bool result = fullG_.insertNode(ID, coords, nodeType); // insert the node into the graph and add it to our vector
            i++; 
        }
    }
    Nodes_.close(); // close the current file at reading
    return i; // this returns the last index of our Nodes, if it is negative one then no nodes were added
}


int fullGraph::insertAllEdges(const std::string& edgefile, Graph& fullG_) {

    string tempWord; // a temp string that holds the data from our files
    int sourceNode; // these two string are temp vars that will hold the source and destination node for our edges
    int destinationNode;
    int i = 0; // a counter variable that will keep track of how many edges have been added
    std::ifstream Edges_ (edgefile);// opens our 2nd file for reading

    if(!Edges_.is_open()) { // if the file was unsuccesfully read then cancel the fn
        return -1;
    } else {
         while(Edges_ >> tempWord){ 
            int ID = std::stoi(tempWord); // using stoi to convert string to int 
            Edges_>>tempWord; //get our start/end nodes and store them
            
            int type = std::stoi(tempWord); // using stoi to convert string to int to get our routeType
            Edges_>>tempWord;

            sourceNode = std::stoi(tempWord);
            Edges_>>tempWord;

            destinationNode = std::stoi(tempWord);
            Edges_>>tempWord;

            double distanceWeight = std::stod(tempWord); //using stod to convert string to double for our edge weight
            
            fullG_.insertEdge(ID, sourceNode, destinationNode, distanceWeight, type); //inserts our edge with the given data
            i++;
         }
    }

    Edges_.close(); // close the current file at reading
    return i; // this returns the last index of our edge, if it is negative one then no edges were added
}

