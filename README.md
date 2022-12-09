# cs225-finalProj-weLuv391
Final Project for CS225 Fa22 group weLuv391

### __Locations of Notable Code__:<br>
#### *finalProj-weLuv391/lib/* : <br>
Folder location for our library that holds all the extraneous code and data structures that the project requires but were either not directly written by us or written by us in a previous assignment. This is where Kd-tree and Disjoint Sets code should go<br>
#### *finalProj-weLuv391/data/*:<br>
Folder location for all the input data required for test.cpp and main.cpp. The user can add their own .dat files here<br>
#### *finalProj-weLuv391/entry/*: <br>
Folder location for main.cpp and the txt files it creates <br>
#### *finalProj-weLuv391/src/*: <br> 
Folder location for all the code written by us for this project <br>
#### *finalProj-weLuv391/test/*:<br>
Folder location for all the test cases and all the txt files created by tests.cpp<br>
#### *finalProj-weLuv391/*:<br>
Our overall folder that not only holds all the previous folders, but also our ProjectProposal.md, TeamContract.md, results.md, and **presetationVideo.mp4**


### __DISCLAIMER__:<br>
This code requires the usage of a Disjoin Set and Kd-tree data structure for complete functionality, however, due to the code being used in previous assignments, we do not want to release those files to the public. As a result, the user must implement their own Disjoint Set that is used for the Kruskals Algorithim, and a Kd-tree for the data cleanup and A-Star algorithim. These files should be implemented in the libary folder. Location: *finalProj-weLuv391/lib/*

### __First Time Setup__: <br>
In the terminal run these commands to set up: "mkdir build", "cd build", "cmake ..". In order to compile the code after any changes or during first time set up, run "make" in your build directory (Note: running "make -j<#cores>" will compile faster). Assuming that a valid implementation of a Kd-tree and Disjoint Sets is present, this will perfectly compile the code. 

### __Data File Format__:<br>
Location: *finalProj-weLuv391/data* <br>
All of our input data is stored at *finalProj-weLuv391/data*; thus if the user wishes to add their own data, they must add it in the data folder in a .dat format where file1 has all Nodes of type 1, file2 has all Nodes of type 2, and file3 has all the Edges of type1. The user must then run "./main" from the build file which will ask for an input in the specific order of Node Type 1, Node Type 2, and Edge Type 1. It will then create a nodes.txt and edges.txt with all the valid nodes and edges and add them to entry.


### __Running the code__:<br>
Location: *finalProj-weLuv391/entry/main.cpp* <br>
In order to run main.cpp, the user must first input their desired files in /data (if this is not done the program will not be able to find the files). Next, run "./main" in the build folder which will ask the user to input their data files and create a nodes.txt and edges.txt placed in entry with all the valid nodes/edges to be used for the graph. It will then create a graph using all the nodes and edges found the created txt files. It will then prompt the user to input two points and the location of where the user wishes the output to be stored and it will return the path connecting the two nodes with the minimum weight at the given file output location.

### __Running the test cases__:<br>
Location: *finalProj-weLuv391/tests/test.cpp* <br>
We have implemented a myriad of test cases that test the validity of every aspect of this project. By running "./test" in the build folder, it will run the test.cpp file and run through all of the test cases. If any test case fails, the code will highlight the failed test in the terminal with the line number. Following the line number will show the test case with a descriptor showing what part of the code the test case was testing

### __General Description of Test Cases__:<br>
Location: *finalProj-weLuv391/tests/test.cpp* <br>
#### __sanitizer__: <br>
This part of the code is what takes in our data set and cleans it up, removing all the extraneous or invalid data. It also creates all the edges between the airports and airports to the closest intersection. The first test case just measures if the program created an edge from every airport to an intersection using the kd-tree. The next two test cases are simple
#### __input_reader__: <br>
Input_reader is a pretty simple algorithim that simply inserts all the nodes and edges from the file and that is what the two test cases do. The small test case just tests with a file of 3 nodes and a file with 1 edge and then checks if all were added. The 2nd test case is a massive one that uses all the nodes/edges created by our sanitize code and also just checks if all of them were properly added/detected by our code.
#### __graph__: <br>

#### __bfs__: <br>
#### __dsets__: <br>
#### __MST__: <br>
#### __A-Star__: <br>