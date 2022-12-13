#include <catch2/catch_test_macros.hpp>
#include "getCleanedData.h"
#include "graph.h"
#include "dsets.h"
#include "fileParser.h"
#include "a_star.h"

#include <algorithm>


TEST_CASE("practiceTest", "[weight=1][part=1]") {
  int i = 0;

  REQUIRE( i == 0 );
}

TEST_CASE("KDTree Test", "[weight=infinity][part=sanitizer]") {
  int airCount, connectingCount;
  Sanitizer files;
  files.getCleanedData("roadIntersections.dat", "airports.dat", "roadEdgeData.dat");
  airCount = files.getNodeCount(1);
  connectingCount = files.getEdgeCount(2);

  REQUIRE( airCount == connectingCount );
}


TEST_CASE("Small Data Sanitize Test with Edge Data Correction", "[weight=1][part=sanitizer]") {
  int interCount, airCount, roadCount, planeCount, connectingCount;
  Sanitizer files;
  files.getCleanedData("smallRoadIntersections.dat", "smallAirports.dat", "smallRoadEdges.dat");

  interCount = files.getNodeCount(0);
  airCount = files.getNodeCount(1);
  roadCount = files.getEdgeCount(0);
  planeCount = files.getEdgeCount(1);
  connectingCount = files.getEdgeCount(2);

  REQUIRE( interCount == 3 );
  REQUIRE( airCount == 2 );
  REQUIRE( roadCount == 2 );
  REQUIRE( planeCount == 1 );
  REQUIRE( connectingCount == 2 );
}

TEST_CASE("Medium Data Sanitize Test with Edge and Node Data Correction", "[weight=1][part=sanitizer]") {
  int interCount, airCount, roadCount, planeCount, connectingCount;
  Sanitizer files;
  files.getCleanedData("mediumRoadIntersections.dat", "mediumAirports.dat", "mediumRoadEdges.dat");

  interCount = files.getNodeCount(0);
  airCount = files.getNodeCount(1);
  roadCount = files.getEdgeCount(0);
  planeCount = files.getEdgeCount(1);
  connectingCount = files.getEdgeCount(2);

  REQUIRE( interCount == 17 );
  REQUIRE( airCount == 4 );
  REQUIRE( roadCount == 13 );
  REQUIRE( planeCount == 6 );
  REQUIRE( connectingCount == 4 );
}

//Test on invalid nodes: omit nodes clearly outside of California boundary 
TEST_CASE("Data Sanitize - Node Checker", "[part=sanitizer]") {
  int nodeCount;
  Sanitizer files;
  files.getCleanedData("roadIntersectionsTest.dat", "airportsTest.dat", "roadEdgeTest.dat");
  nodeCount = files.getNodeCount(0);


  //with 5 total nodes and 2 invalid nodes in this test data file, we should get 3
  REQUIRE( nodeCount == 3 );
}

//Test on invalid edges: we should skip self loops and duplicate edges between the same two nodes
TEST_CASE("Data Sanitize - Invalid Data Test ", "[part=sanitizer]") {
  int airCount, flightsCount, edgeCount;
  Sanitizer files;
  files.getCleanedData("roadIntersectionsTest2.dat", "airportsTest.dat", "roadEdgeTest.dat");

  airCount = files.getNodeCount(1);
  flightsCount = files.getEdgeCount(1);
  edgeCount = files.getEdgeCount(0);

  //within these test data files, there are 3 valid airports, therefore 3 connecting flights (3 choose 2)
  REQUIRE( airCount == 3 );
  REQUIRE( flightsCount == 3 );

  //there are 5 edges, 2 are invalid (one connects to itself, the other is a duplicate edge between same 2 nodes)
  REQUIRE( edgeCount == 3);

}

//With a larger dataset, we test to make sure that correct number of valid airports are included
//Test to make sure that there is indeed one flight connecting each pair of airports
TEST_CASE("Data Sanitize - Flights Large", "[part=sanitizer]") {
  int airCount, flightsCount;
  Sanitizer files;
  files.getCleanedData("roadIntersections.dat", "airports.dat", "roadEdge.dat");

  airCount = files.getNodeCount(1);
  flightsCount = files.getEdgeCount(1);

  //within these test data files, there are 29 valid airports, therefore 406 connecting flights (29 choose 2)
  REQUIRE( airCount == 28 );
  REQUIRE( flightsCount ==  378);

}

TEST_CASE("small edges/test inserted", "[weight=1][part=input_reader]") {
  std::vector<std::string> fileList;
  Graph fullG_;
  fileList.push_back("../tests/nodestest.txt");
  fileList.push_back("../tests/edgestest.txt");
  fullGraph testGraph(fileList, fullG_);

  REQUIRE( testGraph.getNodeCount() == 3 );
  REQUIRE( testGraph.getEdgeCount() == 1 );
}

TEST_CASE("massive edges/test inserted", "[part=input_reader]") {
  std::vector<std::string> fileList;
  Graph fullG_;
  fileList.push_back("../tests/nodes.txt");
  fileList.push_back("../tests/edges.txt");
  fullGraph testGraph = fullGraph(fileList, fullG_);
  cout<< " Nodes Inserted: " << testGraph.getNodeCount() <<endl;
  cout<< " Edges Inserted: " << testGraph.getEdgeCount()<< endl;
  REQUIRE( testGraph.getNodeCount() == 21076 ); // 21048 intersecions (counted) + 28 airports (counted) 
  REQUIRE( testGraph.getEdgeCount() ==  22099 ); // 21693 roads + nCr(28,2) airport flights + 28 airport to road connections
}

TEST_CASE("Empty Graph", "[part=graph]") {
  Graph testGraph;

  //testing getAdj
  try {
    testGraph.getAdj(0);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }
  try {
    testGraph.getAdj(-1);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }

  //testing getEdge
  try {
    testGraph.getEdge(0, 0);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }
  try {
    testGraph.getEdge(-1, 1);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }
}

TEST_CASE("Multiple Nodes Insert", "[part=graph]") {
  Graph testGraph;

  //ensures each insert is valid
  for(int i = 0; i < 5; ++i) {
    REQUIRE(testGraph.insertNode(i, std::pair<double, double>()));
  }

  //ensures node adjacency lists are empty
  REQUIRE(testGraph.getAdj(0).size() == 0);

  //ensures exception throwing is correct
  try {
    testGraph.getAdj(5);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }
  try {
    testGraph.getAdj(-1);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }

  //ensures insertNode returns false when trying to overwrite previously inserted data
  REQUIRE(!(testGraph.insertNode(4, std::pair<double, double>())));
  REQUIRE(testGraph.insertNode(6, std::pair<double, double>()));

  REQUIRE(!(testGraph.insertNode(5, std::pair<double, double>())));
  REQUIRE(testGraph.insertNode(6, std::pair<double, double>()));
}

TEST_CASE("Multiple Edges Insert", "[part=graph]") {
  Graph testGraph;

  for(int i = 0; i < 5; ++i) {
    testGraph.insertNode(i, std::pair<double, double>());
  }

  //cannot insert edge with invalid routeID
  try {
    testGraph.insertEdge(-1, 0, 0, 0, 0);
    REQUIRE(false);
  } catch (...) {
    REQUIRE(true);
  }

  //ensures each insert is valid
  REQUIRE(testGraph.insertEdge(0, 0, 1, 0, 0));
  REQUIRE(testGraph.insertEdge(1, 3, 1, 0, 0));
  REQUIRE(testGraph.insertEdge(2, 3, 0, 0, 0));
  REQUIRE(testGraph.insertEdge(3, 1, 2, 0, 0));
  REQUIRE(testGraph.insertEdge(4, 4, 2, 0, 0));
  REQUIRE(testGraph.insertEdge(5, 3, 4, 0, 0));

  //ensures node adjacency lists are updated
  REQUIRE(testGraph.getAdj(3).size() == 3);
  REQUIRE(testGraph.getAdj(4).size() == 2);

  //ensures exception throwing is correct for getEdge
  try {
    testGraph.getEdge(5, 0);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }
  try {
    testGraph.getEdge(1, -1);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }

  //ensures exception throwing is correct for insertEdge when nodes don't exist
  try {
    testGraph.insertEdge(6, -1, 4, 0, 0);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }
  try {
    testGraph.insertEdge(6, 2, 5, 0, 0);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }

  //getting non-existent edge returns default edge
  REQUIRE(testGraph.getEdge(0, 4).end1 == -1);
  REQUIRE(testGraph.getEdge(0, 4).end2 == -1);

  //getting existing edge returns correct edge, regardless of order of arguments
  REQUIRE(testGraph.getEdge(1, 3).end1 == 3);
  REQUIRE(testGraph.getEdge(3, 1).end2 == 1);

  REQUIRE(testGraph.getEdge(4, 2).end1 == 4);
  REQUIRE(testGraph.getEdge(2, 4).end2 == 2);

  //ensures insertEdge returns false when trying to overwrite previously inserted data
  REQUIRE(!(testGraph.insertEdge(4, 4, 2, 0, 0)));
  REQUIRE(testGraph.insertEdge(6, 1, 4, 0, 0));
  REQUIRE(!(testGraph.insertEdge(6, 2, 4, 0, 0)));
}

// Check that get travel time returns the right time
// Checks that it throws error if invalid id
TEST_CASE("Get Travel Speed/Time", "[part=graph]") {
  Graph testGraph;

  for(int i = 0; i < 5; ++i) {
    testGraph.insertNode(i, std::pair<double, double>());
  }

  testGraph.insertEdge(0, 0, 1, 0, -1);
  testGraph.insertEdge(1, 3, 1, 21, 0);
  testGraph.insertEdge(2, 3, 0, 0, 1);
  testGraph.insertEdge(3, 1, 2, 0, 2);
  testGraph.insertEdge(4, 4, 2, 0, 3);
  testGraph.insertEdge(5, 3, 4, 0, 4);

  std::vector<double> speeds = {21, 12, 69, 420};
  testGraph.setSpeedLookup(speeds);

  //if edgeID is invalid, throws exception
  try {
    testGraph.getTravelSpeed(6);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }
  try {
    testGraph.getTravelSpeed(-1);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }

  //if route type doesn't exist, throws exception
  try {
    testGraph.getTravelSpeed(5);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }

  //if routeType is -1, return default speed
  REQUIRE(testGraph.getTravelSpeed(0) == 1.0);

  //checks if route type corresponds to correct speed
  REQUIRE(testGraph.getTravelSpeed(1) == 21);
  REQUIRE(testGraph.getTravelSpeed(2) == 12);
  REQUIRE(testGraph.getTravelSpeed(3) == 69);
  REQUIRE(testGraph.getTravelSpeed(4) == 420);

  // Check Travel Times
  REQUIRE(testGraph.getTravelTime(1) == testGraph.LINEAR_CONV_FACTOR);
}

// Makes a 5 node graph and iterates through it
// Checks that the nodes were all visited and in the right order
TEST_CASE("Basic BFS iteration", "[part=bfs]") {
  Graph testGraph;

  for(int i = 0; i < 5; ++i) {
    testGraph.insertNode(i, std::pair<double, double>());
  }

  testGraph.insertEdge(0, 0, 1, 0, 0);
  testGraph.insertEdge(1, 3, 1, 0, 0);
  testGraph.insertEdge(2, 3, 0, 0, 0);
  testGraph.insertEdge(3, 1, 2, 0, 0);
  testGraph.insertEdge(4, 4, 2, 0, 0);
  testGraph.insertEdge(5, 3, 4, 0, 0);

  std::vector<int> visitOrder;
  std::vector<int> ans = {0, 1, 3, 2, 4};

  for(Graph::Iterator it = testGraph.iterAt(0); it != testGraph.end(); ++it) {
    visitOrder.push_back((*it).ID);
  }

  REQUIRE(visitOrder == ans);
}

TEST_CASE("Empty BFS iteration", "[part=bfs]") {
  Graph testGraph;

  Graph::Iterator it = testGraph.begin();

  REQUIRE(!(it != testGraph.end()));

  // If you increment iterator of emptyGraph's begin, it should stay the same
  // use ! != for == since == is not implemented
  REQUIRE(!(it != ++it));
}

// Tests empty dset find
TEST_CASE("DisjointSets throws std::out_of_range if query empty dset", "[part=dsets]") {
  DisjointSets emptySet;

  try {
    emptySet.find(0);
    REQUIRE(false);
  } catch(std::out_of_range) {
    REQUIRE(true);
  }
}

// Constructs disjoint set of 5 elements and checks for correction construction
// unions items and chekcs after each batch of unions
TEST_CASE("Basic DisjointSets test", "[part=dsets]") {
  DisjointSets dset;

  // Add NUM_ELEM elems to disjoint set
  const int NUM_ELEM = 5;
  dset.addelements(NUM_ELEM);

  // Make sure each bucket is size 1 and has the correct label
  for(int i = 0; i < NUM_ELEM; ++i) {
    REQUIRE(dset.find(i) == i);
    REQUIRE(dset.size(i) == 1);
  }

  dset.setunion(0, 1);
  dset.setunion(2, 3);
  
  REQUIRE(dset.find(0) == dset.find(1));
  REQUIRE(dset.find(2) == dset.find(3));
  REQUIRE(dset.size(0) == 2);
  REQUIRE(dset.size(2) == 2);

  dset.setunion(1, 2);

  REQUIRE(dset.find(0) == dset.find(3));
  REQUIRE(dset.size(2) == 4);

  REQUIRE(dset.find(4) == 4);
  REQUIRE(dset.size(4) == 1);
}

// Checks tha dsets throws out of range when given out of bounds index
TEST_CASE("Test DisjointSets out of bounds", "[part=dsets]") {
  DisjointSets dset;

  // Add NUM_ELEM elems to disjoint set
  const int NUM_ELEM = 5;
  dset.addelements(NUM_ELEM);

  REQUIRE(dset.find(1) == 1);

  try {
    dset.find(NUM_ELEM);
    FAIL("dset.find(NUM_ELEM) did not throw exception");
  } catch(std::out_of_range) {
    REQUIRE("dset.find(NUM_ELEM) threw correct out_of_range");
  } catch(...) {
    FAIL("dset.find(NUM_ELEM) did not throw correct exception");
  }

  try {
    dset.find(-1);
    FAIL("dset.find(-1) did not throw exception");
  } catch(std::out_of_range) {
    REQUIRE("dset.find(-1) threw correct out_of_range");
  } catch(...) {
    FAIL("dset.find(-1) did not throw correct exception");
  }
}

// Kruskal example taken from CS225 lecture
TEST_CASE("Lecture Kruskal Test Case", "[part=MST]") {
  Graph testGraph;

  for(int i = 0; i < 8; ++i) {
    testGraph.insertNode(i, std::pair<double, double>());
  }

  testGraph.insertEdge(0, 0, 1, 5, 0);
  testGraph.insertEdge(1, 0, 3, 2, 0);
  testGraph.insertEdge(2, 0, 5, 16, 0);
  testGraph.insertEdge(3, 1, 2, 15, 0);
  testGraph.insertEdge(4, 1, 3, 5, 0);
  testGraph.insertEdge(5, 2, 5, 12, 0);
  testGraph.insertEdge(6, 2, 3, 16, 0);
  testGraph.insertEdge(7, 2, 4, 10, 0);
  testGraph.insertEdge(8, 2, 7, 11, 0);
  testGraph.insertEdge(9, 3, 5, 17, 0);
  testGraph.insertEdge(10, 3, 4, 13, 0);
  testGraph.insertEdge(11, 4, 5, 12, 0);
  testGraph.insertEdge(12, 4, 6, 8, 0);
  testGraph.insertEdge(13, 4, 7, 2, 0);
  testGraph.insertEdge(14, 5, 6, 4, 0);
  testGraph.insertEdge(15, 6, 7, 9, 0);

  Graph mst = testGraph.generateMST();

  REQUIRE(mst.getEdgeList().size() == 7);
  
  int edgeWeights[] = {2, 2, 4, 5, 8, 10, 13};
  for(unsigned i = 0; i < 7; ++i) {
    REQUIRE(edgeWeights[i] == mst.getEdgeList()[i].distance);
  }
}

TEST_CASE("Empty & 1 node Kruskal cases", "[part=MST]") {
  Graph testGraph;

  Graph emptyMst = testGraph.generateMST();

  REQUIRE(emptyMst.getEdgeList().size() == 0);
  REQUIRE(emptyMst.getNodes().size() == 0);

  testGraph.insertNode(0, std::pair<double,double>{1.0, 1.0});

  Graph singleMst = testGraph.generateMST();
  REQUIRE(singleMst.getEdgeList().size() == 0);
  REQUIRE(singleMst.getNodes().size() == 1);
}

/*
creates a very basic 5 node graph with edges of all equal distances and speeds
and checks to see if it takes the right path
*/
TEST_CASE("basic a* test", "[part=aa_star]") {
  Graph testGraph;
  testGraph.insertNode(0, std::pair<double, double>(100, 100));
  testGraph.insertNode(1, std::pair<double, double>(99, 100));
  testGraph.insertNode(2, std::pair<double, double>(101, 100));
  testGraph.insertNode(3, std::pair<double, double>(100, 99));
  testGraph.insertNode(4, std::pair<double, double>(100, 101));
  testGraph.insertEdge(0, 0, 1, 25, 0);
  testGraph.insertEdge(1, 0, 2, 25, 0);
  testGraph.insertEdge(2, 0, 3, 25, 0);
  testGraph.insertEdge(3, 0, 4, 25, 0);
  std::vector<double> speedLookup{25};
  testGraph.setSpeedLookup(speedLookup);
  /* shape of graph
          1
          |
      3 - 0 - 4
          |
          2
  all edges are 25 miles with routetype 0, with speed limit 25 mph
  */

  //correct answers
  std::vector<int> ans1{2, 3};
  std::vector<int> ans2{1, 0};

  //a* generated solutions
  std::vector<Graph::Edge> shortest_path1 = shortestPath(testGraph, std::pair<double, double>(100, 99), std::pair<double, double>(100, 101));
  std::vector<Graph::Edge> shortest_path2 = shortestPath(testGraph, std::pair<double, double>(101, 100), std::pair<double, double>(99, 100));
  std::vector<Graph::Edge> shortest_path3 = shortestPath(testGraph, std::pair<double, double>(102, 100), std::pair<double, double>(98, 100));
  for(unsigned i = 0; i < 2; ++i) {
    REQUIRE(shortest_path1[i].ID == ans1[i]);
    REQUIRE(shortest_path2[i].ID == ans2[i]);
    REQUIRE(shortest_path3[i].ID == ans2[i]); //this one tests the correctness of kd-tree get nearest node
  }
}

/*
creating a slightly more difficult graph to navigate through, with edges of different
distances and speed limits. There are multiple paths to get from node to node so this 
test case tests the intelligence of the a* algorithm.
*/
TEST_CASE("moderate graph a* test", "[part=a_star]") {
  Graph testGraph;
  testGraph.insertNode(0, std::pair<double, double>(652, 1009));
  testGraph.insertNode(1, std::pair<double, double>(654, 1012));
  testGraph.insertNode(2, std::pair<double, double>(656, 1012.5));
  testGraph.insertNode(3, std::pair<double, double>(652, 1014));
  testGraph.insertNode(4, std::pair<double, double>(656, 1015));
  testGraph.insertNode(5, std::pair<double, double>(650, 1012));
  testGraph.insertEdge(0, 0, 1, 249, 0);
  testGraph.insertEdge(1, 1, 2, 142, 1);
  testGraph.insertEdge(2, 1, 3, 195, 1);
  testGraph.insertEdge(3, 2, 4, 173, 0);
  testGraph.insertEdge(4, 3, 4, 154, 2);
  testGraph.insertEdge(5, 0, 5, 249, 3);
  testGraph.insertEdge(6, 5, 3, 195, 0);
  std::vector<double> speedLookup{60, 55, 65, 50};
  testGraph.setSpeedLookup(speedLookup);

  std::vector<int> ans1{0, 2}; //shortest path from node 0 to 3
  std::vector<int> ans2{0, 1, 3}; //shortest path from node 0 to 4
  std::vector<int> ans3{3, 4, 6}; //shortest path from node 2 to node 5

  std::vector<Graph::Edge> shortest_path1 = shortestPath(testGraph, std::pair<double, double>(652, 1009), std::pair<double, double>(652, 1014));
  std::vector<Graph::Edge> shortest_path2 = shortestPath(testGraph, std::pair<double, double>(652, 1009), std::pair<double, double>(656, 1015));
  std::vector<Graph::Edge> shortest_path3 = shortestPath(testGraph, std::pair<double, double>(656, 1012.5), std::pair<double, double>(650, 1012));
  for(unsigned i = 0; i < 2; ++i) {
    REQUIRE(shortest_path1[i].ID == ans1[i]);
  }
  for(unsigned i = 0; i < 3; ++i) {
    REQUIRE(shortest_path2[i].ID == ans2[i]);
    REQUIRE(shortest_path3[i].ID == ans3[i]); 
  }
}

TEST_CASE("Full test", "[part=full]") {
  // Clean up data into edges and nodes file
    Sanitizer files;
    files.getCleanedData("roadIntersections.dat", "airports.dat", "roadEdgeData.dat");
    
    // Build graph from edges and nodes file
    Graph network;
    fullGraph fileParser = fullGraph(std::vector<string>{"../src/nodes.txt", "../src/edges.txt"}, network);

    std::vector<double> speeds = {60, 500}; // 60mph average highway, 500 mph cruising speed of 737
    network.setSpeedLookup(speeds);

    std::cout << "Num nodes: " << network.getNodes().size() << std::endl;
    std::cout << "Num edges: " << network.getEdgeList().size() << std::endl << std::endl;

    std::vector<int> visitOrder;
    for(Graph::Iterator it = network.begin(); it != network.end(); ++it) {
        visitOrder.push_back((*it).ID);
    }

    // Checks every ID from 0 to visitOrder.size() - 1 is included in visit list
    std::sort(visitOrder.begin(), visitOrder.end());
    bool consecutiveIds = true;
    for(unsigned i = 0; i < visitOrder.size() - 1; ++i) {
        if(visitOrder[i] != visitOrder[i+1] - 1) {
            consecutiveIds = false;
            break;
        }
    }

    std::cout << "BFS iterator visits " << visitOrder.size() << " nodes" << std::endl;
    std::cout << "BFS iterator visits every node once: " << (consecutiveIds ? "true" : "false") << std::endl << std::endl;

    REQUIRE(visitOrder.size() == 21076);
    REQUIRE(consecutiveIds);

    Graph mst = network.generateMST();

    int counter = 0;
    for(Graph::Iterator it = network.begin(); it != network.end(); ++it) {
        ++counter;
    }

    std::cout << "MST contains " << mst.getEdgeList().size() << " edges" << std::endl;
    std::cout << "BFS of MST contains " << counter << " nodes" << std::endl << std::endl << std::endl;

    REQUIRE(mst.getEdgeList().size() == 21076 - 1);
    REQUIRE(counter == 21076);

    // Golden Gate S Vista Point to Santa Monica Pier
    std::pair<double, double> startpt{-122.474703, 37.807608};
    std::pair<double, double> endpt{-118.498386, 34.008582};
    std::vector<Graph::Edge> pathEdges = shortestPath(network, startpt, endpt);

    // some function to print edges out
    // function to print nodes in path in visited order
    std::cout << "A* traversal includes: " << pathEdges.size() << " steps:"<< std::endl;
    Graph::Node prevNode = network.getNodes()[network.getNearestNode(startpt)];
    std::cout << prevNode.coords.second << ',' << prevNode.coords.first << std::endl;
    for(unsigned i = 0; i < pathEdges.size(); ++i) {
        prevNode = network.getNodes()[(pathEdges[i].end1 == prevNode.ID) ? pathEdges[i].end2 : pathEdges[i].end1];

        std::cout << prevNode.coords.second << ',' << prevNode.coords.first << std::endl;
    }
}
