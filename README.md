# cs225-finalProj-weLuv391
Final Project for CS225 Fa22 group weLuv391


### __DISCLAIMER__:<br>
>#### Location: *finalProj-weLuv391/lib/*

This code requires the usage of a Disjoin Set and Kd-tree data structure for complete functionality, however, due to the code being used in previous assignments, we do not want to release those files to the public. As a result, the user must implement their own Disjoint Set that is used for the Kruskals Algorithim, and a Kd-tree for the data cleanup and A-Star algorithim. These files should be implemented in the libary folder. 

### __First Time Setup__: <br>
In the terminal run these commands in the overall file to set up: 

    > mkdir build 
    > cd build
    > cmake ..

In order to compile the code after any changes or during first time set up in your build directory, run the following command:
    
    > make
>__Fun Fact__:  To compile multiple files at once for faster build times use: <br>
`make -j${nproc}` 

Assuming that a valid implementation of a Kd-tree and Disjoint Sets is present, this will perfectly compile the code. 

### __Locations of Notable Code__:<br>
>#### __finalProj-weLuv391/lib/__ : <br>
>>Folder location for our library that holds all the extraneous code and data structures that the project requires but were either not directly written by us or written by us in a previous assignment. This is where Kd-tree and Disjoint Sets code should go

>#### __finalProj-weLuv391/data/__:<br>
>>Folder location for all the input data required for test.cpp and main.cpp. The user can add their own .dat files here

>#### __finalProj-weLuv391/entry/__: <br>
>>Folder location for main.cpp and the txt files it creates 

>#### __finalProj-weLuv391/src/__: <br> 
>>Folder location for all the code written by us for this project 

>#### __finalProj-weLuv391/test/__:<br>
>>Folder location for all the test cases and all the txt files created by tests.cpp<br>

>#### __finalProj-weLuv391/__:<br>
>>Our overall folder that not only holds all the previous folders, but also our ProjectProposal.md, TeamContract.md, results.md, and **presetationVideo.mp4**

### __Data File Format__:<br>
>Location: *finalProj-weLuv391/data* <br>

All of our input data is stored at *finalProj-weLuv391/data*; thus if the user wishes to add their own data, they must add it in the data folder in a .dat format where file1 has all Nodes of type 1, file2 has all Nodes of type 2, and file3 has all the Edges of type1. The user must then run the following command from the build file:

    ./main

This will ask for an input in the specific order of Node Type 1, Node Type 2, and Edge Type 1. It will then create a nodes.txt and edges.txt with all the valid nodes and edges and add them to entry.


### __Running the code__:<br>
>Location: *finalProj-weLuv391/entry/main.cpp* <br>

In order to run main.cpp, __the user must first input desired data files in `/data`__ (if this is not done the program will not be able to find the files). Next, in the build folder run the command:

    ./main
This will ask the user to input their data files and create a nodes.txt and edges.txt placed in entry with all the valid nodes/edges to be used for the graph. It will then create a graph using all the nodes and edges found the created txt files. It will then prompt the user to input two points and the location of where the user wishes the output to be stored and it will return the path connecting the two nodes with the minimum weight at the given file output location.

### __Running the test cases__:<br>
>Location: *finalProj-weLuv391/tests/test.cpp* <br>

We have implemented a myriad of test cases that test the validity of every aspect of this project. By running "./test" in the build folder, it will run the test.cpp file and run through all of the test cases. If any test case fails, the code will highlight the failed test in the terminal with the line number. Following the line number will show the test case with a descriptor showing what part of the code the test case was testing

### __General Description of Test Cases__:<br>
>Location: *finalProj-weLuv391/tests/test.cpp* <br>

>#### Disclaimer:
>All of the data needed to run these tests are already loaded in ,so simply running ./test will automatically run them.

#### __sanitizer__: <br>
This part of the code is what takes in our data set and cleans it up, removing all the extraneous or invalid data. It also creates all the edges between the airports and airports to the closest intersection. The first test case just measures if the program created an edge from every airport to an intersection using the kd-tree. The next two test cases are simple insertion cases of varying sizes that ensures that all of the relevant data are properly added from our files. However, the small test case only has Edge Data correction to remove any edges between non existant nodes, and the Medium Test Case has that and also the Node Data Correction of removing invalid airport nodes. The fourth test case focuses more on elimanting on invalid edges such as self loops and duplicate edges and removing any airports that don't fit our required parameters. The last test case focuses on a larger dataset, where we test to make sure that correct number of valid airports are included. We also test to make sure that there is indeed one flight connecting each pair of airports. 
#### __input_reader__: <br>
Input_reader is a pretty simple algorithim that simply inserts all the nodes and edges from the file and that is what the two test cases do. The small test case just tests with a file of 3 nodes and a file with 1 edge and then checks if all were added. The 2nd test case is a massive one that uses all the nodes/edges created by our sanitize code and also just checks if all of them were properly added/detected by our code.

#### __graph__: <br>
We test our basic get/insert functions like getAdj, getEdge, insertEdge, insertNode on valid graphs and on invalid (missing nodes, empty, etc) graphs. We make sure to try to read invalid nodes/edges and write invalid nodes/edges to ensure the error handling (whether be auto correct or exception throwing).

#### __bfs__: <br>
For this test, we used one example graph (connected, 5 nodes, 6 edges) with some backedges. This ensures that the graph will not revisit nodes, visit nodes early, or miss nodes. We also test the iterator on an empty graph to make sure it starts on the end iterator and doesn't move when incremented.

#### __dsets__: <br>
This code should already be tested from mp_mazes. We added another basic test to ensure the methods work (add slots, union sets, find size of set, find key of set).

#### __MST__: <br>
We used the Kruskal example from Fa22 CS225 lecture. This shows that it works for an average graph. We also test it on an empty node and a single node graph. This ensures that it will generate an empty MST for those edge cases.

#### __A-Star__: <br>
We have two test cases for A-Star, the first one creates a very basic 5 node graph with edges of all equal distances and speeds and checks to see if it takes the right path. The second creates a slightly more difficult graph to navigate through, with edges of different distances and speed limits. There are multiple paths to get from node to node so this 
test case tests the intelligence of the a* algorithm.