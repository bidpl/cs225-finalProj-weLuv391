#include <catch2/catch_test_macros.hpp>
#include "graph.h"

TEST_CASE("practiceTest", "[weight=1][part=1]") {
  int i = 0;

  REQUIRE( i == 0 );
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
    testGraph.getAdj(-1, 1);
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
  for (int i = 5; i < 7; ++i) {
    if (i == 6) REQUIRE(!(testGraph.insertNode(6, std::pair<double, double>())));
    REQUIRE(testGraph.insertNode(i, std::pair<double, double>()));
  }
}

TEST_CASE("Multiple Edges Insert", "[part=1]") {
  Graph testGraph;

  for(int i = 0; i < 5; ++i) {
    testGraph.insertNode(i, std::pair<double, double>());
  }

  //cannot insert edge with invalid routeID
  REQUIRE(!(testGraph.insertEdge(-1, 0, 0, 0, 0)));

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
  REQUIRE(testGraph.getEdge(0, 4).end1 == 0 && testGraph.getEdge(0, 4).end2 == 0);

  //getting existing edge returns correct edge, regardless of order of arguments
  REQUIRE(testGraph.getEdge(1, 3).end1 == 3 && testGraph.getEdge(3, 1).end2 == 1);
  REQUIRE(testGraph.getEdge(4, 2).end1 == 4 && testGraph.getEdge(2, 4).end2 == 2);

  //ensures insertEdge returns false when trying to overwrite previously inserted data
  REQUIRE(!(testGraph.insertEdge(4, 4, 2, 0, 0)));
  REQUIRE(testGraph.insertEdge(6, 1, 4, 0, 0));
  REQUIRE(!(testGraph.insertEdge(6, 2, 4, 0, 0)));
}

TEST_CASE("Get Travel Time", "[part=1]") {
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

  std::vector<double> speeds{21, 12, 69, 420};

  //if edgeID is invalid, throws exception
  try {
    testGraph.getTravelTime(6, speeds);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }
  try {
    testGraph.getTravelTime(-1, speeds);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }

  //if route type doesn't exist, throws exception
  try {
    testGraph.getTravelTime(5, speeds);
    REQUIRE(false);
  } catch (...) { REQUIRE(true); }

  //if routeType is -1, return default speed
  REQUIRE(testGraph.getTravelTime(0, speeds) == 1.0);

  //checks if route type corresponds to correct speed
  REQUIRE(testGraph.getTravelTime(1, speeds) == 21);
  REQUIRE(testGraph.getTravelTime(2, speeds) == 12);
  REQUIRE(testGraph.getTravelTime(3, speeds) == 69);
  REQUIRE(testGraph.getTravelTime(4, speeds) == 420);
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
