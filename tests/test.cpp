#include <catch2/catch_test_macros.hpp>
#include "../src/getCleanedData.h"
#include "graph.h"
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

TEST_CASE("Small Data Sanitize Test", "[weight=1][part=sanitizer]") {
  int i = 0;

  REQUIRE( i == 0 );
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

TEST_CASE("massive edges/test inserted", "[weight=1][part=input_reader]") {
  std::vector<std::string> fileList;
  Graph fullG_;
  fileList.push_back("../tests/nodes.txt");
  fileList.push_back("../tests/edges.txt");
  fullGraph testGraph = fullGraph(fileList, fullG_);

  REQUIRE( testGraph.getNodeCount() == 21077 );
  REQUIRE( testGraph.getEdgeCount() ==  22128 );
}

TEST_CASE("Empty Graph", "[part=1]") {
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

TEST_CASE("Multiple Nodes Insert", "[part=1]") {
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

TEST_CASE("Multiple Edges Insert", "[part=1]") {
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

TEST_CASE("Get Travel Speed", "[part=1]") {
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