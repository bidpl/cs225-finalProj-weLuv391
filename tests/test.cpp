#include <catch2/catch_test_macros.hpp>
#include "getCleanedData.h"
#include "graph.h"
#include "dsets.h"
#include "fileParser.h"


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

//Test on invalid edges: we should skip self loops and duplicate edges between the same two nodes
TEST_CASE("Data Sanitize - Invalid Data Test ", "[part=sanitizer]") {
  int airCount, flightsCount, edgeCount;
  Sanitizer files;
  files.getCleanedData("roadIntersectionsTest.dat", "airportsTest.dat", "roadEdgeTest.dat");

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
  REQUIRE( airCount == 29 );
  REQUIRE( flightsCount ==  406);

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

  REQUIRE( testGraph.getNodeCount() == 21077 );
  REQUIRE( testGraph.getEdgeCount() ==  22128 );
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

TEST_CASE("Get Travel Time", "[part=graph]") {
  Graph testGraph;

  for(int i = 0; i < 5; ++i) {
    testGraph.insertNode(i, std::pair<double, double>());
  }

  testGraph.insertEdge(0, 0, 1, 0, -1);
  testGraph.insertEdge(1, 3, 1, 0, 0);
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
}

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

TEST_CASE("DisjointSets throws std::out_of_range if query empty dset", "[part=dsets]") {
  DisjointSets emptySet;

  try {
    emptySet.find(0);
    REQUIRE(false);
  } catch(std::out_of_range) {
    REQUIRE(true);
  }
}

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

// Taken from lecture
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

  std::vector<Graph::Edge> mstEdgeList;
  Graph mst = testGraph.generateMST(mstEdgeList);

  REQUIRE(mstEdgeList.size() == 7);
  
  int edgeWeights[] = {2, 2, 4, 5, 8, 10, 13};
  for(unsigned i = 0; i < 7; ++i) {
    REQUIRE(edgeWeights[i] == mstEdgeList[i].distance);
  }
}
