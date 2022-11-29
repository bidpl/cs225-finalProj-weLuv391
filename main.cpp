#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iterator>
#include <istream>
#include <cmath>
#include <sstream>

//TOTALS: 406 flights, 29 airports
//      21692 road segments, 21407 intersections

using namespace std;
int main()
{    
  
  string line;            // used to read/store comma-separated or blankspace-separated strings
  ifstream myfile;        // original data files we open
  fstream newfile;        // new txt file we output or append to
  vector<string> lineVec; // used to iterate through individual line of input data file
  vector<string> outVec;     // used to represent a single line in our output text file

  //STEP 1: ROAD INTERSECTION NODES

  //open data file from out dataset
  myfile.open("../data/roadIntersections.dat");

  //in this dataset, each element is separated by a ' '
  // the following nested while loops will convert each line of the .dat file
  // into a vector of elements (strings)
  // we will then push_back the necessary components onto our outVec as a string
  while(getline(myfile, line)) {
      stringstream ss(line);
      lineVec.clear();
      while (ss.good()) {
          string substr;
          getline(ss, substr, ' ');
          lineVec.push_back(substr);
      }

    //outVec is a vector of strings, where each string represents:
    // "nodeID, type=0, name=0, longitude, latitude"
    outVec.push_back(lineVec[0]+", 0, 0, "+ lineVec[1] +", "+ lineVec[2]);
  }
  myfile.close();

  //onto our output file nodes.txt, we want to output each string in outVec on a single line
  newfile.open("nodes.txt",ios_base::out);
  ostream_iterator<string> out_itr(newfile, "\n");
  copy(outVec.begin(), outVec.end(), out_itr);
  newfile.close();
  //upon reaching here, nodes.txt will contain all of the intersections

  //STEP 2: AIRPORT NODES

  //now let us open our next dataset and clear outVec contents
  myfile.open("../data/airports.dat"); 
  outVec.clear();

  //we want to eventually create flight edges between each airport node, so let us 
  //save the data we need into a vector<vector<string>> called airports
  vector<vector<string>> airports;

  //temporary vectors to be push_back onto the vector 'airports'
  vector<string> tempVec;
  
  //repeat the process as above, with a few nuances
  while(getline(myfile, line)) {
      stringstream ss(line);
      lineVec.clear();
      while (ss.good()) {
          string substr;
          getline(ss, substr, ',');
          lineVec.push_back(substr);
      }

      // this gives us only US pacific time zone airports
      if(lineVec[11]=="\"America/Los_Angeles\""){    

          //get the airportID, we only want specific airports in california
          int airportID = stoi(lineVec[0]);           
        
          //switch statement omits Nevada and military airports
          switch(airportID){                          
            case 3433: 
            case 3434:
            case 3453:
            case 3469:
            case 3484:
            case 3508:
            case 3558:
            case 3582:
            case 3644:
            case 3663:
            case 3683:
            case 3687:
            case 3689:
            case 3709:
            case 3710:
            case 3734:
            case 3748:
            case 3783:
            case 3799:
            case 3805:
            case 3816:
            case 3817:
            case 3867:
            case 3877:
            case 3948:
            case 3949:
            case 4071:
            case 4088:
            case 4136:
              
              //Note: lineVec[0] = airportID
              //      lineVec[4] = airportName
              //      lineVec[7] = longitude
              //      lineVec[6] = latitude
              outVec.push_back("-"+lineVec[0]+", 1, "+lineVec[4]+", "+lineVec[7]+", "+lineVec[6]); 

              //we want to save the airportID, longitude, latitude for use later
              tempVec = {"-"+lineVec[0], lineVec[7], lineVec[6]};
              airports.push_back(tempVec);
            
            default: break;                     
          }
        }
  }
  
  myfile.close();

  //this time, *append* our new outVec onto the nodes.txt file
  newfile.open("nodes.txt",ios_base::app);
  ostream_iterator<string> out2_itr(newfile, "\n");
  copy(outVec.begin(), outVec.end(), out2_itr);
  newfile.close();
  //at this point we should have airports and intersections in one file

  //STEP 3: ROAD SEGMENT EDGES
  //repeat using dataset roadEdgeData.dat
  myfile.open("../data/roadEdgeData.dat");
  outVec.clear();

  while(getline(myfile, line)) {
      stringstream ss(line);
      lineVec.clear();
      while (ss.good()) {
          string substr;
          getline(ss, substr, ' ');
          lineVec.push_back(substr);
      }
    outVec.push_back(lineVec[0]+", 0, "+ lineVec[1] +", "+ lineVec[2] + ", " +lineVec[3]);
  }
  myfile.close();
  
  newfile.open("edges.txt",ios_base::out);
  ostream_iterator<string> out3_itr(newfile, "\n");
  copy(outVec.begin(), outVec.end(), out3_itr);
  newfile.close();

  
  //STEP 4: AIR FLIGHT EDGES
  outVec.clear();

  //this time we are creating our own airportEdges, assuming there are flights
  //from each commercial airport to every other commericial airport
  int airEdgeCounter = 1;

  //now we use the previously saved airports vector from STEP 2
  for(unsigned long i=0; i<airports.size(); i++){
    for(unsigned long j=i+1; j<airports.size(); j++){
        
        string edgeID = "-" + to_string(airEdgeCounter);
        string startNodeID = airports[i][0];
        string endNodeID = airports[j][0];
        double l2distance = sqrt(pow((stod(airports[i][1])-stod(airports[j][1])),2)+pow((stod(airports[i][2])-stod(airports[j][2])),2));
        
        airEdgeCounter++;
        outVec.push_back(edgeID+", 1, "+startNodeID+", "+endNodeID+", "+to_string(l2distance));
      }
    }

  //append to edges.txt
  newfile.open("edges.txt",ios_base::app);
  ostream_iterator<string> out4_itr(newfile, "\n");
  copy(outVec.begin(), outVec.end(), out4_itr);
  newfile.close();
  return 0;

  //by the end we should have two files nodes.txt and edges.txt, with airportNodes and
  //flightNodes appended at the end of each file
}