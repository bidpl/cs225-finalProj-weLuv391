#include "graph.h"
#include "fileParser.h"
#include "kdtree.h"
#include <iostream>
#include <fstream>
#include <string>

fullGraph::fullGraph(const std::string& transport1, const std::string& transport2, const std::string& travelEdge ){
    
    std::vector<std::pair<double,double>> allPoints; // A vector to hold our vertices of the 2nd transport, this will be used to make our KDtree
    string tempWord; // a temp string that holds the data from our files

   
   
    std::fstream Nodes_2 (transport2, std::fstream::out);// opens our 2nd file for reading

    if(!Nodes_2.is_open()) { // if the file was unsuccesfully read then cancel the fn
        return;
    } else {
        while(Nodes_2 >> tempWord){ // we will loop through the entire file
        //however we will pull the word 3 more times within the loop in order to create our Node as the data has already been placed in the necesarry format
        
            int ID = std::stoi(tempWord); // using stoi to convert string to int and stod to convert string to double, we can get the data from the file and place it as a node 
            Nodes_2>>tempWord;
            double longitude,latitude;
            longitude = std::stod(tempWord);
            Nodes_2>>tempWord;
            latitude = std::stod(tempWord);
            std::pair <double,double> coords (longitude, latitude); 
            
            bool result = fullGraph_.insertNode(ID, coords); // insert the node into the graph and 
            allPoints.push_back(coords);

        }
    }

    

    

}