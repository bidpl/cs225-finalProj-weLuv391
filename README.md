# cs225-finalProj-weLuv391
Final Project for CS225 Fa22 group weLuv391

__DISCLAIMER__:<br>
This code requires the usage of a Disjoin Set and Kd-tree data structure for complete functionality, however, due to the code being used in previous assignments, we do not want to release those files to the public. As a result, the user must implement their own Disjoint Set that is used for the Kruskals Algorithim, and a Kd-tree for the data cleanup and A-Star algorithim. These files should be implemented in the libary folder. Location: *finalProj-weLuv391/lib/cs225*

__First Time Setup__: <br>
In the terminal run these commands to set up: "mkdir build", "cd build", "cmake ..". In order to compile the code after any changes or during first time set up, run "make" in your build directory (Note: running "make -j<#cores>" will compile faster). Assuming that a valid implementation of a Kd-tree and Disjoint Sets is present, this will perfectly compile the code. 

__Running the code__:<br>
Location: *finalProj-weLuv391/entry/main.cpp*, *finalProj-weLuv391/entry/dataCleanup.cpp* <br>
In order to run main.cpp, the user must first input their desired files in dataCleanup.cpp (if this is not done an error message will be presented asking the user to run dataCleanup). This can be done by running "./dataCleanup" in the build folder which will ask the user to input their data files and create a nodes.txt and edges.txt with all the valid nodes/edges to be used for the graph. Note that the program is expecting three .dat files that are located in *finalProj-weLuv391/data*. The files must also be in this specific order, Node Type 1, Node Type 2, and Edge Type 1. Now simply run "./main" within the build folder. This will then run main.cpp which will create a graph using all the nodes and edges found the created txt files. It will then prompt the user to input two points and it will return the path connecti*ng the two nodes with the minimum weight.

__Running the test cases__:<br>
Location: *finalProj-weLuv391/tests/test.cpp* <br>
We have implemented a myriad of test cases that test the validity of every aspect of this project. By running "./test" in the build folder, it will run the test.cpp file and run through all of the test cases. If any test case fails, the code will highlight the failed test in the terminal with the line number.